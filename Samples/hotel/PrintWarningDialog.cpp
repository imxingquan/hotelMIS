// PrintWarningDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PrintWarningDialog.h"
#include ".\printwarningdialog.h"


// CPrintWarningDialog 对话框

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


// CPrintWarningDialog 消息处理程序

void CPrintWarningDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(false);
	
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "PrintWarning", m_GuiPrintWarningCheck.GetCheck());
	pApp->WriteProfileInt("Settings", "JzAndPrint", m_GuiJZAndPrintCheck.GetCheck());
	OnOK();
}

BOOL CPrintWarningDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWinApp* pApp = AfxGetApp();
	m_jzAndPrint = pApp->GetProfileInt("Settings", "JzAndPrint",1);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
