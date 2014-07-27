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
// Character handling.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__CTYPE_H__
#define __HEADER__CTYPE_H__

#ifndef __LIBDS_NOLIB
# ifdef __LIBDS_PARTS
__library("ctype");
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
// Global Functions                                                           |
//

#if defined(__LANG_DS__) || defined(__cplusplus)
extern "C"
{
#endif

//
// Character classification functions.
//

// Is alphanumeric?
__function int isalnum(int c);

// Is alphabetic?
__function int isalpha(int c);

// Is blank?
__function int isblank(int c);

// Is control?
__function int iscntrl(int c);

// Is decimal digit?
__function int isdigit(int c);

// Is graphical?
__function int isgraph(int c);

// Is lowercase?
__function int islower(int c);

// Is printing?
__function int isprint(int c);

// Is punctuation?
__function int ispunct(int c);

// Is whitespace?
__function int isspace(int c);

// Is uppercase?
__function int isupper(int c);

// Is hexadecimal digit?
__function int isxdigit(int c);

//
// Character case mapping functions.
//

// To lowercase.
__function int tolower(int c);

// To uppercase.
__function int toupper(int c);

#if defined(__LANG_DS__) || defined(__cplusplus)
};
#endif

#endif//__HEADER__CTYPE_H__

