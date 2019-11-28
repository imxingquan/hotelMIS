#if !defined(AFX_PREVIEW_H__CB7FE153_C705_48D6_B9CC_E9B1F061FC88__INCLUDED_)
#define AFX_PREVIEW_H__CB7FE153_C705_48D6_B9CC_E9B1F061FC88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CPreView dialog
#if defined (WIN32)
    #define IS_WIN32 TRUE
#else
    #define IS_WIN32 FALSE
#endif

#include "resource.h"

#define MAX_DEBUG_STRING    256
#define IS_NT      (0 != (IS_WIN32 && ((BOOL)(GetVersion() < 0x80000000))) )
#define IS_WIN32S  (0 != (IS_WIN32 && (BOOL)(!(IS_NT) && (LOBYTE(LOWORD(GetVersion()))<4))))
#define IS_WIN95   (0 != ((BOOL)(!(IS_NT) && !(IS_WIN32S)) && IS_WIN32))


class CPreView : public CDialog
{
// Construction
public:
	CPreView(CWnd* pParent = NULL);   // standard constructor
	void SetCallBackFun(PRINTPREVIEW pFun, PRNINFO sPrnInfo);
	void PrintDoc();
	void SetCurrentPage(int, int);
// Dialog Data
	//{{AFX_DATA(CPreView)
	enum { IDD = DLG_SYS_PREVIEW };
	//}}AFX_DATA
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreView)
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	PRINTPREVIEW	pDrawInfo;
	PRNINFO			PrnInfo;

	CBitmap		cBmp;
	CBrush		m_brush;
	CPen		cPen;
	int			nW, nH;
	CRect		WndRect;
	int			m_CountPage;	//共多少页
	int			m_CurPage;		//当前页

    SCROLLINFO  si;	
	int			iDeltaPerLine, iAccumDelta, xPt, yPt;


	void	SetScrollbar(int cx, int cy);
	HDC		GetPrinterDC(LPTSTR lpszFriendlyName, PDEVMODE pDevMode);
	LPTSTR	GetDefaultPrinterName(void);
	LPTSTR	GetRegistryString(HKEY hKeyClass, LPTSTR lpszSubKey, LPTSTR lpszValueName);
	LPTSTR	CopyString(LPTSTR  lpszSrc);
	PDEVMODE GetDefaultPrinterDevMode(LPTSTR lpszPrinterName);
	void	DebugMsg (LPTSTR lpszMessage,...);
	HDC		GetDefaultPrinterDC();

	// Generated message map functions
	//{{AFX_MSG(CPreView)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEW_H__CB7FE153_C705_48D6_B9CC_E9B1F061FC88__INCLUDED_)
