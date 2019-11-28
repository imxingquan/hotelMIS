// ConfigServerDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CConfigServerDlg �Ի���



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


// CConfigServerDlg ��Ϣ�������

BOOL CConfigServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���ô�������
	SetWindowPos(&CWnd::wndTopMost,-1,-1,-1,-1,SWP_NOSIZE|SWP_NOMOVE);
	
	InitIdle();

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
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
		pos = m_GuiListBox.AddString(_T("=========ϵͳ׼����ʼ����!========="));
		Sleep(500);
		m_GuiListBox.InsertString(++pos,_T("�����޸������ļ�....            "));
	}
	else if ( n == 2){
		m_GuiListBox.InsertString(++pos,_T("�����ļ��޸����!               "));
		m_GuiListBox.InsertString(++pos,_T("--------------------------------"));
		m_GuiListBox.InsertString(++pos,_T("���ڰ�װ���ݿ����.....         "));
	}else if ( n==3){
		m_GuiListBox.InsertString(++pos,_T("���ݿ����װ���!             "));
		m_GuiListBox.InsertString(++pos,_T("--------------------------------"));
		m_GuiListBox.InsertString(++pos,_T("�뵥��Exit��ť�˳����������ó���!"));
		MessageBox(_T("ϵͳ�������! "));
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConfigServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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

	// TODO:  �ڴ˸��� DC ���κ�����
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
	// TODO: �ֶ�����mysql ���ݿ�

	//�ĳ�my.ini �����ļ�
	::LoadCursor(NULL,IDC_WAIT);
	UpdateData(TRUE);
	if ( atoi(m_port) < 1000 || atoi(m_port) >9999){
		MessageBox(_T("�˿ڷ�Χ1000-9999"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_EDIT_PORT)->SetFocus();
		return;
	}

	std::string port  = m_port.Trim().GetBuffer();
	std::string sName = m_serverName.Trim().GetBuffer();

	KProfile profile("my.ini");
	profile.WirteProfile("client","port",port);
	profile.WirteProfile("mysqld","port",port);

	//���� set.ini
	KProfile setFile("set.ini");
	setFile.WirteProfile("HOST_SET","port",port);
	setFile.WirteProfile("SERVER_NAME","servername",sName);
    
	//��дuninstall.bat �ļ�
	fstream outfile("uninstall.bat",ios_base::out);
	outfile << "rem ����ֹͣ���ݿ����......"<< std::endl;
	outfile <<"net stop "<< sName << std::endl;
	outfile <<"mysqld --remove "<<sName<<std::endl;
	outfile.close();
	
	//������
	AfxBeginThread(ThreadProc,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	::LoadCursor(NULL,IDC_ARROW);
}
