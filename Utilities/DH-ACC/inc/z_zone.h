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
//      Zone Memory Allocation, perhaps NeXT ObjectiveC inspired.
//      Remark: this was the only stuff that, according
//       to John Carmack, might have been useful for
//       Quake.
//
// Rewritten by Lee Killough, though, since it was not efficient enough.
//
// Ported to DS and then DH-acc's C by David Hill.
//
//---------------------------------------------------------------------

#ifndef __HEADER__Z_ZONE_H__
#define __HEADER__Z_ZONE_H__

#ifndef __LIBDS_NOLIB
# ifdef __LIBDS_PARTS
__library("z_zone");
# else
__library("libDS");
# endif
#endif


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// __function
//
#ifndef __function
# ifdef __LANG_DS__
#  define __function __function
# else
#  define __function
# endif
#endif


//----------------------------------------------------------------------------|
// Types                                                                      |
//

//
// size_t
//
#ifndef __HAVE_SIZE_T
#define __HAVE_SIZE_T 1
typedef unsigned int size_t;
#endif

//
// PU - purge tags.
//
enum
{
   PU_FREE,     // block is free
   PU_STATIC,   // block is static (remains until explicitly freed)

   // domain-specific allocation lifetimes

   PU_SOUND,    // currently unused
   PU_MUSIC,    // currently unused
   PU_RENDERER, // haleyjd 06/29/08: for data allocated via R_Init
   PU_AUTO,     // haleyjd 07/08/10: automatic allocation

   // these must remain together:

   PU_LEVEL,    // allocation belongs to level (freed at next level load)
   PU_LEVSPEC,  // used for thinker_t's (same as PU_LEVEL basically)

   PU_CACHE,    // block is cached (may be implicitly freed at any time!)

   PU_MAX       // Must always be last -- killough
};

#define PU_PURGELEVEL PU_CACHE        /* First purgable tag's level */


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

#if defined(__LANG_DS__) || defined(__cplusplus)
extern "C"
{
#endif

__function void  (Z_Close)(__string, int);
__function void  (Z_Init)(__string, int);
__function void *(Z_Malloc)(size_t size, int tag, void **ptr, __string, int);
__function void  (Z_Free)(void *ptr, __string, int);
__function void  (Z_FreeTags)(int lowtag, int hightag, __string, int);
__function void  (Z_ChangeTag)(void *ptr, int tag, __string, int);
__function void *(Z_Calloc)(size_t n, size_t n2, int tag, void **user, __string, int);
__function void *(Z_Realloc)(void *p, size_t n, int tag, void **user, __string, int);
__function char *(Z_Strdup)(char const *s, int tag, void **user, __string, int);
__function void  (Z_FreeAlloca)(__string, int);
__function void *(Z_Alloca)(size_t n, __string, int);
__function void *(Z_Realloca)(void *ptr, size_t n, __string, int);
__function char *(Z_Strdupa)(char const *s, __string, int);
__function void  (Z_CheckHeap)(__string, int);   // killough 3/22/98: add file/line info
__function int   (Z_CheckTag)(void *, __string, int);

__function void *(Z_SysMalloc)(size_t size, __string, int);
__function void *(Z_SysCalloc)(size_t n1, size_t n2, __string, int);
__function void *(Z_SysRealloc)(void *ptr, size_t size, __string, int);
__function void  (Z_SysFree)(void *p, __string, int);

#define Z_Init()           (Z_Init)      (        __FILE__,__LINE__)
#define Z_Close()          (Z_Close)     (        __FILE__,__LINE__)
#define Z_Malloc(a,b,c)    (Z_Malloc)    (a,b,c,  __FILE__,__LINE__)
#define Z_Free(a)          (Z_Free)      (a,      __FILE__,__LINE__)
#define Z_FreeTags(a,b)    (Z_FreeTags)  (a,b,    __FILE__,__LINE__)
#define Z_ChangeTag(a,b)   (Z_ChangeTag) (a,b,    __FILE__,__LINE__)
#define Z_Calloc(a,b,c,d)  (Z_Calloc)    (a,b,c,d,__FILE__,__LINE__)
#define Z_Realloc(a,b,c,d) (Z_Realloc)   (a,b,c,d,__FILE__,__LINE__)
#define Z_Strdup(a,b,c)    (Z_Strdup)    (a,b,c,  __FILE__,__LINE__)
#define Z_FreeAlloca()     (Z_FreeAlloca)(        __FILE__,__LINE__)
#define Z_Alloca(a)        (Z_Alloca)    (a,      __FILE__,__LINE__)
#define Z_Realloca(a,b)    (Z_Realloca)  (a,b,    __FILE__,__LINE__)
#define Z_Strdupa(a)       (Z_Strdupa)   (a,      __FILE__,__LINE__)
#define Z_CheckHeap()      (Z_CheckHeap) (        __FILE__,__LINE__)
#define Z_CheckTag(a)      (Z_CheckTag)  (a,      __FILE__,__LINE__)

#define Z_SysMalloc(a)     (Z_SysMalloc) (a,      __FILE__,__LINE__)
#define Z_SysCalloc(a,b)   (Z_SysCalloc) (a,b,    __FILE__,__LINE__)
#define Z_SysRealloc(a,b)  (Z_SysRealloc)(a,b,    __FILE__,__LINE__)
#define Z_SysFree(a)       (Z_SysFree)   (a,      __FILE__,__LINE__)

__function void Z_ZoneHistory(char *);
__function void Z_PrintStats(); // killough 8/23/98
__function void Z_PrintZoneHeap();
__function void Z_DumpCore();

#if defined(__LANG_DS__) || defined(__cplusplus)
};
#endif


//----------------------------------------------------------------------------|
// Cleanup                                                                    |
//

#undef __function

#endif//__HEADER__Z_ZONE_H__

//----------------------------------------------------------------------------
//
// $Log: z_zone.h,v $
// Revision 1.7  1998/05/08  20:32:12  killough
// fix __attribute__ redefinition
//
// Revision 1.6  1998/05/03  22:38:11  killough
// Remove unnecessary #include
//
// Revision 1.5  1998/04/27  01:49:42  killough
// Add history of malloc/free and scrambler (INSTRUMENTED only)
//
// Revision 1.4  1998/03/23  03:43:54  killough
// Make Z_CheckHeap() more diagnostic
//
// Revision 1.3  1998/02/02  13:28:06  killough
// Add doom_printf
//
// Revision 1.2  1998/01/26  19:28:04  phares
// First rev with no ^Ms
//
// Revision 1.1.1.1  1998/01/19  14:03:06  rand
// Lee's Jan 19 sources
//
//
//----------------------------------------------------------------------------
