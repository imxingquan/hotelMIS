#pragma once


// CStep1 �Ի���

class CStep1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep1)

public:
	CStep1();
	virtual ~CStep1();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LARGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	afx_msg void OnBnClickedButton1();
};
