#pragma once


// CMczDlg 对话框
#include "resource.h"

class CMczDlg : public CDialog
{
	DECLARE_DYNAMIC(CMczDlg)

public:
	CMczDlg(CWnd* pParent ,CString bh,CString name);   // 标准构造函数
	virtual ~CMczDlg();

// 对话框数据
	enum { IDD = IDD_MCZ_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_bh;
	CString m_mname;
	float m_czmoney;
	afx_msg void OnBnClickedOk();
	CString m_remark;
};
