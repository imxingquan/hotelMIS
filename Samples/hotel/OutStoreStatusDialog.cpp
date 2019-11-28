// OutStoreStatusDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "OutStoreStatusDialog.h"
//#include ".\outstorestatusdialog.h"


// COutStoreStatusDialog 对话框

IMPLEMENT_DYNAMIC(COutStoreStatusDialog, CDialog)
COutStoreStatusDialog::COutStoreStatusDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COutStoreStatusDialog::IDD, pParent)
	, m_kind(_T(""))
	, m_stocks(_T(""))
{
}

COutStoreStatusDialog::~COutStoreStatusDialog()
{
}

void COutStoreStatusDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_COMBO_KIND, m_GuiComboKind);
	DDX_Control(pDX, IDC_COMBO_STOCKS, m_GuiComBoStocks);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiButtonPrint);
	DDX_Control(pDX, IDOK, m_GuiButtonCancel);
	DDX_Control(pDX, IDC_LIST_OUTSTORE, m_GuiListCtrlOutStore);
	DDX_CBString(pDX, IDC_COMBO_KIND, m_kind);
	DDX_CBString(pDX, IDC_COMBO_STOCKS, m_stocks);
}


BEGIN_MESSAGE_MAP(COutStoreStatusDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_CBN_SELCHANGE(IDC_COMBO_KIND, OnCbnSelchangeComboKind)
	ON_CBN_SELCHANGE(IDC_COMBO_STOCKS, OnCbnSelchangeComboStocks)
END_MESSAGE_MAP()


// COutStoreStatusDialog 消息处理程序

void COutStoreStatusDialog::OnBnClickedButtonPrint()
{
	// TODO: 在此添加控件通知处理程序代码
}

void COutStoreStatusDialog::OnCbnSelchangeComboKind()
{
	// TODO: 在此添加控件通知处理程序代码
}

void COutStoreStatusDialog::OnCbnSelchangeComboStocks()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL COutStoreStatusDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_GuiButtonPrint.ShowText();
	m_GuiButtonCancel.ShowText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
