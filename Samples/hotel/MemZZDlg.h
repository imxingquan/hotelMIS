#pragma once

#include "resource.h"
#include "afxwin.h"
#include "KDBCon.h"

// CMemZZDlg �Ի���

class CMemZZDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemZZDlg)

public:
	CMemZZDlg(CWnd* pParent = NULL,CString bh="",CString name="",float money=0);   // ��׼���캯��
	virtual ~CMemZZDlg();

// �Ի�������
	enum { IDD = IDD_MEM_ZZ_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_GuiEditOutBh;
	CString m_OutBh;
	CString m_OutName;
	float m_OutRestMoney;
	float m_OutMoney;
	CString m_InBh;
	CString m_InName;
	hotelMIS::KDBCon m_con;

public:
	afx_msg void OnBnClickedZzoutBtn();
	afx_msg void OnEnChangeEditInzzBh();
	afx_msg void OnEnChangeEditZzoutBh();
	CString m_remark;
};
