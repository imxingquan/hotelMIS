#pragma once
#include "afxwin.h"

#include "resource.h"
// CRepDelDlg 对话框

class CRepDelDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepDelDlg)

public:
	CRepDelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRepDelDlg();

// 对话框数据
	enum { IDD = IDD_DELREP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString m_name;
	int m_bh;
	float m_price;
	float m_num;
	CString m_kindName;
	float m_repNum;
	CFont m_font;

public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
