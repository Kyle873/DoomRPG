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
// Common definitions.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__STDDEF_H__
#define __HEADER__STDDEF_H__


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
// offsetof
//
#ifndef offsetof
#define offsetof(T,M) ((size_t)&((T __near *)(NULL))->M)
#endif


//----------------------------------------------------------------------------|
// Types                                                                      |
//

//
// ptrdiff_t
//
#ifndef __HAVE_PTRDIFF_T
#define __HAVE_PTRDIFF_T 1
typedef signed int ptrdiff_t;
#endif

//
// size_t
//
#ifndef __HAVE_SIZE_T
#define __HAVE_SIZE_T 1
typedef unsigned int size_t;
#endif

//
// max_align_t
//
#ifndef __HAVE_MAX_ALIGN_T
#define __HAVE_MAX_ALIGN_T 1
typedef int max_align_t;
#endif

//
// wchar_t
//
#ifndef __HAVE_WCHAR_T
#define __HAVE_WCHAR_T 1
typedef char wchar_t;
#endif

#endif//__HEADER__STDDEF_H__

