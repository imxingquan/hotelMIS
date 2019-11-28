#pragma once


// CSetDBDevDlg 对话框

class CSetDBDevDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDBDevDlg)

public:
	CSetDBDevDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDBDevDlg();

// 对话框数据
	enum { IDD = IDD_SET_DBENV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
