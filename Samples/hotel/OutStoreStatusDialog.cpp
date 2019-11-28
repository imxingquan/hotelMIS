// OutStoreStatusDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "OutStoreStatusDialog.h"
//#include ".\outstorestatusdialog.h"


// COutStoreStatusDialog �Ի���

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


// COutStoreStatusDialog ��Ϣ�������

void COutStoreStatusDialog::OnBnClickedButtonPrint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void COutStoreStatusDialog::OnCbnSelchangeComboKind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void COutStoreStatusDialog::OnCbnSelchangeComboStocks()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

BOOL COutStoreStatusDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_GuiButtonPrint.ShowText();
	m_GuiButtonCancel.ShowText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
