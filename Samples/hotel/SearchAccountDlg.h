/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		�˵���ѯ
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 
	��Ȫ    04/10/06    �����ش�СƱ�Ĺ���

--*/
#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "atlcomtime.h"
#include "HAccSearchBdy.h"
#include "HAccountCtrl.h"
#include "HAccount.h"
#include "KDBCon.h"
#include "HSetHotelPrintMsg.h"
#include "HRoomCtrl.h"

// CSearchAccountDlg �Ի���

class CSearchAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchAccountDlg)

public:
	CSearchAccountDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchAccountDlg();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxUL;
	CGuiGroupBox m_GuiGroupBoxUR;
	CGuiGroupBox m_GuiGroupBoxB;
	CDateTimeCtrl m_GuiDateTime1Ctrl;
	CDateTimeCtrl m_GuiDateTime2Ctrl;
	
	CGuiComboBoxExt m_GuiAccStatusCombo;
	CGuiButton m_GuiSrhByDateBtn;	
	CGuiButton m_GuiSrhByAccidBtn;
	CGuiButton m_GuiOpenDownBtn;
	CGuiButton m_GuiRePrintBtn;
	CGuiButton m_GuiPrintBtn;
	CGuiEdit m_GuiAccidEdit;
	CListCtrl m_GuiAccListCtrl;
	CListCtrl m_GuiDetailsListCtrl;
		
	COleDateTime m_date1;
	COleDateTime m_date2;
	CString m_accid;
	hotelMIS::HAccSearchBdy m_accSearchBdy;
	hotelMIS::KDBCon m_con;
	map<int,string> m_accMap; //map<pos,accid>
	void Init();
	void Refresh();
	void Refresh2();
	void Refresh3();
	void PrintReport(CDC *dc,string accountId);
	static void DrawReport(CDC &memDC, PRNINFO PrnInfo);

	static CString m_exp;
	static CString m_exp2;
	static CString m_hotelname;
	afx_msg void OnSearchByDate();
	afx_msg void OnSearchByAccid();
	afx_msg void OnNMClickAccountList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReprint();
	afx_msg void OnHdnItemchangedAccountList(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedButtonPrint();
	
};
