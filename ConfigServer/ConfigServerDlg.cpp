// ConfigServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConfigServer.h"
#include "ConfigServerDlg.h"
#include ".\configserverdlg.h"
#include "KProfile.h"
#include <fstream>
using namespace std;


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
END_MESSAGE_MAP()


// CConfigServerDlg 对话框



CConfigServerDlg::CConfigServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigServerDlg::IDD, pParent)
	, m_serverName(_T(""))
	, m_port(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_time = 5;
}

void CConfigServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_GuiListBox);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_GuiButtonExit);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_serverName);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_SPIN1, m_SpinCtrl);
}

BEGIN_MESSAGE_MAP(CConfigServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnBnClickedButtonExit)
	ON_MESSAGE(WM_SENDMSG,OnSendMsg)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CConfigServerDlg 消息处理程序

BOOL CConfigServerDlg::OnInitDialog()
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
	//设置窗口最上
	SetWindowPos(&CWnd::wndTopMost,-1,-1,-1,-1,SWP_NOSIZE|SWP_NOMOVE);
	
	InitIdle();

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CConfigServerDlg::InitIdle()
{
	KProfile profile("my.ini");
	std::string port = profile.GetProfile("mysqld","port","3306");
	KProfile setFile("set.ini");
	std::string sName = setFile.GetProfile("SERVER_NAME","servername","hotelmysql");
	m_serverName = sName.c_str();
	m_port = port.c_str();

	m_SpinCtrl.SetRange32(1000,9999);

	UpdateData(false);
}

UINT ThreadProc(LPVOID pParam)
{
	
	PostMessage((HWND)pParam,WM_SENDMSG,(WPARAM)1,0);
	Sleep(500);
	KProfile profile("my.ini");
	profile.WirteProfile("mysqld","basedir",profile.getPath());
	profile.WirteProfile("mysqld","datadir",profile.getPath() +"data");
	Sleep(500);
	PostMessage((HWND)pParam,WM_SENDMSG,(WPARAM)2,0);
	std::string str;
	
	KProfile setFile("set.ini");
	string sName = setFile.GetProfile("SERVER_NAME","servername");
	str = "mysqld --install "+sName+" --defaults-file=\""+profile.getPath()+"my.ini\"";
    system(str.c_str());
	str = "net start "+ sName;
	system(str.c_str());

	Sleep(1000);
	PostMessage((HWND)pParam,WM_SENDMSG,(WPARAM)3,0);
	
	return 0;
}

LRESULT CConfigServerDlg::OnSendMsg(WPARAM wParam,LPARAM lParam)
{
	int n= (int)wParam;
	
	if ( n == 1 ){
		pos = m_GuiListBox.AddString(_T("=========系统准备开始配置!========="));
		Sleep(500);
		m_GuiListBox.InsertString(++pos,_T("正在修改配置文件....            "));
	}
	else if ( n == 2){
		m_GuiListBox.InsertString(++pos,_T("配置文件修改完成!               "));
		m_GuiListBox.InsertString(++pos,_T("--------------------------------"));
		m_GuiListBox.InsertString(++pos,_T("正在安装数据库服务.....         "));
	}else if ( n==3){
		m_GuiListBox.InsertString(++pos,_T("数据库服务安装完成!             "));
		m_GuiListBox.InsertString(++pos,_T("--------------------------------"));
		m_GuiListBox.InsertString(++pos,_T("请单击Exit按钮退出服务器配置程序!"));
		MessageBox(_T("系统配置完成! "));
		GetDlgItem(IDC_BUTTON_EXIT)->EnableWindow(true);
	}
	return 0;
}

void CConfigServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConfigServerDlg::OnPaint() 
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
HCURSOR CConfigServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConfigServerDlg::OnBnClickedButtonExit()
{
	OnCancel();
}

HBRUSH CConfigServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	/*if ( pWnd->GetDlgCtrlID()==IDC_LIST1)
	{
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(0,255,0));
		
	}*/
	
	return hbr;
}

void CConfigServerDlg::OnTimer(UINT nIDEvent)
{
	
	CDialog::OnTimer(nIDEvent);
}

void CConfigServerDlg::OnBnClickedButtonStart()
{
	// TODO: 手动配置mysql 数据库

	//改成my.ini 配置文件
	::LoadCursor(NULL,IDC_WAIT);
	UpdateData(TRUE);
	if ( atoi(m_port) < 1000 || atoi(m_port) >9999){
		MessageBox(_T("端口范围1000-9999"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_EDIT_PORT)->SetFocus();
		return;
	}

	std::string port  = m_port.Trim().GetBuffer();
	std::string sName = m_serverName.Trim().GetBuffer();

	KProfile profile("my.ini");
	profile.WirteProfile("client","port",port);
	profile.WirteProfile("mysqld","port",port);

	//配置 set.ini
	KProfile setFile("set.ini");
	setFile.WirteProfile("HOST_SET","port",port);
	setFile.WirteProfile("SERVER_NAME","servername",sName);
    
	//重写uninstall.bat 文件
	fstream outfile("uninstall.bat",ios_base::out);
	outfile << "rem 正在停止数据库服务......"<< std::endl;
	outfile <<"net stop "<< sName << std::endl;
	outfile <<"mysqld --remove "<<sName<<std::endl;
	outfile.close();
	
	//起动配置
	AfxBeginThread(ThreadProc,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	::LoadCursor(NULL,IDC_ARROW);
}
