/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
经营月报表
Revision History:
Author	Date		Description
------	----		------------
邢泉    04/23/05	v1.2 
邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HReportBdy.h"

// CReportMonthDialog 对话框

class CReportMonthDialog : public CDialog
{
	DECLARE_DYNAMIC(CReportMonthDialog)

public:
	CReportMonthDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportMonthDialog();

	// 对话框数据
	enum { IDD = IDD_REPORT_MONTH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;
	CGuiComboBoxExt m_GuiComboMonth;
	CGuiComboBoxExt m_GuiComboKind;
	CGuiComboBoxExt m_GuiYearCombo;
	CGuiButton m_GuiButtonPrint;
	CGuiButton m_GuiTotalMonthBtn;
	CGuiButton m_GuiButtonOk;
	//CGuiCheckBox m_GuiTotalMonthCheck;
	CButton m_GuiTotalMonthCheck;
	CListCtrl m_GuiListCtrlReportMonth;

	CString m_year;
	CString m_month;
	BOOL m_byCook;
	hotelMIS::HReportBdy m_reportBdy;
	int m_byColNum;
	BOOL m_bPayStatus;

	hotelMIS::KDBCon m_con;

	void totalByMonth();
	void totalByMonthCook();
	void totalByPayStatus();

	void PrintViewByCook();
	void PrintViewByMonths();
	void PrintViewByPayStatus();

	static CString m_exp;
	static CString m_hotelname;

	static void DrawByMonths(CDC &memDC, PRNINFO PrnInfo);  //打印回调
	static void DrawByCook(CDC &memDC, PRNINFO PrnInfo);
	static void DrawByPayStatus(CDC &memDC, PRNINFO PrnInfo);

	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnCbnEditchangeComboMonth();
	afx_msg void OnCbnEditchangeComboKind();
	afx_msg void OnTotalMonth();

	virtual BOOL OnInitDialog();

	
};
