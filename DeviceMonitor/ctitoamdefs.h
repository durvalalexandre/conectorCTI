/*************************************************************/
/* Copyright (C) 2004 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows NT */
/* Abstract syntax: toam_asn_tbl */
/* Created: Fri Feb 27 18:05:33 2004 */
/* ASN.1 compiler version: 6.1.1 */
/* Code generated for runtime version 6.1 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -controlfile toamdefs.c -headerfile ctitoamdefs.h -noshortennames
 * -nouniquepdu -externalname toam_asn_tbl -noconstraints -charintegers
 * -compat v4.1.1 -compat v4.1.2 -compat v4.1.3 -compat v4.1.4 -compat v4.1.5
 * -compat v4.1.6 -compat v4.1.7 -compat v4.1.8
 * v:\ossasn1\win32\6.1.0\asn1dflt\asn1dflt.ms.zp8 tsrvoam
 */

#ifndef OSS_toam_asn_tbl
#define OSS_toam_asn_tbl

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#define          TsrvBelieveWorkStationID_t_PDU 1
#define          TsrvSetAlarmNotify_t_PDU 2
#define          TsrvAlarmInfoEvent_t_PDU 3
#define          TsrvSetHighWaterMark_t_PDU 4
#define          TsrvSetMsgTrace_t_PDU 5
#define          TsrvSetErrLevelMask_t_PDU 6
#define          TsrvGetTsrvInfo_t_PDU 7
#define          TsrvGetTsrvInfoConfEvent_t_PDU 8
#define          TsrvGetDriverInfo_t_PDU 9
#define          TsrvGetDriverInfoConfEvent_t_PDU 10
#define          TsrvDropClient_t_PDU 11
#define          TsrvGetConnectIDList_t_PDU 12
#define          TsrvGetConnectIDConfEvent_t_PDU 13
#define          TsrvGetOldConnectIDList_t_PDU 14
#define          TsrvGetOldConnectIDConfEvent_t_PDU 15
#define          TsrvSetSDBCheck_t_PDU 16
#define          TsrvGetDriverResources_t_PDU 17
#define          TsrvGetDriverResConfEvent_t_PDU 18
#define          TsrvDeleteDriverResource_t_PDU 19
#define          TsrvDeleteDriverResourceConfEvent_t_PDU 20
#define          TsrvSetDriverResource_t_PDU 21
#define          TsrvSetDriverResourceConfEvent_t_PDU 22
#define          TsrvGetFileSize_t_PDU 23
#define          TsrvGetFileSizeConfEvent_t_PDU 24
#define          TsrvSetFileSize_t_PDU 25
#define          TsrvGetTsrvInfoExt_t_PDU 26
#define          TsrvGetTsrvInfoExtConfEvent_t_PDU 27
#define          TsrvSetTcpOptions_t_PDU 28
#define          TsrvSetAdvertiseNs_t_PDU 29
#define          TsrvSetNdsAdvertising_t_PDU 30
#define          TsrvSetSpxOptions_t_PDU 31
#define          TsrvGetDriverResourcesExt_t_PDU 32
#define          TsrvGetDriverResExtConfEvent_t_PDU 33
#define          TsrvSetDriverTcpResource_t_PDU 34
#define          TsrvSetDriverTcpResConfEvent_t_PDU 35
#define          TsrvGetAboutInfo_t_PDU 36
#define          TsrvGetAboutConfEvent_t_PDU 37
#define          TsrvSetAutoAdmin_t_PDU 38
#define          TsrvSetTcpOptionsConfEvent_t_PDU 39
#define          TsrvSetSpxOptionsConfEvent_t_PDU 40
#define          TsrvSetSdbLogOptions_t_PDU 41
#define          TsrvSetSdbLogOptionsConfEvent_t_PDU 42
#define          TsrvGetSdbLogOptions_t_PDU 43
#define          TsrvGetSdbLogOptionsConfEvent_t_PDU 44
#define          TsrvGetServerType_t_PDU 45
#define          TsrvGetServerTypeConfEvent_t_PDU 46
#define          TsrvGetStatInfo_t_PDU 47
#define          TsrvGetStatInfoConfEvent_t_PDU 48
#define          TsrvResetMax_t_PDU 49
#define          TsrvGetConnectIDListNew_t_PDU 50
#define          TsrvGetConnectIDNewConfEvent_t_PDU 51
#define          TsrvGetOldConnectIDNew_t_PDU 52
#define          TsrvGetOldConnectIDNewConfEvent_t_PDU 53
#define          TsrvGetDriverResourcesPro_t_PDU 54
#define          TsrvGetDriverResProConfEvent_t_PDU 55
#define          TsrvGetFileInfo_t_PDU 56
#define          TsrvGetFileInfoConfEvent_t_PDU 57
#define          TsrvGetPbxDll_t_PDU 58
#define          TsrvGetPbxDllConfEvent_t_PDU 59
#define          TsrvSetAutoLoad_t_PDU 60
#define          TsrvSetAutoLoadConfEvent_t_PDU 61
#define          TsrvAddPbx_t_PDU 62
#define          TsrvAddPbxConfEvent_t_PDU 63
#define          TsrvLoadPbx_t_PDU 64
#define          TsrvLoadPbxConfEvent_t_PDU 65
#define          TsrvRemovePbx_t_PDU 66
#define          TsrvRemovePbxConfEvent_t_PDU 67
#define          TsrvUnloadPbx_t_PDU 68
#define          TsrvUnloadPbxConfEvent_t_PDU 69
#define          TsrvGetDrvrRsrceDeluxe_t_PDU 70
#define          TsrvGetDrvrResDeluxeConfEvent_t_PDU 71
#define          TsrvSetDrvrFlow_t_PDU 72
#define          TsrvSetDrvrFlowConfEvent_t_PDU 73
#define          TsrvResetDrvrMaxFlow_t_PDU 74
#define          TsrvResetDrvrMaxFlowConfEvent_t_PDU 75

typedef char            TLoginID_t[49];

typedef char            TAppName_t[21];

typedef char            DriverName_t[49];

typedef char            TsrvVersion_t[21];

typedef char            TypeName_t[16];

typedef struct Hourly {
    unsigned short  count;
    long            value[23];
} Hourly;

typedef struct LastHour {
    unsigned short  count;
    long            value[20];
} LastHour;

typedef char            ClientNode_t[7];

typedef struct Destinations {
    unsigned short  count;
    short           value[6];
} Destinations;

typedef struct OAMDate_t {
    short           year;
    short           month;
    short           date;
    short           hour;
    short           min;
    short           sec;
    short           day;
} OAMDate_t;

typedef struct MsgRateEntry_t {
    TypeName_t      typeName;
    Hourly          hourly;
    LastHour        lastHour;
} MsgRateEntry_t;

typedef struct MsgRate_t {
    struct {
        unsigned short  count;
        MsgRateEntry_t  value[3];
    } msgRate;
    long            sumLastIntv;
} MsgRate_t;

typedef char            IPAddress_t[16];

typedef enum IPNameFormat_t {
    ipHostName = 1,
    ipAddress = 2
} IPNameFormat_t;

typedef enum TsrvStreamType_t {
    streamCsta = 1,
    streamOam = 2,
    streamDirectory = 3
} TsrvStreamType_t;

typedef char            TsrvAboutString[41];

typedef struct TsrvBelieveWorkStationID_t {
    unsigned char   workStation;
} TsrvBelieveWorkStationID_t;

typedef struct TsrvSetAlarmNotify_t {
    unsigned char   alarmNotify;
} TsrvSetAlarmNotify_t;

typedef struct TsrvAlarmInfoEvent_t {
    char            message[256];
} TsrvAlarmInfoEvent_t;

typedef struct TsrvSetHighWaterMark_t {
    short           highWMark;
} TsrvSetHighWaterMark_t;

typedef struct TsrvSetMsgTrace_t {
    short           driverID;
    short           clntDrvID;
    short           driverFlag;
    long            clientID;
    short           clientFlag;
    long            msgType;
    unsigned char   msgTypeTrace;
    unsigned char   driverTrace;
    unsigned char   clientTrace;
} TsrvSetMsgTrace_t;

typedef struct TsrvSetErrLevelMask_t {
    Destinations    destinations;
} TsrvSetErrLevelMask_t;

typedef struct TsrvGetTsrvInfo_t {
    Nulltype        null;
} TsrvGetTsrvInfo_t;

typedef struct TsrvGetTsrvInfoConfEvent_t {
    unsigned char   workStation;
    unsigned char   alarmNotify;
    unsigned char   traceDrivers;
    unsigned char   traceClients;
    TsrvVersion_t   tsrvVersion;
    short           highWMark;
    short           levelMask;
    unsigned char   sdbCheck;
    Destinations    destinations;
} TsrvGetTsrvInfoConfEvent_t;

typedef struct TsrvGetDriverInfo_t {
    Nulltype        null;
} TsrvGetDriverInfo_t;

typedef struct TsrvDriverInfo_t {
    short           driverID;
    DriverName_t    drvrAdvName;
    short           drvrSecurity;
    long            maxBytes;
    long            queToDrv;
    long            queToTsrv;
    long            allocByDrv;
    long            allocByTsrv;
    MsgRate_t       drvToTsrv;
    MsgRate_t       tsrvToDrv;
    unsigned char   msgTrace;
} TsrvDriverInfo_t;

typedef struct TsrvDriverOAMInfo_t {
    unsigned int    count;
    TsrvDriverInfo_t *drvrOAMInfo;
} TsrvDriverOAMInfo_t;

typedef struct TsrvGetDriverInfoConfEvent_t {
    OAMDate_t       minUpd;
    OAMDate_t       hourUpd;
    long            numLeft;
    TsrvDriverOAMInfo_t drvInfo;
} TsrvGetDriverInfoConfEvent_t;

typedef struct ConnectListEntry_t {
    long            connectionID;
    short           driverID;
    TLoginID_t      login;
    long            clientNet;
    ClientNode_t    clientNode;
    TAppName_t      appName;
    OAMDate_t       timeOpened;
    OAMDate_t       timeClosed;
    MsgRate_t       tsrvToClient;
    MsgRate_t       clientToTsrv;
    unsigned char   msgTrace;
    short           connState;
} ConnectListEntry_t;

typedef struct TsrvDropClient_t {
    long            connectionID;
    short           driverID;
} TsrvDropClient_t;

typedef struct TsrvGetConnectIDList_t {
    Nulltype        null;
} TsrvGetConnectIDList_t;

typedef struct TsrvClientOAMInfo_t {
    unsigned int    count;
    ConnectListEntry_t *connPtr;
} TsrvClientOAMInfo_t;

typedef struct TsrvGetConnectIDConfEvent_t {
    OAMDate_t       minUpd;
    OAMDate_t       hourUpd;
    long            numLeft;
    TsrvClientOAMInfo_t clientInfo;
} TsrvGetConnectIDConfEvent_t;

typedef struct TsrvGetOldConnectIDList_t {
    Nulltype        null;
} TsrvGetOldConnectIDList_t;

typedef struct TsrvGetOldConnectIDConfEvent_t {
    long            numLeft;
    TsrvClientOAMInfo_t clientInfo;
} TsrvGetOldConnectIDConfEvent_t;

typedef struct TsrvSetSDBCheck_t {
    unsigned char   sdbCheck;
} TsrvSetSDBCheck_t;

typedef struct TsrvGetDriverResources_t {
    Nulltype        null;
} TsrvGetDriverResources_t;

typedef struct TsrvDriverResource_t {
    short           driverID;
    DriverName_t    drvrAdvName;
    long            connections;
    long            tsdiSize;
    long            hwMark;
    long            tsdiBufSize;
    long            tsdiBufMax;
    short           connSem;
    short           rcvSem;
    short           sendSem;
    short           freeSem;
    short           connEcbFail;
    short           connEcbIdle;
    short           connEcbBusy;
    short           connEcbAdmined;
    short           connEcbMax;
    short           rcvEcbFail;
    short           rcvEcbIdle;
    short           rcvEcbBusy;
    short           rcvEcbMax;
    short           rcvEcbAdmined;
    short           sendEcbFail;
    short           sendEcbIdle;
    short           sendEcbBusy;
    short           sendEcbMax;
    short           sendEcbAdmined;
    long            msgsQueToDrv;
    long            msgsQueToTsrv;
    long            msgsAllocByDrv;
    long            msgsAllocByTsrv;
    long            msgsTserverPriv;
    long            bytesQueToDrv;
    long            bytesQueToTsrv;
    long            bytesAllocByDrv;
    long            bytesAllocByTsrv;
    long            bytesTserverPriv;
    short           invokeInUse;
    short           invokeMax;
} TsrvDriverResource_t;

typedef struct TsrvDriverResInfo_t {
    unsigned int    count;
    TsrvDriverResource_t *drvrResInfo;
} TsrvDriverResInfo_t;

typedef struct TsrvGetDriverResConfEvent_t {
    long            numLeft;
    TsrvDriverResInfo_t drvInfo;
} TsrvGetDriverResConfEvent_t;

typedef struct TsrvDeleteDriverResource_t {
    DriverName_t    drvrAdvName;
} TsrvDeleteDriverResource_t;

typedef struct TsrvDeleteDriverResourceConfEvent_t {
    Nulltype        null;
} TsrvDeleteDriverResourceConfEvent_t;

typedef struct TsrvSetDriverResource_t {
    DriverName_t    drvrAdvName;
    long            tsdiSize;
    long            hwMark;
    long            tsdiBufSize;
    long            tsdiBufMax;
    short           connECB;
    short           rcvECB;
    short           sendECB;
    short           connECBMax;
    short           rcvECBMax;
    short           sendECBMax;
    short           invokeMax;
} TsrvSetDriverResource_t;

typedef struct TsrvSetDriverResourceConfEvent_t {
    Nulltype        null;
} TsrvSetDriverResourceConfEvent_t;

typedef struct TsrvGetFileSize_t {
    Nulltype        null;
} TsrvGetFileSize_t;

typedef struct TsrvGetFileSizeConfEvent_t {
    long            elogSize;
    long            mtrSize;
} TsrvGetFileSizeConfEvent_t;

typedef struct TsrvSetFileSize_t {
    long            elogSize;
    long            mtrSize;
} TsrvSetFileSize_t;

typedef struct TsrvGetTsrvInfoExt_t {
    Nulltype        null;
} TsrvGetTsrvInfoExt_t;

typedef struct TsrvGetTsrvInfoExtConfEvent_t {
    short           maxTcpConns;
    unsigned char   advertiseNS;
    unsigned char   supplementNDS;
    unsigned char   spxEnabled;
    unsigned char   tcpEnabled;
    short           tcpPort;
    IPAddress_t     tcpAddress;
    IPNameFormat_t  tcpNameFormat;
    unsigned char   autoAdmin;
} TsrvGetTsrvInfoExtConfEvent_t;

typedef struct TsrvSetTcpOptions_t {
    short           maxTcpConns;
    unsigned char   tcpEnabled;
    IPAddress_t     tcpAddress;
    IPNameFormat_t  tcpNameFormat;
} TsrvSetTcpOptions_t;

typedef struct TsrvSetAdvertiseNs_t {
    unsigned char   advertiseNS;
} TsrvSetAdvertiseNs_t;

typedef struct TsrvSetNdsAdvertising_t {
    unsigned char   supplementNDS;
} TsrvSetNdsAdvertising_t;

typedef struct TsrvSetSpxOptions_t {
    unsigned char   spxEnabled;
} TsrvSetSpxOptions_t;

typedef struct TsrvGetDriverResourcesExt_t {
    Nulltype        null;
} TsrvGetDriverResourcesExt_t;

typedef struct TsrvDriverResourceExt_t {
    TsrvDriverResource_t drvRes;
    short           tcpMaxConns;
    short           tcpMaxConnsUsed;
    TsrvVersion_t   drvrVersion;
    TsrvStreamType_t streamType;
    short           protocols;
} TsrvDriverResourceExt_t;

typedef struct TsrvDriverResInfoExt_t {
    unsigned int    count;
    TsrvDriverResourceExt_t *drvrResInfo;
} TsrvDriverResInfoExt_t;

typedef struct TsrvGetDriverResExtConfEvent_t {
    long            numLeft;
    TsrvDriverResInfoExt_t drvInfo;
} TsrvGetDriverResExtConfEvent_t;

typedef struct TsrvSetDriverTcpResource_t {
    DriverName_t    drvrAdvName;
    short           tcpMaxConnsUsed;
} TsrvSetDriverTcpResource_t;

typedef struct TsrvSetDriverTcpResConfEvent_t {
    Nulltype        null;
} TsrvSetDriverTcpResConfEvent_t;

typedef struct TsrvGetAboutInfo_t {
    Nulltype        null;
} TsrvGetAboutInfo_t;

typedef struct TsrvGetAbout_t {
    TsrvVersion_t   aboutVer;
    TsrvAboutString aboutString;
} TsrvGetAbout_t;

typedef struct TsrvGetAboutList_t {
    unsigned int    count;
    TsrvGetAbout_t  *aboutList;
} TsrvGetAboutList_t;

typedef struct TsrvGetAboutConfEvent_t {
    long            numLeft;
    TsrvGetAboutList_t aboutInfo;
} TsrvGetAboutConfEvent_t;

typedef struct TsrvSetAutoAdmin_t {
    unsigned char   autoAdmin;
} TsrvSetAutoAdmin_t;

typedef struct TsrvSetTcpOptionsConfEvent_t {
    Nulltype        null;
} TsrvSetTcpOptionsConfEvent_t;

typedef struct TsrvSetSpxOptionsConfEvent_t {
    Nulltype        null;
} TsrvSetSpxOptionsConfEvent_t;

typedef struct TsrvSetSdbLogOptions_t {
    unsigned char   logSdbChanges;
    long            sdbLogSize;
} TsrvSetSdbLogOptions_t;

typedef struct TsrvSetSdbLogOptionsConfEvent_t {
    Nulltype        null;
} TsrvSetSdbLogOptionsConfEvent_t;

typedef struct TsrvGetSdbLogOptions_t {
    Nulltype        null;
} TsrvGetSdbLogOptions_t;

typedef struct TsrvGetSdbLogOptionsConfEvent_t {
    unsigned char   logSdbChanges;
    long            sdbLogSize;
} TsrvGetSdbLogOptionsConfEvent_t;

typedef enum TSServerType_t {
    netwareTserver = 1,
    winntTserver = 2
} TSServerType_t;

typedef unsigned char   TSTransportType_t;
#define                     tsSpxIpx 0x40
#define                     tsTcpIp 0x20

typedef struct TsrvGetServerType_t {
    Nulltype        null;
} TsrvGetServerType_t;

typedef struct TsrvGetServerTypeConfEvent_t {
    TSServerType_t  serverType;
    TSTransportType_t transportType;
} TsrvGetServerTypeConfEvent_t;

typedef struct TsrvGetStatInfo_t {
    Nulltype        null;
} TsrvGetStatInfo_t;

typedef struct TsrvGetStatInfoConfEvent_t {
    long            licenseSize;
    long            licenseSizeInUse;
    long            maxLicenseSize;
    long            totalMemory;
    long            maxMemory;
    long            numTlinks;
    long            usedSpxConns;
    long            spxLogins;
    long            maxSpxLogins;
    long            tcpLogins;
    long            maxTcpLogins;
} TsrvGetStatInfoConfEvent_t;

typedef struct TsrvResetMax_t {
    Nulltype        null;
} TsrvResetMax_t;

typedef struct ConnectListEntryNew_t {
    long            connectionID;
    short           driverID;
    TLoginID_t      login;
    long            clientNet;
    ClientNode_t    clientNode;
    TAppName_t      appName;
    OAMDate_t       timeOpened;
    OAMDate_t       timeClosed;
    unsigned char   msgTrace;
    short           connState;
} ConnectListEntryNew_t;

typedef struct TsrvGetConnectIDListNew_t {
    Nulltype        null;
} TsrvGetConnectIDListNew_t;

typedef struct TsrvClientOAMInfoNew_t {
    unsigned int    count;
    ConnectListEntryNew_t *connPtr;
} TsrvClientOAMInfoNew_t;

typedef struct TsrvGetConnectIDNewConfEvent_t {
    long            numLeft;
    TsrvClientOAMInfoNew_t clientInfo;
} TsrvGetConnectIDNewConfEvent_t;

typedef struct TsrvGetOldConnectIDNew_t {
    Nulltype        null;
} TsrvGetOldConnectIDNew_t;

typedef struct TsrvGetOldConnectIDNewConfEvent_t {
    long            numLeft;
    TsrvClientOAMInfoNew_t clientInfo;
} TsrvGetOldConnectIDNewConfEvent_t;

typedef struct TsrvGetDriverResourcesPro_t {
    Nulltype        null;
} TsrvGetDriverResourcesPro_t;

typedef struct TsrvDriverResourcePro_t {
    TsrvDriverResource_t drvRes;
    short           tcpMaxConns;
    short           tcpMaxConnsUsed;
    TsrvVersion_t   drvrVersion;
    TsrvStreamType_t streamType;
    short           protocols;
    short           flowControl;
    short           drvrSecurity;
    long            maxBytes;
    unsigned char   msgTrace;
    TsrvVersion_t   tsdiVersion;
} TsrvDriverResourcePro_t;

typedef struct TsrvDriverResInfoPro_t {
    unsigned int    count;
    TsrvDriverResourcePro_t *drvrResInfo;
} TsrvDriverResInfoPro_t;

typedef struct TsrvGetDriverResProConfEvent_t {
    long            numLeft;
    TsrvDriverResInfoPro_t drvInfo;
} TsrvGetDriverResProConfEvent_t;

typedef char            TsrvFileName_t[256];

typedef struct TsrvGetFileInfo_t {
    Nulltype        null;
} TsrvGetFileInfo_t;

typedef struct TsrvGetFileInfoConfEvent_t {
    long            elogSize;
    long            mtrSize;
    TsrvFileName_t  elogPath;
    TsrvFileName_t  msgLogPath;
} TsrvGetFileInfoConfEvent_t;

typedef char            PbxDLLid_t[21];

typedef struct TsrvGetPbxDll_t {
    Nulltype        null;
} TsrvGetPbxDll_t;

typedef enum PbxDLLStatus_t {
    dllLoading = 1,
    dllLoaded = 2,
    dllUnloading = 3,
    dllUnloaded = 4,
    dllUnloadRemove = 5
} PbxDLLStatus_t;

typedef struct PbxDLLInfo_t {
    PbxDLLid_t      pbxDLLName;
    unsigned char   autoLoad;
    PbxDLLStatus_t  status;
} PbxDLLInfo_t;

typedef struct TsrvGetPbxDllConfEvent_t {
    unsigned char   more;
    struct {
        unsigned short  count;
        PbxDLLInfo_t    *pbxDll;
    } list;
} TsrvGetPbxDllConfEvent_t;

typedef struct TsrvSetAutoLoad_t {
    PbxDLLid_t      pbxDLLName;
    unsigned char   autoLoad;
} TsrvSetAutoLoad_t;

typedef struct TsrvSetAutoLoadConfEvent_t {
    Nulltype        null;
} TsrvSetAutoLoadConfEvent_t;

typedef struct TsrvAddPbx_t {
    PbxDLLid_t      pbxDLLName;
} TsrvAddPbx_t;

typedef struct TsrvAddPbxConfEvent_t {
    Nulltype        null;
} TsrvAddPbxConfEvent_t;

typedef struct TsrvLoadPbx_t {
    PbxDLLid_t      pbxDLLName;
} TsrvLoadPbx_t;

typedef struct TsrvLoadPbxConfEvent_t {
    Nulltype        null;
} TsrvLoadPbxConfEvent_t;

typedef struct TsrvRemovePbx_t {
    PbxDLLid_t      pbxDLLName;
} TsrvRemovePbx_t;

typedef struct TsrvRemovePbxConfEvent_t {
    Nulltype        null;
} TsrvRemovePbxConfEvent_t;

typedef struct TsrvUnloadPbx_t {
    PbxDLLid_t      pbxDLLName;
} TsrvUnloadPbx_t;

typedef struct TsrvUnloadPbxConfEvent_t {
    Nulltype        null;
} TsrvUnloadPbxConfEvent_t;

typedef struct TsrvGetDrvrRsrceDeluxe_t {
    Nulltype        null;
} TsrvGetDrvrRsrceDeluxe_t;

typedef struct TsrvDrvrRsrceDeluxe_t {
    TsrvDriverResource_t drvRes;
    short           tcpMaxConns;
    short           tcpMaxConnsUsed;
    TsrvVersion_t   drvrVersion;
    TsrvStreamType_t streamType;
    short           protocols;
    short           flowControl;
    short           maxFlowCtrl;
    unsigned char   flowCtrlEnabled;
    short           drvrSecurity;
    long            maxBytes;
    unsigned char   msgTrace;
    TsrvVersion_t   tsdiVersion;
} TsrvDrvrRsrceDeluxe_t;

typedef struct TsrvDrvrResInfoDeluxe_t {
    unsigned int    count;
    TsrvDrvrRsrceDeluxe_t *drvrResInfo;
} TsrvDrvrResInfoDeluxe_t;

typedef struct TsrvGetDrvrResDeluxeConfEvent_t {
    long            numLeft;
    TsrvDrvrResInfoDeluxe_t drvInfo;
} TsrvGetDrvrResDeluxeConfEvent_t;

typedef struct TsrvSetDrvrFlow_t {
    DriverName_t    drvrAdvName;
    short           flowControl;
} TsrvSetDrvrFlow_t;

typedef struct TsrvSetDrvrFlowConfEvent_t {
    Nulltype        null;
} TsrvSetDrvrFlowConfEvent_t;

typedef struct TsrvResetDrvrMaxFlow_t {
    DriverName_t    drvrAdvName;
} TsrvResetDrvrMaxFlow_t;

typedef struct TsrvResetDrvrMaxFlowConfEvent_t {
    Nulltype        null;
} TsrvResetDrvrMaxFlowConfEvent_t;


extern void * const toam_asn_tbl;    /* encoder-decoder control table */
#endif /* OSS_toam_asn_tbl */
