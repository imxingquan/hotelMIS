#pragma once


// CMemberCastSearchDlg 对话框
#include "resource.h"


class CMemberCastSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemberCastSearchDlg)

public:
	CMemberCastSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMemberCastSearchDlg();

// 对话框数据
	enum { IDD = IDD_MEMBERCASTSEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
