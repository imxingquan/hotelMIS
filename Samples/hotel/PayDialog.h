/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		结账
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"
#include "HPayBdy.h"
#include "DiningRoomTab.h"
// CPayDialog 对话框

class CPayDialog : public CDialog
{
	DECLARE_DYNAMIC(CPayDialog)

public:
	CPayDialog(CWnd* pParent,int tableId,int roomId);   // 标准构造函数
	virtual ~CPayDialog();

// 对话框数据
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

	float m_ml;			//摸零账款
	float m_ys;			//应收账款
	float m_ss;			//实收账款
	float m_zk;			//折扣账款
	float m_sj;			//实际收款
	float m_zy;			//找余账款
	BOOL m_invoice;		//需要发票
	float m_subscription; //定金


	CString m_bz;
	// 会员卡，信用卡，支票支付
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

	// 初始化结账数据(清空)
	void InitJz();
	void Refresh();
	float myRound(float x);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
