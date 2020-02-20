/*************************************************************/
/* Copyright (C) 2004 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows NT */
/* Abstract syntax: coam_asn_tbl */
/* Created: Fri Feb 27 18:05:28 2004 */
/* ASN.1 compiler version: 6.1.1 */
/* Code generated for runtime version 6.1 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -controlfile coamdefs.c -headerfile cticoamdefs.h -noshortennames
 * -nouniquepdu -externalname coam_asn_tbl -noconstraints -compat v4.1.1
 * -compat v4.1.2 -compat v4.1.3 -compat v4.1.4 -compat v4.1.5 -compat v4.1.6
 * -compat v4.1.7 -compat v4.1.8
 * v:\ossasn1\win32\6.1.0\asn1dflt\asn1dflt.ms.zp8 csrvoam
 */

#ifndef OSS_coam_asn_tbl
#define OSS_coam_asn_tbl

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#define          CsrvGetCsrvInfo_t_PDU 1
#define          CsrvGetCsrvInfoConfEvent_t_PDU 2
#define          CsrvGetDriverInfo_t_PDU 3
#define          CsrvGetDriverInfoConfEvent_t_PDU 4
#define          CsrvGetDriverResources_t_PDU 5
#define          CsrvGetDriverResConfEvent_t_PDU 6
#define          CsrvDeleteDriverResource_t_PDU 7
#define          CsrvDeleteDriverResourceConfEvent_t_PDU 8
#define          CsrvSetDriverResource_t_PDU 9
#define          CsrvSetDriverResourceConfEvent_t_PDU 10
#define          CsrvSetMsgTrace_t_PDU 11

typedef char            CsrvDriverName_t[49];

typedef char            CsrvVersion_t[21];

typedef struct CsrvGetCsrvInfo_t {
    Nulltype        null;
} CsrvGetCsrvInfo_t;

typedef struct CsrvGetCsrvInfoConfEvent_t {
    CsrvVersion_t   csrvVersion;
    unsigned short  cstaTrace;
    unsigned short  roseTrace;
} CsrvGetCsrvInfoConfEvent_t;

typedef struct CsrvGetDriverInfo_t {
    Nulltype        null;
} CsrvGetDriverInfo_t;

typedef struct CsrvDriverInfo_t {
    short           driverID;
    CsrvDriverName_t drvrName;
    unsigned short  cstaTrace;
    unsigned short  roseTrace;
} CsrvDriverInfo_t;

typedef struct CsrvDriverOAMInfo_t {
    unsigned int    count;
    CsrvDriverInfo_t *drvrOAMInfo;
} CsrvDriverOAMInfo_t;

typedef struct CsrvGetDriverInfoConfEvent_t {
    long            numLeft;
    CsrvDriverOAMInfo_t drvInfo;
} CsrvGetDriverInfoConfEvent_t;

typedef struct CsrvGetDriverResources_t {
    Nulltype        null;
} CsrvGetDriverResources_t;

typedef struct CsrvDriverResource_t {
    short           driverID;
    CsrvDriverName_t drvrAdvName;
    short           sessions;
    short           requests;
    short           monitors;
    short           routeReg;
    short           routingDialogs;
    short           sysStatReg;
    short           systemStatus;
    long            csdiMaxBytes;
    long            csdiHwMark;
    long            csdiLwMark;
    long            csdiUsage;
    short           regSem;
    short           rcvSem;
    short           sendSem;
    short           bufSem;
    long            cstaInSize;
    long            cstaOutSize;
    long            cstaEventSize;
    long            berBufSize;
    long            ropmBufSize;
    long            msgsQueToCsta;
    long            msgsQueToDrv;
    long            msgsAllocByCsta;
    long            msgsAllocByDrv;
    long            msgsCSTAPriv;
    long            bytesQueToCsta;
    long            bytesQueToDrv;
    long            bytesAllocByCsta;
    long            bytesAllocByDrv;
    long            bytesCSTAPriv;
    long            msgsRcvdTsrv;
    long            msgsSentTsrv;
    long            msgsRcvdDrv;
    long            msgsSentDrv;
} CsrvDriverResource_t;

typedef struct CsrvDriverResInfo_t {
    unsigned int    count;
    CsrvDriverResource_t *drvrResInfo;
} CsrvDriverResInfo_t;

typedef struct CsrvGetDriverResConfEvent_t {
    long            numLeft;
    CsrvDriverResInfo_t drvInfo;
} CsrvGetDriverResConfEvent_t;

typedef struct CsrvDeleteDriverResource_t {
    CsrvDriverName_t drvrAdvName;
} CsrvDeleteDriverResource_t;

typedef struct CsrvDeleteDriverResourceConfEvent_t {
    Nulltype        null;
} CsrvDeleteDriverResourceConfEvent_t;

typedef struct CsrvSetDriverResource_t {
    CsrvDriverName_t drvrAdvName;
    long            csdiMaxBytes;
    long            csdiHwMark;
    long            csdiLwMark;
} CsrvSetDriverResource_t;

typedef struct CsrvSetDriverResourceConfEvent_t {
    Nulltype        null;
} CsrvSetDriverResourceConfEvent_t;

typedef struct CsrvSetMsgTrace_t {
    short           driverFlag;
    short           driverID;
    unsigned short  cstaTrace;
    unsigned short  roseTrace;
} CsrvSetMsgTrace_t;


extern void * const coam_asn_tbl;    /* encoder-decoder control table */
#endif /* OSS_coam_asn_tbl */
