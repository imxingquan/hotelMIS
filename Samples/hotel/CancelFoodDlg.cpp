// CancelFoodDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CancelFoodDlg.h"
#include ".\cancelfooddlg.h"

// CCancelFoodDlg 对话框

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


// CCancelFoodDlg 消息处理程序

void CCancelFoodDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if ( m_cancelMsg.IsEmpty() ){
		MessageBox(_T("请填写退菜原因!"));
		m_GuiEditCancelMsg.SetFocus();
	}
	else if ( m_cancelNum > m_nNum || m_cancelNum <=0){
		MessageBox(_T("退菜数量超出范围,请重新输入!"));
		m_GuiEditCancelNum.SetFocus();
	}
	else
		OnOK();
}
