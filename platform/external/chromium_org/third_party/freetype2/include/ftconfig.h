/*  Copyright 1996-2001, 2002, 2003, 2004, 2006, 2007, 2008, 2009 by       */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */


  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


#ifndef __FTCONFIG_H__
#define __FTCONFIG_H__

#include <ft2build.h>
#include FT_CONFIG_OPTIONS_H
#include FT_CONFIG_STANDARD_LIBRARY_H


FT_BEGIN_HEADER


  
  
  
  
  
  
  
  
  
  


#define HAVE_UNISTD_H 1
#define HAVE_FCNTL_H 1
#define HAVE_STDINT_H 1


  
  
  
  
  
  
  

#ifndef FT_CHAR_BIT
#define FT_CHAR_BIT  CHAR_BIT
#endif


#ifdef FT_USE_AUTOCONF_SIZEOF_TYPES

#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define FT_SIZEOF_INT  SIZEOF_INT
#define FT_SIZEOF_LONG SIZEOF_LONG

#else 

  
  
  
  
  

  
#if                                 FT_UINT_MAX == 0xFFFFUL
#define FT_SIZEOF_INT  (16 / FT_CHAR_BIT)
#elif                               FT_UINT_MAX == 0xFFFFFFFFUL
#define FT_SIZEOF_INT  (32 / FT_CHAR_BIT)
#elif FT_UINT_MAX > 0xFFFFFFFFUL && FT_UINT_MAX == 0xFFFFFFFFFFFFFFFFUL
#define FT_SIZEOF_INT  (64 / FT_CHAR_BIT)
#else
#error "Unsupported size of `int' type!"
#endif

  
  
#if                                  FT_ULONG_MAX == 0xFFFFFFFFUL
#define FT_SIZEOF_LONG  (32 / FT_CHAR_BIT)
#elif FT_ULONG_MAX > 0xFFFFFFFFUL && FT_ULONG_MAX == 0xFFFFFFFFFFUL
#define FT_SIZEOF_LONG  (32 / FT_CHAR_BIT)
#elif FT_ULONG_MAX > 0xFFFFFFFFUL && FT_ULONG_MAX == 0xFFFFFFFFFFFFFFFFUL
#define FT_SIZEOF_LONG  (64 / FT_CHAR_BIT)
#else
#error "Unsupported size of `long' type!"
#endif

#endif 


  
#define FT_ALIGNMENT  8


  
  
#ifndef FT_UNUSED
#define FT_UNUSED( arg )  ( (arg) = (arg) )
#endif


  
  
  
  
  
  
  
  
  


  
  
  
  
  
  
  
#if ( defined( __APPLE__ ) && !defined( DARWIN_NO_CARBON ) ) || \
    ( defined( __MWERKS__ ) && defined( macintosh )        )
  
#include "AvailabilityMacros.h"
#if defined( __LP64__ ) && \
    ( MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4 )
#define DARWIN_NO_CARBON 1
#else
#define FT_MACINTOSH 1
#endif

#elif defined( __SC__ ) || defined( __MRC__ )
  
#include "ConditionalMacros.h"
#if TARGET_OS_MAC
#define FT_MACINTOSH 1
#endif

#endif


  
#if defined( __sgi ) && !defined( __GNUC__ )
#if defined( _COMPILER_VERSION ) && ( _COMPILER_VERSION >= 730 )
#pragma set woff 3505
#endif
#endif


  
  
  
  
  
  
  typedef signed short    FT_Int16;
  typedef unsigned short  FT_UInt16;

#if FT_SIZEOF_INT == 4

  typedef signed int      FT_Int32;
  typedef unsigned int    FT_UInt32;

#elif FT_SIZEOF_LONG == 4

  typedef signed long     FT_Int32;
  typedef unsigned long   FT_UInt32;

#else
#error "no 32bit type found -- please check your configuration files"
#endif


  
#if FT_SIZEOF_INT >= 4

  typedef int            FT_Fast;
  typedef unsigned int   FT_UFast;

#elif FT_SIZEOF_LONG >= 4

  typedef long           FT_Fast;
  typedef unsigned long  FT_UFast;

#endif


  
  
#if FT_SIZEOF_LONG == 8

  
#define FT_LONG64
#define FT_INT64  long

#elif defined( _MSC_VER ) && _MSC_VER >= 900  

  
#define FT_LONG64
#define FT_INT64  __int64

#elif defined( __BORLANDC__ )  

  
  

  
#define FT_LONG64
#define FT_INT64  __int64

#elif defined( __WATCOMC__ )   

  

#elif defined( __MWERKS__ )    

#define FT_LONG64
#define FT_INT64  long long int

#elif defined( __GNUC__ )

  
#define FT_LONG64
#define FT_INT64  long long int

#endif 


  
  
  
  
  
  
  
#if defined( FT_LONG64 ) && !defined( FT_CONFIG_OPTION_FORCE_INT64 )

#ifdef __STDC__

  
  
  
  
#undef FT_LONG64
#undef FT_INT64

#endif 

#endif 


#define FT_BEGIN_STMNT  do {
#define FT_END_STMNT    } while ( 0 )
#define FT_DUMMY_STMNT  FT_BEGIN_STMNT FT_END_STMNT


#ifndef  FT_CONFIG_OPTION_NO_ASSEMBLER
  
  

#ifdef __GNUC__

#if defined( __arm__ ) && !defined( __thumb__ )
#define FT_MULFIX_ASSEMBLER  FT_MulFix_arm

  static __inline__ FT_Int32
  FT_MulFix_arm( FT_Int32  a,
                 FT_Int32  b )
  {
    register FT_Int32  t, t2;


    __asm__ __volatile__ (
      "smull  %1, %2, %4, %3\n\t"       
      "mov    %0, %2, asr #31\n\t"      
      "add    %0, %0, #0x8000\n\t"      
      "adds   %1, %1, %0\n\t"           
      "adc    %2, %2, #0\n\t"           
      "mov    %0, %1, lsr #16\n\t"      
      "orr    %0, %0, %2, lsl #16\n\t"  
      : "=r"(a), "=&r"(t2), "=&r"(t)
      : "r"(a), "r"(b) );
    return a;
  }

#endif 

#if defined( i386 )
#define FT_MULFIX_ASSEMBLER  FT_MulFix_i386

  static __inline__ FT_Int32
  FT_MulFix_i386( FT_Int32  a,
                  FT_Int32  b )
  {
    register FT_Int32  result;


    __asm__ __volatile__ (
      "imul  %%edx\n"
      "movl  %%edx, %%ecx\n"
      "sarl  $31, %%ecx\n"
      "addl  $0x8000, %%ecx\n"
      "addl  %%ecx, %%eax\n"
      "adcl  $0, %%edx\n"
      "shrl  $16, %%eax\n"
      "shll  $16, %%edx\n"
      "addl  %%edx, %%eax\n"
      : "=a"(result), "+d"(b)
      : "a"(a)
      : "%ecx" );
    return result;
  }

#endif 

#endif 

#endif 


#ifdef FT_CONFIG_OPTION_INLINE_MULFIX
#ifdef FT_MULFIX_ASSEMBLER
#define FT_MULFIX_INLINED  FT_MULFIX_ASSEMBLER
#endif
#endif


#ifdef FT_MAKE_OPTION_SINGLE_OBJECT

#define FT_LOCAL( x )      static  x
#define FT_LOCAL_DEF( x )  static  x

#else

#ifdef __cplusplus
#define FT_LOCAL( x )      extern "C"  x
#define FT_LOCAL_DEF( x )  extern "C"  x
#else
#define FT_LOCAL( x )      extern  x
#define FT_LOCAL_DEF( x )  x
#endif

#endif 


#ifndef FT_BASE

#ifdef __cplusplus
#define FT_BASE( x )  extern "C"  x
#else
#define FT_BASE( x )  extern  x
#endif

#endif 


#ifndef FT_BASE_DEF

#ifdef __cplusplus
#define FT_BASE_DEF( x )  x
#else
#define FT_BASE_DEF( x )  x
#endif

#endif 


#ifndef FT_EXPORT

#ifdef __cplusplus
#define FT_EXPORT( x )  __attribute__((visibility("default"))) extern "C"  x
#else
#define FT_EXPORT( x )  __attribute__((visibility("default"))) extern  x
#endif

#endif 


#ifndef FT_EXPORT_DEF

#ifdef __cplusplus
#define FT_EXPORT_DEF( x )  __attribute__((visibility("default"))) extern "C"  x
#else
#define FT_EXPORT_DEF( x )  __attribute__((visibility("default"))) extern  x
#endif

#endif 


#ifndef FT_EXPORT_VAR

#ifdef __cplusplus
#define FT_EXPORT_VAR( x )  extern "C"  x
#else
#define FT_EXPORT_VAR( x )  extern  x
#endif

#endif 

  
  
  

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
#ifndef FT_CALLBACK_DEF
#ifdef __cplusplus
#define FT_CALLBACK_DEF( x )  extern "C"  x
#else
#define FT_CALLBACK_DEF( x )  static  x
#endif
#endif 

#ifndef FT_CALLBACK_TABLE
#ifdef __cplusplus
#define FT_CALLBACK_TABLE      extern "C"
#define FT_CALLBACK_TABLE_DEF  extern "C"
#else
#define FT_CALLBACK_TABLE      extern
#define FT_CALLBACK_TABLE_DEF  
#endif
#endif 


FT_END_HEADER


#endif 

