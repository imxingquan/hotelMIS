// CreateDBDlg.h : 头文件
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		创建系统数据库 调用 demo.db 或 starand.db 文件中的Sql执行
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉	08/28/05	v1.3 版本

--*/

#pragma once
#include "afxwin.h"

#include "config.h"
#include "KDBCon.h"


// CCreateDBDlg 对话框
class CCreateDBDlg : public CDialog
{
// 构造
public:
	CCreateDBDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CREATEDB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetdbButton();
	LRESULT OnDetails(WPARAM wParam ,LPARAM lParam);
	
	CEdit m_hostEdit;
	CEdit m_portEdit;
	CEdit m_nameEdit;
	CEdit m_passwordEdit;
	CEdit m_detailsEdit;
	CString m_host;
	CString m_port;
	CString m_name;
	CString m_password;

	hotelMIS::KDBCon con;
	CButton m_setDBBtn;
	CString m_details;
	afx_msg void OnBnClickedSetdemodbBtn();
private:
	void SetDB(string dbfile);
public:
	CButton m_setDemoDBBtn;
};
