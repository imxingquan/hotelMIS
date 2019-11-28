#pragma once
#include "afxcmn.h"
#include "HAccSearchBdy.h"
#include "HAccountCtrl.h"
#include "HAccount.h"
#include "KDBCon.h"
#include "HSetHotelPrintMsg.h"
#include "HRoomCtrl.h"
// CXFDetailsDlg 对话框

class CXFDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CXFDetailsDlg)

public:
	CXFDetailsDlg(CWnd* pParent,CString accountId);   // 标准构造函数
	virtual ~CXFDetailsDlg();

// 对话框数据
	enum { IDD = IDD_XF_DETAILS_DIALOG };
protected:
	CString m_accountId;
	hotelMIS::HAccSearchBdy m_accSearchBdy;
	hotelMIS::KDBCon m_con;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void PrintReport(CDC *dc,CString accountId);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_xfDetailsList;
	virtual BOOL OnInitDialog();
	void Init();
	afx_msg void OnBnClickedButtonPrint();
};
