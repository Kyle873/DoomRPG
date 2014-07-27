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
// Variable arguments.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__STDARG_H__
#define __HEADER__STDARG_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// va_arg
//
#define va_arg(ap, T) (*--*(T __near *__local *)&(ap))

//
// va_copy
//
#define va_copy(dest, src) ((void)((dest) = (src)))

//
// va_end
//
#define va_end(ap) ((void)0)

//
// va_start
//
#define va_start(ap, parmN) ((void)((ap) = (void __local *)0))


//----------------------------------------------------------------------------|
// Types                                                                      |
//

//
// va_list
//
#ifndef __HAVE_VA_LIST
#define __HAVE_VA_LIST 1
typedef void __near *va_list;
#endif

#endif//__HEADER__STDARG_H__

