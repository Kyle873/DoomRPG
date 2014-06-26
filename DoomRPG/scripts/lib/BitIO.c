//-----------------------------------------------------------------------------
//
// Copyright (c) 2014, David Hill
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
//-----------------------------------------------------------------------------
//
// Bit-packing I/O.
//
//-----------------------------------------------------------------------------

#include "BitIO.h"


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

#define WORD_BIT 32


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

//
// BitIO_GetBits
//
int BitIO_GetBits(BitIO_State *state, int bits)
{
   int data;

   // Cache structure members because far pointers are so slow.
   int  posB = state->posB;
   int  posW = state->posW;
   int *word = state->data + posW;

   int avail = WORD_BIT - posB;

   // If enough space, fetch from current word.
   if(avail >= bits)
   {
      data = *word >> posB;

      // Update state.
      state->posB = posB + bits;
   }

   // Spanning value.
   else if(avail)
   {
      data  = (*word >> posB) & ((1 << avail) - 1);
      data |= word[1] << avail;

      // Update state.
      state->posB = bits - avail;
      state->posW = posW + 1;
   }

   // No space, fetch from next word.
   else
   {
      data = word[1];

      // Update state.
      state->posB = bits;
      state->posW = posW + 1;
   }

   // Truncate value and return.
   return data & ((1 << bits) - 1);
}

//
// BitIO_Open
//
void BitIO_Open(BitIO_State *state, int *data)
{
   state->data = data;
   state->posW = 0;
   state->posB = 0;
}

//
// BitIO_PutBits
//
void BitIO_PutBits(BitIO_State *state, int bits, int data)
{
   // Cache structure members because far pointers are so slow.
   int  posB = state->posB;
   int  posW = state->posW;
   int *word = state->data + posW;

   int avail = WORD_BIT - posB;

   // Truncate data, just in case.
   data = data & ((1 << bits) - 1);

   // If enough space, add to current word.
   if(avail >= bits)
   {
      *word |= data << posB;

      // Update state.
      state->posB = posB + bits;
   }

   // Some space left, but not enough. Span the words.
   else if(avail)
   {
      *word  |= data << posB;
      word[1] = data >> avail;

      // Update state.
      state->posB = bits - avail;
      state->posW = posW + 1;
   }

   // No space left, so a simplified version of the above.
   else
   {
      word[1] = data;

      // Update state.
      state->posB = bits;
      state->posW = posW + 1;
   }
}

//
// BitIO_UsedB
//
int BitIO_UsedB(BitIO_State *state)
{
   return state->posW * WORD_BIT + state->posB;
}

//
// BitIO_UsedW
//
int BitIO_UsedW(BitIO_State *state)
{
   return state->posB ? state->posW + 1 : state->posW;
}

// EOF

