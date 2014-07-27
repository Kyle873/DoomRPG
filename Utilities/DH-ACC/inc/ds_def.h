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
// DS common definitions.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__DS_DEF_H__
#define __HEADER__DS_DEF_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

// Alternate spellings of DS keywords.
#ifdef __LANG_DS__
#  define address_space_decl __address_space_decl
#  define asmfunc            __asmfunc
#  define extfunc            __extfunc
#  define extscript          __extscript
#  define extvar             __extvar
#  define force_cast         __force_cast
#  define function           __function
#  define intern             __intern
#  define intfunc            __intfunc
#  define intscript          __intscript
#  define intvar             __intvar
#  define linespec           __linespec
#  define script             __script
#  define store_cast         __store_cast
#  define variable           __variable
#endif

// Alternate spellings of DS/C extension keywords.
#define address_space   __address_space
#define far             __far
#define global_array    __global_array
#define global_register __global_register
#define library         __library
#define local           __local
#define local_register  __local_register
#define map_array       __map_array
#define map_register    __map_register
#define near            __near
#define storeof         __storeof
#define typestr         __typestr
#define world_array     __world_array
#define world_register  __world_register

#endif//__HEADER__DS_DEF_H__

