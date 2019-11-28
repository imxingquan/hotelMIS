#pragma once
#include "afxwin.h"
#include "resource.h"


// CCheckNeedPwdDlg 对话框

class CCheckNeedPwdDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckNeedPwdDlg)

public:
	CCheckNeedPwdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheckNeedPwdDlg();

// 对话框数据
	enum { IDD = IDD_CHECKNEEDPWD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_GuiPwdEdit;
	afx_msg void OnBnClickedOk();
	CString m_pwd;
	BOOL m_pwdIsRight;
};
