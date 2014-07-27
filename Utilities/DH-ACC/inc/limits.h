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
// Sizes of integer types.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__LIMITS_H__
#define __HEADER__LIMITS_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

#define CHAR_BIT 32

#define SCHAR_MIN (-0x7FFFFFFF-1)
#define SCHAR_MAX ( 0x7FFFFFFF  )
#define UCHAR_MAX ( 0xFFFFFFFFU )

#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX

#define MB_LEN_MAX 1

#define SHRT_MIN (-0x7FFFFFFF-1)
#define SHRT_MAX ( 0x7FFFFFFF  )
#define USHRT_MAX  0xFFFFFFFFU

#define INT_MIN (-0x7FFFFFFF-1)
#define INT_MAX ( 0x7FFFFFFF  )
#define UINT_MAX  0xFFFFFFFFU

#define LONG_MIN (-0x7FFFFFFFFFFFFFFFL-1)
#define LONG_MAX ( 0x7FFFFFFFFFFFFFFFL  )
#define ULONG_MAX  0xFFFFFFFFFFFFFFFFUL

#define LLONG_MIN (-0x7FFFFFFFFFFFFFFFLL-1)
#define LLONG_MAX ( 0x7FFFFFFFFFFFFFFFLL  )
#define ULLONG_MAX  0xFFFFFFFFFFFFFFFFULL

#endif//__HEADER__LIMITS_H__

