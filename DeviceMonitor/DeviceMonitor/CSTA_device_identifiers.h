/*************************************************************/
/* Copyright (C) 2006 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows */
/* Abstract syntax: CSTA_device_identifiers */
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

#ifndef OSS_CSTA_device_identifiers
#define OSS_CSTA_device_identifiers

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */



typedef char            DeviceID_t[64];

typedef enum DeviceIDType_t {
    deviceIdentifier = 0,
    implicitPublic = 20,
    explicitPublicUnknown = 30,
    explicitPublicInternational = 31,
    explicitPublicNational = 32,
    explicitPublicNetworkSpecific = 33,
    explicitPublicSubscriber = 34,
    explicitPublicAbbreviated = 35,
    implicitPrivate = 40,
    explicitPrivateUnknown = 50,
    explicitPrivateLevel3RegionalNumber = 51,
    explicitPrivateLevel2RegionalNumber = 52,
    explicitPrivateLevel1RegionalNumber = 53,
    explicitPrivatePtnSpecificNumber = 54,
    explicitPrivateLocalNumber = 55,
    explicitPrivateAbbreviated = 56,
    otherPlan = 60,
    trunkIdentifier = 70,
    trunkGroupIdentifier = 71
} DeviceIDType_t;

typedef enum DeviceIDStatus_t {
    idProvided = 0,
    idNotKnown = 1,
    idNotRequired = 2
} DeviceIDStatus_t;

typedef struct ExtendedDeviceID_t {
    DeviceID_t      deviceID;
    DeviceIDType_t  deviceIDType;
    DeviceIDStatus_t deviceIDStatus;
} ExtendedDeviceID_t;

typedef ExtendedDeviceID_t CallingDeviceID_t;

typedef ExtendedDeviceID_t CalledDeviceID_t;

typedef ExtendedDeviceID_t SubjectDeviceID_t;

typedef ExtendedDeviceID_t RedirectionDeviceID_t;

#endif /* OSS_CSTA_device_identifiers */
