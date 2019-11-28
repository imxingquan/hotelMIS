// SetpConfigDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "SetpConfigDialog.h"

// CSetpConfigDialog
#include "step1.h"
#include "step2.h"
#include "step3.h"


IMPLEMENT_DYNAMIC(CSetpConfigDialog, CTreePropSheet)

CSetpConfigDialog::CSetpConfigDialog()
:CTreePropSheet()
{
	Init();
}
CSetpConfigDialog::CSetpConfigDialog(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CTreePropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	Init();
}

CSetpConfigDialog::CSetpConfigDialog(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CTreePropSheet(pszCaption, pParentWnd, iSelectPage)
{
	Init();
}

void CSetpConfigDialog::Init()
{

	m_step1.m_psp.dwFlags&= ~PSP_HASHELP;
	m_step2.m_psp.dwFlags&= ~PSP_HASHELP;
	m_step4.m_psp.dwFlags&= ~PSP_HASHELP;
	m_step5.m_psp.dwFlags&= ~PSP_HASHELP;
	m_step6.m_psp.dwFlags&= ~PSP_HASHELP;

	
	AddPage(&m_step1);
	AddPage(&m_step2);
	//AddPage(&m_step3);
	AddPage(&m_step4);
	AddPage(&m_step5);
	AddPage(&m_step6);
	m_isModify = false;

	SetEmptyPageText(_T("请选择子项 '%s'."));

	SetTreeViewMode(TRUE, TRUE,FALSE);
}
CSetpConfigDialog::~CSetpConfigDialog()
{
}


BEGIN_MESSAGE_MAP(CSetpConfigDialog, CTreePropSheet)
	ON_MESSAGE(WM_MODIFIED,OnModified)
END_MESSAGE_MAP()


// CSetpConfigDialog 消息处理程序
LRESULT CSetpConfigDialog::OnModified(WPARAM wParam,LPARAM lParam)
{
	m_isModify = true;
	TRACE("sys config is modified!\n");
	return 0;
}
BOOL CSetpConfigDialog::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( m_isModify ){
		AfxMessageBox(_T("系统设置被改变!程序将自动关闭!请重新启动!"));
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
	return CPropertySheet::DestroyWindow();
}
