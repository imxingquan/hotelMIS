// ArrearageSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ArrearageSetDlg.h"
//#include ".\arrearagesetdlg.h"


// CArrearageSetDlg �Ի���

IMPLEMENT_DYNAMIC(CArrearageSetDlg, CDialog)
CArrearageSetDlg::CArrearageSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArrearageSetDlg::IDD, pParent)
{
}

CArrearageSetDlg::~CArrearageSetDlg()
{
}

void CArrearageSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXT, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);
	DDX_Control(pDX, IDC_LIST_ARREARAGE, m_GuiListCtrlArr);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_GuiButtonAdd);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_GuiButtonModify);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_GuiButtonDel);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
}


BEGIN_MESSAGE_MAP(CArrearageSetDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CArrearageSetDlg ��Ϣ�������

void CArrearageSetDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CArrearageSetDlg::OnBnClickedButtonModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CArrearageSetDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
