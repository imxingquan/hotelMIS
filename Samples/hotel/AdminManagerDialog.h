/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统用户管理
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAdminManagerDialog 对话框

class CAdminManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(CAdminManagerDialog)

public:
	CAdminManagerDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminManagerDialog();

// 对话框数据
	enum { IDD = IDD_ADMIN_MANAGER };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;
	CGuiEdit m_GuiEditAdminLogName;
	CGuiComboBoxExt m_GuiComboBoxAdminOType;
	CListCtrl m_GuiListCtrlAdmin;
	CGuiEdit m_GuiEditLogPassword;
	CGuiEdit m_GuiEditAdminName;
	CGuiEdit m_GuiEditAdminRemark;
	CGuiButton m_GuiButtonAddUpdate;
	CGuiButton m_GuiButtonDel;
	CGuiCheckBox m_GuiCheck01;
	CGuiCheckBox m_GuiCheck02;
	CGuiCheckBox m_GuiCheck03;
	CGuiCheckBox m_GuiCheck04;
	CGuiCheckBox m_GuiCheck05;
	CGuiCheckBox m_GuiCheck06;

	CString m_logName;
	CString m_adminOtype;
	CString m_adminName;
	CString m_adminRemark;
	BOOL m_op01;
	BOOL m_op02;
	BOOL m_op03;
	BOOL m_op04;
	BOOL m_op05;
	BOOL m_op06;

	afx_msg void OnBnClickedButtonAddUpdate();
	afx_msg void OnBnClickedButtonDel();
	
	virtual BOOL OnInitDialog();
};
