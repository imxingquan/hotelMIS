#pragma once


// CStep3 �Ի���

class CStep3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep3)

public:
	CStep3();
	virtual ~CStep3();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LARGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
};
