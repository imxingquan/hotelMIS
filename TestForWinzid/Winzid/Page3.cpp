// Page3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Winzid.h"
#include "Page3.h"
#include ".\page3.h"


// CPage3 �Ի���

IMPLEMENT_DYNAMIC(CPage3, CPropertyPage)
CPage3::CPage3()
	: CPropertyPage(CPage3::IDD)
{
}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
END_MESSAGE_MAP()


// CPage3 ��Ϣ�������

BOOL CPage3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
	pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}
