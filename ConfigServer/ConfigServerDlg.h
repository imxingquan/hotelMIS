// ConfigServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

UINT ThreadProc(LPVOID pParam);
struct CMSG
{
	TCHAR t[MAX_PATH];
};
// CConfigServerDlg �Ի���
class CConfigServerDlg : public CDialog
{
// ����
public:
	CConfigServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONFIGSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int pos;
	int m_time;

	// ���ɵ���Ϣӳ�亯��
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
