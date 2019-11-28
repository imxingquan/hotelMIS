// CancelFoodDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "CancelFoodDlg.h"
#include ".\cancelfooddlg.h"

// CCancelFoodDlg �Ի���

IMPLEMENT_DYNAMIC(CCancelFoodDlg, CDialog)
CCancelFoodDlg::CCancelFoodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCancelFoodDlg::IDD, pParent)
	, m_cancelSnum(_T(""))
	, m_cancelNum(1)
	, m_cancelMsg(_T(""))
{
}

CCancelFoodDlg::~CCancelFoodDlg()
{
}

void CCancelFoodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITCANCEL_NUM, m_GuiEditCancelNum);
	DDX_Control(pDX, IDC_EDIT_CANCELMSG, m_GuiEditCancelMsg);
	DDX_Text(pDX, IDC_STATIC_CANCELNUM, m_cancelSnum);
	DDX_Text(pDX, IDC_EDITCANCEL_NUM, m_cancelNum);
	DDX_Text(pDX, IDC_EDIT_CANCELMSG, m_cancelMsg);
}


BEGIN_MESSAGE_MAP(CCancelFoodDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCancelFoodDlg ��Ϣ�������

void CCancelFoodDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if ( m_cancelMsg.IsEmpty() ){
		MessageBox(_T("����д�˲�ԭ��!"));
		m_GuiEditCancelMsg.SetFocus();
	}
	else if ( m_cancelNum > m_nNum || m_cancelNum <=0){
		MessageBox(_T("�˲�����������Χ,����������!"));
		m_GuiEditCancelNum.SetFocus();
	}
	else
		OnOK();
}
