/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		出库状态
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// COutStoreStatusDialog 对话框

class COutStoreStatusDialog : public CDialog
{
	DECLARE_DYNAMIC(COutStoreStatusDialog)

public:
	COutStoreStatusDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COutStoreStatusDialog();

// 对话框数据
	enum { IDD = IDD_OUTSTORE_STATUS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//control var
	CGuiGroupBox m_GuiGroupBox;
	CGuiComboBoxExt m_GuiComboKind;
	CGuiComboBoxExt m_GuiComBoStocks;
	CGuiButton m_GuiButtonPrint;
	CGuiButton m_GuiButtonCancel;
	CListCtrl m_GuiListCtrlOutStore;
	//bind var
	CString m_kind;
	CString m_stocks;
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnCbnSelchangeComboKind();
	afx_msg void OnCbnSelchangeComboStocks();
	virtual BOOL OnInitDialog();
};
