/*****************************************************************************/
/* Copyright (C) 2002-2003 OSS Nokalva, Inc.  All rights reserved.           */
/*****************************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/*****************************************************************************/
/* FILE: @(#)asn1glob.h	11.3  03/04/18                       */
/*****************************************************************************/

#ifndef ASN1GLOB_H
#define ASN1GLOB_H

#define getmem runtime_getmem
#include "ossdll.h"
#include "asn1code.h"
#undef getmem

#ifdef _WIN32
typedef struct osscagTbl {
    int (DLL_ENTRY_FPTR *_System ossCreateControlTablep)(struct ossAsn1Global *,
						char *, char *, void **);
    void (DLL_ENTRY_FPTR *_System ossDeleteControlTablep)(struct ossAsn1Global *,
						void *);
} OssCagTbl;


/*
 * The structure "cagWinParm" is used to store DLL-related information.
 */
typedef struct cagWinParm {
    OssCagTbl  *osscagTbl;      /* Runtime compiler DLL function table */
    HINSTANCE   hOsscagDLL;     /* Handle of runtime compiler DLL */
} CagWinParm;


PUBLIC void DLL_ENTRY ossLinkCAGL(struct ossAsn1Global *aworld);
#endif /* _WIN32 */

typedef struct ossAsn1Global {
    void	*ctlTbl;
    void	*(*mallocp)(size_t p);
    void	*(*reallocp)(void *p, size_t s);
    void	(*freep)(void *p);
    unsigned long parmFlags;
    unsigned int  isExternal:1;
    long	bufsAllocated;
    long	bufsFreed;
    void	*llink;		/* previous node on memory queue */
    void	*rlink;		/* next node on memory queue	 */
	/*
	 * used for storing DLL- & library NLMs-related parameters
	 */
#ifdef _WIN32
    CagWinParm	wp;
#endif /* _WIN32 */
} OssAsn1Global;

#endif /* ASN1GLOB_H */
