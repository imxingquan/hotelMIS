/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		用户登录
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "KDBCon.h"
#include "HAdmin.h"
#include "HAdminBdy.h"
// CLoginDlg 对话框

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//Control Variable
	CGuiEdit m_GuiEditUserName;
	CGuiEdit m_GuiEditPassword;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	
	//Binding Variable
	CString m_userName;		// 登录用户名
	CString m_password;		// 密码
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_GuiStaticMsg;
	afx_msg void OnBnClickedOk();
	CComboBox m_userComboBox;
	CString m_uName;

	hotelMIS::KDBCon m_con;
};
