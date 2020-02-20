/*****************************************************************************/
/* Copyright (C) 1989-2003 OSS Nokalva, Inc.  All rights reserved.           */
/*****************************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* @(#)asn1hdr.h: stdtypes.c 10.3 01/09/27 */

#ifndef ASN1HDR
#define ASN1HDR

#ifdef ASN1CPLUSPLUS
#define MixedReal ossMixedReal
#define GeneralizedTime ossGeneralizedTime
#define UTCTime ossUTCTime
#endif

/*****************************************************************************/
/*                       COMPILER-GENERATED values                           */
/*****************************************************************************/

#include <stdlib.h>
#include <float.h>
#include <limits.h>


extern int ossFreeOpenTypeEncoding;

#ifdef __BORLANDC__
#undef FLT_MAX
#undef DBL_MAX
#include <values.h>
#define FLT_MAX MAXFLOAT
#define DBL_MAX MAXDOUBLE
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

#ifndef DBL_MAX
#ifdef  HUGE_VAL
#define DBL_MAX HUGE_VAL
#else
#ifdef  HUGE
#define DBL_MAX HUGE
#endif
#endif
#endif
#ifndef FLT_MAX
#define FLT_MAX DBL_MAX
#endif

#ifndef FLT_RADIX
#ifdef  u370
#define FLT_RADIX 16
#else
#define FLT_RADIX 2
#endif
#endif

#ifndef OSS_NAN_PRESENT
#define OSS_NAN_PRESENT
#define OSS_NAN_DOUBLE "\x00\x00\x00\x00\x00\x00\xf8\xff"
#define OSS_NAN_FLOAT "\x00\x00\x00\x00\x00\x00\xf8\xff"

#endif
#ifndef OSS_MINUS_ZERO_PRESENT
#define OSS_MINUS_ZERO_PRESENT
#define OSS_MINUS_ZERO_DOUBLE "\x00\x00\x00\x00\x00\x00\x00\x80"
#define OSS_MINUS_ZERO_FLOAT "\x00\x00\x00\x00\x00\x00\x00\x80"

#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif


/*****************************************************************************/
/*                       COMPILER-GENERATED typedefs                         */
/*****************************************************************************/


#ifndef __cplusplus
#define _union
#endif

#ifndef OSS_INT16
#define OSS_INT16 short
#endif

#define OSS_UINT16 unsigned OSS_INT16

#ifndef OSS_INT32
#define OSS_INT32 int
#endif

#define OSS_UINT32 unsigned OSS_INT32

#ifndef LONG_LONG
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LONG_LONG __int64
#define LLONG_FMT "%I64d"
#elif defined(__IBMC__)
#define LONG_LONG long long
#define LLONG_FMT "%lld"
#else
#define LONG_LONG long
#define LLONG_FMT "%ld"
#endif
#endif

#ifndef ULONG_LONG
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ULONG_LONG unsigned __int64
#define ULLONG_FMT "%I64u"
#elif defined(__IBMC__)
#define ULONG_LONG unsigned long long
#define ULLONG_FMT "%llu"
#else
#define ULONG_LONG unsigned long
#define ULLONG_FMT "%lu"
#endif
#endif

#ifndef LLONG_MAX
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LLONG_MAX _I64_MAX
#elif defined(__IBMC__)
#define LLONG_MAX LONGLONG_MAX
#else
#define LLONG_MAX LONG_MAX
#endif
#endif

#ifndef LLONG_MIN
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LLONG_MIN _I64_MIN
#elif defined(__IBMC__)
#define LLONG_MIN LONGLONG_MIN
#else
#define LLONG_MIN LONG_MIN
#endif
#endif

#ifndef ULLONG_MAX
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ULLONG_MAX _UI64_MAX
#elif defined(__IBMC__)
#define ULLONG_MAX ULONGLONG_MAX
#else
#define ULLONG_MAX ULONG_MAX
#endif
#endif

#ifndef LLONG_MIN
#define LLONG_MIN (-2147483647i64-1i64)
#endif
#ifndef LLONG_MAX
#define LLONG_MAX (2147483647i64)
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX (4294967295ui64)
#endif

typedef char ossBoolean;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef char Nulltype;

typedef struct {
  short          year;         /* YYYY format when used for GeneralizedTime */
                               /* YY format when used for UTCTime */
  short          month;
  short          day;
  short          hour;
  short          minute;
  short          second;
  short          millisec;
  short          mindiff;      /* UTC +/- minute differential     */  
  ossBoolean     utc;          /* TRUE means UTC time             */  
} GeneralizedTime; 

typedef GeneralizedTime UTCTime;

typedef struct {
  int            pduNum;
  long           length;       /* length of encoded */
  void          *encoded;
  void          *decoded;
#ifdef OSS_OPENTYPE_HAS_USERFIELD
  void          *userField;
#endif
} OpenType;

typedef struct {
  int            pduNum;
  long           length;       /* length of encoded */
  void          *encoded;
  void          *decoded;
  unsigned long  byteOffset;
  unsigned short bitOffset;    /* Used only for PER */
  unsigned short residualBits; /* Used only for PER */
#ifdef OSS_OPENTYPE_HAS_USERFIELD
  void          *userField;
#endif /* OSS_OPENTYPE_HAS_USERFIELD */
} OpenTypeExtended;

enum MixedReal_kind {OSS_BINARY, OSS_DECIMAL};

typedef struct {
  enum MixedReal_kind kind;
  union {
      double base2;
      char  *base10;
  } u;
} MixedReal;

typedef struct ObjectSetEntry {
  struct ObjectSetEntry *next;
  void                  *object;
  struct ObjectSetEntry *prev;
  char                  *object_name;
} ObjectSetEntry;

typedef struct {
  struct ObjectSetEntry *oset;
  struct ObjectSetEntry *xoset;
  unsigned char *        flags;
  unsigned int           count;
} XOSetInfoEntry;

#ifndef _OSAK_BUFFER_
#define _OSAK_BUFFER_

typedef struct osak_buffer {
    struct osak_buffer *next;          /* next element in list */
    unsigned char      *buffer_ptr;    /* start of actual buffer */
    unsigned long int   buffer_length; /* size of actual buffer */
    unsigned char      *data_ptr;      /* start of user data */
    unsigned long int   data_length;   /* length of user data */
    unsigned long int   reserved [4];
} osak_buffer;

#endif     /* #ifndef _OSAK_BUFFER_ */

#ifdef ASN1CPLUSPLUS
#undef MixedReal
#undef GeneralizedTime
#undef UTCTime
#endif

#endif     /* #ifndef ASN1HDR */
