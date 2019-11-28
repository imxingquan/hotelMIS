#pragma once
#include "afxcmn.h"
#include "HAccSearchBdy.h"
#include "HAccountCtrl.h"
#include "HAccount.h"
#include "KDBCon.h"
#include "HSetHotelPrintMsg.h"
#include "HRoomCtrl.h"
// CXFDetailsDlg �Ի���

class CXFDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CXFDetailsDlg)

public:
	CXFDetailsDlg(CWnd* pParent,CString accountId);   // ��׼���캯��
	virtual ~CXFDetailsDlg();

// �Ի�������
	enum { IDD = IDD_XF_DETAILS_DIALOG };
protected:
	CString m_accountId;
	hotelMIS::HAccSearchBdy m_accSearchBdy;
	hotelMIS::KDBCon m_con;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void PrintReport(CDC *dc,CString accountId);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_xfDetailsList;
	virtual BOOL OnInitDialog();
	void Init();
	afx_msg void OnBnClickedButtonPrint();
};
