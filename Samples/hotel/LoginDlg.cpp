// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "LoginDlg.h"
#include ".\logindlg.h"
#include "MyCdKey.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_userName(_T(""))
	, m_password(_T(""))
	, m_uName(_T(""))
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERNAME, m_GuiEditUserName);
	DDX_Control(pDX, IDC_PASSWORD, m_GuiEditPassword);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Text(pDX, IDC_USERNAME, m_userName);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Control(pDX, IDC_STATIC_MSG, m_GuiStaticMsg);
	DDX_Control(pDX, IDC_USER_COMBO, m_userComboBox);
	DDX_CBString(pDX, IDC_USER_COMBO, m_uName);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MyCdKey cdkey;
	if (!cdkey.RegisterCdKey() )
	{
		m_GuiStaticMsg.ShowWindow(SW_SHOW);
	}

	m_GuiButtonOk.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonCancel.ShowText();
	int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
	CRect rt;
	GetWindowRect(&rt);
	
	TCHAR buf[MAX_PATH];
	LoadString(AfxGetInstanceHandle(),IDR_MAINFRAME,buf,MAX_PATH);
	SetWindowText(buf);
	SetWindowPos(&CWnd::wndTop,(width - rt.Width()) /2,(height-rt.Height())/2,0,0,SWP_NOSIZE);  
	AnimateWindow(500,AW_BLEND);
	Invalidate();
	

	hotelMIS::HAdminBdy adminBdy(m_con.get_con());
	hotelMIS::HAdminVec vec= adminBdy.getAllAdminInfo();
	hotelMIS::HAdminVec::iterator it;

	int i=0;
	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		m_userComboBox.InsertString(i,it->getLoginId().c_str());
		//m_userComboBox.SetItemData(i++,(DWORD)it->getLoginId().c_str());
	}
	m_userComboBox.SetCurSel(0);


	//获取安装日期
	/*CWinApp* pWinApp = AfxGetApp();
	CString setupDate =pWinApp->GetProfileString("Settings", "date");
	if ( setupDate.IsEmpty())
	{
		CTime time=CTime::GetCurrentTime();
		pWinApp->WriteProfileString("Settings","date",time.Format("%Y-%m-%d"));
	}*/


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if ( pWnd->GetDlgCtrlID() == IDC_STATIC_MSG){
		pDC->SetTextColor(RGB(255,0,0));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
