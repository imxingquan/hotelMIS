#include "..\samples\hotel\outlookdemo.cpp"
// CreateDBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "CreateDB.h"
#include "CreateDBDlg.h"
#include "KResetDB.h"




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
	//ON_STN_DBLCLK(IDC_ABOUT_ICON, OnStnDblclickAboutIcon)
END_MESSAGE_MAP()


// CCreateDBDlg �Ի���



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


// CCreateDBDlg ��Ϣ�������

BOOL CCreateDBDlg::OnInitDialog()
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
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCreateDBDlg::OnPaint() 
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
	// TODO: ��������
	UpdateData(true);
	con.init(m_host.GetBuffer(),m_port.GetBuffer(),m_name.GetBuffer(),m_password.GetBuffer());
	con.get_con();
	if ( ! con.isConnect() ) {
		MessageBox("����Դ���ò���ȷ,����������!","����!",MB_ICONWARNING|MB_OK);
		con.close();
		return;
	}

	int result = MessageBox("�������ݿ⽫������ǰ����������,ȷ��Ҫ������?","����",MB_ICONWARNING|MB_YESNO);
	if ( IDYES == result ){
		KResetDB db(con.get_con());
		if ( db.ResetDB(dbfile)){
			MessageBox("���ݿ����óɹ�!","����",MB_ICONINFORMATION|MB_OK);
			m_setDBBtn.EnableWindow(false);
			m_setDemoDBBtn.EnableWindow(false);
		}else{
			MessageBox("���ݿ�����ʧ��!","����",MB_ICONINFORMATION|MB_OK);
		}
	}
	con.close();
}

LRESULT CCreateDBDlg::OnDetails(WPARAM wParam ,LPARAM lParam)
{
	
	m_details +="ִ�����:";
	m_details += theApp.globaStr.c_str();
	m_details += "\r\n";

	TRACE("buf = %s",theApp.globaStr.c_str());
	UpdateData(false);
	return 0;
}

