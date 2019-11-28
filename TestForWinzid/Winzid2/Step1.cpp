// Step1.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Step1.h"
#include ".\step1.h"


// CStep1 对话框

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


// CStep1 消息处理程序

BOOL CStep1::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
CPropertySheet* pParent=(CPropertySheet*)GetParent(); // 获得属性表的指针
pParent->SetWizardButtons(PSWIZB_NEXT); // 设置属性表的显示按钮只为下一步
//SetDlgItemText(IDC_TEXT1,"这是向导的第一步"); 

	return CPropertyPage::OnSetActive();
}

LRESULT CStep1::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CPropertyPage::OnWizardNext();
}

BOOL CStep1::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxMessageBox("step1");
	return CPropertyPage::OnWizardFinish();
}

void CStep1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

}
