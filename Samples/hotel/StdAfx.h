// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__98E93E6B_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_STDAFX_H__98E93E6B_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

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

#include <Guilib.h>
#include <afxcview.h>
#include <afxdlgs.h>

//#define _CRTDBG_MAP_ALLOC
//#include<stdlib.h>
//#include<crtdbg.h>
#include <WINSPOOL.H>


#define WM_ONREDRAW WM_USER + 100
#define WM_GETROOMNO WM_USER + 101
#define	WM_DELMENU	WM_USER + 102
#define WM_MODIFIED WM_USER + 103
#define WM_DELSELF WM_USER + 104
#define WM_GETTABLEINFO WM_USER +105


//#pragma warning(disable:4244)

#define	 B5_W			210				//B5纸宽度mm
#define	 B5_H			297				//B5纸高度mm
#define	 B5_ONELINE		35				//B5纸第一页行数
#define	 B5_OTHERLINE	37				//B5纸其它页行数

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

enum TOTAL_FL
{
	SHIWU = 1,		//食物
	YINLIAO=2,		//饮料
	JIULEI=3,		//酒类
	XIANGYAN=4,		//香烟
	ZAXIANG=5,		//杂项
	FUWUFEI=6		//服务费
};

typedef void(*PRINTPREVIEW) (CDC &MemDC, PRNINFO PrnInfo);

#include "resource.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__98E93E6B_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
