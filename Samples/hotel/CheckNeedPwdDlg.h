#pragma once
#include "afxwin.h"
#include "resource.h"


// CCheckNeedPwdDlg �Ի���

class CCheckNeedPwdDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckNeedPwdDlg)

public:
	CCheckNeedPwdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckNeedPwdDlg();

// �Ի�������
	enum { IDD = IDD_CHECKNEEDPWD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_GuiPwdEdit;
	afx_msg void OnBnClickedOk();
	CString m_pwd;
	BOOL m_pwdIsRight;
};
