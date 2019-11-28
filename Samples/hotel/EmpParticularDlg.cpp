// EmpParticularDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "EmpParticularDlg.h"
//#include ".\empparticulardlg.h"


// CEmpParticularDlg 对话框

IMPLEMENT_DYNAMIC(CEmpParticularDlg, CDialog)
CEmpParticularDlg::CEmpParticularDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpParticularDlg::IDD, pParent)
	, m_empId(_T(""))
	, m_empName(_T(""))
	, m_empSex(_T(""))
	, m_empBir(_T(""))
	, m_empAddress(_T(""))
	, m_empPhone(_T(""))
	, m_empRemark(_T(""))
	, m_photoUrl(_T(""))
{
}

CEmpParticularDlg::~CEmpParticularDlg()
{
}

void CEmpParticularDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_EDIT_EMP_ID, m_GuiEditEmpId);
	DDX_Control(pDX, IDC_EDIT_EMP_NAME, m_GuiEditEmpName);
	DDX_Control(pDX, IDC_COMBO_EMP_SEX, m_GuiComboSex);
	DDX_Control(pDX, IDC_EDIT_EMP_BIR, m_GuiEditEmpBir);
	DDX_Control(pDX, IDC_EDIT_EMP_ADDRESS, m_GuiEditEmpAddress);
	DDX_Control(pDX, IDC_EDIT_EMP_PHONE, m_GuiEditEmpPhone);
	DDX_Control(pDX, IDC_EDIT_EMP_REMARK, m_GuiEditEmpRemark);
	DDX_Control(pDX, IDC_MODIFY, m_GuiButtonModify);
	DDX_Control(pDX, IDC_DEL, m_GuiButtonDel);

	DDX_Text(pDX, IDC_EDIT_EMP_ID, m_empId);
	DDX_Text(pDX, IDC_EDIT_EMP_NAME, m_empName);
	DDX_CBString(pDX, IDC_COMBO_EMP_SEX, m_empSex);
	DDX_Text(pDX, IDC_EDIT_EMP_BIR, m_empBir);
	DDX_Text(pDX, IDC_EDIT_EMP_ADDRESS, m_empAddress);
	DDX_Text(pDX, IDC_EDIT_EMP_PHONE, m_empPhone);
	DDX_Text(pDX, IDC_EDIT_EMP_REMARK, m_empRemark);
	DDX_Text(pDX, IDC_EDIT_PHOTO_URL, m_photoUrl);
	
}


BEGIN_MESSAGE_MAP(CEmpParticularDlg, CDialog)
	ON_BN_CLICKED(IDC_MODIFY, OnBnClickedModify)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
END_MESSAGE_MAP()


// CEmpParticularDlg 消息处理程序

void CEmpParticularDlg::OnBnClickedModify()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CEmpParticularDlg::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CEmpParticularDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_GuiButtonModify.ShowText();
	m_GuiButtonDel.ShowText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
