// Step3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Step3.h"
#include ".\step3.h"


// CStep3 �Ի���

IMPLEMENT_DYNAMIC(CStep3, CPropertyPage)
CStep3::CStep3()
	: CPropertyPage(CStep3::IDD)
{
}

CStep3::~CStep3()
{
}

void CStep3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStep3, CPropertyPage)
END_MESSAGE_MAP()


// CStep3 ��Ϣ�������

BOOL CStep3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}

LRESULT CStep3::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::OnWizardNext();
}

BOOL CStep3::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���
	AfxMessageBox("step3");
	return CPropertyPage::OnWizardFinish();
}
