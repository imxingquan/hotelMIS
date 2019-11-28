// RegisterDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "RegisterDialog.h"
#include "mycdkey.h"
#include ".\registerdialog.h"
// CRegisterDialog 对话框

IMPLEMENT_DYNAMIC(CRegisterDialog, CDialog)
CRegisterDialog::CRegisterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDialog::IDD, pParent)
	, m_cdkey1(_T(""))
	, m_cdkey2(_T(""))
	, m_cdkey3(_T(""))
	, m_cdkey4(_T(""))
{
}

CRegisterDialog::~CRegisterDialog()
{
}

void CRegisterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CDKEY1_EDIT, m_GuiCdKey1Edit);
	DDX_Control(pDX, IDC_CDKEY2_EDIT, m_GuiCdKey2Edit);
	DDX_Control(pDX, IDC_CDKEY3_EDIT, m_GuiCdKey3Edit);
	DDX_Control(pDX, IDC_CDKEY4_EDIT, m_GuiCdKey4Edit);
	DDX_Text(pDX, IDC_CDKEY1_EDIT, m_cdkey1);
	DDX_Text(pDX, IDC_CDKEY2_EDIT, m_cdkey2);
	DDX_Text(pDX, IDC_CDKEY3_EDIT, m_cdkey3);
	DDX_Text(pDX, IDC_CDKEY4_EDIT, m_cdkey4);
	DDX_Control(pDX, IDC_LINK_BUTTON, m_linkBtn);
	DDX_Control(pDX, IDC_REG_STATIC, m_GuiRegStatic);
}


BEGIN_MESSAGE_MAP(CRegisterDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CRegisterDialog 消息处理程序

void CRegisterDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//验证并入并
	UpdateData(true);
	MyCdKey myCdKey;
	CString cdkey;
	cdkey.Format("%s-%s-%s-%s",m_cdkey1,m_cdkey2,m_cdkey3,m_cdkey4);
	if ( cdkey == myCdKey.getKey() )
	{
		CWinApp* pApp = AfxGetApp();
		pApp->WriteProfileString("Settings", "cdkey", cdkey);
		MessageBox(_T("注册成功！欢迎您的使用！"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
		OnOK();
	}
	else{
		MessageBox(_T("序列号不正确！单击取消继续试用本软件！"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
}

BOOL CRegisterDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
	CRect rt;
	GetWindowRect(&rt);

	SetWindowPos(&CWnd::wndTop,(width - rt.Width()) /2,(height-rt.Height())/2,0,0,SWP_NOSIZE);  
	AnimateWindow(600,AW_CENTER);

	//m_linkBtn.SetWindowText("请您购买正版软件! 欢迎访问西部数字网(http://www.idcwest.net)试用我们的产品！ ");
	MyCdKey cdkey;
	DWORD reg = cdkey.GetCpuPeInfo();
	CString t;
	t.Format("本软件的序列号激活码为 %lu",reg);
	m_GuiRegStatic.SetWindowText(t);
	t.Format("访问西部数字,下载我们的软件!本软件的序列号激活码为 %lu",reg);
	m_linkBtn.SetLink(_T("http://www.digitwest.com/"));
	m_linkBtn.SetToolTip(t);
	Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRegisterDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("软件未经过授权,您现在是试用用户!"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
	OnCancel();
}


