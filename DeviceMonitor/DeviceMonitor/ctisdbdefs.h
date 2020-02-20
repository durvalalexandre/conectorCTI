/*************************************************************/
/* Copyright (C) 2006 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/* Generated for: Avaya Inc., Lincroft, NJ - license 7175 for Windows */
/* Abstract syntax: sdb_asn_tbl */
/* Created: Wed Feb 15 18:14:13 2006 */
/* ASN.1 compiler version: 6.1.1 */
/* Code generated for runtime version 6.1 or later */
/* Target operating system: Windows NT/Windows 9x */
/* Target machine type: Intel x86 */
/* C compiler options required: -Zp8 (Microsoft) */
/* ASN.1 compiler options and file names specified:
 * -controlfile sdbdefs.c -headerfile ctisdbdefs.h -noshortennames -nouniquepdu
 * -externalname sdb_asn_tbl -noconstraints -charintegers -compat v4.1.1
 * -compat v4.1.2 -compat v4.1.3 -compat v4.1.4 -compat v4.1.5 -compat v4.1.6
 * -compat v4.1.7 -compat v4.1.8
 * v:\ossasn1\win32\6.1.0\asn1dflt\asn1dflt.ms.zp8 sdb
 */

#ifndef OSS_sdb_asn_tbl
#define OSS_sdb_asn_tbl

#include "asn1hdr.h"
#include "asn1code.h"

#ifndef OSS_INT32
#define OSS_INT32 int
#endif /* OSS_INT32 */

#define          SDBOpenConnection_t_PDU 1
#define          SDBOpenConnConfEvent_t_PDU 2
#define          SDBCloseConnection_t_PDU 3
#define          SDBCloseConnConfEvent_t_PDU 4
#define          SDBInsertObject_t_PDU 5
#define          SDBInsertObjectConfEvent_t_PDU 6
#define          SDBInsertAttribute_t_PDU 7
#define          SDBInsertAttributeConfEvent_t_PDU 8
#define          SDBDeleteObject_t_PDU 9
#define          SDBDeleteObjectConfEvent_t_PDU 10
#define          SDBDeleteAttribute_t_PDU 11
#define          SDBDeleteAttributeConfEvent_t_PDU 12
#define          SDBSelectObject_t_PDU 13
#define          SDBSelectObjectConfEvent_t_PDU 14
#define          SDBOpenCursor_t_PDU 15
#define          SDBOpenCursorConfEvent_t_PDU 16
#define          SDBFetchCursor_t_PDU 17
#define          SDBFetchCursorConfEvent_t_PDU 18
#define          SDBCloseCursor_t_PDU 19
#define          SDBCloseCursorConfEvent_t_PDU 20
#define          SDBModifyObject_t_PDU 21
#define          SDBModifyObjectConfEvent_t_PDU 22
#define          SDBStartTrans_t_PDU 23
#define          SDBStartTransConfEvent_t_PDU 24
#define          SDBCommitTrans_t_PDU 25
#define          SDBCommitTransConfEvent_t_PDU 26
#define          SDBRollbackTrans_t_PDU 27
#define          SDBRollbackTransConfEvent_t_PDU 28
#define          SDBBackupDataBase_t_PDU 29
#define          SDBBackupDataBaseConfEvent_t_PDU 30
#define          SDBUpdateDataBase_t_PDU 31
#define          SDBUpdateDataBaseConfEvent_t_PDU 32
#define          SDBCreateTemplate_t_PDU 33
#define          SDBCreateTemplateConfEvent_t_PDU 34
#define          SDBQueryVersions_t_PDU 35
#define          SDBQueryVersionsConfEvent_t_PDU 36
#define          SDBQueryFiles_t_PDU 37
#define          SDBQueryFilesConfEvent_t_PDU 38
#define          SDBQueryAttributes_t_PDU 39
#define          SDBQueryAttributesConfEvent_t_PDU 40
#define          SDBQueryStatus_t_PDU 41
#define          SDBQueryStatusConfEvent_t_PDU 42
#define          SDBUniversalFailureConfEvent_t_PDU 43
#define          SDBUniversalFailureEvent_t_PDU 44
#define          SDBSelectKey_t_PDU 45
#define          SDBSelectKeyConfEvent_t_PDU 46
#define          SDBConvertDataBase_t_PDU 47
#define          SDBConvertDataBaseConfEvent_t_PDU 48
#define          SDBBackupNdsDataBase_t_PDU 49
#define          SDBBackupNdsDataBaseConfEvent_t_PDU 50
#define          SDBUpdateNdsDataBase_t_PDU 51
#define          SDBUpdateNdsDataBaseConfEvent_t_PDU 52
#define          SDBSetSdbLogOptions_t_PDU 53
#define          SDBSetSdbLogOptionsConfEvent_t_PDU 54
#define          SDBGetSdbLogOptions_t_PDU 55
#define          SDBGetSdbLogOptionsConfEvent_t_PDU 56
#define          SDBGetConnections_t_PDU 57
#define          SDBGetConnectionsConfEvent_t_PDU 58
#define          SDBGetAboutInfo_t_PDU 59
#define          SDBGetAboutConfEvent_t_PDU 60
#define          SDBGetAdminInfo_t_PDU 61
#define          SDBGetAdminInfoConfEvent_t_PDU 62
#define          SDBSetAdminInfo_t_PDU 63
#define          SDBSetAdminInfoConfEvent_t_PDU 64
#define          SDBGetTcpInfo_t_PDU 65
#define          SDBGetTcpInfoConfEvent_t_PDU 66
#define          SDBSetTcpInfo_t_PDU 67
#define          SDBSetTcpInfoConfEvent_t_PDU 68

typedef char            SDBContext_t[512];

typedef char            SDBVersion_t[22];

typedef char            SDBBtrvVersion_t[8];

typedef enum SDBIPNameFormat_t {
    sdbIpHostName = 1,
    sdbIpAddress = 2
} SDBIPNameFormat_t;

typedef unsigned int    SDBFileType_t;
#define                     sdbOrg 0x40000000
#define                     sdbOrgunit 0x20000000
#define                     sdbSimple 0x10000000
#define                     sdbIndex 0x00000800
#define                     sdbOamlistIndex 0x00000400
#define                     sdbTlistIndex 0x00000200
#define                     sdbDlistIndex 0x00000100
#define                     sdbTserv 0x00000080
#define                     sdbOamlist 0x00000040
#define                     sdbTlist 0x00000020
#define                     sdbTlink 0x00000010
#define                     sdbDlist 0x00000008
#define                     sdbDevice 0x00000004
#define                     sdbWorktop 0x00000002
#define                     sdbUser 0x00000001

typedef enum SDBAttributeID_t {
    nullAttr = 0,
    login = 100,
    userName = 101,
    userWktp = 102,
    devDevList = 103,
    callDevList = 104,
    callCall = 105,
    callCtlList = 106,
    routingList = 107,
    oamList = 108,
    superAdminUser = 109,
    aclUser = 110,
    wktpName = 200,
    wktpDevice = 201,
    ipxLanAddr = 202,
    ipLanAddr = 203,
    ipName = 204,
    wktpDlist = 205,
    aclWktp = 206,
    wktpIndex = 207,
    deviceId = 300,
    dbDeviceType = 301,
    deviceTlist = 302,
    location = 303,
    telephoneNo = 304,
    aclDevice = 305,
    deviceIndex = 306,
    dlistName = 400,
    exceptList = 401,
    dlistDevice = 402,
    aclDlist = 403,
    dlistIndex = 404,
    dlstIndx = 490,
    devIndx = 491,
    dlstComb = 492,
    tlinkName = 500,
    serviceType = 510,
    tlinkIndex = 526,
    tlistName = 600,
    tlistLinknm = 601,
    aclTlist = 602,
    tlistIndex = 603,
    tlstIndx = 690,
    tlnkIndx = 691,
    tlistComb = 692,
    oamlistName = 700,
    oamlistLinknm = 701,
    aclOamlist = 702,
    oamlistIndex = 703,
    oamlstIndx = 790,
    oamlnkIndx = 791,
    oamlistComb = 792,
    orgName = 900,
    aclOrg = 901,
    orgunitName = 910,
    aclOrgunit = 911
} SDBAttributeID_t;

typedef char            SDBFileName_t[22];

typedef SDBFileName_t   SDBFlatFileName_t;

typedef SDBFileName_t   SDBSimpleFileName_t;

typedef SDBFileName_t   SDBErrorFileName_t;

typedef short           SDBConnectionID_t;

typedef short           SDBAttrDataLength_t;

typedef char            SDBComments_t[256];

typedef char            SDBLogPath_t[256];

typedef char            SDBAttributeName_t[22];

typedef char            SDBLoginName_t[49];

typedef short           SDBBufferSize_t;

typedef short           SDBConnectCount_t;

typedef short           SDBFileReadCount_t;

typedef int             SDBMemoryUsed_t;

typedef short           SDBReturnedCount_t;

typedef unsigned char   SDBDriverType_t;
#define                     sdbBtrieve 0x40
#define                     sdbNds 0x20

typedef enum SDBRetrievalStatus_t {
    sdbRetSuccess = 0,
    sdbRetMoreData = 1,
    sdbRetEndOfFile = 2
} SDBRetrievalStatus_t;

typedef enum SDBDriverState_t {
    sdbNormal = 1,
    sdbInitialized = 2,
    sdbInconsistent = 3,
    sdbUninitialized = 4,
    sdbOldDatabase = 5,
    sdbSickDbEngine = 6,
    sdbUnloading = 7
} SDBDriverState_t;

typedef enum SDBAttrDataType_t {
    sdbShort = 100,
    sdbLong = 200,
    sdbStr = 300,
    sdbBool = 400,
    sdbStrDn = 500,
    sdbIpx = 600,
    sdbIp = 700,
    sdbAcl = 800,
    sdbPhone = 900
} SDBAttrDataType_t;

typedef short           SDBBulkAddIgnore_t;

typedef short           SDBMultiValOpt_t;

typedef short           SDBPrimaryKeyOpt_t;

typedef short           SDBQueryFlg_t;

typedef char            *SDBAttrVariable_t;

typedef struct SDBAttrHdr_t {
    SDBAttributeID_t attrID;
    SDBAttrVariable_t attrDesc;
} SDBAttrHdr_t;

typedef struct SDBAttributeList_t {
    unsigned int    count;
    SDBAttrHdr_t    *sdbAttrHdr;
} SDBAttributeList_t;

typedef SDBAttributeList_t SDBKeyList_t;

typedef struct SDBSelectAttrList_t {
    unsigned int    count;
    int             *value;
} SDBSelectAttrList_t;

typedef struct SDBFileHdr_t {
    SDBFileType_t   fileType;
    SDBFileName_t   fileName;
} SDBFileHdr_t;

typedef struct SDBFileList_t {
    unsigned int    count;
    SDBFileHdr_t    *sdbFileHdr;
} SDBFileList_t;

typedef struct SDBQryAttr_t {
    SDBAttributeID_t attrID;
    SDBAttributeName_t attrName;
    SDBAttributeID_t rootID;
    SDBAttrDataLength_t dataLen;
    SDBAttrDataType_t dataType;
    SDBPrimaryKeyOpt_t primaryKey;
    SDBMultiValOpt_t multiVal;
    SDBBulkAddIgnore_t baIgnore;
    SDBQueryFlg_t   flag1;
    SDBQueryFlg_t   flag2;
} SDBQryAttr_t;

typedef struct SDBQryAttrList_t {
    unsigned int    count;
    SDBQryAttr_t    *sdbQryAttr;
} SDBQryAttrList_t;

typedef enum SDBSelectOpcodes_t {
    sdbGetAll = 1,
    sdbGetEqual = 2,
    sdbExtGetEqual = 3,
    sdbGetGroup = 4,
    sdbExtGetGroup = 5
} SDBSelectOpcodes_t;

typedef enum SDBFailureCodes_t {
    sdbCorruptDictnry = 501,
    sdbBadIndexFile = 502,
    sdbMissingDictionary = 503,
    sdbInvalidState = 504,
    sdbInvalidAttributeType = 505,
    sdbTooManyAttributes = 506,
    sdbInvalidFileType = 507,
    sdbAttrNotInFile = 508,
    sdbInvalidCommand = 509,
    sdbRecordNotFound = 510,
    sdbDatabaseError = 511,
    sdbInconsistentDatabase = 512,
    sdbInternalErr = 513,
    sdbConnectionTableFull = 514,
    sdbInvalidConnectionId = 515,
    sdbConnectionNotActive = 516,
    sdbInvalidContext = 517,
    sdbLoginTableFull = 518,
    sdbFailedLogin = 519,
    sdbNoPermissions = 520,
    sdbInvalidData = 521,
    sdbMissingPrimaryKey = 522,
    sdbMandatoryAttributeMissing = 523,
    sdbInvalidPrimaryKey = 524,
    sdbInvalidKey = 525,
    sdbDuplicateKey = 526,
    sdbMultiValAttr = 527,
    sdbNotMultiValued = 528,
    sdbInvalidListFile = 529,
    sdbCursorNotActive = 530,
    sdbCursorSelectionNotSet = 531,
    sdbInvalidCursorOp = 532,
    sdbCursorAlreadyActive = 533,
    sdbCursorActive = 534,
    sdbObjectNotAccessed = 535,
    sdbContention = 536,
    sdbNoMoreDiskSpace = 537,
    sdbNoMemory = 538,
    sdbMaxOpenFilesExceeded = 539,
    sdbNoActiveTransaction = 540,
    sdbTransactionAlreadyActive = 541,
    sdbTransactionError = 542,
    sdbTransactionAborted = 543,
    sdbInvalidOpcode = 544,
    sdbInvalidRtnCnt = 545,
    sdbBufTooSmall = 546,
    sdbKeySpecification = 547,
    sdbAttrOverMax = 548,
    sdbAttrUnderMin = 549,
    sdbDataTooLarge = 550,
    sdbDotInKey = 551,
    sdbWriteFailed = 552,
    sdbReadFailure = 553,
    sdbFileNotPresent = 554,
    sdbNoInform1Line = 555,
    sdbInvalidAttrList = 556,
    sdbInvalidKeyList = 557,
    sdbInvalidSelectList = 558,
    sdbForeignKey = 559,
    sdbOldDictionaryFailure = 560,
    sdbUpgradeErr = 561,
    sdbFileAlreadyExists = 562,
    sdbOpenSdbLogFailed = 563,
    sdbWriteSdbLogFailed = 564,
    sdbFileOpenFailure = 565,
    sdbQueryVersFailed = 566,
    sdbBaBackupFailed = 567,
    sdbSimpleUpdateFailed = 568,
    sdbQryFilesFailed = 569,
    sdbQryAttrFailed = 570,
    sdbInvalidInputLine = 571,
    sdbCreateTmpltFailed = 572,
    sdbFlatUpdateFailed = 573,
    sdbCantModifyMvattr = 574,
    sdbDuplicateFileNames = 575,
    sdbInvalidVendorLen = 576,
    sdbInvalidServiceLen = 577,
    sdbInvalidSrvType = 578,
    sdbInvalidSrvNameLen = 579,
    sdbAllocResourceErr = 580,
    sdbInitTsrvPasswdErr = 581,
    sdbGetTsrvDefaultErr = 582,
    sdbTsrvLoaded = 583,
    sdbSchemaChangeErr = 584,
    sdbMustBeCsta = 585,
    sdbInvalidFileNm = 586,
    sdbInvalidFileFormat = 587,
    sdbLastAdminUser = 588,
    sdbMixedVersionNumbers = 589,
    sdbLastErr = 599
} SDBFailureCodes_t;

typedef unsigned char   SDBOptions_t;
#define                     sdbNonFatal 0x40
#define                     sdbOverwrite 0x20
#define                     sdbConvertSimple 0x10
#define                     sdbConvertFlat 0x08

typedef unsigned char   SDBConvertOptions_t;
#define                     btrvToNds 0x40
#define                     btrvToUnix 0x20

typedef struct SDBOpenConnection_t {
    SDBContext_t    context;
    SDBLoginName_t  login;
} SDBOpenConnection_t;

typedef struct SDBOpenConnConfEvent_t {
    SDBConnectionID_t connID;
    SDBContext_t    context;
} SDBOpenConnConfEvent_t;

typedef struct SDBCloseConnection_t {
    SDBConnectionID_t connID;
} SDBCloseConnection_t;

typedef struct SDBCloseConnConfEvent_t {
    Nulltype        null;
} SDBCloseConnConfEvent_t;

typedef struct SDBInsertObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t *attrList;
} SDBInsertObject_t;

typedef struct SDBInsertObjectConfEvent_t {
    Nulltype        null;
} SDBInsertObjectConfEvent_t;

typedef struct SDBInsertAttribute_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t *keyList;
    struct SDBAttributeList_t *attrList;
} SDBInsertAttribute_t;

typedef struct SDBInsertAttributeConfEvent_t {
    Nulltype        null;
} SDBInsertAttributeConfEvent_t;

typedef struct SDBDeleteObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t *keyList;
} SDBDeleteObject_t;

typedef struct SDBDeleteObjectConfEvent_t {
    Nulltype        null;
} SDBDeleteObjectConfEvent_t;

typedef struct SDBDeleteAttribute_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t *keyList;
    struct SDBAttributeList_t *attrList;
} SDBDeleteAttribute_t;

typedef struct SDBDeleteAttributeConfEvent_t {
    Nulltype        null;
} SDBDeleteAttributeConfEvent_t;

typedef struct SDBSelectObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t *keyList;
    SDBSelectOpcodes_t opcode;
    struct SDBSelectAttrList_t *attrList;
    SDBBufferSize_t bufSize;
    SDBReturnedCount_t retrnCnt;
} SDBSelectObject_t;

typedef struct SDBSelectObjectConfEvent_t {
    struct SDBAttributeList_t *attrList;
    SDBReturnedCount_t retrnCnt;
    SDBRetrievalStatus_t status;
} SDBSelectObjectConfEvent_t;

typedef struct SDBOpenCursor_t {
    SDBConnectionID_t connID;
} SDBOpenCursor_t;

typedef struct SDBOpenCursorConfEvent_t {
    Nulltype        null;
} SDBOpenCursorConfEvent_t;

typedef struct SDBFetchCursor_t {
    SDBConnectionID_t connID;
    SDBBufferSize_t bufSize;
    SDBReturnedCount_t retrnCnt;
} SDBFetchCursor_t;

typedef struct SDBFetchCursorConfEvent_t {
    struct SDBAttributeList_t *attrList;
    SDBReturnedCount_t retrnCnt;
    SDBRetrievalStatus_t status;
} SDBFetchCursorConfEvent_t;

typedef struct SDBCloseCursor_t {
    SDBConnectionID_t connID;
} SDBCloseCursor_t;

typedef struct SDBCloseCursorConfEvent_t {
    Nulltype        null;
} SDBCloseCursorConfEvent_t;

typedef struct SDBModifyObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t *keyList;
    struct SDBAttributeList_t *attrList;
} SDBModifyObject_t;

typedef struct SDBModifyObjectConfEvent_t {
    Nulltype        null;
} SDBModifyObjectConfEvent_t;

typedef struct SDBStartTrans_t {
    SDBConnectionID_t connID;
} SDBStartTrans_t;

typedef struct SDBStartTransConfEvent_t {
    Nulltype        null;
} SDBStartTransConfEvent_t;

typedef struct SDBCommitTrans_t {
    SDBConnectionID_t connID;
} SDBCommitTrans_t;

typedef struct SDBCommitTransConfEvent_t {
    Nulltype        null;
} SDBCommitTransConfEvent_t;

typedef struct SDBRollbackTrans_t {
    SDBConnectionID_t connID;
} SDBRollbackTrans_t;

typedef struct SDBRollbackTransConfEvent_t {
    Nulltype        null;
} SDBRollbackTransConfEvent_t;

typedef struct SDBBackupDataBase_t {
    SDBFileName_t   fileNm;
    SDBComments_t   comments;
} SDBBackupDataBase_t;

typedef struct SDBBackupDataBaseConfEvent_t {
    Nulltype        null;
} SDBBackupDataBaseConfEvent_t;

typedef struct SDBUpdateDataBase_t {
    SDBFlatFileName_t flatFile;
    SDBSimpleFileName_t simpleFile;
    SDBErrorFileName_t errorFile;
    SDBOptions_t    options;
} SDBUpdateDataBase_t;

typedef struct SDBUpdateDataBaseConfEvent_t {
    Nulltype        null;
} SDBUpdateDataBaseConfEvent_t;

typedef struct SDBCreateTemplate_t {
    SDBFlatFileName_t flatFile;
    SDBSimpleFileName_t simpleFile;
} SDBCreateTemplate_t;

typedef struct SDBCreateTemplateConfEvent_t {
    Nulltype        null;
} SDBCreateTemplateConfEvent_t;

typedef struct SDBQueryVersions_t {
    Nulltype        null;
} SDBQueryVersions_t;

typedef struct SDBQueryVersionsConfEvent_t {
    SDBVersion_t    dataDictionaryVersion;
    SDBVersion_t    oldDictionaryVersion;
    SDBVersion_t    overallVersion;
    SDBVersion_t    userVersion;
    SDBVersion_t    worktopVersion;
    SDBVersion_t    deviceVersion;
    SDBVersion_t    dlistVersion;
    SDBVersion_t    tlinkVersion;
    SDBVersion_t    tlistVersion;
    SDBVersion_t    oamlistVersion;
    SDBVersion_t    tservVersion;
    SDBDriverType_t driverType;
    SDBVersion_t    driverVersion;
    SDBVersion_t    tsrvnlmVersion;
    SDBDriverState_t driverState;
    SDBBtrvVersion_t btrvVersion;
} SDBQueryVersionsConfEvent_t;

typedef struct SDBQueryFiles_t {
    SDBBufferSize_t bufSize;
} SDBQueryFiles_t;

typedef struct SDBQueryFilesConfEvent_t {
    struct SDBFileList_t *fileList;
} SDBQueryFilesConfEvent_t;

typedef struct SDBQueryAttributes_t {
    SDBFileType_t   fileType;
    SDBBufferSize_t bufSize;
    SDBReturnedCount_t retrnCnt;
} SDBQueryAttributes_t;

typedef struct SDBQueryAttributesConfEvent_t {
    struct SDBQryAttrList_t *attrList;
    SDBReturnedCount_t retrnCnt;
    SDBRetrievalStatus_t status;
} SDBQueryAttributesConfEvent_t;

typedef struct SDBFileReadList_t {
    unsigned int    count;
    SDBFileReadCount_t *sdbFileRd;
} SDBFileReadList_t;

typedef struct SDBQueryStatus_t {
    Nulltype        null;
} SDBQueryStatus_t;

typedef struct SDBQueryStatusConfEvent_t {
    SDBConnectCount_t sdbConns;
    SDBMemoryUsed_t memUsed;
    SDBFileReadList_t fileRd;
} SDBQueryStatusConfEvent_t;

typedef struct SDBUniversalFailureConfEvent_t {
    SDBFailureCodes_t error;
    SDBAttributeID_t attrID;
} SDBUniversalFailureConfEvent_t;

typedef struct SDBUniversalFailureEvent_t {
    SDBFailureCodes_t error;
} SDBUniversalFailureEvent_t;

typedef struct SDBSelectKey_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    SDBAttributeID_t key;
    SDBAttrHdr_t    filter;
    SDBBufferSize_t bufSize;
} SDBSelectKey_t;

typedef struct SDBSelectKeyConfEvent_t {
    SDBRetrievalStatus_t status;
    struct {
        unsigned short  length;
        unsigned char   *value;
    } keyList;
} SDBSelectKeyConfEvent_t;

typedef struct SDBConvertDataBase_t {
    SDBFlatFileName_t flatFile;
    SDBFlatFileName_t finalFile;
    SDBErrorFileName_t errorFile;
    SDBConvertOptions_t options;
    SDBContext_t    context;
} SDBConvertDataBase_t;

typedef struct SDBConvertDataBaseConfEvent_t {
    Nulltype        null;
} SDBConvertDataBaseConfEvent_t;

typedef struct SDBBackupNdsDataBase_t {
    SDBFileName_t   fileNm;
    SDBComments_t   comments;
    SDBContext_t    context;
} SDBBackupNdsDataBase_t;

typedef struct SDBBackupNdsDataBaseConfEvent_t {
    Nulltype        null;
} SDBBackupNdsDataBaseConfEvent_t;

typedef struct SDBUpdateNdsDataBase_t {
    SDBFlatFileName_t flatFile;
    SDBSimpleFileName_t simpleFile;
    SDBErrorFileName_t errorFile;
    SDBOptions_t    options;
    SDBContext_t    context;
} SDBUpdateNdsDataBase_t;

typedef struct SDBUpdateNdsDataBaseConfEvent_t {
    Nulltype        null;
} SDBUpdateNdsDataBaseConfEvent_t;

typedef struct SDBSetSdbLogOptions_t {
    ossBoolean      logSdbChanges;
    SDBLogPath_t    logPath;
    long            sdbLogSize;
} SDBSetSdbLogOptions_t;

typedef struct SDBSetSdbLogOptionsConfEvent_t {
    Nulltype        null;
} SDBSetSdbLogOptionsConfEvent_t;

typedef struct SDBGetSdbLogOptions_t {
    Nulltype        null;
} SDBGetSdbLogOptions_t;

typedef struct SDBGetSdbLogOptionsConfEvent_t {
    ossBoolean      logSdbChanges;
    SDBLogPath_t    logPath;
    long            sdbLogSize;
} SDBGetSdbLogOptionsConfEvent_t;

typedef struct SDBGetConnections_t {
    Nulltype        null;
} SDBGetConnections_t;

typedef struct SDBGetConnectionsConfEvent_t {
    long            sdbConns;
} SDBGetConnectionsConfEvent_t;

typedef char            SDBAboutString[41];

typedef struct SDBGetAboutInfo_t {
    Nulltype        null;
} SDBGetAboutInfo_t;

typedef struct SDBGetAbout_t {
    SDBVersion_t    aboutVer;
    SDBAboutString  aboutString;
} SDBGetAbout_t;

typedef struct SDBGetAboutList_t {
    unsigned int    count;
    SDBGetAbout_t   *aboutList;
} SDBGetAboutList_t;

typedef struct SDBGetAboutConfEvent_t {
    long            numLeft;
    SDBGetAboutList_t aboutInfo;
} SDBGetAboutConfEvent_t;

typedef struct SDBGetAdminInfo_t {
    Nulltype        null;
} SDBGetAdminInfo_t;

typedef struct SDBGetAdminInfoConfEvent_t {
    ossBoolean      workStation;
    ossBoolean      autoAdmin;
} SDBGetAdminInfoConfEvent_t;

typedef struct SDBSetAdminInfo_t {
    ossBoolean      workStation;
    ossBoolean      autoAdmin;
} SDBSetAdminInfo_t;

typedef struct SDBSetAdminInfoConfEvent_t {
    Nulltype        null;
} SDBSetAdminInfoConfEvent_t;

typedef struct SDBGetTcpInfo_t {
    Nulltype        null;
} SDBGetTcpInfo_t;

typedef struct SDBGetTcpInfoConfEvent_t {
    SDBIPNameFormat_t tcpNameFormat;
} SDBGetTcpInfoConfEvent_t;

typedef struct SDBSetTcpInfo_t {
    SDBIPNameFormat_t tcpNameFormat;
} SDBSetTcpInfo_t;

typedef struct SDBSetTcpInfoConfEvent_t {
    Nulltype        null;
} SDBSetTcpInfoConfEvent_t;


extern void * const sdb_asn_tbl;    /* encoder-decoder control table */
#endif /* OSS_sdb_asn_tbl */
