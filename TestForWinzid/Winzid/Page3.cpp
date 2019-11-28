// Page3.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid.h"
#include "Page3.h"
#include ".\page3.h"


// CPage3 对话框

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


// CPage3 消息处理程序

BOOL CPage3::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
	pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK); 

	return CPropertyPage::OnSetActive();
}
