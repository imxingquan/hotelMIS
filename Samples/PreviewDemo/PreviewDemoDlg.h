// PreviewDemoDlg.h : header file
//

#if !defined(AFX_PREVIEWDEMODLG_H__1EABA665_F50F_45AE_9100_1FD9F02973BA__INCLUDED_)
#define AFX_PREVIEWDEMODLG_H__1EABA665_F50F_45AE_9100_1FD9F02973BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPreviewDemoDlg dialog

class CPreviewDemoDlg : public CDialog
{
// Construction
public:
	CPreviewDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPreviewDemoDlg)
	enum { IDD = IDD_PREVIEWDEMO_DIALOG };
	CListCtrl	CLtv;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static void DrawInfo(CDC &memDC, PRNINFO PrnInfo);

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPreviewDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWDEMODLG_H__1EABA665_F50F_45AE_9100_1FD9F02973BA__INCLUDED_)
