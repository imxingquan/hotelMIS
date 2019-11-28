// PrintWarningDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintWarningDialog.h"
#include ".\printwarningdialog.h"


// CPrintWarningDialog �Ի���

IMPLEMENT_DYNAMIC(CPrintWarningDialog, CDialog)
CPrintWarningDialog::CPrintWarningDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintWarningDialog::IDD, pParent)
	, m_printWarningCheck(TRUE)
	, m_jzAndPrint(FALSE)
{
}

CPrintWarningDialog::~CPrintWarningDialog()
{
}

void CPrintWarningDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_printWarningCheck);
	DDX_Control(pDX, IDC_CHECK1, m_GuiPrintWarningCheck);
	DDX_Control(pDX, IDC_JZANDPRINT_CHECK, m_GuiJZAndPrintCheck);
	DDX_Check(pDX, IDC_JZANDPRINT_CHECK, m_jzAndPrint);
}


BEGIN_MESSAGE_MAP(CPrintWarningDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CPrintWarningDialog ��Ϣ�������

void CPrintWarningDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(false);
	
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "PrintWarning", m_GuiPrintWarningCheck.GetCheck());
	pApp->WriteProfileInt("Settings", "JzAndPrint", m_GuiJZAndPrintCheck.GetCheck());
	OnOK();
}

BOOL CPrintWarningDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CWinApp* pApp = AfxGetApp();
	m_jzAndPrint = pApp->GetProfileInt("Settings", "JzAndPrint",1);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
