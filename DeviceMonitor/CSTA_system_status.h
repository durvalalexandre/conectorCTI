/*************************************************************/
/* Copyright (C) 2006 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_system_status */
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

#ifndef OSS_CSTA_system_status
#define OSS_CSTA_system_status

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */



typedef enum SystemStatus_t {
    ssInitializing = 0,
    ssEnabled = 1,
    ssNormal = 2,
    ssMessagesLost = 3,
    ssDisabled = 4,
    ssOverloadImminent = 5,
    ssOverloadReached = 6,
    ssOverloadRelieved = 7
} SystemStatus_t;

typedef unsigned char   SystemStatusFilter_t;
#define                     sfInitializing 0x80
#define                     sfEnabled 0x40
#define                     sfNormal 0x20
#define                     sfMessagesLost 0x10
#define                     sfDisabled 0x08
#define                     sfOverloadImminent 0x04
#define                     sfOverloadReached 0x02
#define                     sfOverloadRelieved 0x01

typedef struct CSTAReqSysStat_t {
    Nulltype        null;
} CSTAReqSysStat_t;

typedef struct CSTASysStatReqConfEvent_t {
    SystemStatus_t  systemStatus;
} CSTASysStatReqConfEvent_t;

typedef struct CSTASysStatStart_t {
    SystemStatusFilter_t statusFilter;
} CSTASysStatStart_t;

typedef struct CSTASysStatStartConfEvent_t {
    SystemStatusFilter_t statusFilter;
} CSTASysStatStartConfEvent_t;

typedef struct CSTASysStatStop_t {
    Nulltype        null;
} CSTASysStatStop_t;

typedef struct CSTASysStatStopConfEvent_t {
    Nulltype        null;
} CSTASysStatStopConfEvent_t;

typedef struct CSTAChangeSysStatFilter_t {
    SystemStatusFilter_t statusFilter;
} CSTAChangeSysStatFilter_t;

typedef struct CSTAChangeSysStatFilterConfEvent_t {
    SystemStatusFilter_t statusFilterSelected;
    SystemStatusFilter_t statusFilterActive;
} CSTAChangeSysStatFilterConfEvent_t;

typedef struct CSTASysStatEvent_t {
    SystemStatus_t  systemStatus;
} CSTASysStatEvent_t;

typedef struct CSTASysStatEndedEvent_t {
    Nulltype        null;
} CSTASysStatEndedEvent_t;

typedef struct CSTASysStatReqEvent_t {
    Nulltype        null;
} CSTASysStatReqEvent_t;

typedef struct CSTAReqSysStatConf_t {
    SystemStatus_t  systemStatus;
} CSTAReqSysStatConf_t;

typedef struct CSTASysStatEventSend_t {
    SystemStatus_t  systemStatus;
} CSTASysStatEventSend_t;

#endif /* OSS_CSTA_system_status */
