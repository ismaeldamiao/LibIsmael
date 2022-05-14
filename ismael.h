/* *****************************************************************************
   This file is a collection of functions and subroutine for use in
   physics, mathematics and engineering.
   This is conformed to the ISO/IEC 9899:1999 (also called C99), but
   contains intructions to compile with some GNU extensions if __GNUC__ is
   defined.
   *****************************************************************************
   E-mail: ismaellxd@gmail.com
   Site: https://ismaeldamiao.github.io/
   *****************************************************************************
   Copyright (c) 2022 I.F.F. dos SANTOS

   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the “Software”), to 
   deal in the Software without restriction, including without limitation the 
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
   sell copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
   IN THE SOFTWARE.
***************************************************************************** */

#ifndef ISMAEL_H
#define ISMAEL_H 1

/* *****************************************************************************
   Aliases for standards and systems
***************************************************************************** */

/* ISO C standards (__STDC_VERSION__) */
#define __ISO_C94 199409L /* ISO/IEC 9899-1:1994 */
#define __ISO_C99 199901L /* ISO/IEC 9899:1999 */
#define __ISO_C11 201112L /* ISO/IEC 9899:2011 */
#define __ISO_C17 201710L /* ISO/IEC 9899:2018 */

/* POSIX C standards (_POSIX_VERSION) */
#define __POSIX_2008 200809L /* IEEE 1003.1-2008 */




/* *****************************************************************************
   ISO C standard
***************************************************************************** */

#if !defined(__STDC__) || (__STDC_VERSION__ < __ISO_C99) /* __ISO_C99 */
#error "Use only ISO C99 and later."
#endif /* __ISO_C99 */


/* Standard libraries */
#include <stdio.h>   /* Many functions for file input and output */
#include <stdlib.h>  /* Numeric conversion functions, memory allocation */
#include <stdbool.h> /* Defines a boolean data type */
#include <stdint.h>  /* Defines exact-width integer types. */
#include <math.h>    /* Many mathematical functions */
#include <complex.h> /* Many complex mathematical functions */
#include <float.h>   /* DBL_MAX */
#include <limits.h>  /* INT_MAX, INT_MIN */
#include <time.h>    /* Defines date- and time-handling functions */
#include <stdarg.h>  /* var-args */


/* Standard pragmas */
#pragma STDC FENV_ACCESS OFF
#pragma STDC FP_CONTRACT ON
#pragma STDC CX_LIMITED_RANGE OFF

/* Do not proceed if complex arithmetic is not supported. */
#if (__STDC_VERSION__ >= __ISO_C11) /* __ISO_C11 */
#if (__STDC_NO_COMPLEX__ == 1)
#error "Complex arithmetic is not supported."
#endif /* __STDC_NO_COMPLEX__ */
#endif /* __ISO_C11 */

/* Always define CMPLX if it's not defined. */
#if !defined(CMPLX) && ((_Imaginary_I) || (__STDC_VERSION__ < __ISO_C11))
#define CMPLX(x, y) ((double _Complex)((double)(x) + _Complex_I * (double)(y)))
#endif

/* Some implementations of the C standards use functions in creal and cimag, but
   is best use simples operators (musl implemented like this).
   See
   * ISO/IEC 9899:1999 6.3.1.7 2
   * ISO/IEC 9899:1999 6.2.5 13 */
#ifdef creal
#undef creal
#endif
#define creal(z) ((double)(z))

/*#ifdef cimag
#undef cimag
#endif
static double _Complex __CIMAG;
#define cimag(z) (__CIMAG = (z), ((double*)&(__CIMAG))[1])*/




/* *****************************************************************************
   GNU Compiler Collection API and extensions to the C standard
***************************************************************************** */

#if defined(__GNUC__)
#pragma GCC optimize ("O3") /* Always optimize the code */
#pragma GCC diagnostic warning "-Wall" /* Always show all warning */
#pragma GCC diagnostic warning "-Wextra" /* Always show extra warning */
#pragma GCC diagnostic warning "-Wpedantic" /* To test portabilit. */
#endif /* __GNUC__ */




/* *****************************************************************************
   POSIX/UNIX extensions to the C standard
***************************************************************************** */

#if defined(__unix__)
#include <unistd.h> /* chdir */
#include <sys/stat.h> /* mkdir */
#include <sys/types.h>
#endif /* __unix__ */

/* Math constants defined in POSIX.1-2008 standard */
#if !defined(M_PI)
#define M_E             2.7182818284590452354   /* e */
#define M_LOG2E         1.4426950408889634074   /* log_2 e */
#define M_LOG10E        0.43429448190325182765  /* log_10 e */
#define M_LN2           0.69314718055994530942  /* log_e 2 */
#define M_LN10          2.30258509299404568402  /* log_e 10 */
#define M_PI            3.14159265358979323846  /* pi */
#define M_PI_2          1.57079632679489661923  /* pi/2 */
#define M_PI_4          0.78539816339744830962  /* pi/4 */
#define M_1_PI          0.31830988618379067154  /* 1/pi */
#define M_2_PI          0.63661977236758134308  /* 2/pi */
#define M_2_SQRTPI      1.12837916709551257390  /* 2/sqrt(pi) */
#define M_SQRT2         1.41421356237309504880  /* sqrt(2) */
#define M_SQRT1_2       0.70710678118654752440  /* 1/sqrt(2) */
#endif /* M_PI */




/* *****************************************************************************
   Linux kernel API
***************************************************************************** */

#if defined(__linux__)
#endif /* __linux__ */




/* *****************************************************************************
   Android API
***************************************************************************** */

#if defined(__ANDROID__)
#endif /* __ANDROID__ */




/* *****************************************************************************
   Windows API
***************************************************************************** */

#if defined(_WIN32)
#endif /* _WIN32 */




/* *****************************************************************************
   GNU Scientific Library, Release 2.6
***************************************************************************** */

/*
#include "./src/gsl/gsl_const_num.h"

#include "./src/gsl/gsl_const_cgs.h"
#include "./src/gsl/gsl_const_mks.h"

#include "./src/gsl/gsl_const_cgsm.h"
#include "./src/gsl/gsl_const_mksa.h"
*/



/* *****************************************************************************
   Some physical constants
***************************************************************************** */
/* exactly */
#define CONST_SPEED_OF_LIGHT      2.99792458e8              /* m / s */
#define CONST_AVOGADRO            6.02214076e23             /* 1 / mol */
#define CONST_PLANCK              6.62607015e-34            /* kg m^2 / s */
#define CONST_BOLTZMANN           1.380649e-23              /* J / K */
#define CONST_ELEMENTARY_CHARGE   1.602176634e-19           /* A s */
/* approximately */
#define CONST_GRAVITATIONAL       6.674e-11                 /* m^3 / (kg s^2) */
#define CONST_REDUCED_PLANCK      1.054571817646156472e-34  /* kg m^2 / s */
#define CONST_VACUUM_PERMITTIVITY 8.8541878128e-12          /* s^4A^2/(Kg m^3)*/
#define CONST_VACUUM_PERMEABILITY 1.25663706212e-6          /* Kg m^2/(s A)^2 */




/* *****************************************************************************
   ...
***************************************************************************** */

#if defined(random)
#undef random
#endif

#if !defined(UINT64_MAX)
#define uint64_t void
#endif
typedef struct {
   struct {
      const long double a[35][35];
      const long double b[35];
      const long double c[35];
   } rk14;
   struct {
      const long double a[11][11];
      const long double b[11];
      const long double c[11];
   } rk8;
   struct {
      double (* const mt64)(uint64_t*);
      double (* const mt32)(uint32_t*);
      double (* const system)(int*);
      double* (* const bernoulli)(double,int,int);
      double* (* const distance)(double,int,int);
      double* (* const fourier)(double,int,int);
   } random;
   _Complex double (* const atoc)(const char*);
   double** (* const FDP)(double*,int,int);
   void (*error)(int,const char*);
} __ismael_namespace;
extern const __ismael_namespace ismael;

#if (__STDC_VERSION__ >= __ISO_C11)
   #define ialloc(size, type) \
   (type*)aligned_alloc(sizeof(type), (size_t)size * sizeof(type))
#else
   #define ialloc(size, type) \
   (type*)malloc((size_t)size * sizeof(type))
#endif /* __ISO_C11 */

#endif /* ISMAEL_H */
