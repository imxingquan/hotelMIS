#pragma once


// CStep2 �Ի���

class CStep2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep2)

public:
	CStep2();
	virtual ~CStep2();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LARGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
};
