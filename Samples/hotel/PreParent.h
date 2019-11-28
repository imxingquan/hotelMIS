#if !defined(AFX_PRVPARENT_H__8FA9EB85_4FCF_4D19_A88F_FCFBCB478CC3__INCLUDED_)
#define AFX_PRVPARENT_H__8FA9EB85_4FCF_4D19_A88F_FCFBCB478CC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PreView.h"		//打印预览

// PrvParent.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CPreParent dialog
//A4 = 210 * 297 mm
//B5 = 169 * 239 
class CPreParent : public CDialog
{
// Construction
public:
	void SetCallBackFun(PRINTPREVIEW pv, PRNINFO PrnInfo);
	CPreParent(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CPreParent)
	enum { IDD = DLG_SYS_PREPARENT };
	CStatic	CSDown;
	CStatic	CSUP;
	CListBox	CList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreParent)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	PRINTPREVIEW pDrawInfo;
	PRNINFO		PrnInfo;
	HICON		m_hIcon;
	CToolBar	m_wndtoolbar;
	CRect		m_TbRect;
	CRect		rcClient;
	CPreView	*pPreView;
	int			m_nCount;	//共多少行数据
	int			m_OneCount, m_NextCount;	//第一页的行数, 其它页的行数
	int			m_PosPage;		//当前页
	int			m_nCountPage;	//共有多少页;

	static LRESULT CALLBACK ListProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static WNDPROC		wpListProc;
	static HWND			hPrvWnd;

	void	UpdatePreViewWnd();


	// Generated message map functions
	//{{AFX_MSG(CPreParent)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTop();
	afx_msg void OnPrevious();
	afx_msg void OnGoto();
	afx_msg void OnNext();
	afx_msg void OnLast();
	afx_msg void OnExit();
	afx_msg void OnPrint();
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRVPARENT_H__8FA9EB85_4FCF_4D19_A88F_FCFBCB478CC3__INCLUDED_)
