#pragma once
#include "afxwin.h"

#include "resource.h"
// CRepAddDlg �Ի���

class CRepAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepAddDlg)

public:
	CRepAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepAddDlg();

// �Ի�������
	enum { IDD = IDD_ADDREP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CString m_name;
	int m_bh;
	float m_price;
	float m_num;
	CString m_kindName;
public:
	CFont m_font;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
