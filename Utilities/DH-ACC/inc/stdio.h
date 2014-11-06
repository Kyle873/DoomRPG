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
// Input/output.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__STDIO_H__
#define __HEADER__STDIO_H__

#ifndef __LIBDS_NOLIB
# ifdef __LIBDS_PARTS
__library("stdio");
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
// _IO*
//
#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 3

//
// BUFSIZ
//
#define BUFSIZ 256

//
// EOF
//
#define EOF (-1)

//
// FOPEN_MAX
//
#define FOPEN_MAX 8

//
// FILENAME_MAX
//
#define FILENAME_MAX 13

//
// L_tmpnam
//
#define L_tmpnam 13

//
// SEEK_*
//
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 3

//
// TMP_MAX
//
#define TMP_MAX 25

//
// std*
//
#define stderr (&_Stream[0])
#define stdin  (&_Stream[1])
#define stdout (&_Stream[2])

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
typedef unsigned int size_t;
#endif

//
// FILE
//
typedef struct _FILE
{
   #ifdef __LANG_DS__
   char[BUFSIZ] buf;
   #else
   char buf[BUFSIZ];
   #endif
   unsigned bufpos;
   unsigned flags;
} FILE;

//
// fpos_t
//
typedef unsigned int fpos_t;

//
// va_list
//
// Needed for vfprintf and friends. C doesn't say to define it, though.
//
#ifndef __HAVE_VA_LIST
#define __HAVE_VA_LIST 1
typedef void __near *va_list;
#endif


//----------------------------------------------------------------------------|
// Global Variables                                                           |
//

#ifdef __LANG_DS__
extern "C" __variable static FILE[] _Stream;
#else
extern FILE _Stream[];
#endif


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

#if defined(__LANG_DS__) || defined(__cplusplus)
extern "C"
{
#endif

//
// Operations on files.
//

// File removal.
__function int remove(char const *filename);

// File renaming.
__function int rename(char const *oldname, char const *newname);

// Temporary file creation.
__function FILE *tmpfile(void);

// Temporary file naming.
__function char *tmpnam(char *s);

//
// File access functions.
//

// Stream closing.
__function int fclose(FILE *stream);

// Stream flushing.
__function int fflush(FILE *stream);

// Stream opening.
__function FILE *fopen(char const *restrict filename, char const *restrict mode);

// Stream reopening.
__function FILE *freopen(char const *restrict filename, char const *restrict mode,
                         FILE *restrict stream);

// Stream buffering.
__function void setbuf(FILE *restrict stream, char *restrict buf);

// Stream buffering.
__function int setvbuf(FILE *restrict stream, char *restrict buf, int mode, size_t size);

//
// Formatted input/output functions.
//

// FILE print formatted.
__function int fprintf(FILE *restrict stream, char const *restrict format, ...);

// FILE scan formatted.
__function int fscanf(FILE *restrict stream, char const *restrict format, ...);

// Print formatted.
__function int printf(char const *restrict format, ...);

// Scan formatted.
__function int scanf(char const *restrict format, ...);

// String length print formatted.
__function int snprintf(char *restrict s, size_t n, char const *restrict format, ...);

// String print formatted.
__function int sprintf(char *restrict s, char const *restrict format, ...);

// String scan formatted.
__function int sscanf(char const *restrict s, char const *restrict format, ...);

// va_list FILE print formatted.
__function int vfprintf(FILE *restrict stream, char const *restrict format, va_list arg);

// va_list FILE scan formatted.
__function int vfscanf(FILE *restrict stream, char const *restrict format, va_list arg);

// va_list print formatted.
__function int vprintf(char const *restrict format, va_list arg);

// va_list scan formatted.
__function int vscanf(char const *restrict format, va_list arg);

// va_list string length print formatted.
__function int vsnprintf(char *restrict s, size_t n, char const *restrict format, va_list arg);

// va_list string print formatted.
__function int vsprintf(char *restrict s, char const *restrict format, va_list arg);

// String scan formatted.
__function int vsscanf(char const *restrict s, char const *restrict format, va_list arg);

//
// Character input/output functions.
//

// FILE get character.
__function int fgetc(FILE *stream);

// FILE get string.
__function char *fgets(char *restrict s, int n, FILE *restrict stream);

// FILE put character.
__function int fputc(int c, FILE *stream);

// FILE put string.
__function int fputs(char const *restrict s, FILE *restrict stream);

// FILE get character.
__function int getc(FILE *stream);

// Get character.
__function int getchar(void);

// Get string.
__function char *gets(char *s);

// FILE put character.
__function int putc(int c, FILE *stream);

// Put character.
__function int putchar(int c);

// Put string.
__function int puts(char const *s);

// FILE unget character.
__function int ungetc(int c, FILE *stream);

//
// Direct input/output functions.
//

// FILE read.
__function size_t fread(void *restrict ptr, size_t size, size_t nmemb,
                        FILE *restrict stream);

// FILE write.
__function size_t fwrite(void const *restrict ptr, size_t size, size_t nmemb,
                         FILE *restrict stream);

//
// File positioning functions.
//

// FILE get position.
__function int fgetpos(FILE *restrict stream, fpos_t *restrict pos);

// FILE seek.
__function int fseek(FILE *stream, long int offset, int whence);

// FILE set position.
__function int fsetpos(FILE *stream, fpos_t const *pos);

// FILE tell.
__function long int ftell(FILE *stream);

// FILE reset.
__function void rewind(FILE *stream);

//
// Error-handling functions.
//

// Clear error.
__function void clearerr(FILE *stream);

// End of file test.
__function int feof(FILE *stream);

// Error test.
__function int ferror(FILE *stream);

// Print error.
__function void perror(char const *s);

//
// Implementation extensions.
//

// %o
__function int _Print_o(int flags, int width, int prec, char fmt, unsigned o);

// %lo
__function int _Print_lo(int flags, int width, int prec, char fmt, unsigned long o);

// %s
__function int _Print_s(int flags, int width, int prec, char fmt, char const __far *s);

// %u
__function int _Print_u(int flags, int width, int prec, char fmt, unsigned u);

// %lu
__function int _Print_lu(int flags, int width, int prec, char fmt, unsigned long u);

// %x
__function int _Print_x(int flags, int width, int prec, char fmt, unsigned x);

// %lx
__function int _Print_lx(int flags, int width, int prec, char fmt, unsigned long x);

#if defined(__LANG_DS__) || defined(__cplusplus)
};
#endif

#endif//__HEADER__STDIO_H__

