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

#ifndef _BITIO_H_
#define _BITIO_H_

//----------------------------------------------------------------------------|
// Macros                                                                     |
//

#define WORD_BIT 32

//----------------------------------------------------------------------------|
// Types                                                                      |
//

struct BitIO_State
{
   int *data;
   int  posB;
   int  posW;
};

//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

#ifdef __LANG_DS__
extern "C"
{
    __function void BitIO_Open(BitIO_State *state, int *data);
    __function int BitIO_GetBits(BitIO_State *state, int bits);
    __function void BitIO_PutBits(BitIO_State *state, int bits, int data);
};
#else
    void BitIO_Open(struct BitIO_State *state, int *data);
    int BitIO_GetBits(struct BitIO_State *state, int bits);
    void BitIO_PutBits(struct BitIO_State *state, int bits, int data);
#endif

#endif
