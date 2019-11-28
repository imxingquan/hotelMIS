// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D9580E2B_9161_42CE_80F0_310DFEF9BDE3__INCLUDED_)
#define AFX_STDAFX_H__D9580E2B_9161_42CE_80F0_310DFEF9BDE3__INCLUDED_

#pragma warning(disable : 4244 4146)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <WINSPOOL.H>


#define	 B5_W			182				//B5纸宽度mm
#define	 B5_H			257				//B5纸高度mm
#define	 B5_ONELINE		29				//B5纸第一页行数
#define	 B5_OTHERLINE	30				//B5纸其它页行数

//打印结构
typedef struct
{
	int 	nMaxLine;			//最大行数
	int		nCountPage;			//一共页数
	int		nCurPage;			//当前页码
	BOOL	IsPrint;			//是否打印
	HWND	hWnd;				//窗口句柄
	HWND	hListView;			//列表控件句柄
	TCHAR	szTag[256];			//其它数据
	int		nTag;				//其它数据
	LPVOID	lpVoid;				//其它数据
}PRNINFO, *PPRNINFO;

typedef void(*PRINTPREVIEW) (CDC &MemDC, PRNINFO PrnInfo);
#include "Resource.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D9580E2B_9161_42CE_80F0_310DFEF9BDE3__INCLUDED_)
