#pragma once
#include "atlcomtime.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "HAccSearchBdy.h"
#include "HAccountCtrl.h"
#include "HAccount.h"
#include "KDBCon.h"
#include "HSetHotelPrintMsg.h"
#include "HRoomCtrl.h"

// CSyyReportDlg 对话框

class CSyyReportDlg : public CDialog
{
	DECLARE_DYNAMIC(CSyyReportDlg)

public:
	CSyyReportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSyyReportDlg();

// 对话框数据
	enum { IDD = IDD_SYY_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

protected:
	hotelMIS::HAccSearchBdy m_accSearchBdy;
public:
	COleDateTime m_date1;
	COleDateTime m_date2;
	CComboBox m_GuiAccStatusCombo;
	CListCtrl m_GuiAccListCtrl;
	CComboBox m_dwCombo;
	map<int,string> m_accMap;
	hotelMIS::KDBCon m_con;
	hotelMIS::HAccountVec m_vec;
	afx_msg void OnBnClickedSrhBydatebtn();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedPrintButton();
	COleDateTime m_time1;
	COleDateTime m_time2;

	CString m_acc_status;
	CString m_exp;

	afx_msg void OnExactExcel();
	afx_msg void OnPrintPreview();
	afx_msg void OnPopupPrint();

	afx_msg void OnNMDblclkAccountList(NMHDR *pNMHDR, LRESULT *pResult);
	
	float myRound(float x);

	BOOL m_cwCheck;
	CComboBox m_GuiJsfsCombo;
	int m_jsfs;
	afx_msg void OnCbnSelchangeAccstatusCombo();
	afx_msg void OnCbnSelchangeDwCombo();
};
