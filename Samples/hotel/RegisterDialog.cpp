// RegisterDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RegisterDialog.h"
#include "mycdkey.h"
#include ".\registerdialog.h"
// CRegisterDialog �Ի���

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


// CRegisterDialog ��Ϣ�������

void CRegisterDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��֤���벢
	UpdateData(true);
	MyCdKey myCdKey;
	CString cdkey;
	cdkey.Format("%s-%s-%s-%s",m_cdkey1,m_cdkey2,m_cdkey3,m_cdkey4);
	if ( cdkey == myCdKey.getKey() )
	{
		CWinApp* pApp = AfxGetApp();
		pApp->WriteProfileString("Settings", "cdkey", cdkey);
		MessageBox(_T("ע��ɹ�����ӭ����ʹ�ã�"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
		OnOK();
	}
	else{
		MessageBox(_T("���кŲ���ȷ������ȡ���������ñ������"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
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

	//m_linkBtn.SetWindowText("���������������! ��ӭ��������������(http://www.idcwest.net)�������ǵĲ�Ʒ�� ");
	MyCdKey cdkey;
	DWORD reg = cdkey.GetCpuPeInfo();
	CString t;
	t.Format("����������кż�����Ϊ %lu",reg);
	m_GuiRegStatic.SetWindowText(t);
	t.Format("������������,�������ǵ����!����������кż�����Ϊ %lu",reg);
	m_linkBtn.SetLink(_T("http://www.digitwest.com/"));
	m_linkBtn.SetToolTip(t);
	Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CRegisterDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("���δ������Ȩ,�������������û�!"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_OK);
	OnCancel();
}


