/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统警告弹出对话框
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once


// CSysWarningDialog 对话框
#include "resource.h"
#include "afxwin.h"

class CSysWarningDialog : public CDialog
{
	DECLARE_DYNAMIC(CSysWarningDialog)

public:
	CSysWarningDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysWarningDialog();

// 对话框数据
	enum { IDD = IDD_SYS_WARNING_DLG };
	void SetWarningMsg(CString msg){ m_warning_msg = msg;}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

	DECLARE_MESSAGE_MAP()
public:
	CString m_warning_msg;
	CString m_auto_close_msg;
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	int m_second;
	afx_msg void OnClose();
	CGuiButton m_GuiOkBtn;
	CStatic m_GuiWarningMsg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
