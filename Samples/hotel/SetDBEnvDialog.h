/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		数据库环境设置
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "resource.h"


// CSetDBEnvDialog 对话框
//#define IDD_SET_DBENV_DIALOG 202
class CSetDBEnvDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetDBEnvDialog)

public:
	CSetDBEnvDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDBEnvDialog();

// 对话框数据
	enum { IDD = IDD_SET_DBENV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_host;
	CString m_user;
	CString m_pwd;
	CString m_port;
};
