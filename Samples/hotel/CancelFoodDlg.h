#pragma once
#include "afxwin.h"


// CCancelFoodDlg 对话框

class CCancelFoodDlg : public CDialog
{
	DECLARE_DYNAMIC(CCancelFoodDlg)

public:
	CCancelFoodDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCancelFoodDlg();

// 对话框数据
	enum { IDD = IDD_CANCELFOOD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_GuiEditCancelNum;
	CEdit m_GuiEditCancelMsg;
	
	CString m_cancelSnum; //可以取消的数量
	int m_cancelNum;
	int m_nNum;
	CString m_cancelMsg; //取消原因
	afx_msg void OnBnClickedOk();
};
