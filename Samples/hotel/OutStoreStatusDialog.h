/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		����״̬
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// COutStoreStatusDialog �Ի���

class COutStoreStatusDialog : public CDialog
{
	DECLARE_DYNAMIC(COutStoreStatusDialog)

public:
	COutStoreStatusDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COutStoreStatusDialog();

// �Ի�������
	enum { IDD = IDD_OUTSTORE_STATUS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
