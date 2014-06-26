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

#ifndef BitIO_H__
#define BitIO_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

#if defined(__LANG_DS__)
#  define BitIO_FuncDecl extern "C" __function
#elif defined(__cplusplus)
#  define BitIO_FuncDecl extern "C"
#else
#  define BitIO_FuncDecl extern
#endif


//----------------------------------------------------------------------------|
// Types                                                                      |
//

typedef struct BitIO_State
{
   int *data;
   int  posB;
   int  posW;
} BitIO_State;


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

// Retrieves a value from the stream.
BitIO_FuncDecl int BitIO_GetBits(BitIO_State *state, int bits);

// Creates a new stream using data as the buffer.
BitIO_FuncDecl void BitIO_Open(BitIO_State *state, int *data);

// Writes a value to the stream.
BitIO_FuncDecl void BitIO_PutBits(BitIO_State *state, int bits, int data);

// Returns number of bits read/written.
BitIO_FuncDecl int BitIO_UsedB(BitIO_State *state);

// Returns number of words read/written.
BitIO_FuncDecl int BitIO_UsedW(BitIO_State *state);

#endif//BitIO_H__

