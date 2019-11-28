// Page2.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid.h"
#include "Page2.h"
#include ".\page2.h"


// CPage2 对话框

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


// CPage2 消息处理程序

BOOL CPage2::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
	pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}
