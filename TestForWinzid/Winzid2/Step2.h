#pragma once


// CStep2 对话框

class CStep2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep2)

public:
	CStep2();
	virtual ~CStep2();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
};
