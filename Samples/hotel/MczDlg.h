#pragma once


// CMczDlg �Ի���
#include "resource.h"

class CMczDlg : public CDialog
{
	DECLARE_DYNAMIC(CMczDlg)

public:
	CMczDlg(CWnd* pParent ,CString bh,CString name);   // ��׼���캯��
	virtual ~CMczDlg();

// �Ի�������
	enum { IDD = IDD_MCZ_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_bh;
	CString m_mname;
	float m_czmoney;
	afx_msg void OnBnClickedOk();
	CString m_remark;
};
