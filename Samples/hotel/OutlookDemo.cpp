// OutlookDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OutlookDemo.h"

#include "MainFrm.h"
#include "OutlookDemoDoc.h"
#include "OutlookDemoView.h"
#include "GOut.h"

#include "LoginDlg.h"
#include "KDBCon.h"
#include "HAdminBdy.h"
//#include ".\outlookdemo.h"
#include "SetDBEnvDialog.h"
#include "MyCdKey.h"

#include "afxwin.h"
#include "RegisterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoApp

BEGIN_MESSAGE_MAP(COutlookDemoApp, CWinApp)
	
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoApp construction

COutlookDemoApp::COutlookDemoApp()
:m_isLogin(false)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COutlookDemoApp object

COutlookDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoApp initialization


bool COutlookDemoApp::InitDbConnect()
{

	hotelMIS::KDBCon con;
	con.init();
	con.get_con();
	bool isConnected =con.isConnect();
	if ( isConnected == false ){ con.close(); };
	
	return isConnected;
}

void COutlookDemoApp::CloseDbConnect()
{
	hotelMIS::KDBCon con;
	if ( con.isConnect() ){
		con.close();
	}
}

bool COutlookDemoApp::UserLogin()
{
	CLoginDlg dlg;
	int i =0;
	while ( dlg.DoModal() == IDOK )
	{
		hotelMIS::KDBCon con;
		
		hotelMIS::HAdminBdy hAdminBdy(con.get_con());
		if ( hAdminBdy.login(ReplaceChar(dlg.m_uName).GetBuffer(),ReplaceChar(dlg.m_password).GetBuffer()) ){
			return true;
		}
		else{
			AfxMessageBox(HMIS_LOGIN_ERR,MB_OK|MB_ICONINFORMATION);
		}

		//AfxMessageBox(dlg.m_uName,MB_OK|MB_ICONINFORMATION);
	}
	return false;
}

BOOL COutlookDemoApp::InitInstance()
{
	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("初始化失败!"));
		return FALSE;
	}

	m_flashDlg.Create(IDD_FLASH_DIALOG);
	m_flashDlg.ShowWindow(SW_SHOW);
	m_flashDlg.UpdateWindow();

    
	//连接数据源
	while ( !InitDbConnect() ){
		int res = AfxMessageBox(HMIS_CONNECTED_DB_ERR,MB_YESNO);
		if ( IDYES == res ){
			//设置数据源
			//AfxMessageBox("display set dialog");
			CSetDBEnvDialog dlg;
			dlg.DoModal();
		}
		else
		{  //不配置直接退出应用程序
			return false;
		}
	}


	//--------------------------------------------------------------------------------------------
	//试用限制
	/*CTime time=CTime::GetCurrentTime();
	if ( time.GetYear() >= 2009 && time.GetMonth() >= 12 && time.GetDay() >= 1)
	{
		MessageBox(NULL,_T("试用期以过!请与厂商联系,\n电话:0471-3334390!"),_T("提示"),MB_OK);
		return false;
	}*/


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("HOTEL_MIS"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)


	m_isLogin =  UserLogin();
	if ( !m_isLogin ){ return FALSE; }
	
	m_flashDlg.SendMessage(WM_CLOSE);


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COutlookDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(COutlookDemoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	
	//m_pMainWnd->PostMessage(WM_DELMENU);
	//m_pMainWnd->GetMenu()->DeleteMenu(0,MF_BYPOSITION);
	
	MyCdKey cdkey;
	if ( !cdkey.RegisterCdKey()){
		CRegisterDialog dlg;
		dlg.DoModal();
	}
	
	TCHAR buf[MAX_PATH];
	LoadString(AfxGetInstanceHandle(),IDR_MAINFRAME,buf,MAX_PATH);
	m_pMainWnd->SetWindowText(buf);
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	
	enum { IDD = IDD_ABOUTBOX };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	

// Implementation
protected:
	
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	
	DECLARE_MESSAGE_MAP()
public:
	CGuiLinkButton m_GuiLinkBtn;
	virtual BOOL OnInitDialog();
	afx_msg void OnStnDblclickAboutIcon();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiLinkBtn.SetLink(_T("http://www.digitwest.com"));
	m_GuiLinkBtn.SetToolTip(_T("欢迎您访问西部数字"));
	return TRUE;
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LINK_BUTTON, m_GuiLinkBtn);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	
END_MESSAGE_MAP()

// App command to run the dialog
void COutlookDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoApp message handlers


void CAboutDlg::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CAboutDlg::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

int COutlookDemoApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	CloseDbConnect();
	MyCdKey cdkey;
	if ( !cdkey.RegisterCdKey() ){
		int res = MessageBox(NULL,_T("感谢您使用西部数字产品!是否访问我们的网站,了解更多的信息!"),_T("提醒"),MB_ICONINFORMATION|MB_YESNO);
		if ( res == IDYES)
		{
			ShellExecute(NULL,_T("open"),_T("www.digitwest.com"),NULL,NULL,SW_SHOWNORMAL);
		}
	}
	//::CoUninitialize();
	return CWinApp::ExitInstance();
}

void CAboutDlg::OnStnDblclickAboutIcon()
{

}
