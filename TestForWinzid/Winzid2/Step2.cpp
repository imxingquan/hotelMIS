// Step2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Step2.h"
#include ".\step2.h"


// CStep2 �Ի���

IMPLEMENT_DYNAMIC(CStep2, CPropertyPage)
CStep2::CStep2()
	: CPropertyPage(CStep2::IDD)
{
}

CStep2::~CStep2()
{
}

void CStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStep2, CPropertyPage)
END_MESSAGE_MAP()


// CStep2 ��Ϣ�������

BOOL CStep2::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}

LRESULT CStep2::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::OnWizardNext();
}

BOOL CStep2::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���
	AfxMessageBox("step2");
	return CPropertyPage::OnWizardFinish();
}
