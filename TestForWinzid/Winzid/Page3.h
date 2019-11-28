#pragma once


// CPage3 对话框

class CPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3();
	virtual ~CPage3();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
