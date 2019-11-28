/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
��Ӫ�±���
Revision History:
Author	Date		Description
------	----		------------
��Ȫ    04/23/05	v1.2 
��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HReportBdy.h"

// CReportMonthDialog �Ի���

class CReportMonthDialog : public CDialog
{
	DECLARE_DYNAMIC(CReportMonthDialog)

public:
	CReportMonthDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportMonthDialog();

	// �Ի�������
	enum { IDD = IDD_REPORT_MONTH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

	static void DrawByMonths(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�
	static void DrawByCook(CDC &memDC, PRNINFO PrnInfo);
	static void DrawByPayStatus(CDC &memDC, PRNINFO PrnInfo);

	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnCbnEditchangeComboMonth();
	afx_msg void OnCbnEditchangeComboKind();
	afx_msg void OnTotalMonth();

	virtual BOOL OnInitDialog();

	
};
