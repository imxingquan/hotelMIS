// Page2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Winzid.h"
#include "Page2.h"
#include ".\page2.h"


// CPage2 �Ի���

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)
CPage2::CPage2()
	: CPropertyPage(CPage2::IDD)
{
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
END_MESSAGE_MAP()


// CPage2 ��Ϣ�������

BOOL CPage2::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
	pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}
