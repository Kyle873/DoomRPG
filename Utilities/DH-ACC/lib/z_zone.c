// Emacs style mode select   -*- C -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2000 James Haley
// Copyright(C) 2012 David Hill
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//--------------------------------------------------------------------------
//
// DESCRIPTION:
//      Zone Memory Allocation. Neat.
//
// Neat enough to be rewritten by Lee Killough...
//
// Must not have been real neat :)
//
// Made faster and more general, and added wrappers for all of Doom's
// memory allocation functions, including malloc() and similar functions.
// Added line and file numbers, in case of error. Added performance
// statistics and tunables.
//
// Ported to DS and then DH-acc's C by David Hill.
//
//-----------------------------------------------------------------------------

#include <z_zone.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// __LIBDS_ZONESIZE
//
// Specifies the size of the dynamic memory heap in megabytes.
//
#ifndef __LIBDS_ZONESIZE
#define __LIBDS_ZONESIZE 16
#endif

#define HEAPSIZE (__LIBDS_ZONESIZE * 1024 * 1024)

#define zonef __printf __log

//
// VoidToBlock
//
// davidph 12/09/12: Converts a void * (as returned from Z_Malloc or passed to
// Z_Free) to a memblock_t __near * for internal usage.
//
#define VoidToBlock(p) ((memblock_t __near *)((char __near *)(p) - HEADER_SIZE))

//
// BlockToVoid
//
// Reverses the above. Yields a memblock_t __near * for efficiency reasons.
//
#define BlockToVoid(p) ((memblock_t __near *)((char __near *)p + HEADER_SIZE))

//===================================================================
// Features
//

// Uncomment this to see real-time memory allocation statistics.
//#define INSTRUMENTED

// Uncomment this to use memory scrambling on allocations and frees.
// haleyjd 01/27/09: made independent of INSTRUMENTED
//#define ZONESCRAMBLE

// Uncomment this to exhaustively run memory checks
// while the game is running (this is EXTREMELY slow).
// haleyjd 01/27/09: made independent of INSTRUMENTED
//#define CHECKHEAP

// Uncomment this to automatically invoke Z_PrintStats.
// davidph 08/18/12: made independent of INSTRUMENTED
//#define ZONESTATS

// Uncomment this to perform id checks on zone blocks,
// to detect corrupted and illegally freed blocks
//#define ZONEIDCHECK

// Uncomment this to dump the heap to file on exit.
//#define DUMPONEXIT

// Uncomment this to log all memory operations to a file
//#define ZONEFILE

// Uncomment this to log all memory operations to the terminal.
//#define ZONEFILE_FAKE

// Uncomment this to enable smarter Z_Realloc.
#define SMART_REALLOC

//===================================================================
// Tunables
//

// Alignment of zone memory (benefit may be negated by HEADER_SIZE, CHUNK_SIZE)
#define CACHE_ALIGN 1

// size of block header
#define HEADER_SIZE ((sizeof(memblock_t) + CACHE_ALIGN - 1) & ~(CACHE_ALIGN - 1))

// Minimum chunk size at which blocks are allocated
#define CHUNK_SIZE 32

// Minimum size a block must be to become part of a split
#define MIN_BLOCK_SPLIT (1024)

// signature for block header
#define ZONEID  0x931d4a11

//===================================================================
// Debug Macros
//
// haleyjd 11/18/09
// These help clean up the #ifdef hell.
//

// Instrumentation macros
#ifdef INSTRUMENTED
#  define INSTRUMENT(a) a
#  define INSTRUMENT_IF(opt, a, b) if((opt)) (a) else (b)
#else
#  define INSTRUMENT(a)
#  define INSTRUMENT_IF(opt, a, b)
#endif

// Automatic stat printing.
#ifdef ZONESTATS
#  define Z_PrintStats() (Z_PrintStats)()
#else
#  define Z_PrintStats()
#endif

// ID Check macros
#ifdef ZONEIDCHECK
#  define IDCHECK(a) a
#  define IDBOOL(a) (a)
#  define Z_IDCheckNB(a,b,c,d) (Z_IDCheckNB)(a,b,c,d)
#  define Z_IDCheck(a,b,c,d,e) (Z_IDCheck)(a,b,c,d,e)
#else
#  define IDCHECK(a)
#  define IDBOOL(a) false
#  define Z_IDCheckNB(a,b,c,d)
#  define Z_IDCheck(a,b,c,d,e)
#endif

// Heap checking macro
#ifdef CHECKHEAP
#  define DEBUG_CHECKHEAP() Z_CheckHeap()
#else
#  define DEBUG_CHECKHEAP()
#endif

// Zone scrambling macro
#ifdef ZONESCRAMBLE
#  define SCRAMBLER(b, s) memset((b), 1 | (gametic & 0xff), (s))
#else
#  define SCRAMBLER(b, s)
#endif

// Zone logging macros.
#ifdef ZONEFILE
#  ifdef ZONEFILE_FAKE
#     define Z_OpenLogFile()
#     define Z_CloseLogFile()
#     define Z_LogPrintf(...)  zonef          (__VA_ARGS__)
#     define Z_LogPuts(a)      zonef          ("%s\n", a)
#  else
#     define Z_OpenLogFile()  (Z_OpenLogFile) ()
#     define Z_CloseLogFile() (Z_CloseLogFile)()
#     define Z_LogPrintf(...) (Z_LogPrintf)   (__VA_ARGS__)
#     define Z_LogPuts(a)     (Z_LogPuts)     (a)
#  endif
#else
#  define Z_OpenLogFile()
#  define Z_CloseLogFile()
#  define Z_LogPrintf(...)
#  define Z_LogPuts(a)
#endif


//----------------------------------------------------------------------------|
// Types                                                                      |
//

//
// memblock_t
//
typedef struct memblock_s
{
#ifdef ZONEIDCHECK
   unsigned id;
#endif

   struct memblock_s __near *next, *prev;
   size_t size;
   void **user;
   unsigned char tag;

#ifdef INSTRUMENTED
   unsigned short extra;
   __string file;
   int line;
#endif
} memblock_t;

//
// alloca_header_t
//
typedef struct alloca_header_s
{
   struct alloca_header_s __near *next;
} alloca_header_t;


//----------------------------------------------------------------------------|
// Static Variables                                                           |
//

static char heap[HEAPSIZE];

static memblock_t __near *rover;         // roving pointer to memory blocks
static memblock_t __near *zone;          // pointer to first block
static memblock_t __near *zonebase;      // pointer to entire zone memory
static size_t             zonebase_size; // zone memory allocated size

static alloca_header_t __near *alloca_root;

#ifdef INSTRUMENTED
// statistics for evaluating performance
static size_t free_memory;
static size_t active_memory;
static size_t purgable_memory;
static size_t inactive_memory;
#endif

#if defined(ZONEFILE) && !defined(ZONEFILE_FAKE)
// haleyjd 09/16/06: zone logging file
static FILE *zonelog;
#endif


//----------------------------------------------------------------------------|
// Static Functions                                                           |
//

//
// Z_IDCheckNB
//
// Performs a fatal error condition check contingent on the definition
// of ZONEIDCHECK, in any context where a memblock pointer is not available.
//
static void (Z_IDCheckNB)(_Bool err, __string errmsg, __string file, int line)
{
   if(!err) return;

   zonef("%s\nSource: %s:%d\n", errmsg, file, line);
   abort();
}

//
// Z_IDCheck
//
// Performs a fatal error condition check contingent on the definition
// of ZONEIDCHECK, and accepts a memblock pointer for provision of additional
// malloc source information available when INSTRUMENTED is also defined.
//
static void (Z_IDCheck)(_Bool err, __string errmsg, memblock_t *block,
                        __string file, int line)
{
   if(!err) return

   zonef("%s\nSource: %s:%d\nSource of malloc: %s:%d\n",
         errmsg, file, line,
#if defined(INSTRUMENTED)
         block->file, block->line
#else
         "(not available)", 0
#endif
        );
   abort();
}

static void (Z_OpenLogFile)()
{
#if defined(ZONEFILE) && !defined(ZONEFILE_FAKE)
   zonelog = fopen("zonelog.txt", "w");
#endif
}

static void (Z_CloseLogFile)()
{
#if defined(ZONEFILE) && !defined(ZONEFILE_FAKE)
   if(zonelog)
   {
      fputs("Closing zone log", zonelog);
      fclose(zonelog);
      zonelog = NULL;
   }
#endif
}

static void (Z_LogPrintf)(__string msg, ...)
{
#if defined(ZONEFILE) && !defined(ZONEFILE_FAKE)
   if(zonelog)
   {
      va_list ap;
      va_start(ap, msg);
      vfprintf(zonelog, msg, ap);
      va_end(ap);

      // flush after every message
      fflush(zonelog);
   }
#endif
}

static void (Z_LogPuts)(__string msg)
{
#if defined(ZONEFILE) && !defined(ZONEFILE_FAKE)
   if(zonelog)
   {
      fputs(msg, zonelog);
   }
#endif
}



//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

//
// Z_Close
//
// davidph 06/17/12: User must find the right time to call this.
//
void (Z_Close)(__string file, int line)
{
   Z_CloseLogFile();

#ifdef DUMPONEXIT
   Z_PrintZoneHeap();
#endif

   // Probably not a good idea.
 //zone = rover = zonebase = NULL;
}

//
// Z_Init
//
void (Z_Init)(__string file, int line)
{
   register size_t size;

   // Allocate the memory
   // davidph 06/17/12: For DS, memory is a static allocation.
   zonebase = (memblock_t __near *)heap;
   zonebase_size = HEAPSIZE;

   // Align on cache boundary
   // davidph 08/03/12 FIXME: This causes invalid codegen.
 //zone = (memblock_t *)(((uintptr_t)zonebase + (CACHE_ALIGN - 1)) & ~(CACHE_ALIGN - 1));
   zone = zonebase;

   size = zonebase_size - ((char __near *)zone - (char __near *)zonebase);

   rover = zone;                    // Rover points to base of zone mem
   zone->next = zone->prev = zone;  // Single node
   zone->size = size - HEADER_SIZE; // All memory in one block
   zone->tag = PU_FREE;             // A free block

#ifdef ZONEIDCHECK
   zone->id  = 0;
#endif

   INSTRUMENT(free_memory = zone->size);
   INSTRUMENT(inactive_memory = zonebase_size - zone->size);
   INSTRUMENT(active_memory = purgable_memory = 0);

   Z_OpenLogFile();
   Z_LogPrintf("Initialized zone heap with size of %u bytes (zonebase = %p)\n",
               zonebase_size, (void *)zonebase);
}

//
// Z_Malloc
//
// You can pass a NULL user if the tag is < PU_PURGELEVEL.
//
void *(Z_Malloc)(size_t size, int tag, void **user, __string file, int line)
{
   register memblock_t __near *block, *start;

   INSTRUMENT(register size_t size_orig = size);

   // davidph 12/10/12: If zone not initialized, do so now.
   if(!zone) (Z_Init)(file, line);

   DEBUG_CHECKHEAP();

   Z_IDCheckNB(IDBOOL(tag >= PU_PURGELEVEL && !user),
               "Z_Malloc: an owner is required for purgable blocks",
               file, line);

   if(!size)
      return user ? *user = NULL : NULL;          // malloc(0) returns NULL

   size = (size+CHUNK_SIZE-1) & ~(CHUNK_SIZE-1);  // round to chunk size

   block = rover;

   if(block->prev->tag == PU_FREE)
      block = block->prev;

   start = block;

   // haleyjd 01/01/01 (happy new year!):
   // the first if() inside the loop below contains cph's memory
   // purging efficiency fix

   do
   {
      // Free purgable blocks; replacement is roughly FIFO
      if(block->tag >= PU_PURGELEVEL)
      {
         start = block->prev;
         Z_Free((char __near *)block + HEADER_SIZE);

         // cph - If start->next == block, we did not merge with the previous
         //       If !=, we did, so we continue from start.
         //  Important: we've reset start!
         if(start->next == block)
            start = start->next;
         else
            block = start;
      }

      if(block->tag == PU_FREE && block->size >= size)   // First-fit
      {
         size_t extra = block->size - size;
         if(extra >= MIN_BLOCK_SPLIT + HEADER_SIZE)
         {
            memblock_t __near *newb = (memblock_t __near *)((char __near *)block + HEADER_SIZE + size);

            (newb->next = block->next)->prev = newb;
            (newb->prev = block)->next = newb;          // Split up block
            block->size = size;
            newb->size = extra - HEADER_SIZE;
            newb->tag = PU_FREE;

            INSTRUMENT(inactive_memory += HEADER_SIZE);
            INSTRUMENT(free_memory -= HEADER_SIZE);
         }

         rover = block->next;           // set roving pointer for next search

#ifdef INSTRUMENTED
         inactive_memory += block->extra = block->size - size_orig;
         if(tag >= PU_PURGELEVEL)
            purgable_memory += size_orig;
         else
            active_memory += size_orig;
         free_memory -= block->size;
#endif

         INSTRUMENT(block->file = file);
         INSTRUMENT(block->line = line);

         IDCHECK(block->id = ZONEID);// signature required in block header
         block->tag = tag;           // tag
         block->user = user;         // user
         block = BlockToVoid(block);
         if(user)                    // if there is a user
            *user = block;           // set user to point to new block

         Z_PrintStats();             // print memory allocation stats

         // scramble memory -- weed out any bugs
         SCRAMBLER(block, size);

         Z_LogPrintf("* %p = Z_Malloc(size=%u, tag=%d, user=%p, source=%s:%d)\n",
                     block, size, tag, user, file, line);

         return block;
      }
   }
   while((block = block->next) != start);   // detect cycles as failure

   zonef("Z_Malloc: Failure trying to allocate %u bytes\nSource: %s:%d\n", size, file, line);
   abort();
}

//
// Z_Free
//
void (Z_Free)(void *p, __string file, int line)
{
   register memblock_t __near *other, *block;

   if(!p) return;

   DEBUG_CHECKHEAP();

   block = VoidToBlock(p);

   Z_IDCheck(IDBOOL(block->id != ZONEID),
             "Z_Free: freed a pointer without ZONEID", block, file, line);

   IDCHECK(block->id = 0); // Nullify id so another free fails

   // haleyjd 01/20/09: check invalid tags
   // catches double frees and possible selective heap corruption
   if(block->tag == PU_FREE || block->tag >= PU_MAX)
   {
      zonef("Z_Free: freed a pointer with invalid tag %d\nSource: %s:%d\n"
#ifdef INSTRUMENTED
            "Source of malloc: %s:%d\n"
            , block->tag, file, line, block->file, block->line
#else
            , block->tag, file, line
#endif
            );
      abort();
   }

   SCRAMBLER(p, block->size);

   if(block->user)            // Nullify user if one exists
      *block->user = NULL;

#ifdef INSTRUMENTED
   free_memory += block->size;
   inactive_memory -= block->extra;
   if(block->tag >= PU_PURGELEVEL)
      purgable_memory -= block->size - block->extra;
   else
      active_memory -= block->size - block->extra;
#endif

   block->tag = PU_FREE; // Mark block freed

   if(block != zone)
   {
      other = block->prev; // Possibly merge with previous block
      if(other->tag == PU_FREE)
      {
         if(rover == block)  // Move back rover if it points at block
            rover = other;
         (other->next = block->next)->prev = other;
         other->size += block->size + HEADER_SIZE;
         block = other;

         INSTRUMENT(inactive_memory -= HEADER_SIZE);
         INSTRUMENT(free_memory += HEADER_SIZE);
      }
   }

   other = block->next;        // Possibly merge with next block
   if(other->tag == PU_FREE && other != zone)
   {
      if(rover == other) // Move back rover if it points at next block
         rover = block;
      (block->next = other->next)->prev = block;
      block->size += other->size + HEADER_SIZE;

      INSTRUMENT(inactive_memory -= HEADER_SIZE);
      INSTRUMENT(free_memory += HEADER_SIZE);
   }

   Z_PrintStats(); // print memory allocation stats
   Z_LogPrintf("* Z_Free(p=%p, file=%s:%d)\n", p, file, line);
}

//
// Z_FreeTags
//
void (Z_FreeTags)(int lowtag, int hightag, __string file, int line)
{
   register memblock_t __near *block = zone;

   if(lowtag <= PU_FREE)
      lowtag = (int)PU_FREE + 1;

   // haleyjd: code inside this do loop has been updated with
   //          cph's fix for memory wastage

   do               // Scan through list, searching for tags in range
   {
      if(block->tag >= lowtag && block->tag <= hightag)
      {
         register memblock_t __near *prev = block->prev, *cur = block;
         (Z_Free)((char __near *)block + HEADER_SIZE, file, line);
         /* cph - be more careful here, we were skipping blocks!
          * If the current block was not merged with the previous,
          *  cur is still a valid pointer, prev->next == cur, and cur is
          *  already free so skip to the next.
          * If the current block was merged with the previous,
          *  the next block to analyse is prev->next.
          * Note that the while() below does the actual step forward
          */
         block = (prev->next == cur) ? cur : prev;
      }
   }
   while((block = block->next) != zone);

   Z_LogPrintf("* Z_FreeTags(lowtag=%d, hightag=%d, file=%s:%d)\n",
               lowtag, hightag, file, line);
}

//
// Z_ChangeTag
//
void (Z_ChangeTag)(void *ptr, int tag, __string file, int line)
{
   register memblock_t __near *block = VoidToBlock(ptr);

   DEBUG_CHECKHEAP();

   Z_IDCheck(IDBOOL(block->id != ZONEID),
             "Z_ChangeTag: Changed a tag without ZONEID", block, file, line);

   Z_IDCheck(IDBOOL(tag >= PU_PURGELEVEL && !block->user),
             "Z_ChangeTag: an owner is required for purgable blocks",
             block, file, line);

#ifdef INSTRUMENTED
   if(block->tag < PU_PURGELEVEL && tag >= PU_PURGELEVEL)
   {
      active_memory -= block->size - block->extra;
      purgable_memory += block->size - block->extra;
   }
   else if(block->tag >= PU_PURGELEVEL && tag < PU_PURGELEVEL)
   {
      active_memory += block->size - block->extra;
      purgable_memory -= block->size - block->extra;
   }
#endif
   block->tag = tag;

   Z_LogPrintf("* Z_ChangeTag(p=%p, tag=%d, file=%s:%d)\n", ptr, tag, file, line);
}

//
// Z_Calloc
//
void *(Z_Calloc)(size_t n1, size_t n2, int tag, void **user, __string file, int line)
{
   if(!(n1 *= n2))
      return NULL;

   return memset_near((void __near *)(Z_Malloc)(n1, tag, user, file, line), 0, n1);
}

#ifdef SMART_REALLOC
//
// Z_Realloc
//
// haleyjd 09/18/06: Rewritten to be an actual realloc routine. The
// various cases are as follows:
//
// 1. If the block is NULL, is in virtual memory, or we're trying to set it to
//    zero-byte size, we use Z_ReallocOld above.
// 2. If the block is smaller than the new size, we need to expand it. If the
//    next block on the zone heap is free, check to see if it together with the
//    current block is large enough. If so, merge the blocks. Now test to make
//    sure the internal fragmentation does not exceed the split limit. If it
//    does, resplit the blocks at the new boundary. If the next block wasn't
//    free, we have to call Z_ReallocOld to move the entire block elsewhere.
// 3. If the block is larger than the new size, we can shrink it, but we only
//    need to shrink it if the wasted space is larger than the split limit.
//    If so, the block is split at its new boundary. If the next block on the
//    zone heap is free, it is then necessary to merge the new free block with
//    the next block on the heap. In the event the block is not shrunk, only the
//    INSTRUMENTED data needs to be updated to reflect the new internal fragmen-
//    tation.
// 4. If the block is already the same size as "n", we don't need to do anything
//    aside from adjusting the INSTRUMENTED block data for debugging purposes.
//
void *(Z_Realloc)(void *ptr, size_t n, int tag, void **user, __string file, int line)
{
   register memblock_t __near *block, *other;
   register size_t curr_size = 0;

   // davidph 12/09/12: Handle null and size 0 right here instead of in Z_ReallocOld.
   if(n == 0) { (Z_Free)(ptr, file, line); return NULL; }

   if(!ptr)
      return (Z_Malloc)(n, tag, user, file, line);

   // get current size of block
   block = VoidToBlock(ptr);

   Z_IDCheck(IDBOOL(block->id != ZONEID),
             "Z_Realloc: Reallocated a block without ZONEID\n",
             block, file, line);

   other = block->next; // save pointer to next block
   curr_size = block->size;

   // round new size to CHUNK_SIZE
   n = (n + CHUNK_SIZE - 1) & ~(CHUNK_SIZE - 1);

   if(n > curr_size) // is new allocation size larger than current?
   {
      register size_t extra;

      // haleyjd 10/03/06: free adjacent purgable blocks
      while(other != zone && other != block &&
            (other->tag == PU_FREE || other->tag >= PU_PURGELEVEL))
      {
         if(other->tag >= PU_PURGELEVEL)
         {
            (Z_Free)(BlockToVoid(other), file, line);

            // reset pointer to next block
            other = block->next;
         }

         // use current size of block; note it may have increased if it was
         // merged with an adjacent free block

         // if we've freed enough, stop
         if(curr_size + other->size + HEADER_SIZE >= n)
            break;

         // move to next block
         other = other->next;
      }

      // reset pointer
      other = block->next;

      // check to see if it can fit if we merge with the next block
      if(other != zone && other->tag == PU_FREE &&
         curr_size + other->size + HEADER_SIZE >= n)
      {
         // merge the blocks
         if(rover == other)
            rover = block;
         (block->next = other->next)->prev = block;
         block->size += other->size + HEADER_SIZE;

#ifdef INSTRUMENTED
         // lost a block...
         inactive_memory -= HEADER_SIZE;
         // lost a free block...
         free_memory -= other->size;
         // increased active or purgable
         if(block->tag >= PU_PURGELEVEL)
            purgable_memory += other->size + HEADER_SIZE;
         else
            active_memory += other->size + HEADER_SIZE;
#endif

         // check to see if there's enough extra to warrant splitting off
         // a new free block
         extra = block->size - n;

         if(extra >= MIN_BLOCK_SPLIT + HEADER_SIZE)
         {
            register memblock_t __near *newb =
               (memblock_t __near *)((char __near *)block + HEADER_SIZE + n);

            (newb->next = block->next)->prev = newb;
            (newb->prev = block)->next = newb;
            block->size = n;
            newb->size = extra - HEADER_SIZE;
            newb->tag = PU_FREE;

            if(rover == block)
               rover = newb;

#ifdef INSTRUMENTED
            // added a block...
            inactive_memory += HEADER_SIZE;
            // added a free block...
            free_memory += newb->size;
            // decreased active or purgable
            if(block->tag >= PU_PURGELEVEL)
               purgable_memory -= newb->size + HEADER_SIZE;
            else
               active_memory -= newb->size + HEADER_SIZE;
#endif
         }

         // subtract old internal fragmentation and add new
         INSTRUMENT(inactive_memory -= block->extra);
         INSTRUMENT(inactive_memory += (block->extra = block->size - n));
      }
      else // else, do old realloc (make new, copy old, free old)
      {
         // davidph 12/10/12: This was the only place Z_ReallocOld was called.
         //   And we know that ptr != NULL and n != 0 and n > curr_size.

         register void *p = (Z_Malloc)(n, tag, user, file, line);

         memcpy_near((void __near *)p, (void __near *)ptr, curr_size);
         (Z_Free)(ptr, file, line);
         if(user) // in case Z_Free nullified same user
            *user = p;

         return p;
      }
   }
   else if(n < curr_size) // is new allocation size smaller than current?
   {
      // check to see if there's enough extra to warrant splitting off
      // a new free block
      size_t extra = curr_size - n;

      if(extra >= MIN_BLOCK_SPLIT + HEADER_SIZE)
      {
         register memblock_t __near *newb =
            (memblock_t __near *)((char __near *)block + HEADER_SIZE + n);

         (newb->next = block->next)->prev = newb;
         (newb->prev = block)->next = newb;
         block->size = n;
         newb->size = extra - HEADER_SIZE;
         newb->tag = PU_FREE;

#ifdef INSTRUMENTED
         // added a block...
         inactive_memory += HEADER_SIZE;
         // added a free block...
         free_memory += newb->size;
         // decreased purgable or active
         if(block->tag >= PU_PURGELEVEL)
            purgable_memory -= newb->size + HEADER_SIZE;
         else
            active_memory -= newb->size + HEADER_SIZE;
#endif

         // may need to merge new block with next block
         if(other && other->tag == PU_FREE && other != zone)
         {
            if(rover == other) // Move back rover if it points at next block
               rover = newb;
            (newb->next = other->next)->prev = newb;
            newb->size += other->size + HEADER_SIZE;

            // deleted a block...
            INSTRUMENT(inactive_memory -= HEADER_SIZE);
            // space between blocks is now free
            INSTRUMENT(free_memory += HEADER_SIZE);
         }
      }
      // else, leave block the same size

      // subtract old internal fragmentation and add new
      INSTRUMENT(inactive_memory -= block->extra);
      INSTRUMENT(inactive_memory += (block->extra = block->size - n));
   }
   // else new allocation size is same as current, don't change it

   // modify the block
   INSTRUMENT(block->file = file);
   INSTRUMENT(block->line = line);

   // reset ptr for consistency
   ptr = BlockToVoid(block);

   if(block->user != user)
   {
      if(block->user)           // nullify old user if any
         *(block->user) = NULL;
      block->user = user;       // set block's new user
      if(user)                  // if non-null, set user to allocation
         *user = ptr;
   }

   // let Z_ChangeTag handle changing the tag
   if(block->tag != tag)
      (Z_ChangeTag)(ptr, tag, file, line);

   Z_PrintStats();           // print memory allocation stats
   Z_LogPrintf("* Z_Realloc(ptr=%p, n=%u, tag=%d, user=%p, source=%s:%d)\n",
               ptr, n, tag, user, file, line);

   return ptr;
}
#else
//
// Z_Realloc
//
// haleyjd 05/29/08: *Something* is wrong with my Z_Realloc routine, and I
// cannot figure out what! So we're back to using Old Faithful for now.
//
// davidph 12/09/12: You fool, you threw away gold! Gold, I say!
//
void *(Z_Realloc)(void *ptr, size_t n, int tag, void **user, __string file, int line)
{
   register void *p = (Z_Malloc)(n, tag, user, file, line);

   if(ptr)
   {
      memblock_t *block = VoidToBlock(ptr);
      if(p) // haleyjd 09/18/06: allow to return NULL without crashing
         memcpy_near((void __near *p, (void __near *)ptr, n <= block->size ? n : block->size);
      (Z_Free)(ptr, file, line);
      if(user) // in case Z_Free nullified same user
         *user=p;
   }

   Z_LogPrintf("* %p = Z_Realloc(ptr=%p, n=%u, tag=%d, user=%p, source=%s:%d)\n",
               p, ptr, n, tag, user, file, line);

   return p;
}
#endif

//
// Z_Strdup
//
char *(Z_Strdup)(char const *s, int tag, void **user, __string file, int line)
{
   return (char *)strcpy((char *)(Z_Malloc)(strlen(s)+1, tag, user, file, line), s);
}

//
// haleyjd 12/06/06: Zone alloca functions
//

//
// Z_FreeAlloca
//
// haleyjd 12/06/06: Frees all blocks allocated with Z_Alloca.
//
void (Z_FreeAlloca)(__string file, int line)
{
   register alloca_header_t __near *hdr = alloca_root, *next;

   Z_LogPuts("* Freeing alloca blocks\n");

   while(hdr)
   {
      next = hdr->next;

      Z_Free(hdr);

      hdr = next;
   }

   alloca_root = NULL;
}

//
// Z_Alloca
//
// haleyjd 12/06/06:
// Implements a portable garbage-collected alloca on the zone heap.
//
void *(Z_Alloca)(size_t n, __string file, int line)
{
   register alloca_header_t __near *hdr;
   register void *ptr;

   if(n == 0)
      return NULL;

   // add an alloca_header_t to the requested allocation size
   ptr = (Z_Malloc)(n + sizeof(alloca_header_t), PU_STATIC, NULL, file, line);

   Z_LogPrintf("* %p = Z_Alloca(n = %u, file = %s, line = %d)\n", ptr, n, file, line);

   // add to linked list
   hdr = (alloca_header_t __near *)ptr;
   hdr->next = alloca_root;
   alloca_root = hdr;

   // return a pointer to the actual allocation
   return (void *)((char __near *)ptr + sizeof(alloca_header_t));
}

//
// Z_Strdupa
//
// haleyjd 05/07/08: strdup that uses alloca, for convenience.
//
char *(Z_Strdupa)(char const *s, __string file, int line)
{
   return (char *)strcpy((char *)(Z_Alloca)(strlen(s)+1, file, line), s);
}

//
// Z_CheckHeap
//
void (Z_CheckHeap)(__string file, int line)
{
   register memblock_t __near *block = zone;   // Start at base of zone mem

   do                          // Consistency check (last node treated special)
   {
      if((block->next != zone &&
          (memblock_t __near *)((char __near *)block + HEADER_SIZE + block->size) != block->next) ||
         block->next->prev != block || block->prev->next != block)
      {
         zonef("Z_CheckHeap: Block size does not touch the next block\nSource: %s:%d\n"
#ifdef INSTRUMENTED
               "Source of offending block: %s:%d\n"
               , file, line, block->file, block->line
#else
               , file, line
#endif
               );
         abort();
      }
   }
   while((block = block->next) != zone);

#ifndef CHECKHEAP
   Z_LogPrintf("* Z_CheckHeap(file=%s:%d)\n", file, line);
#endif
}

//
// Z_CheckTag
//
// haleyjd: a function to return the allocation tag of a block.
// This is needed by W_CacheLumpNum so that it does not
// inadvertently lower the cache level of lump allocations and
// cause code which expects them to be static to lose them
//
int (Z_CheckTag)(void *ptr, __string file, int line)
{
   register memblock_t __near *block = VoidToBlock(ptr);

   DEBUG_CHECKHEAP();

   Z_IDCheck(IDBOOL(block->id != ZONEID),
             "Z_CheckTag: block doesn't have ZONEID", block, file, line);

   return block->tag;
}

//
// Z_PrintZoneHeap
//
void Z_PrintZoneHeap(void)
{
   // This function isn't exactly fantastically useful without an fopen, anyway.
   #ifndef __NEAR_POINTERS__
   register FILE *outfile;
   register memblock_t __near *block = zone;

   char const *fmtstr =
#if defined(ZONEIDCHECK) && defined(INSTRUMENTED)
      "%p: { %8X : %p : %p : %8u : %p : %d : %s : %d }\n"
#elif defined(INSTRUMENTED)
      "%p: { %p : %p : %8u : %p : %d : %s : %d }\n"
#elif defined(ZONEIDCHECK)
      "%p: { %8X : %p : %p : %8u : %p : %d }\n"
#else
      "%p: { %p : %p : %8u : %p : %d }\n"
#endif
      ;

   char const *freestr =
#if defined(ZONEIDCHECK)
      "%p: { %8X : %p : %p : %8u }\n"
#else
      "%p: { %p : %p : %8u }\n"
#endif
      ;

   outfile = fopen("heap.txt", "w");
   if(!outfile)
      return;

   do
   {
      if(block->tag != PU_FREE)
      {
         fprintf(outfile, fmtstr, block,
#if defined(ZONEIDCHECK)
                 block->id,
#endif
                 block->next, block->prev, block->size,
                 block->user, block->tag
#if defined(INSTRUMENTED)
                 , block->file, block->line
#endif
                 );
      }
      else
      {
         fprintf(outfile, freestr, block,
#if defined(ZONEIDCHECK)
                 block->id,
#endif
                 block->next, block->prev, block->size);
      }

      // warnings
#if defined(ZONEIDCHECK)
      if(block->tag != PU_FREE && block->id != ZONEID)
         fputs("\tWARNING: block does not have ZONEID\n", outfile);
#endif
      if(!block->user && block->tag >= PU_PURGELEVEL)
         fputs("\tWARNING: purgable block with no user\n", outfile);
      if(block->tag >= PU_MAX)
         fputs("\tWARNING: invalid cache level\n", outfile);
      if(block->next != zone &&
         (memblock_t *)((char *)block + HEADER_SIZE + block->size) != block->next)
         fputs("\tWARNING: block size doesn't touch next block\n", outfile);
      if(block->next->prev != block || block->prev->next != block)
         fputs("\tWARNING: block pointer inconsistency\n", outfile);

      fflush(outfile);
   }
   while((block = block->next) != zone);

   fclose(outfile);
   #endif
}

//
// Z_DumpCore
//
// haleyjd 03/18/07: Write the zone heap to file
//
void Z_DumpCore()
{
   // This function isn't exactly fantastically useful without an fopen, anyway.
   #ifndef __NEAR_POINTERS__
   register FILE *outfile;

   if(!(outfile = fopen("zone.bin", "wb")))
      return;

   fwrite(zonebase, 1, zonebase_size, outfile);
   fclose(outfile);
   #endif
}

//
// Z_SysMalloc
//
// Similar to I_AllocLow in the original source, this function gives explicit
// access to the C heap. There are allocations which are a detriment to the zone
// system, such as large video buffers, which should be handled through this
// function instead.
//
// Care must be taken, of course, to not mix zone and C heap allocations.
//
void *(Z_SysMalloc)(size_t size, __string file, int line)
{
   void *ret;

   // davidph 12/09/12: Don't fail on a null return if size is 0.
   if(!(ret = malloc(size)) && size)
   {
      zonef("Z_SysMalloc: failed on allocation of %u bytes\nSource: %s:%d\n",
            size, file, line);
      abort();
   }

   return ret;
}

//
// Z_SysCalloc
//
// Convenience routine to match above.
//
void *(Z_SysCalloc)(size_t n1, size_t n2, __string file, int line)
{
   void *ret;

   // davidph 12/09/12: Don't fail on a null return if size is 0.
   if(!(ret = calloc(n1, n2)) && n1*n2)
   {
      zonef("Z_SysCalloc: failed on allocation of %u bytes\nSource: %s:%d\n",
            n1*n2, file, line);
      abort();
   }

   return ret;
}

//
// Z_SysRealloc
//
// Turns out I need this in the sound code to avoid possible multithreaded
// race conditions.
//
void *(Z_SysRealloc)(void *ptr, size_t size, __string file, int line)
{
   void *ret;

   // davidph 12/09/12: Don't fail on a null return if size is 0.
   if(!(ret = realloc(ptr, size)) && size)
   {
      zonef("Z_SysRealloc: failed on allocation of %u bytes\nSource: %s:%d\n",
            size, file, line);
      abort();
   }

   return ret;
}

//
// Z_SysFree
//
// For use with Z_SysAlloc.
//
void (Z_SysFree)(void *p, __string file, int line)
{
   free(p);
}


//
// Z_PrintStats
//
// Print allocation statistics.
//
void (Z_PrintStats)()
{
   #ifdef INSTRUMENTED
   unsigned int total_memory = free_memory + active_memory +
                               purgable_memory + inactive_memory;

   zonef(
      "%9u  %3u%%  static\n"
      "%9u  %3u%%  purgable\n"
      "%9u  %3u%%  free\n"
      "%9u  %3u%%  fragmentary\n"
      "%9u  100%%  total\n",
      active_memory,   active_memory*100/total_memory,
      purgable_memory, purgable_memory*100/total_memory,
      free_memory,     free_memory*100/total_memory,
      inactive_memory, inactive_memory*100/total_memory,
      total_memory);
   #else
   zonef("Z_PrintStats: not instrumented\n");
   #endif
}

//-----------------------------------------------------------------------------
//
// $Log: z_zone.c,v $
// Revision 1.13  1998/05/12  06:11:55  killough
// Improve memory-related error messages
//
// Revision 1.12  1998/05/03  22:37:45  killough
// beautification
//
// Revision 1.11  1998/04/27  01:49:39  killough
// Add history of malloc/free and scrambler (INSTRUMENTED only)
//
// Revision 1.10  1998/03/28  18:10:33  killough
// Add memory scrambler for debugging
//
// Revision 1.9  1998/03/23  03:43:56  killough
// Make Z_CheckHeap() more diagnostic
//
// Revision 1.8  1998/03/02  11:40:02  killough
// Put #ifdef CHECKHEAP around slow heap checks (debug)
//
// Revision 1.7  1998/02/02  13:27:45  killough
// Additional debug info turned on with #defines
//
// Revision 1.6  1998/01/26  19:25:15  phares
// First rev with no ^Ms
//
// Revision 1.5  1998/01/26  07:15:43  phares
// Added rcsid
//
// Revision 1.4  1998/01/26  06:12:30  killough
// Fix memory usage problems and improve debug stat display
//
// Revision 1.3  1998/01/22  05:57:20  killough
// Allow use of virtual memory when physical memory runs out
//
// ???
//
//-----------------------------------------------------------------------------
