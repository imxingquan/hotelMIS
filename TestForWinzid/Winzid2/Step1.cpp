// Step1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Step1.h"
#include ".\step1.h"


// CStep1 �Ի���

IMPLEMENT_DYNAMIC(CStep1, CPropertyPage)
CStep1::CStep1()
	: CPropertyPage(CStep1::IDD)
{
}

CStep1::~CStep1()
{
}

void CStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStep1, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CStep1 ��Ϣ�������

BOOL CStep1::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
CPropertySheet* pParent=(CPropertySheet*)GetParent(); // ������Ա��ָ��
pParent->SetWizardButtons(PSWIZB_NEXT); // �������Ա����ʾ��ťֻΪ��һ��
//SetDlgItemText(IDC_TEXT1,"�����򵼵ĵ�һ��"); 

	return CPropertyPage::OnSetActive();
}

LRESULT CStep1::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	return CPropertyPage::OnWizardNext();
}

BOOL CStep1::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���
	AfxMessageBox("step1");
	return CPropertyPage::OnWizardFinish();
}

void CStep1::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
