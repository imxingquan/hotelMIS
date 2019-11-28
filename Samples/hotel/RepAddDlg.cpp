// RepAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RepAddDlg.h"
#include ".\repadddlg.h"


// CRepAddDlg �Ի���

IMPLEMENT_DYNAMIC(CRepAddDlg, CDialog)
CRepAddDlg::CRepAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRepAddDlg::IDD, pParent)
	, m_name(_T(""))
	, m_bh(0)
	, m_price(0)
	, m_num(0)
	, m_kindName(_T(""))
{
}

CRepAddDlg::~CRepAddDlg()
{
}

void CRepAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MC, m_name);
	DDX_Text(pDX, IDC_STATIC_SPBH, m_bh);
	DDX_Text(pDX, IDC_EDIT_DJ, m_price);
	DDV_MinMaxFloat(pDX,IDC_EDIT_DJ,0,99999);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDV_MinMaxFloat(pDX, m_num, 0.01f, 99999);
	DDX_Text(pDX, IDC_STATIC_LB, m_kindName);
}


BEGIN_MESSAGE_MAP(CRepAddDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRepAddDlg ��Ϣ�������

void CRepAddDlg::OnBnClickedOk()
{
	
	UpdateData(TRUE);
	if ( m_num <= 0){
		MessageBox(_T("�����������С�ڻ������!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_EDIT_NUM)->SetFocus();
		return ;
	}
	else{
	OnOK();
	}
}

BOOL CRepAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_font.CreatePointFont(180,_T("Arial"));

	GetDlgItem(IDC_EDIT_DJ)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_NUM)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
