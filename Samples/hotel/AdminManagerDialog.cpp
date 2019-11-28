// AdminManagerDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "AdminManagerDialog.h"
//#include ".\adminmanagerdialog.h"


// CAdminManagerDialog 对话框

IMPLEMENT_DYNAMIC(CAdminManagerDialog, CDialog)
CAdminManagerDialog::CAdminManagerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAdminManagerDialog::IDD, pParent)
	, m_logName(_T(""))
	, m_adminOtype(_T(""))
	, m_adminName(_T(""))
	, m_adminRemark(_T(""))
	, m_op01(FALSE)
{
}

CAdminManagerDialog::~CAdminManagerDialog()
{
}

void CAdminManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXT, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);
	DDX_Control(pDX, IDC_EDIT_ADMIN_LOG_NAME, m_GuiEditAdminLogName);
	DDX_Control(pDX, IDC_COMBO_ADMIN_OTYPE, m_GuiComboBoxAdminOType);
	DDX_Control(pDX, IDC_EDIT_LOG_PASSWORD, m_GuiEditLogPassword);
	DDX_Control(pDX, IDC_EDIT_ADMIN_NAME, m_GuiEditAdminName);
	DDX_Control(pDX, IDC_EDIT_ADMIN_REMARK, m_GuiEditAdminRemark);
	DDX_Control(pDX, IDC_BUTTON_ADD_UPDATE, m_GuiButtonAddUpdate);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_GuiButtonDel);
	DDX_Control(pDX, IDC_LIST_ADMIN, m_GuiListCtrlAdmin);
	DDX_Text(pDX, IDC_EDIT_ADMIN_LOG_NAME, m_logName);
	DDX_CBString(pDX, IDC_COMBO_ADMIN_OTYPE, m_adminOtype);
	DDX_Text(pDX, IDC_EDIT_ADMIN_NAME, m_adminName);
	DDX_Text(pDX, IDC_EDIT_ADMIN_REMARK, m_adminRemark);
	DDX_Control(pDX, IDC_CHECK1, m_GuiCheck01);
	DDX_Control(pDX, IDC_CHECK2, m_GuiCheck02);
	DDX_Control(pDX, IDC_CHECK3, m_GuiCheck03);
	DDX_Control(pDX, IDC_CHECK4, m_GuiCheck04);
	DDX_Control(pDX, IDC_CHECK5, m_GuiCheck05);
	DDX_Control(pDX, IDC_CHECK6, m_GuiCheck06);
	DDX_Check(pDX, IDC_CHECK1, m_op01);
	DDX_Check(pDX, IDC_CHECK2, m_op02);
	DDX_Check(pDX, IDC_CHECK3, m_op03);
	DDX_Check(pDX, IDC_CHECK4, m_op04);
	DDX_Check(pDX, IDC_CHECK5, m_op05);
	DDX_Check(pDX, IDC_CHECK6, m_op06);
}


BEGIN_MESSAGE_MAP(CAdminManagerDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_UPDATE, OnBnClickedButtonAddUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CAdminManagerDialog 消息处理程序

void CAdminManagerDialog::OnBnClickedButtonAddUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAdminManagerDialog::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CAdminManagerDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_GuiButtonAddUpdate.ShowText();
m_GuiButtonDel.ShowText();
//m_GuiCheck01.ShowText();
//m_GuiCheck02.ShowText();
//m_GuiCheck03.ShowText();
//m_GuiCheck04.ShowText();
//m_GuiCheck05.ShowText();
//m_GuiCheck06.ShowText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
