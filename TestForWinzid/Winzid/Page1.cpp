// Page1.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid.h"
#include "Page1.h"
#include ".\page1.h"


// CPage1 对话框

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


// CPage1 消息处理程序

void CPage1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


}

BOOL CPage1::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* pParent=(CPropertySheet*)GetParent(); // 获得属性表的指针
	pParent->SetWizardButtons(PSWIZB_NEXT); // 设置属性表的显示按钮只为下一步
	//SetDlgItemText(IDC_TEXT1,"这是向导的第一步"); 

	return CPropertyPage::OnSetActive();
}
