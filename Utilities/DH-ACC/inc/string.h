//-----------------------------------------------------------------------------
//
// Copyright(C) 2011, 2012 David Hill
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------
//
// String handling.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__STRING_H__
#define __HEADER__STRING_H__

#ifndef __LIBDS_NOLIB
# ifdef __LIBDS_PARTS
__library("string");
# else
__library("libDS");
# endif
#endif


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// NULL
//
#ifndef NULL
#define NULL 0
#endif

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
typedef unsigned size_t;
#endif


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

#if defined(__LANG_DS__) || defined(__cplusplus)
extern "C"
{
#endif

//
// Copying functions.
//

// Copies a chunk of memory.
__function void *memcpy(void *restrict s1, void const *restrict s2, size_t n);
__function void __near *memcpy_near(void __near *restrict s1,
   void const __near *restrict s2, size_t n);

// Copies a chunk of memory.
__function void *memmove(void *s1, void const *s2, size_t n);

// Swaps two chunks of memory.
__function void *memswp(void *restrict s1, void *restrict s2, size_t n);

// Copies a null-terminated string.
__function char *strcpy(char *restrict s1, char const *restrict s2);

// Copies a null-terminated string.
__function char *strncpy(char *restrict s1, char const *restrict s2, size_t n);

//
// Concatenation functions.
//

// Concatenates two null-terminated strings.
__function char *strcat(char *restrict s1, char const *restrict s2);

// Concatenates two null-terminated strings.
__function char *strncat(char *restrict s1, char const *restrict s2, size_t n);

//
// Comparison functions.
//

// Compares two chunks of memory.
__function int memcmp(void const *s1, void const *s2, size_t n);

// Compares two null-terminated strings.
__function int strcmp(char const *s1, char const *s2);

// Compares two null-terminated strings.
__function int strcoll(char const *s1, char const *s2);

// Compares two null-terminated strings.
__function int strncmp(char const *s1, char const *s2, size_t n);

//
__function size_t strxfrm(char *restrict s1, char const *restrict s2, size_t n);

//
// Search functions
//

// Finds a value in a chunk of memory.
__function void *memchr(void const *s, int c, size_t n);

// Finds a value in a null-terminated string.
__function char *strchr(char const *s, int c);

//
__function size_t strcspn(char const *s1, char const *s2);

//
__function char *strpbrk(char const *s1, char const *s2);

// Finds a value in a null-terminated string.
__function char *strrchr(char const *s, int c);

//
__function size_t strspn(char const *s1, char const *s2);

// Finds a value in a null-terminated string.
__function char *strstr(char const *s1, char const *s2);

// Tokenizes a null-terminated string.
__function char *strtok(char *restrict s1, char const *restrict s2);

//
// Miscellaneous functions.
//

// Sets a chunk of memory.
__function void *memset(void *s, int c, size_t n);
__function void __near *memset_near(void __near *s, int c, size_t n);

//
__function char *strerror(int errnum);

// Finds the length of a null-terminated string.
__function size_t strlen(char const *s);

#if defined(__LANG_DS__) || defined(__cplusplus)
};
#endif

#endif//__HEADER__STRING_H__

