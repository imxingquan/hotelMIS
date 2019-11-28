#pragma once
#include "resource.h"
//自定义价格
// CZdyPriceDlg 对话框

class CZdyPriceDlg : public CDialog
{
	DECLARE_DYNAMIC(CZdyPriceDlg)

public:
	CZdyPriceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZdyPriceDlg();

// 对话框数据
	enum { IDD = IDD_ZDY_PRICE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_zdyPrice;
	afx_msg void OnBnClickedOk();
};
