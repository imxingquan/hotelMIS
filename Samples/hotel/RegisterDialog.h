/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		ϵͳע��
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"

#include "resource.h"

// CRegisterDialog �Ի���

class CRegisterDialog : public CDialog
{
	DECLARE_DYNAMIC(CRegisterDialog)

public:
	CRegisterDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterDialog();

// �Ի�������
	enum { IDD = IDD_CDKEY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiEdit m_GuiCdKey1Edit;
	CGuiEdit m_GuiCdKey2Edit;
	CGuiEdit m_GuiCdKey3Edit;
	CGuiEdit m_GuiCdKey4Edit;
	afx_msg void OnBnClickedOk();
	CString m_cdkey1;
	CString m_cdkey2;
	CString m_cdkey3;
	CString m_cdkey4;
	virtual BOOL OnInitDialog();
	CGuiLinkButton m_linkBtn;

	afx_msg void OnBnClickedCancel();
	CStatic m_GuiRegStatic;
};
