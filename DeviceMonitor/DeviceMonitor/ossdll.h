/***************************************************************************
 * Copyright (C) 1993-2003 OSS Nokalva, Inc.  All rights reserved.
 ***************************************************************************/
/*
 *  THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 *  AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 *  THIS FILE MAY NOT BE DISTRIBUTED.
 ***************************************************************************
 * FILE: @(#)ossdll.h	12.24.1.4  03/06/24
 */


#ifndef OSSDLL_H
#define OSSDLL_H
#include <stdarg.h>
#include "asn1hdr.h"

typedef enum  {
    OSS_BER = 0,
    OSS_PER_ALIGNED,
    OSS_PER_UNALIGNED,
    OSS_DER,
    OSS_ECN,
    OSS_XER,
    OSS_CXER,
    OSS_CER
} ossEncodingRules;

#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32))
#pragma pack(push, ossPacking, 4)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack(1)
#elif defined(__BORLANDC__) && defined(__MSDOS__)
#ifdef _BC31
#pragma option -a-
#else
#pragma option -a1
#endif /* _BC31 */
#elif defined(__BORLANDC__) && defined(__WIN32__)
#pragma option -a4
#elif defined(__IBMC__) && (defined(__WIN32__) || defined(__OS2__))
#pragma pack(4)
#elif defined(__WATCOMC__) && defined(__NT__)
#pragma pack(push, 4)
#elif defined(__WATCOMC__) && (defined(__WINDOWS__) || defined(__DOS__))
#pragma pack(push, 1)
#endif /* _MSC_VER && _WIN32 */

#if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || \
    defined(__WIN32__) || defined(__OS2__)  || defined(NETWARE_DLL)
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#if !defined(__OS2__) && !defined(NETWARE_DLL) && !defined(WIN32_SIMPLE) && !defined(_NTSDK)
	/*
	 * Borland C++ does not allow windows.h #included
	 * within extern "C" {...}.
	 */
#if defined(__BORLANDC__)? !defined(__cplusplus): 1
#include <windows.h>
#endif /* __BORLANDC__? !__cplusplus: 1 */
#endif /* !__OS2__ && !NETWARE_DLL && !WIN32_SIMPLE */
#ifndef DLL_ENTRY
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
#ifdef __BORLANDC__
#define PUBLIC
#define DLL_ENTRY      __stdcall
#define DLL_ENTRY_FDEF __stdcall
#define DLL_ENTRY_FPTR __stdcall
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA  __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#ifdef __cplusplus
typedef void *         HINSTANCE;
typedef void *         HWND;
typedef int            BOOL;
typedef long           LONG;
#endif /* __cplusplus */
#elif defined(__IBMC__)
#define PUBLIC
#define DLL_ENTRY      WINAPI
#define DLL_ENTRY_FDEF WINAPI __export
#define DLL_ENTRY_FPTR WINAPI
#elif defined(__WATCOMC__)
#define PUBLIC
#define DLL_ENTRY      WINAPI __export
#define DLL_ENTRY_FDEF WINAPI __export
#define DLL_ENTRY_FPTR WINAPI __export
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA  __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#elif defined(_NTSDK)
typedef int            BOOL;
typedef void *         HWND;
typedef void *         HINSTANCE;
typedef long           LONG;
#define PUBLIC         __declspec(dllexport)
#define DLL_ENTRY
#define DLL_ENTRY_FDEF
#define DLL_ENTRY_FPTR
#else
#ifdef WIN32_SIMPLE
#include <ril.h>
typedef void *         HWND;
typedef void *         HINSTANCE;
typedef long           LONG;
#define WINAPI __stdcall
#undef PUBLIC
#endif /* WIN32_SIMPLE */
#if defined(__cplusplus) && defined(_DLL) && !defined(ONE_DLL)
#define PUBLIC         __declspec(dllexport)
#else
#define PUBLIC
#endif /* __cplusplus && _DLL && !ONE_DLL */
#define DLL_ENTRY      WINAPI
#define DLL_ENTRY_FDEF WINAPI
#define DLL_ENTRY_FPTR WINAPI
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#endif /* __BORLANDC__ */
#define _System
#elif defined(_WINDOWS)
#define PUBLIC
#ifdef DPMI_DLL
#define DLL_ENTRY      FAR PASCAL __export
#define DLL_ENTRY_FDEF FAR PASCAL __export
#define DLL_ENTRY_FPTR FAR PASCAL __export
#else
#define DLL_ENTRY      far pascal _export
#define DLL_ENTRY_FDEF far pascal _export
#define DLL_ENTRY_FPTR far pascal _export
#endif /* DPMI_DLL */
#define _System
#elif defined(__OS2__)
#define PUBLIC
#define DLL_ENTRY      _System
#define DLL_ENTRY_FDEF _Export _System
#define DLL_ENTRY_FPTR
#include <os2def.h>
#define LONG long
#define DWORD unsigned long
#define HINSTANCE unsigned long
#ifndef OSS_EXPORT_DLL_DATA
#define OSS_EXPORT_DLL_DATA __declspec(dllexport)
#endif /* OSS_EXPORT_DLL_DATA */
#elif defined(NETWARE_DLL)
#define PUBLIC
#define DLL_ENTRY
#define DLL_ENTRY_FDEF
#define DLL_ENTRY_FPTR
#define _Export
#undef _System
#define _System
#define LONG unsigned long
#define HWND int
#define DWORD LONG
#define BOOL char
#define HINSTANCE LONG
#endif /* _WIN32 || WIN32 || __WIN32__ */
#endif /* DLL_ENTRY */

/*
 * The DLL_LINKAGE is #defined if and only if the OSS DLLs are used
 * when linking with ossapi.lib (SOED) or ossapit.lib (TOED).
 */
#ifdef DLL_LINKAGE
#undef DLL_LINKAGE
#endif /* DLL_LINKAGE */

#if ((defined(_DLL)? !defined(ONE_DLL): 0) || defined(OS2_DLL) \
		|| defined(NETWARE_DLL)) && !defined(WIN32_DRIVER)
#define DLL_LINKAGE
#endif /* (_DLL || OS2_DLL || NETWARE_DLL) && !WIN32_DRIVER */

#define BUFFERSIZE 1024
			/*
			 * NUMBER_OF_LINES_IN_BLOCK is the number of
			 * 4-byte offsets in a block of memory allocated
			 * at a time.  Each offset corresponds to a line
			 * of a text file to be displayed in a window.
			 */
#define NUMBER_OF_LINES_IN_BLOCK 200

#if defined(macintosh) && defined(__CFM68K__)
#pragma import on
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct memblock {
    struct memblock     *prev;
    struct memblock     *next;
    LONG                *fileOffset;
    short               *lineLength;
    short                blockNumber;
} MEMBLOCK;

#ifdef __alpha
#define ossArg LONG_LONG
#else
#define ossArg int
#endif /* __alpha */

typedef struct memManagerTbl {
    int			 (DLL_ENTRY_FPTR *_System ossMinitp)(void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System dopenInp)(void *,
						void **, unsigned long *);
    unsigned long	 (DLL_ENTRY_FPTR *_System dclosInp)(void *,
						void **, size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System dswapInp)(void *,
						void **, size_t *);
    void		 (DLL_ENTRY_FPTR *_System dopenOutp)(void *, void *,
						unsigned long, unsigned long);
    unsigned char	*(DLL_ENTRY_FPTR *_System dxferObjp)(void *,
						void **inn, void **out,
						size_t *, unsigned long *);
    unsigned char	*(DLL_ENTRY_FPTR *_System dxferDeferObjp)(void *,
						void **inn, void **out, size_t *,
						unsigned long *, unsigned long *);
    int			(DLL_ENTRY_FPTR *_System dxferEndp)(void *, void **out);
    unsigned long	 (DLL_ENTRY_FPTR *_System dclosOutp)(void *, void **);
    void		*(DLL_ENTRY_FPTR *_System dallcOutp)(void *, size_t,
								char root);
    void		 (DLL_ENTRY_FPTR *_System openWorkp)(void *);
    void		 (DLL_ENTRY_FPTR *_System pushHndlp)(void *, void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System popHndlp)(void *,
							void **, size_t);
    void		 (DLL_ENTRY_FPTR *_System closWorkp)(void *);
    void		*(DLL_ENTRY_FPTR *_System allcWorkp)(void *, size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System lockMemp)(void *, void *);
    void		 (DLL_ENTRY_FPTR *_System unlokMemp)(void *, void *,
								char);
    void		 (DLL_ENTRY_FPTR *_System ossFreerp)(void *, void *);
    int			 (DLL_ENTRY_FPTR *_System freePDUp)(void *, int,
							void *, void *);
    void		 (DLL_ENTRY_FPTR *_System drcovObjp)(void *, int,
							void *, void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System eopenInp)(void *, void *,
								size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System eswapInp)(void *, void *,
							void *, size_t);
    void		 (DLL_ENTRY_FPTR *_System eclosInp)(void *, void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System eopenOutp)(void *, void **,
							size_t *, char);
    unsigned char	*(DLL_ENTRY_FPTR *_System eswapOutp)(void *, void **,
							size_t, size_t *);
    unsigned char	*(DLL_ENTRY_FPTR *_System exferObjp)(void *, void **,
				void **, unsigned long *, unsigned long);
    unsigned long	 (DLL_ENTRY_FPTR *_System eclosOutp)(void *, void **,
							size_t, char);
    void		 (DLL_ENTRY_FPTR *_System ercovObjp)(void *);
    unsigned char	*(DLL_ENTRY_FPTR *_System asideBeginp)(void *,
						void **, size_t, size_t *);
    unsigned char	*(DLL_ENTRY_FPTR *_System asideSwapp)(void *,
						void **, size_t, size_t *);
    void		*(DLL_ENTRY_FPTR *_System asideEndp)(void *,
							void *, size_t);
    unsigned char	*(DLL_ENTRY_FPTR *_System setDumpp)(void *, void **,
							void *, size_t *);
    void		 (DLL_ENTRY_FPTR *_System ossSetSortp)(void *, void *,
							unsigned char);
    void		 (DLL_ENTRY_FPTR *_System freeBUFp)(void *, void *);
    unsigned char	 (DLL_ENTRY_FPTR *_System egetBytep)(void *, void *,
							unsigned long);
    void		*(DLL_ENTRY_FPTR *_System _ossMarkObjp)(void *,
								int, void *);
    void		*(DLL_ENTRY_FPTR *_System _ossUnmarkObjp)(void *,
								void *);
    void		*(DLL_ENTRY_FPTR *_System _ossGetObjp)(void *,
								void *);
    int			(DLL_ENTRY_FPTR *_System _ossTestObjp)(void *,
								void *);
    void		(DLL_ENTRY_FPTR *_System _ossFreeObjectStackp)(void *);
    void		(DLL_ENTRY_FPTR *_System ossMtermp)(void *);
    void		(DLL_ENTRY_FPTR *_System _ossSetTimeoutp)(void *, long);
    int			(DLL_ENTRY_FPTR *_System _ossGetBufferp)(void *, void *);
    int			(DLL_ENTRY_FPTR *_System _ossSetBufferp)(void *, void *);
    int			(DLL_ENTRY_FPTR *_System _ossOpenDecoderInputFilep)(void *, char *);
    int			(DLL_ENTRY_FPTR *_System _ossCloseDecoderInputFilep)(void *);
    int			(DLL_ENTRY_FPTR *_System _ossOpenEncoderOutputFilep)(void *, char *);
    int			(DLL_ENTRY_FPTR *_System _ossCloseEncoderOutputFilep)(void *);
    long		(DLL_ENTRY_FPTR *_System _ossSetMinFileSizep)(void *, long);
    long		(DLL_ENTRY_FPTR *_System _ossGetMinFileSizep)(void *);
    void		(DLL_ENTRY_FPTR *_System _ossSetUserMallocFreeReallocp)(void *,
					void *(*)(struct ossGlobal *, size_t),
					void  (*)(struct ossGlobal *, void *),
					void *(*)(struct ossGlobal *, void *, size_t));
    void		(DLL_ENTRY_FPTR *_System _ossGetUserMallocFreeReallocp)(void *,
					void *(**)(struct ossGlobal *, size_t),
					void  (**)(struct ossGlobal *, void *),
					void *(**)(struct ossGlobal *, void *, size_t));
    int			memMgrType;
} MemManagerTbl;

#define osswinit ossWinit
#ifndef __IBMC__
PUBLIC int       DLL_ENTRY ossOpenTraceWindow(struct ossGlobal *);
void                      *getStartAddress(struct ossGlobal *, char *);
void            *DLL_ENTRY ossGetHeader(void);
int                        ossWriteWindow(struct ossGlobal *, HWND);
PUBLIC int       DLL_ENTRY ossPrintWin(struct ossGlobal *, const char *,
			ossArg, ossArg, ossArg, ossArg, ossArg, ossArg,
					ossArg, ossArg, ossArg, ossArg);
PUBLIC int       DLL_ENTRY ossReadLine(struct ossGlobal *, HWND, FILE *,
						char *, MEMBLOCK *, LONG);
PUBLIC int       DLL_ENTRY ossVprintWin(struct ossGlobal *, const char *,
			va_list ap);
PUBLIC void      DLL_ENTRY ossFreeList(struct ossGlobal *);
PUBLIC void      DLL_ENTRY ossSaveTraceInfo(struct ossGlobal *, HWND, char *);
PUBLIC void      DLL_ENTRY ossWterm(struct ossGlobal *);
PUBLIC HINSTANCE DLL_ENTRY ossLoadMemoryManager(struct ossGlobal *, int, char *);
PUBLIC int       DLL_ENTRY ossWinit(struct ossGlobal *, void *, char *, HWND);
int              DLL_ENTRY oss_test(struct ossGlobal *);
int                        ossGeneric(struct ossGlobal *, HWND);
extern const int           ossEncoderDecoderType;
extern HINSTANCE DLL_ENTRY ossLoadDll(struct ossGlobal *, char *);

	/*
	 * The following two functions are used by the memory manager &
	 * tracing routine DLL as low level memory allocator and freer
	 * replacing the default--which is malloc() and free()--in the
	 * sample tests.  See ossgnrc.c for more information.
	 */
extern void *DLL_ENTRY getmem(size_t);
extern void  DLL_ENTRY rlsmem(void *);
extern HINSTANCE hInst;
#endif /* !__IBMC__ */
#else
	/*
	 * Mappings and definitions provided for compatibility for other
	 * platforms.
	 */
#ifndef __IBMC__
#define osswinit(world, ctl_tbl, dll_name, hwnd) ossinit(world, ctl_tbl)
#define ossWinit(world, ctl_tbl, dll_name, hwnd) ossinit(world, ctl_tbl)
#define ossWterm(world) ossterm(world)
#endif /* !__IBMC__ */
#endif /* _WINDOWS ||_WIN32 || WIN32 || __WIN32__ || __OS2__ || NETWARE_DLL */


#if defined(_WINDOWS) || defined(_WIN32) || \
    defined(__OS2__)  || defined(NETWARE_DLL)


typedef struct cstrainTbl {
    int  (DLL_ENTRY_FPTR *_System ossConstrainp)(void *, int, void *, void *);
} CstrainTbl;

typedef struct berTbl {
    int   (DLL_ENTRY_FPTR *_System ossBerEncodep)(void *, int, void *,
				char **, long *, void *, unsigned, char *);
    int   (DLL_ENTRY_FPTR *_System ossBerDecodep)(void *, int *, char **,
			long *, void **, long *, void *, unsigned, char *);
#ifdef SOED
    int   (DLL_ENTRY_FPTR *_System ossBerEncodeOpenTypep)(void *, int,
				void *, void **, long *, void *, unsigned);
    int   (DLL_ENTRY_FPTR *_System ossBerDecodeOpenTypep)(void  *, int *, void **,
				long  *, void **, long *, void *, unsigned);
    void  (DLL_ENTRY_FPTR *_System oss_enc_errorp)(void *, int, void *); /* NOT USED */
    void  (DLL_ENTRY_FPTR *_System oss_dec_errorp)(void *, int, void *); /* NOT USED */
    long  (DLL_ENTRY_FPTR *_System oss_writetobufferp)(void *, unsigned char c);
    long  (DLL_ENTRY_FPTR *_System oss_write_intp)(void *, char length, LONG_LONG);
    long  (DLL_ENTRY_FPTR *_System oss_write_valuep)(void *, unsigned long,
							unsigned char *, char);
    int   (DLL_ENTRY_FPTR *_System oss_numbitsp)(long);
    void  (DLL_ENTRY_FPTR *_System oss_fpeHandlerp)(int);
    void *(DLL_ENTRY_FPTR *_System oss_new_perm_pointed_top)(void *, void *,
							size_t, size_t);
    void  (DLL_ENTRY_FPTR *_System oss_release_work_spacep)(void *, void *, size_t);
    void *(DLL_ENTRY_FPTR *_System oss_copy_from_work_spacep)(void *, size_t,
					size_t suffix, void *, size_t, char);
    unsigned char (DLL_ENTRY_FPTR *_System oss_get_bytep)(void *);
    void  (DLL_ENTRY_FPTR *_System oss_set_intp)(void *, unsigned char *,
			unsigned int, LONG_LONG value, int);
    void *(DLL_ENTRY_FPTR *_System oss_reserve_work_spacep)(void *, size_t, size_t *, ossBoolean);
    long  (DLL_ENTRY_FPTR *_System oss_encode_lengthp)(void *, long);
    void  (DLL_ENTRY_FPTR *_System oss_debug_realp)(void *, char, unsigned char *, int, long);
    void  (DLL_ENTRY_FPTR *_System oss_debug_strp)(void *, unsigned char *, size_t);
    void  (DLL_ENTRY_FPTR *_System ossPrintBerValuep)(void *, void *);
#else
#define   _dstd_parms_defx char **, long *, long
#define   _sdstd_parms_defx char **, long *
#define   _std_parms_defx char **, long *, char
    LONG_LONG (DLL_ENTRY_FPTR *_System _oss_dec_llintp)     (void *, _dstd_parms_defx);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_dec_ullintp)   (void *, _dstd_parms_defx);
    char (DLL_ENTRY_FPTR *_System _oss_dec_boolp)           (void *, _dstd_parms_defx);
    int  (DLL_ENTRY_FPTR *_System _oss_dec_iintp)           (void *, _dstd_parms_defx);
    long (DLL_ENTRY_FPTR *_System _oss_count_setof_itemsp)  (void *, _dstd_parms_defx);
    long (DLL_ENTRY_FPTR *_System _oss_dec_lengthp)         (void *, _sdstd_parms_defx);
    long (DLL_ENTRY_FPTR *_System _oss_dec_lintp)           (void *, _dstd_parms_defx);
    long (DLL_ENTRY_FPTR *_System _oss_encd_aiobjidp)       (void *, _std_parms_defx, void *, short);
    long (DLL_ENTRY_FPTR *_System _oss_encd_alobjidp)       (void *, _std_parms_defx, void *, short);
    long (DLL_ENTRY_FPTR *_System _oss_encd_asobjidp)       (void *, _std_parms_defx, void *, short);
    long (DLL_ENTRY_FPTR *_System _oss_encd_boolp)          (void *, _std_parms_defx, char);
    long (DLL_ENTRY_FPTR *_System _oss_encd_crealp)         (void *, _std_parms_defx, char *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_gtimep)         (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_huge_intp)      (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uhuge_intp)     (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_intp)           (void *, _std_parms_defx, LONG_LONG);
    long (DLL_ENTRY_FPTR *_System _oss_encd_lengthp)        (void *, _std_parms_defx, unsigned long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_liobjidp)       (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_llobjidp)       (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_lsobjidp)       (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_mrealp)         (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_nstrp)          (void *, _std_parms_defx, char *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_opentypep)      (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_pbitp)          (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_pstrp)          (void *, _std_parms_defx, char *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_realp)          (void *, _std_parms_defx, double);
    long (DLL_ENTRY_FPTR *_System _oss_encd_tagp)           (void *, _std_parms_defx, unsigned short, char);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uanyp)          (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ubitp)          (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uintp)          (void *, _std_parms_defx, ULONG_LONG);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uiobjidp)       (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ulobjidp)       (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uoctp)          (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_usobjidp)       (void *, _std_parms_defx, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ustrp)          (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utimep)         (void *, _std_parms_defx, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_vbitp)          (void *, _std_parms_defx, void *, long, char);
    long (DLL_ENTRY_FPTR *_System _oss_encd_voctp)          (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_vstrp)          (void *, _std_parms_defx, void *, char, long);
    short (DLL_ENTRY_FPTR *_System _oss_dec_sintp)          (void *, _dstd_parms_defx);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_dec_uiintp)  (void *, _dstd_parms_defx);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_ulintp) (void *, _dstd_parms_defx);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_usintp)(void *, _dstd_parms_defx);
    void (DLL_ENTRY_FPTR *_System _oss_dec_aiobjid_ptrp)    (void *, _dstd_parms_defx, char, void **, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_aiobjidp)        (void *, _dstd_parms_defx, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_alobjid_ptrp)    (void *, _dstd_parms_defx, char, void **, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_alobjidp)        (void *, _dstd_parms_defx, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_asobjid_ptrp)    (void *, _dstd_parms_defx, char, void **, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_asobjidp)        (void *, _dstd_parms_defx, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_crealp)          (void *, _dstd_parms_defx, char, char **);
    void (DLL_ENTRY_FPTR *_System _oss_dec_frealp)          (void *, _dstd_parms_defx, float *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_gtimep)          (void *, _dstd_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_hintp)           (void *, _dstd_parms_defx, char, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_liobjidp)        (void *, _dstd_parms_defx, char, void **, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_llobjidp)        (void *, _dstd_parms_defx, char, void **, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_lsobjidp)        (void *, _dstd_parms_defx, char, void **, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_mrealp)          (void *, _dstd_parms_defx, char, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_nstr_ptrp)       (void *, _dstd_parms_defx, char, char **, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_nstrp)           (void *, _dstd_parms_defx, char *, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_opentypep)       (void *, _dstd_parms_defx, char, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_pbitp)           (void *, _dstd_parms_defx, void *, long, char, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_pstrp)           (void *, _dstd_parms_defx, char *, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_realp)           (void *, _dstd_parms_defx, double *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_tagp)            (void *, _sdstd_parms_defx, unsigned short *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_uanyp)           (void *, _dstd_parms_defx, char, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_ubitp)           (void *, _dstd_parms_defx, char, void *, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_uiobjidp)        (void *, _dstd_parms_defx, char, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_ulobjidp)        (void *, _dstd_parms_defx, char, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_uoctp)           (void *, _dstd_parms_defx, char, void *, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_usobjidp)        (void *, _dstd_parms_defx, char, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_ustrp)           (void *, _dstd_parms_defx, char, void *, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_utimep)          (void *, _dstd_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_vbit_ptrp)       (void *, _dstd_parms_defx, char, void **, long, char, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_vbitp)           (void *, _dstd_parms_defx, void *, long, char, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_voct_ptrp)       (void *, _dstd_parms_defx, char, void **, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_voctp)           (void *, _dstd_parms_defx, void *, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_vstr_ptrp)       (void *, _dstd_parms_defx, char, void **, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_dec_vstrp)           (void *, _dstd_parms_defx, void *, char, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_enc_errorp_obsolete) (void *, char, int, long); /* NOT USED */
    void (DLL_ENTRY_FPTR *_System _oss_enci_aiobjidp)       (void *, _std_parms_defx, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_enci_alobjidp)       (void *, _std_parms_defx, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_enci_asobjidp)       (void *, _std_parms_defx, void *, short);
    void (DLL_ENTRY_FPTR *_System _oss_enci_boolp)          (void *, _std_parms_defx, char);
    void (DLL_ENTRY_FPTR *_System _oss_enci_crealp)         (void *, _std_parms_defx, char *);
    void (DLL_ENTRY_FPTR *_System _oss_enci_gtimep)         (void *, _std_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_enci_intp)           (void *, _std_parms_defx, LONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_enci_lengthp)        (void *, _std_parms_defx, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_liobjidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_llobjidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_lsobjidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_mrealp)         (void *, _std_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_enci_nstrp)          (void *, _std_parms_defx, char *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_opentypep)      (void *, _std_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_enci_pbitp)          (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_pstrp)          (void *, _std_parms_defx, char *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_realp)          (void *, _std_parms_defx, double);
    void (DLL_ENTRY_FPTR *_System _oss_enci_tagp)           (void *, _std_parms_defx, unsigned short, char);
    void (DLL_ENTRY_FPTR *_System _oss_enci_uanyp)          (void *, _std_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_enci_ubitp)          (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_uintp)          (void *, _std_parms_defx, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_enci_uiobjidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_ulobjidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_uoctp)          (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_usobjidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_ustrp)          (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_utimep)         (void *, _std_parms_defx, void *);
    void (DLL_ENTRY_FPTR *_System _oss_enci_vbitp)          (void *, _std_parms_defx, void *, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_enci_voctp)          (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_enci_vstrp)          (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_free_crealp_obsolete) (void *, char *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_eobjidp)        (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_eobjidp)         (void *, _dstd_parms_defx, char, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ereloidp)       (void *, _std_parms_defx, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_ereloidp)        (void *, _dstd_parms_defx, char, void *, long);
    long (DLL_ENTRY_FPTR *_System _oss_write_bytes_dp)      (void *, _std_parms_defx, unsigned char *, long);
    char (DLL_ENTRY_FPTR *_System _oss_not_dfltp_obsolete)  (void *, void *, void *, long, long, int); /* NOT USED */
    long (DLL_ENTRY_FPTR *_System _oss_encd_dubitp)         (void *, _std_parms_defx, void *, char, long, char);
    long (DLL_ENTRY_FPTR *_System _oss_encd_dvbitp)         (void *, _std_parms_defx, void *, long, char, char);
    void (DLL_ENTRY_FPTR *_System _oss_chk_enump_obsolete)  (void *, long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_uenump_obsolete) (void *, unsigned long, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utf8bmpstrp)    (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utf8unistrp)    (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_utf8bmpstrp)     (void *, _dstd_parms_defx, ossBoolean, void *, char, long, ossBoolean);
    void (DLL_ENTRY_FPTR *_System _oss_dec_utf8unistrp)     (void *, _dstd_parms_defx, ossBoolean, void *, char, long, ossBoolean);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pacp)            (void *, char *, ULONG_LONG, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac2p)           (void *, unsigned short *, ULONG_LONG, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac4p)           (void *, OSS_INT32 *, ULONG_LONG, void *);
    void (DLL_ENTRY_FPTR *_System _oss_skip_past_itemp)     (void *, _dstd_parms_defx);
    long (DLL_ENTRY_FPTR *_System _oss_encd_bmpstrp)        (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_unistrp)        (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_enci_bmpstrp)        (void *, _std_parms_defx, void *, char, long);
    long (DLL_ENTRY_FPTR *_System _oss_enci_unistrp)        (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_bmpstrp)         (void *, _dstd_parms_defx, ossBoolean, void *, char, long, ossBoolean);
    void (DLL_ENTRY_FPTR *_System _oss_dec_unistrp)         (void *, _dstd_parms_defx, ossBoolean, void *, char, long, ossBoolean);
    void (DLL_ENTRY_FPTR *_System _oss_dec_rsf_extp)        (void *, _dstd_parms_defx, ossBoolean, void **, char **, long *, unsigned int *);
    void (DLL_ENTRY_FPTR *_System _oss_free_rsf_extp)       (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_dec_deferp)          (void *, _dstd_parms_defx, char, void *, short, char);
    long (DLL_ENTRY_FPTR *_System _oss_encd_deferp)         (void *, _std_parms_defx, void *, char *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_untimep)        (void *, _std_parms_defx, char *, long, short);
    void (DLL_ENTRY_FPTR *_System _oss_dec_untimep)         (void *, _dstd_parms_defx, ossBoolean, char**, long, ossBoolean, short);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utf8unboundp)    (void *, _std_parms_defx, void *, char, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_utf8unboundp)     (void *, _dstd_parms_defx, ossBoolean, void *, char, long, ossBoolean);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac_lp_obsolete)  (void *, char *, unsigned long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac2_lp_obsolete) (void *, unsigned short *, unsigned long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac4_lp_obsolete) (void *, OSS_INT32 *, unsigned long, void *);
	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_bmpstr_iap)       (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_hint_iap)         (void *, _dstd_parms_defx, ossBoolean, void *);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_ubit_iap)         (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_unistr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_uoct_iap) (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_ustr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_utf8bmpstr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_utf8unbound_iap) (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_dec_utf8unistr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, long, ossBoolean);

    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_vbit_iap) (void *, _dstd_parms_defx, void *, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_vbit_ptr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, unsigned int, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_voct_iap) (void *, _dstd_parms_defx, void *, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_voct_ptr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, unsigned int, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_vstr_iap) (void *, _dstd_parms_defx, void *, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_dec_vstr_ptr_iap) (void *, _dstd_parms_defx, ossBoolean, void *, unsigned int, long, ossBoolean);
    enum MixedReal_kind (DLL_ENTRY_FPTR *_System _oss_dec_mreal_iap) (void *, _dstd_parms_defx, ossBoolean, void *);

	unsigned int
	(DLL_ENTRY_FPTR *_System _oss_dec_eobjid_iap) (void *, _dstd_parms_defx, ossBoolean, void *
		    , long
	);

	unsigned int
	(DLL_ENTRY_FPTR *_System _oss_dec_ereloid_iap) (void *, _dstd_parms_defx, ossBoolean, void *
		    , long
	);

    long (DLL_ENTRY_FPTR *_System _oss_encd_bmpstr_iap) (void *, _std_parms_defx, unsigned short *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_dubit_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long, ossBoolean);
    long (DLL_ENTRY_FPTR *_System _oss_encd_dvbit_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long, ossBoolean);
    long (DLL_ENTRY_FPTR *_System _oss_encd_huge_int_iap) (void *, _std_parms_defx, unsigned char *, unsigned long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ubit_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uhuge_int_iap) (void *, _std_parms_defx, unsigned char *, unsigned long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_unistr_iap) (void *, _std_parms_defx, OSS_INT32 *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uoct_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ustr_iap) (void *, _std_parms_defx, char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utf8bmpstr_iap) (void *, _std_parms_defx, unsigned short *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utf8unbound_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_utf8unistr_iap) (void *, _std_parms_defx, OSS_INT32 *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_vbit_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_voct_iap) (void *, _std_parms_defx, unsigned char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_vstr_iap) (void *, _std_parms_defx, char *, unsigned long, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_mreal_iap) (void *, _std_parms_defx, enum MixedReal_kind, void *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_eobjid_iap) (void *, _std_parms_defx, unsigned char *, unsigned int, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ereloid_iap) (void *, _std_parms_defx, unsigned char *, unsigned int, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_llobjid_iap) (void *, _std_parms_defx, void *, long, unsigned int);
    void * (DLL_ENTRY_FPTR *_System _oss_dec_llobjid_iap) (void *, _dstd_parms_defx, ossBoolean, long, unsigned int);

    long (DLL_ENTRY_FPTR *_System _oss_encd_usobjid_iap) (void *, _std_parms_defx, unsigned short *, unsigned int, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uiobjid_iap) (void *, _std_parms_defx, unsigned int *, unsigned int, long);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ulobjid_iap) (void *, _std_parms_defx, unsigned long *, unsigned int, long);

    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_usobjid_iap) (void *, _dstd_parms_defx, ossBoolean, void *, short);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_uiobjid_iap) (void *, _dstd_parms_defx, ossBoolean, void *, short);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_ulobjid_iap) (void *, _dstd_parms_defx, ossBoolean, void *, short);

    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_asobjid_iap) (void *, _dstd_parms_defx, unsigned short *, short);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_aiobjid_iap) (void *, _dstd_parms_defx, unsigned int *, short);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_dec_alobjid_iap) (void *, _dstd_parms_defx, unsigned long *, short);

    void * (DLL_ENTRY_FPTR *_System _oss_dec_asobjid_ptr_iap) (void *, _dstd_parms_defx, ossBoolean, short, unsigned int);
    void * (DLL_ENTRY_FPTR *_System _oss_dec_aiobjid_ptr_iap) (void *, _dstd_parms_defx, ossBoolean, short, unsigned int);
    void * (DLL_ENTRY_FPTR *_System _oss_dec_alobjid_ptr_iap) (void *, _dstd_parms_defx, ossBoolean, short, unsigned int);

    long (DLL_ENTRY_FPTR *_System _oss_encd_tag_lengthp)(void *, _sdstd_parms_defx,
	long, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_encd_tag_length2p)(void *, _sdstd_parms_defx,
	long, OSS_UINT32, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_encd_bool_tlp)(void *, _sdstd_parms_defx,
	OSS_UINT32, ossBoolean);
    long (DLL_ENTRY_FPTR *_System _oss_encd_int_tlp)(void *, _sdstd_parms_defx,
	long, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_encd_uint_tlp)(void *, _sdstd_parms_defx,
	unsigned long, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_dec_tag_lengthp) (void *, _sdstd_parms_defx,
	unsigned long, char *);
    long (DLL_ENTRY_FPTR *_System _oss_encd_llint_tlp)(void *, _sdstd_parms_defx,
	LONG_LONG, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_encd_ullint_tlp)(void *, _sdstd_parms_defx,
	ULONG_LONG, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_encd_pbit_tlp)(void *, _sdstd_parms_defx,
	OSS_UINT32, unsigned int, OSS_UINT32);
#endif /* SOED */
} BERTbl;

typedef struct perTbl {
    int  (DLL_ENTRY_FPTR *_System ossPerEncodep)(void *, int, void *, char **, long *, void *, unsigned, char *);
    int  (DLL_ENTRY_FPTR *_System ossPerDecodep)(void *, int *, char **, long *, void **, long *, void *, unsigned, char *);
#ifdef SOED
    int  (DLL_ENTRY_FPTR *_System ossPerEncodeOpenTypep)(void *, int,
				void *, void **, long *, void *, unsigned);
    int  (DLL_ENTRY_FPTR *_System ossPerDecodeOpenTypep)(void  *, int *, void **,
				long  *, void **, long *, void *, unsigned);
    void (DLL_ENTRY_FPTR *_System oss_encode_PDUp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System oss_decode_PDUp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System oss_den_errorp)(void *, int, void *);
    void (DLL_ENTRY_FPTR *_System oss_encode_lengthp)(void *, long, LONG_LONG, LONG_LONG);
    void (DLL_ENTRY_FPTR *_System oss_debug_realp)(void *, char, unsigned char *, int, long);
    void (DLL_ENTRY_FPTR *_System oss_debug_strp)(void *, unsigned char *, size_t);
    void (DLL_ENTRY_FPTR *_System oss_append_to_field_listp)(void *, unsigned char *, LONG_LONG, int);
    int  (DLL_ENTRY_FPTR *_System oss_numbitsp)(long);
    void (DLL_ENTRY_FPTR *_System oss_decode_lengthp)(void *, unsigned long *, unsigned long, unsigned long, unsigned short *);
    unsigned char (DLL_ENTRY_FPTR *_System oss_get_octetp)(void *, unsigned short, char);
    void (DLL_ENTRY_FPTR *_System oss_set_intp)(void *, unsigned char *, unsigned int, LONG_LONG, int);
    void (DLL_ENTRY_FPTR *_System oss_set_uintp)(void *, unsigned char *, unsigned int, ULONG_LONG, int);
    LONG_LONG (DLL_ENTRY_FPTR *_System oss_twos_comp_intp)(unsigned char *, int);
    void (DLL_ENTRY_FPTR *_System oss_get_octetsp)(void *, unsigned char *, LONG_LONG, unsigned short, char);
    void (DLL_ENTRY_FPTR *_System oss_encode_normally_small_numberp)(void *, ULONG_LONG, char);
    void (DLL_ENTRY_FPTR *_System oss_decode_normally_small_numberp)(void *, LONG_LONG *, char);
    void (DLL_ENTRY_FPTR *_System oss_add_fieldp)(void *, char *, int, int);
    void (DLL_ENTRY_FPTR *_System oss_output_linep)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System oss_get_bitp)(void *, unsigned short, char);
    unsigned char *(DLL_ENTRY_FPTR *_System dswapOutp)(void *, void *, void **, size_t, char, char);
    void (DLL_ENTRY_FPTR *_System oss_debug_objidp)(void *, unsigned char *, int, int, int);
    void  (DLL_ENTRY_FPTR *_System ossPrintPerValuep)(void *, void *);
#elif !defined(ASN1CPLUSPLUS)
    void (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_intp)(void *, LONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_kmstrp)       (void *, char *, ULONG_LONG, ULONG_LONG, ULONG_LONG, int, long, char);
    LONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_intp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_ub_kmstrp)    (void *, void *, char **, int, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_ntp_kmstrp)   (void *, char **, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_appendp)           (void *, unsigned char *, unsigned long, int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_bitp)(void *, unsigned char *, ULONG_LONG, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_constr_bitp)  (void *, unsigned char *, ULONG_LONG, ULONG_LONG, ULONG_LONG, char, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_octp)(void *, unsigned char *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_constr_octp)  (void *, unsigned char *, ULONG_LONG, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_link_objidsp) (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_objidsp)      (void *, unsigned short *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_link_objidlp) (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_objidlp)      (void *, unsigned long *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_link_objidip) (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_objidip)      (void *, unsigned int *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nkmstrp)      (void *, char *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_opentypep)    (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_intp)  (void *, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_realp)        (void *, double);
    void (DLL_ENTRY_FPTR *_System _oss_penc_uenump)       (void *, unsigned long, void *, void *);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_penc_lengthp)(void *, ULONG_LONG, ULONG_LONG, ULONG_LONG, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_gtimep)       (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_utimep)       (void *, void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_bitp) (void *, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_ubitp)(void *, void *, unsigned char **, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_ubitp) (void *, void *, unsigned char **, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_vbit_ptrp)(void *, void **, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_vbitp)(void *, void *, unsigned char *, int, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_voctp) (void *, void *, unsigned char  *, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_uoctp)(void *, void *, unsigned char **, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_voct_ptrp)(void *, void **, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_voctp)(void *, void *, unsigned char  *, int, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_uoctp) (void *, void *, unsigned char **value, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_vbitp) (void *, void *, unsigned char *, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_link_objidsp) (void *, void **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_link_objidip) (void *, void **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_link_objidlp) (void *, void **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_uobjidsp)     (void *, unsigned short **, unsigned short *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_uobjidip)     (void *, unsigned int **, unsigned short *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_uobjidlp)     (void *, unsigned long **, unsigned short *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidsp)     (void *, unsigned short *, unsigned short *, unsigned short);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidip)     (void *, unsigned int *, unsigned short *, unsigned short);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidlp)     (void *, unsigned long *, unsigned short *, unsigned short);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_aobjids_ptrp) (void *, void **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidi_ptrp) (void *, void **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidl_ptrp) (void *, void **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_ntp_nkmstrp)  (void *, char **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_opentypep)    (void *, void *);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_intp)(void *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_get_bitsp)         (void *, unsigned char *, unsigned long, int);
    float  (DLL_ENTRY_FPTR *_System _oss_pdec_frealp)     (void *);
    double (DLL_ENTRY_FPTR *_System _oss_pdec_realp)      (void *);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_uenump)(void *, void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_lsofp)        (void *, unsigned long *, ULONG_LONG, ULONG_LONG, unsigned char, char *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_usofp)        (void *, unsigned long *, unsigned char **, int, long, ULONG_LONG, ULONG_LONG, unsigned char, char *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_asofp)        (void *, unsigned long *, int, ULONG_LONG, ULONG_LONG, unsigned char, char *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_gtimep)       (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_utimep)       (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_asof_ptrp)    (void *, void **, int, long, long, char *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_nt_kmstrp)    (void *, void *, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_va_kmstrp)    (void *, void *, char *, int, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_vap_kmstrp)   (void *, void **, int, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_pad_kmstrp)   (void *, void *, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_enc_errorp_obsolete) (void *, char, int, long); /* NOT USED */
    double (DLL_ENTRY_FPTR *_System _oss_pdec_binrealp)   (void *, unsigned char, long);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_bpbitp)(void *, unsigned char *, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_pbitp) (void *, void *, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_vbit_ptrp)(void *, void **, int, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_constr_voct_ptrp)(void *, void **, int, ULONG_LONG, ULONG_LONG);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_eapp)(void *, unsigned char **);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_easp)         (void *, unsigned char *, unsigned long, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_chrrealp)     (void *, unsigned char, long, double *, unsigned char *);
    long (DLL_ENTRY_FPTR *_System _oss_pdec_enump)        (void *, void *, void *);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_indeflen_intp)(void *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_nt_nkmstrp)   (void *, char *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_bmpstrp)      (void *, void *, unsigned short **, int, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_bmpstrp)      (void *, unsigned short *, ULONG_LONG, ULONG_LONG, ULONG_LONG, int, long, ossBoolean);
    char *(DLL_ENTRY_FPTR *_System _oss_pdec_crealp)      (void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_pad_kmstr_ptrp)(void *, char **, ULONG_LONG, ULONG_LONG, int, long, char);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_lengthp) (void *, unsigned long, unsigned long, ossBoolean *);
    MixedReal (DLL_ENTRY_FPTR *_System _oss_pdec_mrealp)  (void *);
    struct ossGlobal *(DLL_ENTRY_FPTR *_System _oss_pdec_popp)        (void *);
    struct ossGlobal *(DLL_ENTRY_FPTR *_System _oss_pdec_pushp)       (void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_uanyp)        (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unistrp)      (void *, void *, OSS_INT32 **, int, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_unistrp)      (void *, OSS_INT32 *, ULONG_LONG, ULONG_LONG, ULONG_LONG, int, long, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_utf8unistrp)  (void *, OSS_INT32 *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_utf8unistrp)  (void *, void *, OSS_INT32 **, int);
    LONG_LONG  (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_intp)(void *, LONG_LONG);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_uintp)(void *, ULONG_LONG);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_small_intp)(void *);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_small_lenp)(void *);
    long (DLL_ENTRY_FPTR *_System _oss_pdec_subidp)       (void *, long, long, long *, long *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_ub_nkmstrp)   (void *, void *, char **, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_bpbitp)(void *, unsigned char *, long);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_pbitp)(void *, void *, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_hugep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_vap_nkmstrp)   (void *, void **, int);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_va_nkmstrp)    (void *, void *, char *, int, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_constr_bpbitp) (void *, void *, ULONG_LONG, ULONG_LONG, char, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_constr_pbitp)  (void *, ULONG_LONG, ULONG_LONG, ULONG_LONG, ULONG_LONG, char, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_crealp)        (void *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_enump)         (void *, long, void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_indeflen_intp) (void *, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_mrealp)        (void *, MixedReal);
    struct ossGlobal *(DLL_ENTRY_FPTR *_System _oss_pop_globalp)       (void *);
    struct ossGlobal *(DLL_ENTRY_FPTR *_System _oss_push_globalp_obsolete)      (void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_semicon_intp)  (void *, LONG_LONG, LONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_semicon_uintp) (void *, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_small_intp)    (void *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_small_lenp)    (void *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_subidp)        (void *, int, unsigned long, unsigned long *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_uanyp)         (void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_hugep)(void *, void *);

    void (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_pbitp)(void *, ULONG_LONG, ULONG_LONG, ULONG_LONG, char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_semicon_hugep) (void *, void *, LONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_hugep) (void *, void *, LONG_LONG);

    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_octetp)(void *, int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_eobjidp)       (void *, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_eobjidp)       (void *, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_ereloidp)      (void *, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_ereloidp)      (void *, void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_free_crealp_obsolete) (void *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_sotp)          (void *);
    ossBoolean (DLL_ENTRY_FPTR *_System _oss_lnchkp)       (unsigned char *, ULONG_LONG *, unsigned short, ULONG_LONG, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_penc_utf8bmpstrp)   (void *, unsigned short *, ULONG_LONG);
    void (DLL_ENTRY_FPTR *_System _oss_pdec_utf8bmpstrp)   (void *, void *, unsigned short **, int);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_copy_preamblep)(void *, unsigned char *, unsigned long, unsigned long, void *, unsigned char **, unsigned int, ossBoolean);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_limited_intp)(void *, ULONG_LONG, LONG_LONG, LONG_LONG);
    LONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_limited_intp)(void *, LONG_LONG, LONG_LONG);
    LONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_limited_intp)  (void *, LONG_LONG, LONG_LONG, LONG_LONG);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_pdec_indeflen_limited_intp)(void *, ULONG_LONG, LONG_LONG, LONG_LONG, LONG_LONG);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_1bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_2bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_3bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_4bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_5bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_6bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_7bit_unalignedp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_get_8bit_unalignedp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_1intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_2intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_3intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_4intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_5intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_6intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_7intp)(void *);
    unsigned int (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_8intp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_append_1bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_2bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_3bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_4bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_5bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_6bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_7bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_append_8bit_unalignedp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_1intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_2intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_3intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_4intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_5intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_6intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_7intp)(void *, unsigned int);
    void (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_8intp)(void *, unsigned int);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_indeflen_int_lp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_indeflen_limited_int_lp)(void *, unsigned long, long, long, long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_int_lp)(void *, unsigned int);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_nonneg_limited_int_lp)(void *, unsigned int, long, long);
    long          (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_int_lp)(void *, long);
    long          (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_limited_int_lp)(void *, long, long, long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_semicon_uint_lp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_small_int_lp)(void *);
    long          (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_int_lp)(void *);
    long          (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_limited_int_lp)(void *, long, long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_indeflen_int_lp)(void *, unsigned long, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_nonneg_int_lp)(void *, unsigned long, unsigned int);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_semicon_int_lp)(void *, long, long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_semicon_uint_lp)(void *, unsigned long, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_small_int_lp)(void *, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_int_lp)(void *, long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_constr_oct_lp)(void *, unsigned char *, unsigned long, unsigned long, unsigned long);

    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_constr_vbit_ptr_iap) (void *, void *, unsigned int, unsigned long, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_constr_voct_ptr_iap) (void *, void *, unsigned int, unsigned long, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_vbit_ptr_iap) (void *, void *, unsigned int);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_voct_ptr_iap) (void *, void *, unsigned int);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_vap_kmstr_iap) (void *, void *, unsigned int, unsigned long, unsigned long, int, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_vap_nkmstr_iap) (void *, void *, unsigned int);

	unsigned int
	(DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_huge_iap) (void *, void *);

    enum MixedReal_kind (DLL_ENTRY_FPTR *_System _oss_pdec_mreal_iap) (void *, void *);

	unsigned int
	(DLL_ENTRY_FPTR *_System _oss_pdec_semicon_huge_iap) (void *, void *
	      , long lb
		       );
	unsigned int
	(DLL_ENTRY_FPTR *_System _oss_pdec_eobjid_iap) (void *, void *
					    , long
	);

	unsigned int
	(DLL_ENTRY_FPTR *_System _oss_pdec_ereloid_iap) (void *, void *
					     , long
	);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_constr_ubit_iap) (void *, unsigned char **, unsigned long, unsigned long);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_constr_uoct_iap) (void *, unsigned char **, unsigned long, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_constr_vbit_iap) (void *, unsigned char *, unsigned long, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_constr_voct_iap) (void *, unsigned char *, unsigned long, unsigned long);
	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_bmpstr_iap) (void *, unsigned short **, unsigned long, unsigned long, int, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_unistr_iap) (void *g, OSS_INT32 **, unsigned long, unsigned long, int, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_utf8bmpstr_iap) (void *, unsigned short **);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_utf8unistr_iap) (void *, OSS_INT32 **);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_ub_kmstr_iap) (void *, char **, unsigned long, unsigned long, int, long, ossBoolean);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_ub_nkmstr_iap) (void *, char **);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_ubit_iap) (void *, unsigned char **);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_uoct_iap) (void *, unsigned char **);

    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_vbit_iap) (void *, unsigned char *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_unconstr_voct_iap) (void *, unsigned char *, unsigned long);

	unsigned long
	(DLL_ENTRY_FPTR *_System _oss_pdec_usof_iap) (void *, unsigned long, void *, long, unsigned long, unsigned long, unsigned char, ossBoolean *);

    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_va_kmstr_iap) (void *, char *, unsigned long, unsigned long, int, long, ossBoolean);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_pdec_va_nkmstr_iap) (void *, char *, unsigned long);

    void (DLL_ENTRY_FPTR *_System _oss_penc_mreal_iap) (void *, enum MixedReal_kind, void *);

    void (DLL_ENTRY_FPTR *_System _oss_penc_semicon_huge_iap) (void *, unsigned char *, unsigned long
    , long lb
	     );
    void (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_huge_iap) (void *, unsigned char *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_eobjid_iap) (void *, unsigned char *, unsigned int, long);
    void (DLL_ENTRY_FPTR *_System _oss_penc_ereloid_iap) (void *, unsigned char *, unsigned int, long);

    void          (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_pbit_lp)(void *, unsigned long, unsigned long, unsigned long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_oct_lp)(void *, unsigned char *, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_unconstr_bit_lp)(void *, unsigned char *, unsigned long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_small_len_lp)(void *, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_nkmstr_lp)(void *, char *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_penc_length_lp)(void *, unsigned long, unsigned long, unsigned long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_kmstr_lp)(void *, char *, unsigned long, unsigned long, unsigned long, int, long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_constr_pbit_lp)(void *, unsigned long, unsigned long, unsigned long, unsigned long, char, char);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_constr_bpbit_lp)(void *, void *, unsigned long, unsigned long, char, char);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_constr_bit_lp)(void *, unsigned char *, unsigned long, unsigned long, unsigned long, char, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_utf8bmpstr_lp)(void *, unsigned short *, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_utf8unistr_lp)(void *, OSS_INT32 *, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_bmpstr_lp)(void *, unsigned short *, unsigned long, unsigned long, unsigned long, int, long, ossBoolean);
    void          (DLL_ENTRY_FPTR *_System _oss_penc_unistr_lp)(void *, OSS_INT32 *, unsigned long, unsigned long, unsigned long, int, long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_pad_kmstr_lp)(void *, void *, unsigned long, unsigned long, int, long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_ntp_kmstr_lp)(void *, char **, unsigned long, unsigned long, int, long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_nt_kmstr_lp)(void *, void *, unsigned long, unsigned long, int, long, char);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_lsof_lp)(void *, unsigned long *, unsigned long, unsigned long, unsigned char, char *);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_constr_pbit_lp)(void *, void *, int, unsigned long, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_constr_bpbit_lp)(void *, unsigned char *, int, unsigned long, unsigned long);
    void          (DLL_ENTRY_FPTR *_System _oss_pdec_asof_ptr_iap)(void *, void *, int, long, unsigned int, ossBoolean *);

    void (DLL_ENTRY_FPTR *_System _oss_penc_link_objidl_iap)(void *, void *, unsigned int);
    void * (DLL_ENTRY_FPTR *_System _oss_pdec_link_objidl_iap)(void *, unsigned int);

    void * (DLL_ENTRY_FPTR *_System _oss_pdec_aobjids_ptr_iap)(void *, unsigned int);
    void * (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidi_ptr_iap)(void *, unsigned int);
    void * (DLL_ENTRY_FPTR *_System _oss_pdec_aobjidl_ptr_iap)(void *, unsigned int);


    void (DLL_ENTRY_FPTR *_System _oss_fast_push_globalp)   (void *);
    void (DLL_ENTRY_FPTR *_System _oss_fast_pop_globalp)    (void *);
#endif /* SOED */
} PERTbl;

typedef struct _xerTbl {
    int  (DLL_ENTRY_FPTR *_System ossXerEncodep)(void *, int, void *, char **, long *, void *, unsigned, char *);
    int  (DLL_ENTRY_FPTR *_System ossXerDecodep)(void *, int *, char **, long *, void **, long *, void *, unsigned, char *);
#ifdef SOED
    void (DLL_ENTRY_FPTR *_System ossPrintRealp)(void *, void *,
							unsigned char *);
#if !defined(TRACE_OFF)
    void (DLL_ENTRY_FPTR *_System ossPrintXerValuep)(void *, void *);
#endif /* !TRACE_OFF */
#else  /* TOED */
    long	(DLL_ENTRY_FPTR *_System  _oss_tex_appendp)(void *, unsigned char *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_format_tagp)(void *, char *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_indentp)(void *);
    long	(DLL_ENTRY_FPTR *_System  _oss_tex_count_bitsp)(unsigned char *, long);
    long	(DLL_ENTRY_FPTR *_System  _oss_tex_count_charsp)(char *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_lintp)(void *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_ulintp)(void *, unsigned long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_llintp)(void *, LONG_LONG);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_ullintp)(void *, ULONG_LONG);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_hintp)(void *, unsigned char *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_timep)(void *, void *, char);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_enump)(void *, void *, long, int);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_format_enump)(void *, char *, int);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_drealp)(void *, double);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_frealp)(void *, float);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_crealp)(void *, char *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_eobjidp)(void *, unsigned char *, long, long, ossBoolean);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_aobjidsp)(void *, unsigned short *, long, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_aobjidip)(void *, unsigned int *, long, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_aobjidlp)(void *, unsigned long *, long, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_lobjidsp)(void *, void *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_lobjidip)(void *, void *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_lobjidlp)(void *, void *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_format_charp)(void *, unsigned char *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_format_bitp)(void *, unsigned char *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_format_octetp)(void *, unsigned char *, unsigned long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_prologp)(void *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_opentypep)(void *, void *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_2byte_charp)(void *, unsigned short *, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_4byte_charp)(void *, OSS_UINT32 *, long);

    void (DLL_ENTRY_FPTR *_System _oss_tdx_open_tagp)(void *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_empty_tagp)(void *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_close_tagp)(void *, char *);
    ossBoolean (DLL_ENTRY_FPTR *_System _oss_tdx_open_or_empty_tagp)(void *, char *);
    ossBoolean (DLL_ENTRY_FPTR *_System _oss_tdx_open_fieldp)(void *, void *, short *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_skip_blockp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_prologp)(void *);
    unsigned char (DLL_ENTRY_FPTR *_System _oss_tdx_lexem_lookaheadp)(void *);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_allocate_array_sofp)(void *, void **, int, long);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_allocate_unbounded_sofp)(void *, void **, long, OSS_UINT32, OSS_UINT32);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_opentypep)(void *, void *, OSS_UINT32);
    ossBoolean (DLL_ENTRY_FPTR *_System _oss_tdx_boolp)(void *);
    OSS_INT32 (DLL_ENTRY_FPTR *_System _oss_tdx_enump)(void *, void *);
    LONG_LONG (DLL_ENTRY_FPTR *_System _oss_tdx_llintp)(void *, LONG_LONG, LONG_LONG, OSS_UINT32);
    ULONG_LONG (DLL_ENTRY_FPTR *_System _oss_tdx_ullintp)(void *, ULONG_LONG, ULONG_LONG, OSS_UINT32);
    long (DLL_ENTRY_FPTR *_System _oss_tdx_lintp)(void *, long, long, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_ulintp)(void *, unsigned long, unsigned long, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_hintp)(void *, void **, OSS_UINT32);
    double (DLL_ENTRY_FPTR *_System _oss_tdx_drealp)(void *);
    float (DLL_ENTRY_FPTR *_System _oss_tdx_frealp)(void *);
    char * (DLL_ENTRY_FPTR *_System _oss_tdx_crealp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_mrealp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_char1_nulltermp)(void *, void *, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_char1_unboundedp)(void *, void **, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_char1_pvaryingp)(void *, void **, int, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_char1_varyingp)(void *, void *, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_char2p)(void *, void **, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_char4p)(void *, void **, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_octets_unboundedp)(void *, void **, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_octets_pvaryingp)(void *, void **, int, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_octets_varyingp)(void *, void *, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_bits_unboundedp)(void *, void **, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_bits_pvaryingp)(void *, void **, int, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_bits_varyingp)(void *, void *, OSS_UINT32, OSS_UINT32);
    unsigned long (DLL_ENTRY_FPTR *_System _oss_tdx_bits_paddedp)(void *, int, OSS_UINT32);
    OSS_UINT32 (DLL_ENTRY_FPTR *_System _oss_tdx_objid_encodedp)(void *, void *, OSS_UINT32, OSS_UINT32);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_objid_linkedp)(void *, void **, unsigned short, OSS_UINT32, OSS_UINT32);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_tdx_objid_unboundedp)(void *, void **, unsigned short, OSS_UINT32, OSS_UINT32);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_tdx_objid_arrayp)(void *, void *, OSS_UINT32, unsigned short);
    unsigned short (DLL_ENTRY_FPTR *_System _oss_tdx_objid_parrayp)(void *, void **, int, unsigned short);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_gtimep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_tdx_utimep)(void *, void *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_open_tagp)(void *, char *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_close_tagp)(void *, char *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_empty_or_id_tagp)(void *, char *);
    long	(DLL_ENTRY_FPTR *_System  _oss_tex_curr_enclenp)(void *);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_indent_dltp)(void *, int);
    void (DLL_ENTRY_FPTR *_System _oss_tex_format_pbitp)(void *, OSS_UINT32, long);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_open_tagNp)(void *, char *, int);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_close_tagNp)(void *, char *, int);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_empty_or_id_tagNp)(void *, char *, int);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_format_tagNp)(void *, char *, int);
    void	(DLL_ENTRY_FPTR *_System  _oss_tex_anyopentypep)(void *, unsigned char *, long);
    void        (DLL_ENTRY_FPTR *_System  _oss_allocate_memblockp)(void *, void **, void **, long);
    void        (DLL_ENTRY_FPTR *_System  _oss_consolidate_memblockp)(void *, void **, long, long,
				void *, long, long, long, int, OSS_UINT32, OSS_UINT32);
    void        (DLL_ENTRY_FPTR *_System  _oss_tex_format_char_tp)(void *, unsigned char *, long);
    enum MixedReal_kind (DLL_ENTRY_FPTR *_System _oss_tdx_mreal_iap)(void *, void *);
#endif /* TOED */
} XERTbl;

typedef struct apiTbl {
    int (DLL_ENTRY_FPTR *_System ossSetEncodingRulesp)(void *, int);
    int (DLL_ENTRY_FPTR *_System ossGetEncodingRulesp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetRuntimeVersionp)(void *, int);
    int (DLL_ENTRY_FPTR *_System ossGetRuntimeVersionp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetCompatibilityFlagsp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System ossGetCompatibilityFlagsp)(void *);
    int (DLL_ENTRY_FPTR *_System encodep)(void *, int, void *, char **,
					long *, void *, unsigned, char *);
    int (DLL_ENTRY_FPTR *_System decodep)(void *, int *, char **, long *,
				void **, long *, void *, unsigned, char *);
    int (DLL_ENTRY_FPTR *_System ossDispatchEncodep)(void *, int, void *, char **,
					long *, void *, unsigned, char *);
    int (DLL_ENTRY_FPTR *_System ossDispatchDecodep)(void *, int *, char **, long *,
				void **, long *, void *, unsigned, char *);
    int (DLL_ENTRY_FPTR *_System ossSetDecodingLengthp)(void *, long);
    long (DLL_ENTRY_FPTR *_System ossGetDecodingLengthp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetEncodingFlagsp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System ossGetEncodingFlagsp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetFlagsp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System ossGetFlagsp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetDecodingFlagsp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System ossGetDecodingFlagsp)(void *);
    char *(DLL_ENTRY_FPTR *_System ossGetErrMsgp)(void *world);
    void (DLL_ENTRY_FPTR *_System ossPrintHexp)(void *, char *, long);
    int (DLL_ENTRY_FPTR *_System ossEncodep)(void *, int, void *, void *);
    int (DLL_ENTRY_FPTR *_System ossDecodep)(void *, int *, void *, void **);
    int (DLL_ENTRY_FPTR *_System ossPrintPDUp)(void *, int, void *);
    int (DLL_ENTRY_FPTR *_System ossFreePDUp)(void *, int, void *);
    void (DLL_ENTRY_FPTR *_System ossFreeBufp)(void *, void *);
    int  (DLL_ENTRY_FPTR *ossPrintWinp)(void *, const char *,
				ossArg, ossArg, ossArg, ossArg, ossArg,
					ossArg, ossArg, ossArg, ossArg, ossArg);
    int  (DLL_ENTRY_FPTR *ossVprintWinp)(void *, const char *, va_list);
    int  (DLL_ENTRY_FPTR *_System ossReadLinep)(void *, HWND, FILE *,
						char *, MEMBLOCK *, LONG);
    void (DLL_ENTRY_FPTR *_System ossFreeListp)(void *);
    void (DLL_ENTRY_FPTR *_System ossSaveTraceInfop)(void *, HWND, char *);
    void (DLL_ENTRY_FPTR *_System osstracep)(void *, void *p, size_t);
    int  (DLL_ENTRY_FPTR *_System ossOpenTraceWindowp)(void *);
    int  (DLL_ENTRY_FPTR *_System ossOpenTraceFilep)(void *, char *);
    int  (DLL_ENTRY_FPTR *_System ossCloseTraceFilep)(void *);
    long (DLL_ENTRY_FPTR *_System ossDetermineEncodingLengthp)(void *,
								int, void *);
    long (DLL_ENTRY_FPTR *_System ossDetermineMessageLengthp)(void *, void *);
    int  (DLL_ENTRY_FPTR *_System ossCallerIsDecoderp)(void *);
    void *(DLL_ENTRY_FPTR *_System ossMarkObjp)(void *, int, void *);
    void *(DLL_ENTRY_FPTR *_System ossUnmarkObjp)(void *, void *);
    void *(DLL_ENTRY_FPTR *_System ossGetObjp)(void *, void *);
    int  (DLL_ENTRY_FPTR *_System ossTestObjp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossFreeObjectStackp)(void *);
    void (DLL_ENTRY_FPTR *_System ossSetTimeoutp)(void *, long);
    int  (DLL_ENTRY_FPTR *_System ossGetBufferp)(void *, void *);
    int  (DLL_ENTRY_FPTR *_System ossSetTemporaryBufferp)(void *, void *);
    int  (DLL_ENTRY_FPTR *_System ossSetFormatterBufferSizep)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System ossGetFormatterBufferSizep)(void *);
    int  (DLL_ENTRY_FPTR *_System ossSetBufferp)(void *, void *);
    int  (DLL_ENTRY_FPTR *_System ossOpenDecoderInputFilep)(void *, char *);
    int  (DLL_ENTRY_FPTR *_System ossCloseDecoderInputFilep)(void *);
    int  (DLL_ENTRY_FPTR *_System ossOpenEncoderOutputFilep)(void *, char *);
    int  (DLL_ENTRY_FPTR *_System ossCloseEncoderOutputFilep)(void *);
    long (DLL_ENTRY_FPTR *_System ossSetMinFileSizep)(void *, long);
    long (DLL_ENTRY_FPTR *_System ossGetMinFileSizep)(void *);
    void (DLL_ENTRY_FPTR *_System ossSetUserMallocFreeReallocp)(void *,
					void *(*)(void *, size_t),
					void  (*)(void *, void *),
					void *(*)(void *, void *, size_t));
    void (DLL_ENTRY_FPTR *_System ossGetUserMallocFreeReallocp)(void *,
					void *(**)(void *, size_t),
					void  (**)(void *, void *),
					void *(**)(void *, void *, size_t));
    void (DLL_ENTRY_FPTR *_System ossSetUserPrintp)(void *, FILE *,
			int (DLL_ENTRY_FPTR *)(void *, const char *, ...));
    void (DLL_ENTRY_FPTR *_System ossGetUserPrintp)(void *, FILE **,
			int (DLL_ENTRY_FPTR **)(void *, const char *, ...));
    void (DLL_ENTRY_FPTR *_System ossSetUserVprintp)(void *, FILE *,
			int (DLL_ENTRY_FPTR *)(void *, const char *, va_list));
    void (DLL_ENTRY_FPTR *_System ossGetUserVprintp)(void *, FILE **,
			int (DLL_ENTRY_FPTR **)(void *, const char *, va_list));
    void (DLL_ENTRY_FPTR *_System ossSetUserFieldCpyCmpp)(void *,
					int (*)(void *, void *, void *),
					int (*)(void *, void *, void *));
    void (DLL_ENTRY_FPTR *_System ossGetUserFieldCpyCmpp)(void *,
					int (**)(void *, void *, void *),
					int (**)(void *, void *, void *));
    long (DLL_ENTRY_FPTR *_System ossGetBytesReadByDecoderp)(void *);
    void *(DLL_ENTRY_FPTR *_System ossGetDefaultValuep)(void *, unsigned int);
    char *(DLL_ENTRY_FPTR *_System ossGetPDUNamep)(void *, unsigned short);
    int (DLL_ENTRY_FPTR *_System ossGeneralizedTimeToIntsp)(void *, char *,
		unsigned int *, unsigned int *,	unsigned int *,
		unsigned int *, unsigned int *,	unsigned int *,
		unsigned int *, unsigned short *, int *);
    int (DLL_ENTRY_FPTR *_System ossUTCTimeToIntsp)(void *, char *,
		unsigned int *, unsigned int *,	unsigned int *,
		unsigned int *, unsigned int *,	unsigned int *, int *);
    int (DLL_ENTRY_FPTR *_System ossIntsToGeneralizedTimep)(void *,
		unsigned int, unsigned int, unsigned int,
		unsigned int, unsigned int, unsigned int,
		unsigned int, unsigned short, int, char *);
    int (DLL_ENTRY_FPTR *_System ossIntsToUTCTimep)(void *,
		unsigned int, unsigned int, unsigned int,
		unsigned int, unsigned int, unsigned int, int, char *);
    void (DLL_ENTRY_FPTR *_System ossPrintOctetAsIPAddressp)(void *, char *);
    void (DLL_ENTRY_FPTR *_System ossPrintOctetAsASCIIp)(void *, char *);
    void (DLL_ENTRY_FPTR *_System ossFreeScopeStackp)(void *);
    void (DLL_ENTRY_FPTR *_System ossFreeEncodedTypesListp)(void *, unsigned char );
    int  (DLL_ENTRY_FPTR *_System ossDetermineNumberOfPadBitsp)(void *);
    int  (DLL_ENTRY_FPTR *_System ossFindPduNumberOfOpenTypep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossNewScopeInfop)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossEndScopeInfop)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossNewReferencedp)(void *,
		unsigned short, void *, void *, size_t);
    void *(DLL_ENTRY_FPTR *_System ossNewReferencingp)(void *, void *,
		void *, size_t);
    void (DLL_ENTRY_FPTR *_System ossFreeReferencingp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossDecodeRestOfOpenTypep)(void *);
    void (DLL_ENTRY_FPTR *_System ossStoreErrorInfop)(void *);
    char (DLL_ENTRY_FPTR *_System ossCmpObjectsp)(unsigned char *,
			unsigned char *, void *, void *, char);
    int (DLL_ENTRY_FPTR *_System ossIsSetFlagp)(char *, short int);
    void *(DLL_ENTRY_FPTR *_System ossGetUserFunctionp)(void *, char *,
			short int);
    char *(DLL_ENTRY_FPTR *_System name_ofp)(char *);
    int (DLL_ENTRY_FPTR *ossGetPrintIndentp)(struct ossGlobal *world);
    void (DLL_ENTRY_FPTR *ossSetPrintIndentp)(struct ossGlobal *world, int indent_level);
    int (DLL_ENTRY_FPTR *_System ossGeneralizedTimeToShortsp)(void *, char *,
		unsigned short *, unsigned short *, unsigned short *,
		unsigned short *, unsigned short *, unsigned short *,
		unsigned int   *, unsigned short *, int *);
    int (DLL_ENTRY_FPTR *_System ossUTCTimeToShortsp)(void *, char *,
		unsigned short *, unsigned short *, unsigned short *,
		unsigned short *, unsigned short *, unsigned short *, int *);
    void (DLL_ENTRY_FPTR *_System ossSetPaddingBitsp)(void *, unsigned char);
    void (DLL_ENTRY_FPTR *_System ossSetPresetDecFlagsp)(void *, unsigned long);
    unsigned long (DLL_ENTRY_FPTR *_System ossGetPresetDecFlagsp)(void *);
    int (DLL_ENTRY_FPTR *_System ossDecodeRestOfContainingp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetXmlStylesheetp)(void *, char *);
    int (DLL_ENTRY_FPTR *_System ossSetXmlDTDp)(void *, char *, char *, short);
#ifndef SOED
    void (DLL_ENTRY_FPTR *_System ossMinitp)(void *);
    void *(DLL_ENTRY_FPTR *_System _oss_dec_getmemp)(void *, long, char);
    void *(DLL_ENTRY_FPTR *_System _oss_enc_getmemp)(void *, char);
    void *(DLL_ENTRY_FPTR *_System _oss_enc_popp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_enc_pushp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_releaseMemp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_freeMemp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_freeGlobalsp)(void *, ossBoolean);
    void (DLL_ENTRY_FPTR *_System _oss_freeDerBlocksp_obsolete)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_enc_freeMemp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_set_outmem_dp)(void *, long,
							long *, char **);
    void (DLL_ENTRY_FPTR *_System _oss_set_outmem_pp)(void *, long *, char **);
    void (DLL_ENTRY_FPTR *_System _oss_set_outmem_pbp)(void *, long *, char **, unsigned);
    void (DLL_ENTRY_FPTR *_System _oss_beginBlockp)(void *, long, char **, long *);
    void (DLL_ENTRY_FPTR *_System _oss_nextItemp)(void *, long *);
    void (DLL_ENTRY_FPTR *_System _oss_endBlockp)(void *, char **, long *, unsigned char);
    void (DLL_ENTRY_FPTR *_System _oss_chk_enump)(void *, long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_uenump)(void *, unsigned long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_binp)(void *, char *, unsigned char *, long, char *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_bitp)(void *, void *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_prt_charp)(void *, char *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_prt_crealp)(void *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_gentimep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_hexp)(void *, char *, unsigned char *, long, char *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_ncharp)(void *, char *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_octp)(void *, void *, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_prt_opentypep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_prt_pbitp)(void *, void *, unsigned long, unsigned long);
    void (DLL_ENTRY_FPTR *_System _oss_prt_realp)(void *, double);
    void (DLL_ENTRY_FPTR *_System _oss_prt_utctimep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_indentp)(void *, int);
    void (DLL_ENTRY_FPTR *_System _oss_prt_mbcharp)(void *, unsigned char *, long, unsigned short);
    void (DLL_ENTRY_FPTR *_System _oss_prt_enump)(void *, ULONG_LONG, struct _string_data const *, int);
    void *(DLL_ENTRY_FPTR *_System _oss_dec_getmem_internalp)(void *, long, ossBoolean);
    void *(DLL_ENTRY_FPTR *_System _oss_getdispmemp)(void *, long);
    void *(DLL_ENTRY_FPTR *_System _oss_dec_gettempmemp)(void *, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_freetempmemp)(void *, void *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_binp)(void *, char *, unsigned char *, long, char *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_bitp)(void *, void *, unsigned long);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_charp)(void *, char *, unsigned long);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_crealp)(void *, char *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_gentimep)(void *, void *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_hexp)(void *, char *, unsigned char *, long, char *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_ncharp)(void *, char *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_octp)(void *, void *, unsigned long);


    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_pbitp)(void *, void *, unsigned long, unsigned long);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_realp)(void *, double);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_utctimep)(void *, void *);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_mbcharp)(void *, unsigned char *, long, unsigned short);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_intp)(void *, LONG_LONG);
    char *(DLL_ENTRY_FPTR *_System _oss_getdisp_uintp)(void *, ULONG_LONG);
    void  (DLL_ENTRY_FPTR *_System _oss_free_dispp)(void *, void *);
    int   (DLL_ENTRY_FPTR *_System _oss_init_oset_tablep)(void *, const void * ,
							 unsigned int , const void * , unsigned int, void *);
    char (DLL_ENTRY_FPTR *_System _ossCmpPrimitiveValuep)(void *, void *, void *,
							long, long, int);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_valuep)(void *, int, void *, void *);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_membitsp)(unsigned char *, unsigned char *, long);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_arrbitsp)(unsigned char *, unsigned char *, long, long);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_unbnd_octetp)(void *, void *, short, long);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_huge_intp)(void *, void *, short, int);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_link_objp)(void *, void *, long);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_dlink_objp)(void **, void **, long);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_open_typep)(void *, void *, void*);
    void   (DLL_ENTRY_FPTR *_System _oss_init_xapi_entryp)(void *, const void *);
    int   (DLL_ENTRY_FPTR *_System _oss_cpy_valuep)(void *, int , void *, void **);
    void **(DLL_ENTRY_FPTR *_System _oss_cpy_link_objp)(void *, void **, void **, long);
    void **(DLL_ENTRY_FPTR *_System _oss_cpy_dlink_objp)(void *, void **, void **, long);
    void * (DLL_ENTRY_FPTR *_System _oss_cpy_unbnd_octetp)(void *, void *, void *, short, long);
    char * (DLL_ENTRY_FPTR *_System _oss_cpy_char_realp)(void *, char *);
    OpenType * (DLL_ENTRY_FPTR *_System _oss_cpy_open_typep)(void *, OpenType *, OpenType *);
    void *(DLL_ENTRY_FPTR *_System _oss_dec_realloctempmemp)(void *, void *, long, long);
    void (DLL_ENTRY_FPTR *_System _oss_dec_freep)(void *, void *);
    void (DLL_ENTRY_FPTR *_System _oss_freedispmemp)(void *, void *);
    void * (DLL_ENTRY_FPTR *_System _oss_cpy_unbnd_octet_iap)(void *, void *, void *, short, long, unsigned int);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_unbnd_octet_iap)(void *, void *, short, long, unsigned int);
    int   (DLL_ENTRY_FPTR *_System _oss_cmp_huge_int_iap)(void *, void *, short, int, unsigned int);
    char (DLL_ENTRY_FPTR *_System _oss_not_dfltp)(void *, void *, void *, long,
						  long, int);
    ossBoolean (DLL_ENTRY_FPTR *_System _oss_not_dflt_iap) (void *, void *, void *, long,
						unsigned int, long, int);
    void (DLL_ENTRY_FPTR *_System _ossSetOutMemQueuep)(void *, long *, char **, unsigned);
    void (DLL_ENTRY_FPTR *_System _ossFreeEncMemoryp)(void *);
    void *(DLL_ENTRY_FPTR *_System _oss_epop_globalp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_enc_errorp) (void *, char, int, long);
    struct ossGlobal *(DLL_ENTRY_FPTR *_System _oss_push_globalp)      (void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac_lp)  (void *, char *, unsigned long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac2_lp) (void *, unsigned short *, unsigned long, void *);
    void (DLL_ENTRY_FPTR *_System _oss_chk_pac4_lp) (void *, OSS_INT32 *, unsigned long, void *);
#else /* !SOED */
    void (DLL_ENTRY_FPTR *_System ossDenErrorp)(void *, enum warning, void *);
    void (DLL_ENTRY_FPTR *_System ossSignalHdlp)(int, void *);
    void (DLL_ENTRY_FPTR *_System _oss_ex_parse_creal_X693p)(char *, void *);
    void (DLL_ENTRY_FPTR *_System ossLinkOidp)(void *);
    void (DLL_ENTRY_FPTR *_System ossResetNestingp)(void *);
    void (DLL_ENTRY_FPTR *_System ossIncreaseConstructedNestingp)(void *);
    ossBoolean (DLL_ENTRY_FPTR *_System ossIncreaseSeqSetNestingp)(void *, int);
    void (DLL_ENTRY_FPTR *_System ossDecreaseConstructedNestingp)(void *);
    void (DLL_ENTRY_FPTR *_System ossDecreaseSeqSetNestingp)(void *);
    ossBoolean (DLL_ENTRY_FPTR *_System ossCheckUTF8Stringp)(void *, unsigned long);
#if defined(LEAN)
    void (DLL_ENTRY_FPTR *_System placeholder[4])(void);
#endif /* LEAN */
#endif /* !SOED */
    int (DLL_ENTRY_FPTR *_System ossGetConstructedNestingLimitp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetConstructedNestingLimitp)(void *, int);
    int (DLL_ENTRY_FPTR *_System ossGetSeqSetNestingLimitp)(void *);
    int (DLL_ENTRY_FPTR *_System ossSetSeqSetNestingLimitp)(void *, int);
    int  api;
#ifndef SOED
    void **(DLL_ENTRY_FPTR *_System _oss_load_enc_stackp)(void *, OSS_UINT32 *);
    void (DLL_ENTRY_FPTR *_System _oss_save_enc_stackp)(void *, OSS_UINT32);
    void **(DLL_ENTRY_FPTR *_System _oss_increment_enc_stackp)(void *);
    void **(DLL_ENTRY_FPTR *_System _oss_decrement_enc_stackp)(void *);
    void (DLL_ENTRY_FPTR *_System _oss_free_crealp)(void *, char *);
#else  /* !SOED */
    void (DLL_ENTRY_FPTR *_System ossCloseDecodeContainingp)(void *);
#endif /* !SOED */
    int (DLL_ENTRY_FPTR *_System ossBinary2XMLp)(void *, int,
		    				 ossEncodingRules, void *,
						 void *);
    int (DLL_ENTRY_FPTR *_System ossXML2Binaryp)(void *, int,
		    				 ossEncodingRules, void *,
						 void *);
    void (DLL_ENTRY_FPTR *_System ossPrintXMLp)(void *, char *, long,
						ossBoolean);
    ossBoolean (DLL_ENTRY_FPTR *_System oss_is_float_special_valuep)(void *, int, int);
    char *(DLL_ENTRY_FPTR *_System oss_get_float_special_kind_stringp)(int, ossBoolean);
    ossBoolean (DLL_ENTRY_FPTR *_System oss_set_float_special_valuep)(void *, int, int);
} ApiTbl;

typedef struct cpyvalTbl {
    int (DLL_ENTRY_FPTR *_System ossCpyValuep)(void *, int, void *, void **);
} CpyValTbl;

typedef struct cmpvalTbl {
    int (DLL_ENTRY_FPTR *_System ossCmpValuep)(void *, int, void *, void *);
    int (DLL_ENTRY_FPTR *_System oss_compare_themp)(void *, void *, void *, void *);
} CmpValTbl;

typedef struct berrealTbl {
    long (DLL_ENTRY_FPTR *_System ossBerEncodeRealp)(void *, void *,
							unsigned char *);
    long (DLL_ENTRY_FPTR *_System ossBerDecodeRealp)(void *, void *,
								long, char);
    void (DLL_ENTRY_FPTR *_System ossPrintRealp)(void *, void *,
							unsigned char *);
} BerRealTbl;

typedef struct printPerTbl {
    int (DLL_ENTRY_FPTR *_System ossPrintPerp)(void *, int *,void *, void **, long, void *);
    int (DLL_ENTRY_FPTR *_System ossPrintXPerp)(void *, int *,void *, void **, long, void *);
    int (DLL_ENTRY_FPTR *_System ossPrintPerDecodingp)(void *, void *, char **, void *, void *, long *, void *, unsigned, void *, long, void *, void *, int);
} PrintPerTbl;

typedef struct perrealTbl {
    void (DLL_ENTRY_FPTR *_System ossPerEncodeRealp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossPerDecodeRealp)(void *, void *);
    void (DLL_ENTRY_FPTR *_System ossPrintRealp)(void *, void *,
							unsigned char *);
} PerRealTbl;

typedef struct oidTbl {
int (DLL_ENTRY_FPTR *_System ossEncodedOidToAsnValp)(void *,
						const void *, void *);
int (DLL_ENTRY_FPTR *_System ossEncodedOidToDotValp)(void *,
						const void *, void *);
int (DLL_ENTRY_FPTR *_System ossAsnValToEncodedOidp)(void *,
						const char *, void *);
int (DLL_ENTRY_FPTR *_System ossDotValToEncodedOidp)(void *,
						const char *, void *);
int (DLL_ENTRY_FPTR *_System ossEncodedRelOidToAsnValp)(void *,
						const void *, void *);
int (DLL_ENTRY_FPTR *_System ossEncodedRelOidToDotValp)(void *,
						const void *, void *);
int (DLL_ENTRY_FPTR *_System ossAsnValToEncodedRelOidp)(void *,
						const void *, void *);
int (DLL_ENTRY_FPTR *_System ossDotValToEncodedRelOidp)(void *,
						const void *, void *);
int (DLL_ENTRY_FPTR *_System oid_e2cp)(void *, const void *,
						void *, short );
} OidTbl;

/*
 * The structure "functionTables" is used to store DLL-related information.
 */
typedef struct functionTables {
    HWND        hWnd;           /* Handle of the window */
    LONG        index;          /* Current index into the file pointer array;
				 * it indicates the number of lines written */
    MEMBLOCK   *memBlock;       /* Pointer to a current node of a memory
				 * handling linked list of MEMBLOCKs */
    MEMBLOCK   *startBlock;     /* Pointer to the first node of a memory
				 * handling linked list of MEMBLOCKs */
    short       length;         /* Length of a line that is written only
				 * in part and no '\n' symbol was reached yet */
    short       blockNumber;    /* Current MEMBLOCK number */
    FILE       *tmpfp;          /* Temporary output file with tracing info */
    char        tmpfn[16];      /* Temporary output file name */
    BOOL        endSwitch;      /* Indicates if a '\n' symbol was reached or
				 * not when writing a tracing info file to
				 * a window */
    BOOL        conSwitch;      /* If FALSE, the output goes to a console,
				 * otherwise to a window */
    BOOL	ossEncoderDecoderType; /* SOED vs. TOED */
    BOOL	cstrainNeeded;  /* If TRUE, constraint checking is needed */
    CstrainTbl *cstrainTbl;     /* Constraint checker DLL function table */
    BERTbl     *berTbl;         /* BER & DER DLL function table */
    PERTbl     *perTbl;         /* PER DLL function table */
    ApiTbl     *apiTbl;         /* Spartan/basic API DLL function table */
    CpyValTbl  *cpyvalTbl;      /* Value copier DLL function table */
    CmpValTbl  *cmpvalTbl;      /* Value comparator DLL function table */
    BerRealTbl *berrealTbl;     /* BER/DER encoder/decoder real DLL function
				 * table */
    void       *berpdvTbl;      /* PER encoder/decoder EMBEDDED PDV DLL
				 * function table */
    PerRealTbl *perrealTbl;     /* PER encoder/decoder real DLL function table */
    void       *perpdvTbl;      /* BER encoder/decoder EMBEDDED PDV DLL
				 * function table */
    OidTbl     *oidTbl;         /* OBJECT IDENTIFIER converter DLL
				 * function table */
    HINSTANCE   hBerDLL;        /* Handle of BER/DER encoder/decoder DLL */
    HINSTANCE   hPerDLL;        /* Handle of PER DLL */
    HINSTANCE   hCtlDLL;        /* Handle of control table/code file DLL */
    HINSTANCE   hMemDLL;        /* Handle of memory manager DLL */
    HINSTANCE   hCstrainDLL;    /* Handle of constraint checker DLL */
    HINSTANCE   hApiDLL;        /* Handle of Spartan/basic API DLL */
    HINSTANCE   hCpyvalDLL;     /* Handle of value copier DLL */
    HINSTANCE   hCmpvalDLL;     /* Handle of value comparator DLL */
    HINSTANCE   hBerrealDLL;    /* Handle of BER/DER encoder/decoder real DLL */
    HINSTANCE   hBerpdvDLL;     /* Handle of BER encoder/decoder EMBEDDED PDV
				 * DLL */
    HINSTANCE   hPerrealDLL;    /* Handle of PER encoder/decoder real DLL */
    HINSTANCE   hPerpdvDLL;     /* Handle of PER encoder/decoder EMBEDDED PDV
				 * DLL */
    HINSTANCE   hOidDLL;        /* Handle of OBJID converter DLL */
    MemManagerTbl *memMgrTbl;   /* Memory manager DLL function table */
    XERTbl      *xerTbl;        /* XER & CXER DLL function table */
    HINSTANCE   hXerDLL;        /* Handle of XER/CXER encoder/decoder DLL */
    void       *reserved[8];    /* Reserved for possible future use */
} FunctionTables;

#if defined(_WINDOWS) && !defined(_WIN32) && !defined(WIN32)
#define GWL_USERDATA 0
#endif /* _WINDOWS && !_WIN32 && !WIN32 */
extern void * const ctl_tbl;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#if defined(macintosh) && defined(__CFM68K__)
#pragma import reset
#endif

#elif !defined(DLL_ENTRY)
#include <stdarg.h>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#define DLL_ENTRY      WINAPI
#define DLL_ENTRY_FDEF WINAPI
#define DLL_ENTRY_FPTR WINAPI
#elif defined(__WATCOMC__) && defined(__DOS__)
#define DLL_ENTRY __cdecl
#define DLL_ENTRY_FDEF __cdecl
#define DLL_ENTRY_FPTR __cdecl
#define PUBLIC
#else
#define DLL_ENTRY
#define DLL_ENTRY_FDEF
#define DLL_ENTRY_FPTR
#define PUBLIC
#endif /* _WIN32 || WIN32 */
#undef  _System
#define _System
#endif /* _WINDOWS || _WIN32 || __OS2__ || NETWARE_DLL */
#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32))
#pragma pack(pop, ossPacking)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack()
#elif defined(__BORLANDC__) && (defined(__WIN32__) || defined(__MSDOS__))
#pragma option -a.
#elif defined(__IBMC__) && (defined(__WIN32__) || defined(__OS2__))
#pragma pack()
#elif defined(__WATCOMC__) && (defined(__NT__) || defined(__WINDOWS__) || defined(__DOS__))
#pragma pack(pop)
#endif /* _MSC_VER && _WIN32 */


#endif /* OSSDLL_H */
