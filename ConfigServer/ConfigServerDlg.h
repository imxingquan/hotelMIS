// ConfigServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

UINT ThreadProc(LPVOID pParam);
struct CMSG
{
	TCHAR t[MAX_PATH];
};
// CConfigServerDlg 对话框
class CConfigServerDlg : public CDialog
{
// 构造
public:
	CConfigServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONFIGSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	int pos;
	int m_time;

	// 生成的消息映射函数
	void InitIdle();

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_GuiListBox;
	LRESULT OnSendMsg(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedButtonExit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	CButton m_GuiButtonExit;
	CString m_serverName;
	CString m_port;
	afx_msg void OnBnClickedButtonStart();
	CSpinButtonCtrl m_SpinCtrl;
};
