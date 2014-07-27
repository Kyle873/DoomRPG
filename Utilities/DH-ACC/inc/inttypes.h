//-----------------------------------------------------------------------------
//
// Copyright(C) 2012 David Hill
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
// Format conversion of integer types.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__INTTYPES_H__
#define __HEADER__INTTYPES_H__

#include <stdint.h>


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// PRId*
//
#define PRId32       "d"
#define PRId64      "ld"

#define PRIdLEAST8   "d"
#define PRIdLEAST16  "d"
#define PRIdLEAST32  "d"
#define PRIdLEAST64 "ld"

#define PRIdFAST8    "d"
#define PRIdFAST16   "d"
#define PRIdFAST32   "d"
#define PRIdFAST64  "ld"

#define PRIdMAX    "lld"
#define PRIdPTR     "ld"

//
// PRIi*
//
#define PRIi32       "i"
#define PRIi64      "li"

#define PRIiLEAST8   "i"
#define PRIiLEAST16  "i"
#define PRIiLEAST32  "i"
#define PRIiLEAST64 "li"

#define PRIiFAST8    "i"
#define PRIiFAST16   "i"
#define PRIiFAST32   "i"
#define PRIiFAST64  "li"

#define PRIiMAX    "lli"
#define PRIiPTR     "li"

//
// PRIo*
//
#define PRIo32       "o"
#define PRIo64      "lo"

#define PRIoLEAST8   "o"
#define PRIoLEAST16  "o"
#define PRIoLEAST32  "o"
#define PRIoLEAST64 "lo"

#define PRIoFAST8    "o"
#define PRIoFAST16   "o"
#define PRIoFAST32   "o"
#define PRIoFAST64  "lo"

#define PRIoMAX    "llo"
#define PRIoPTR     "lo"

//
// PRIu*
//
#define PRIu32       "u"
#define PRIu64      "lu"

#define PRIuLEAST8   "u"
#define PRIuLEAST16  "u"
#define PRIuLEAST32  "u"
#define PRIuLEAST64 "lu"

#define PRIuFAST8    "u"
#define PRIuFAST16   "u"
#define PRIuFAST32   "u"
#define PRIuFAST64  "lu"

#define PRIuMAX    "llu"
#define PRIuPTR     "lu"

//
// PRIx*
//
#define PRIx32       "x"
#define PRIx64      "lx"

#define PRIxLEAST8   "x"
#define PRIxLEAST16  "x"
#define PRIxLEAST32  "x"
#define PRIxLEAST64 "lx"

#define PRIxFAST8    "x"
#define PRIxFAST16   "x"
#define PRIxFAST32   "x"
#define PRIxFAST64  "lx"

#define PRIxMAX    "llx"
#define PRIxPTR     "lx"

//
// PRIX*
//
#define PRIX32       "X"
#define PRIX64      "lX"

#define PRIXLEAST8   "X"
#define PRIXLEAST16  "X"
#define PRIXLEAST32  "X"
#define PRIXLEAST64 "lX"

#define PRIXFAST8    "X"
#define PRIXFAST16   "X"
#define PRIXFAST32   "X"
#define PRIXFAST64  "lX"

#define PRIXMAX    "llX"
#define PRIXPTR     "lX"

//
// SCNd*
//
#define SCNd32       "d"
#define SCNd64      "ld"

#define SCNdLEAST8   "d"
#define SCNdLEAST16  "d"
#define SCNdLEAST32  "d"
#define SCNdLEAST64 "ld"

#define SCNdFAST8    "d"
#define SCNdFAST16   "d"
#define SCNdFAST32   "d"
#define SCNdFAST64  "ld"

#define SCNdMAX    "lld"
#define SCNdPTR     "ld"

//
// SCNi*
//
#define SCNi32       "i"
#define SCNi64      "li"

#define SCNiLEAST8   "i"
#define SCNiLEAST16  "i"
#define SCNiLEAST32  "i"
#define SCNiLEAST64 "li"

#define SCNiFAST8    "i"
#define SCNiFAST16   "i"
#define SCNiFAST32   "i"
#define SCNiFAST64  "li"

#define SCNiMAX    "lli"
#define SCNiPTR     "li"

//
// SCNo*
//
#define SCNo32       "o"
#define SCNo64      "lo"

#define SCNoLEAST8   "o"
#define SCNoLEAST16  "o"
#define SCNoLEAST32  "o"
#define SCNoLEAST64 "lo"

#define SCNoFAST8    "o"
#define SCNoFAST16   "o"
#define SCNoFAST32   "o"
#define SCNoFAST64  "lo"

#define SCNoMAX    "llo"
#define SCNoPTR     "lo"

//
// SCNu*
//
#define SCNu32       "u"
#define SCNu64      "lu"

#define SCNuLEAST8   "u"
#define SCNuLEAST16  "u"
#define SCNuLEAST32  "u"
#define SCNuLEAST64 "lu"

#define SCNuFAST8    "u"
#define SCNuFAST16   "u"
#define SCNuFAST32   "u"
#define SCNuFAST64  "lu"

#define SCNuMAX    "llu"
#define SCNuPTR     "lu"

//
// SCNx*
//
#define SCNx32       "x"
#define SCNx64      "lx"

#define SCNxLEAST8   "x"
#define SCNxLEAST16  "x"
#define SCNxLEAST32  "x"
#define SCNxLEAST64 "lx"

#define SCNxFAST8    "x"
#define SCNxFAST16   "x"
#define SCNxFAST32   "x"
#define SCNxFAST64  "lx"

#define SCNxMAX    "llx"
#define SCNxPTR     "lx"

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
// imaxdiv_t
//
typedef struct _IdivMAX_t
{
   intmax_t quot;
   intmax_t rem;
} imaxdiv_t;

//
// wchar_t
//
// Needed for wcsto*max. C doesn't say to define it, though.
//
#ifndef __HAVE_WCHAR_T
#define __HAVE_WCHAR_T 1
typedef char wchar_t;
#endif


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

#if defined(__LANG_DS__) || defined(__cplusplus)
extern "C"
{
#endif

//
// Functions for greatest-width integer types.
//

// Absolute value.
__function intmax_t imaxabs(intmax_t j);

// Division.
__function imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);

// Conversion from string.
__function intmax_t strtoimax(char const *restrict nptr, char **restrict endptr, int base);
__function uintmax_t strtoumax(char const *restrict nptr, char **restrict endptr, int base);

// Conversion from wide string.
__function intmax_t wcstoimax(wchar_t const *restrict nptr, wchar_t **restrict endptr, int base);
__function uintmax_t wcstoumax(wchar_t const *restrict nptr, wchar_t **restrict endptr, int base);

#if defined(__LANG_DS__) || defined(__cplusplus)
};
#endif

#endif//__HEADER__INTTYPES_H__

