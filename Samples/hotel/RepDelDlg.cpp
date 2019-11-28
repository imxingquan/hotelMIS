// RepAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RepDelDlg.h"
#include ".\repdeldlg.h"


// CRepDelDlg �Ի���

IMPLEMENT_DYNAMIC(CRepDelDlg, CDialog)
CRepDelDlg::CRepDelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRepDelDlg::IDD, pParent)
	, m_name(_T(""))
	, m_bh(0)
	, m_price(0)
	, m_num(0)
	, m_kindName(_T(""))
	, m_repNum(0)
{
}

CRepDelDlg::~CRepDelDlg()
{
}

void CRepDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MC, m_name);
	DDX_Text(pDX, IDC_STATIC_SPBH, m_bh);
	DDX_Text(pDX, IDC_EDIT_DJ, m_price);
	DDV_MinMaxFloat(pDX,IDC_EDIT_DJ,0,99999);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDV_MinMaxFloat(pDX, m_num, 0.10f, 99999);
	DDX_Text(pDX, IDC_STATIC_LB, m_kindName);
	DDX_Text(pDX, IDC_REP_NUM, m_repNum);
}


BEGIN_MESSAGE_MAP(CRepDelDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRepDelDlg ��Ϣ�������

void CRepDelDlg::OnBnClickedOk()
{
	UpdateData();
	if ( m_num <=0 ){
		MessageBox(_T("������������С�ڻ������"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_EDIT_NUM)->SetFocus();
		return;
	}
	if ( m_num > m_repNum ){
		int r = MessageBox(_T("������������ڿ����,�Ƿ��������?"),_T("��ʾ"),MB_ICONINFORMATION|MB_YESNO);
		if ( r == IDYES)
			OnOK();
		//GetDlgItem(IDOK)->SetFocus();
	}
	else{
		OnOK();
	}
}

BOOL CRepDelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_font.CreatePointFont(180,_T("Arial"));

	GetDlgItem(IDC_EDIT_NUM)->SetFont(&m_font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
