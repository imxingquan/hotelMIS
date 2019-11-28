// Step3.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Step3.h"
#include ".\step3.h"


// CStep3 对话框

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


// CStep3 消息处理程序

BOOL CStep3::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}

LRESULT CStep3::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CPropertyPage::OnWizardNext();
}

BOOL CStep3::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxMessageBox("step3");
	return CPropertyPage::OnWizardFinish();
}
