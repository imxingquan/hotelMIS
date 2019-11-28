/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统注册
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"

#include "resource.h"

// CRegisterDialog 对话框

class CRegisterDialog : public CDialog
{
	DECLARE_DYNAMIC(CRegisterDialog)

public:
	CRegisterDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegisterDialog();

// 对话框数据
	enum { IDD = IDD_CDKEY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
