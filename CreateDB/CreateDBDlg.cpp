#include "..\samples\hotel\outlookdemo.cpp"
// CreateDBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CreateDB.h"
#include "CreateDBDlg.h"
#include "KResetDB.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//ON_STN_DBLCLK(IDC_ABOUT_ICON, OnStnDblclickAboutIcon)
END_MESSAGE_MAP()


// CCreateDBDlg 对话框



CCreateDBDlg::CCreateDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateDBDlg::IDD, pParent)
	, m_host(_T("localhost"))
	, m_port(_T("3306"))
	, m_name(_T("root"))
	, m_password(_T(""))
	, m_details(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	

}

void CCreateDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOST_EDIT, m_hostEdit);
	DDX_Control(pDX, IDC_PORT_EDIT, m_portEdit);
	DDX_Control(pDX, IDC_NAME_EDIT, m_nameEdit);
	DDX_Control(pDX, IDC_PASSWORD_EDIT, m_passwordEdit);
	DDX_Control(pDX, IDC_DETAILS_EDIT, m_detailsEdit);
	DDX_Text(pDX, IDC_HOST_EDIT, m_host);
	DDX_Text(pDX, IDC_PORT_EDIT, m_port);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Text(pDX, IDC_PASSWORD_EDIT, m_password);
	DDX_Control(pDX, IDC_SETDB_BUTTON, m_setDBBtn);
	DDX_Text(pDX, IDC_DETAILS_EDIT, m_details);
	DDX_Control(pDX, IDC_SETDEMODB_BTN, m_setDemoDBBtn);
}

BEGIN_MESSAGE_MAP(CCreateDBDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SETDB_BUTTON, OnBnClickedSetdbButton)
	ON_MESSAGE(WM_DETAILS,OnDetails)
	ON_BN_CLICKED(IDC_SETDEMODB_BTN, OnBnClickedSetdemodbBtn)
END_MESSAGE_MAP()


// CCreateDBDlg 消息处理程序

BOOL CCreateDBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CCreateDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCreateDBDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CCreateDBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCreateDBDlg::OnBnClickedSetdbButton()
{
	char dir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH,dir);
	strcat(dir,"\\standard.db");
	string file;
	file = dir;
	SetDB(file);
}

void CCreateDBDlg::OnBnClickedSetdemodbBtn()
{
	char dir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH,dir);
	strcat(dir,"\\demo.db");
	string file;
	file = dir;
	SetDB(file);	
}

void CCreateDBDlg::SetDB(string dbfile)
{
	// TODO: 数据配置
	UpdateData(true);
	con.init(m_host.GetBuffer(),m_port.GetBuffer(),m_name.GetBuffer(),m_password.GetBuffer());
	con.get_con();
	if ( ! con.isConnect() ) {
		MessageBox("数据源配置不正确,请重新配置!","警告!",MB_ICONWARNING|MB_OK);
		con.close();
		return;
	}

	int result = MessageBox("重置数据库将销毁以前的所有数据,确定要这样做?","警告",MB_ICONWARNING|MB_YESNO);
	if ( IDYES == result ){
		KResetDB db(con.get_con());
		if ( db.ResetDB(dbfile)){
			MessageBox("数据库重置成功!","警告",MB_ICONINFORMATION|MB_OK);
			m_setDBBtn.EnableWindow(false);
			m_setDemoDBBtn.EnableWindow(false);
		}else{
			MessageBox("数据库重置失败!","警告",MB_ICONINFORMATION|MB_OK);
		}
	}
	con.close();
}

LRESULT CCreateDBDlg::OnDetails(WPARAM wParam ,LPARAM lParam)
{
	
	m_details +="执行完成:";
	m_details += theApp.globaStr.c_str();
	m_details += "\r\n";

	TRACE("buf = %s",theApp.globaStr.c_str());
	UpdateData(false);
	return 0;
}

