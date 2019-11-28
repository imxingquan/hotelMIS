/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		����
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"
#include "HPayBdy.h"
#include "DiningRoomTab.h"
// CPayDialog �Ի���

class CPayDialog : public CDialog
{
	DECLARE_DYNAMIC(CPayDialog)

public:
	CPayDialog(CWnd* pParent,int tableId,int roomId);   // ��׼���캯��
	virtual ~CPayDialog();

// �Ի�������
	enum { IDD = IDD_PAY_DLG };
	enum JSFS{ XJ=1,MCARD=2,XYCARD=3,ZP=4};
	JSFS m_nCurrJSFS;

public:
	//Control Var
	CGuiGroupBox m_GuiGroupBoxL;
	CGuiGroupBox m_GuiGroupBoxRT;
	CGuiGroupBox m_GuiGroupBoxRB;
	CListCtrl m_GuiListCtrlReckoning;
	CGuiEdit m_GuiEditML;
	CGuiEdit m_GuiEditYS;
	CGuiEdit m_GuiEditSS;
	CGuiEdit m_GuiEditZK;
	CGuiEdit m_GuiEditSJ;
	CGuiEdit m_GuiEditZY;
	CGuiEdit m_GuiEditDj;
	CButton m_GuiButtonInvoice; //checkbox
	CGuiButton m_GuiButtonJZ;
	CGuiButton m_GuiButtonGZ;
	CGuiButton m_GuiButtonPrint;
	CGuiButton m_GuiButtonOk;
	CButton m_GuiCheckDaiJin;
	CGuiEdit m_GuiEditDaiJin;
	CGuiButton m_GuiButtonCancel;
	CSpinButtonCtrl m_GuiSpinML;
	

	//Binding Var
	float m_daijin;
	BOOL m_bCheckDaiJin;
	int m_tableId,m_roomId;
	BOOL m_sswrCheck;

	float m_ml;			//�����˿�
	float m_ys;			//Ӧ���˿�
	float m_ss;			//ʵ���˿�
	float m_zk;			//�ۿ��˿�
	float m_sj;			//ʵ���տ�
	float m_zy;			//�����˿�
	BOOL m_invoice;		//��Ҫ��Ʊ
	float m_subscription; //����


	CString m_bz;
	// ��Ա�������ÿ���֧Ʊ֧��
	float m_zfprice;
	CEdit m_GuiZfPriceEdit;


	hotelMIS::HPayBdy *m_payBdy;
	hotelMIS::KDBCon m_con;
	CFont m_font;
	CBrush m_brush;
	CDiningRoomTab *m_pRoomTab;
	CString m_accountId;
	CComboBox m_GuiJzfsCombo;
	CEdit m_GuiMbhEdit;
	CEdit m_GuiMxmEdit;
	CButton m_GuiGetMemBtn;
	CEdit m_GuiCzEdit;
	CString m_bh;
	CString m_mname;
	float m_czmoney;
	string m_account_Id;
	
	//op
	void Init();
	afx_msg void OnEnChangeEditSj();
	afx_msg void OnBnClickedButtonJz();
	BOOL TestDigit(CString &s,CEdit *pEdit);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	bool WarningPrint();

	// ��ʼ����������(���)
	void InitJz();
	void Refresh();
	float myRound(float x);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void PrintReport(CDC *dc);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGz();
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedCheckDaijin();
	afx_msg void OnEnChangeEditDaijin();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnCbnSelchangeJzfsCombo();
	afx_msg void OnEnChangeMbhEdit();
	

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSswrCheck();
	
	
};