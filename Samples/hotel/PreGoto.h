#if !defined(AFX_PREGOTO_H__411EF153_F8A4_48FD_878E_B3FD6FF33D63__INCLUDED_)
#define AFX_PREGOTO_H__411EF153_F8A4_48FD_878E_B3FD6FF33D63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreGoto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreGoto dialog

class CPreGoto : public CDialog
{
// Construction
public:
	CPreGoto(CWnd* pParent = NULL);   // standard constructor
	int nMax;		//最大页码
	int nGoto;		//转向页码
	int nCurPage;	//当前页码

// Dialog Data
	//{{AFX_DATA(CPreGoto)
	enum { IDD = DLG_SYS_PREGOTO };
	CSpinButtonCtrl	CSpinGoto;
	CEdit	CEdtGoto;
	int		vGoto;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreGoto)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreGoto)
	afx_msg void OnOk();
	afx_msg void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusGoto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREGOTO_H__411EF153_F8A4_48FD_878E_B3FD6FF33D63__INCLUDED_)
