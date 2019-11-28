/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��Ӫ�걨��
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "HReportBdy.h"
#include "afxcmn.h"

// CReportYearDialog �Ի���

class CReportYearDialog : public CDialog
{
	DECLARE_DYNAMIC(CReportYearDialog)

public:
	CReportYearDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportYearDialog();

// �Ի�������
	enum { IDD = IDD_REPORT_YEAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;
	CGuiComboBoxExt m_GuiComboYear;
	CGuiComboBoxExt m_GuiComboKind;
	CGuiButton m_GuiButtonPrint;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiTotalYearBtn;
	//CGuiCheckBox m_GuiCookCheck;	
	CButton m_GuiCookCheck;
	CListCtrl m_GuiListReportYear;
	BOOL m_byCook;
	BOOL m_bPayStatus;

	CString m_year;
	CString m_kind;
	hotelMIS::HReportBdy m_reportBdy;
	map<int,string> m_map;
	int m_nIndex;
	int m_byColNum;
public:
	//for print
	
	hotelMIS::KDBCon m_con;
	static CString m_exp;
	static CString m_hotelname;

	void PrintViewByYear();
	void PrintViewByCook();
	void PrintViewByPayStatus();

	static void DrawByYear(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�
	static void DrawByCook(CDC &memDC, PRNINFO PrnInfo);
	static void DrawByPayStatus(CDC &memDC, PRNINFO PrnInfo);
	
public:

	void totalByYear();
	void totalByYearCook();
	void totalByPayStatus();
	
	void Refresh();

	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnTotalByYear();

	virtual BOOL OnInitDialog();
	
	afx_msg void OnDelAccount();
	afx_msg void OnDelallAccount();
	afx_msg void OnNMRclickListReportYear(NMHDR *pNMHDR, LRESULT *pResult);
	
};
