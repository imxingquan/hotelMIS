// SetpConfigDialog.cpp : ʵ���ļ�
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

	SetEmptyPageText(_T("��ѡ������ '%s'."));

	SetTreeViewMode(TRUE, TRUE,FALSE);
}
CSetpConfigDialog::~CSetpConfigDialog()
{
}


BEGIN_MESSAGE_MAP(CSetpConfigDialog, CTreePropSheet)
	ON_MESSAGE(WM_MODIFIED,OnModified)
END_MESSAGE_MAP()


// CSetpConfigDialog ��Ϣ�������
LRESULT CSetpConfigDialog::OnModified(WPARAM wParam,LPARAM lParam)
{
	m_isModify = true;
	TRACE("sys config is modified!\n");
	return 0;
}
BOOL CSetpConfigDialog::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( m_isModify ){
		AfxMessageBox(_T("ϵͳ���ñ��ı�!�����Զ��ر�!����������!"));
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
	return CPropertySheet::DestroyWindow();
}
