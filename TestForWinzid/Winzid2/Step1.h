#pragma once


// CStep1 对话框

class CStep1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep1)

public:
	CStep1();
	virtual ~CStep1();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	afx_msg void OnBnClickedButton1();
};
