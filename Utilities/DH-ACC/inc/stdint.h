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
// Integer types.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__STDINT_H__
#define __HEADER__STDINT_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

#define  INT32_MIN (-0x7FFFFFFF-1)
#define  INT32_MAX ( 0x7FFFFFFF  )
#define UINT32_MAX ( 0xFFFFFFFFU )

#define  INT64_MIN (-0x7FFFFFFFFFFFFFFF-1)
#define  INT64_MAX ( 0x7FFFFFFFFFFFFFFF  )
#define UINT64_MAX ( 0xFFFFFFFFFFFFFFFFU )

#define  INT_LEAST8_MIN (-0x7FFFFFFF-1)
#define  INT_LEAST8_MAX ( 0x7FFFFFFF  )
#define UINT_LEAST8_MAX ( 0xFFFFFFFFU )

#define  INT_LEAST16_MIN (-0x7FFFFFFF-1)
#define  INT_LEAST16_MAX ( 0x7FFFFFFF  )
#define UINT_LEAST16_MAX ( 0xFFFFFFFFU )

#define  INT_LEAST32_MIN (-0x7FFFFFFF-1)
#define  INT_LEAST32_MAX ( 0x7FFFFFFF  )
#define UINT_LEAST32_MAX ( 0xFFFFFFFFU )

#define  INT_LEAST64_MIN (-0x7FFFFFFFFFFFFFFF-1)
#define  INT_LEAST64_MAX ( 0x7FFFFFFFFFFFFFFF  )
#define UINT_LEAST64_MAX ( 0xFFFFFFFFFFFFFFFFU )

#define  INT_FAST8_MIN (-0x7FFFFFFF-1)
#define  INT_FAST8_MAX ( 0x7FFFFFFF  )
#define UINT_FAST8_MAX ( 0xFFFFFFFFU )

#define  INT_FAST16_MIN (-0x7FFFFFFF-1)
#define  INT_FAST16_MAX ( 0x7FFFFFFF  )
#define UINT_FAST16_MAX ( 0xFFFFFFFFU )

#define  INT_FAST32_MIN (-0x7FFFFFFF-1)
#define  INT_FAST32_MAX ( 0x7FFFFFFF  )
#define UINT_FAST32_MAX ( 0xFFFFFFFFU )

#define  INT_FAST64_MIN (-0x7FFFFFFFFFFFFFFF-1)
#define  INT_FAST64_MAX ( 0x7FFFFFFFFFFFFFFF  )
#define UINT_FAST64_MAX ( 0xFFFFFFFFFFFFFFFFU )

#define  INTPTR_MIN (-0x7FFFFFFFFFFFFFFF-1)
#define  INTPTR_MAX ( 0x7FFFFFFFFFFFFFFF  )
#define UINTPTR_MAX ( 0xFFFFFFFFFFFFFFFFU )

#define  INTMAX_MIN (-0x7FFFFFFFFFFFFFFF-1)
#define  INTMAX_MAX ( 0x7FFFFFFFFFFFFFFF  )
#define UINTMAX_MAX ( 0xFFFFFFFFFFFFFFFFU )

#ifndef PTRDIFF_MIN
#  define PTRDIFF_MIN (-0x7FFFFFFF-1)
#  define PTRDIFF_MAX ( 0x7FFFFFFF  )
#endif

#ifndef SIG_ATOMIC_MIN
#  define SIG_ATOMIC_MIN (-0x7FFFFFFF-1)
#  define SIG_ATOMIC_MAX ( 0x7FFFFFFF  )
#endif

#ifndef SIZE_MAX
#  define SIZE_MAX (0xFFFFFFFFU)
#endif

#ifndef WCHAR_MIN
#  define WCHAR_MIN (-0x7FFFFFFF-1)
#  define WCHAR_MAX ( 0x7FFFFFFF  )
#endif

#ifndef WINT_MIN
#  define WINT_MIN (-0x7FFFFFFF-1)
#  define WINT_MAX ( 0x7FFFFFFF  )
#endif

#define INT8_C (VALUE) (VALUE     )
#define INT16_C(VALUE) (VALUE     )
#define INT32_C(VALUE) (VALUE     )
#define INT64_C(VALUE) (VALUE ## L)

#define UINT8_C (VALUE) (VALUE ## U )
#define UINT16_C(VALUE) (VALUE ## U )
#define UINT32_C(VALUE) (VALUE ## U )
#define UINT64_C(VALUE) (VALUE ## UL)

#define  INTMAX_C(VALUE) (VALUE ##  LL)
#define UINTMAX_C(VALUE) (VALUE ## ULL)


//----------------------------------------------------------------------------|
// Types                                                                      |
//

typedef   signed      int  int32_t;
typedef   signed long int  int64_t;

typedef unsigned      int uint32_t;
typedef unsigned long int uint64_t;

typedef   signed      char  int_least8_t;
typedef   signed short int  int_least16_t;
typedef   signed       int  int_least32_t;
typedef   signed  long int  int_least64_t;

typedef unsigned      char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned       int uint_least32_t;
typedef unsigned  long int uint_least64_t;

typedef   signed      int  int_fast8_t;
typedef   signed      int  int_fast16_t;
typedef   signed      int  int_fast32_t;
typedef   signed long int  int_fast64_t;

typedef unsigned      int uint_fast8_t;
typedef unsigned      int uint_fast16_t;
typedef unsigned      int uint_fast32_t;
typedef unsigned long int uint_fast64_t;

typedef   signed long int  intptr_t;
typedef unsigned long int uintptr_t;

typedef   signed long long int  intmax_t;
typedef unsigned long long int uintmax_t;

#endif//__HEADER__STDINT_H__

