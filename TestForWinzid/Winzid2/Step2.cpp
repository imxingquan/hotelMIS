// Step2.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Step2.h"
#include ".\step2.h"


// CStep2 对话框

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


// CStep2 消息处理程序

BOOL CStep2::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}

LRESULT CStep2::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CPropertyPage::OnWizardNext();
}

BOOL CStep2::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxMessageBox("step2");
	return CPropertyPage::OnWizardFinish();
}
