/*************************************************************/
/* Copyright (C) 2006 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_call_connection_identifiers */
/* Created: Thu Feb 16 12:03:13 2006 */
/* ASN.1 compiler version: 6.1.1 */
/* Code generated for runtime version 6.1 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -controlfile cstadefs.c -headerfile cticstadefs.h -noshortennames
 * -nouniquepdu -externalname csta_asn_tbl -noconstraints -charintegers
 * -splitheaders -compat v4.1.1 -compat v4.1.2 -compat v4.1.3 -compat v4.1.4
 * -compat v4.1.5 -compat v4.1.6 -compat v4.1.7 -compat v4.1.8
 * v:\ossasn1\win32\6.1.0\asn1dflt\asn1dflt.ms.zp8 csta
 */

#ifndef OSS_CSTA_call_connection_identifiers
#define OSS_CSTA_call_connection_identifiers

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#include "CSTA_device_identifiers.h"


typedef enum ConnectionID_Device_t {
    staticId = 0,
    dynamicId = 1
} ConnectionID_Device_t;

typedef struct ConnectionID_t {
    long            callID;
    DeviceID_t      deviceID;
    ConnectionID_Device_t devIDType;
} ConnectionID_t;

#endif /* OSS_CSTA_call_connection_identifiers */
