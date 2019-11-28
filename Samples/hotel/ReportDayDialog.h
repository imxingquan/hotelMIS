/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��Ӫ�ձ���
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "HReportBdy.h"

// CReportDayDialog �Ի���

class CReportDayDialog : public CDialog
{
	DECLARE_DYNAMIC(CReportDayDialog)

public:
	CReportDayDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportDayDialog();

// �Ի�������
	enum { IDD = IDD_REPORT_DAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	void Init();
	float myRound(float x);

	DECLARE_MESSAGE_MAP()
public:
	//control var
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;


	CGuiButton m_GuiButtonSearch;
	CGuiButton m_GuiButtonPrint;
	


	CListCtrl m_GuiListCtrlReporyDay;	
	CDateTimeCtrl m_GuiDTCtrl;
	//bind var
	
	map<int,string> m_accMap;
	hotelMIS::HReportBdy m_reportBdy;
	int m_byColNum;
	static CString m_hotelname;
	hotelMIS::KDBCon m_con;
	static CString m_exp;
	
	COleDateTime m_dStart;
	COleDateTime m_tStart;
	COleDateTime m_dEnd;
	COleDateTime m_tEnd;

	hotelMIS::HAccountVec m_accvec;
public:
	void totalByDay();
	

	void PrintViewByDay();
	

	static void DrawByDay(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�
	

public:	
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPrint();

	afx_msg void OnPrintPreview();
	afx_msg void OnPopupPrint();
	afx_msg void OnExactExcel();
	afx_msg void OnNMDblclkListReportDay(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_jzfsCombo;
	int m_jsfsPos;
};
