// Page1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Winzid.h"
#include "Page1.h"
#include ".\page1.h"


// CPage1 �Ի���

IMPLEMENT_DYNAMIC(CPage1, CPropertyPage)
CPage1::CPage1()
	: CPropertyPage(CPage1::IDD)
{
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CPage1 ��Ϣ�������

void CPage1::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


}

BOOL CPage1::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* pParent=(CPropertySheet*)GetParent(); // ������Ա��ָ��
	pParent->SetWizardButtons(PSWIZB_NEXT); // �������Ա����ʾ��ťֻΪ��һ��
	//SetDlgItemText(IDC_TEXT1,"�����򵼵ĵ�һ��"); 

	return CPropertyPage::OnSetActive();
}
