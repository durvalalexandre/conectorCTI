/*************************************************************/
/* Copyright (C) 2006 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows */
/* Abstract syntax: drvr_asn_tbl */
/* Created: Wed Feb 15 18:13:18 2006 */
/* ASN.1 compiler version: 6.1.1 */
/* Code generated for runtime version 6.1 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -controlfile drvrdefs.c -headerfile ctidrvrdefs.h -noshortennames
 * -nouniquepdu -externalname drvr_asn_tbl -noconstraints -compat v4.1.1
 * -compat v4.1.2 -compat v4.1.3 -compat v4.1.4 -compat v4.1.5 -compat v4.1.6
 * -compat v4.1.7 -compat v4.1.8
 * v:\ossasn1\win32\6.1.0\asn1dflt\asn1dflt.ms.zp8 drvr
 */

#ifndef OSS_drvr_asn_tbl
#define OSS_drvr_asn_tbl

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#define          TSRVDriverOAMReq_t_PDU 1
#define          TSRVDriverOAMConfEvent_t_PDU 2
#define          TSRVDriverOAMEvent_t_PDU 3

typedef struct TSRVDriverOAMReq_t {
    unsigned int    length;
    unsigned char   *data;
} TSRVDriverOAMReq_t;

typedef struct TSRVDriverOAMConfEvent_t {
    unsigned int    length;
    unsigned char   *data;
} TSRVDriverOAMConfEvent_t;

typedef struct TSRVDriverOAMEvent_t {
    unsigned int    length;
    unsigned char   *data;
} TSRVDriverOAMEvent_t;


extern void * const drvr_asn_tbl;    /* encoder-decoder control table */
#endif /* OSS_drvr_asn_tbl */
