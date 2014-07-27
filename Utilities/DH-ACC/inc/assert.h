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
// Diagnostics.
//
//-----------------------------------------------------------------------------

//#ifndef __HEADER__ASSERT_H__
//#define __HEADER__ASSERT_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// assert
//
#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
# define assert(ignore) ((void)0)
#else
# ifdef __LANG_C__
#  define assert(expression) \
   if(!(expression)) \
   { \
      __printf log("Assertion failed: %s, function %s, file %s, line %i.", \
         #expression, __func__, __FILE__, __LINE__); \
      abort(); \
   } \
   else ((void)0)
# else
#  define assert(expression) \
   if(!(expression)) \
   { \
      __printf<__printf_log>("Assertion failed: %s, function %s, file %s, line %i.", \
         #expression, __func__, __FILE__, __LINE__); \
      abort(); \
   } \
   else ((void)0)
# endif
#endif

//
// static_assert
//
#if !defined(static_assert) && !defined(__cplusplus) && !defined(__LANG_DS__)
#define static_assert _Static_assert
#endif

//#endif//__HEADER__ASSERT_H__

