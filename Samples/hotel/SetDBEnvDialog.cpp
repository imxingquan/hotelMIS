// SetDBEnvDialog.cpp : 实现文件
//

#include "stdafx.h"
//#include "HotelMIS.h"
#include "SetDBEnvDialog.h"
//#include ".\setdbenvdialog.h"
#include "KProfile.h"

// CSetDBEnvDialog 对话框

IMPLEMENT_DYNAMIC(CSetDBEnvDialog, CDialog)
CSetDBEnvDialog::CSetDBEnvDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDBEnvDialog::IDD, pParent)
	, m_host(_T(""))
	, m_user(_T(""))
	, m_pwd(_T(""))
	, m_port(_T(""))
{
	hotelMIS::KProfile profile("set.ini");

	m_host =  profile.GetProfile("HOST_SET","host").c_str();
	m_user = profile.GetProfile("HOST_SET","user").c_str();
	m_pwd = profile.GetProfile("HOST_SET","pwd").c_str();
	m_port =  profile.GetProfile("HOST_SET","port").c_str();
	
}

CSetDBEnvDialog::~CSetDBEnvDialog()
{
}

void CSetDBEnvDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOST_EDIT, m_host);
	DDX_Text(pDX, IDC_USER_EDIT, m_user);
	DDX_Text(pDX, IDC_PWD_EDIT, m_pwd);
	DDX_Text(pDX, IDC_PORT_EDIT, m_port);
}


BEGIN_MESSAGE_MAP(CSetDBEnvDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSetDBEnvDialog 消息处理程序

void CSetDBEnvDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	hotelMIS::KProfile profile("set.ini");
	profile.WirteProfile("HOST_SET","host",m_host.GetBuffer());
	profile.WirteProfile("HOST_SET","user",m_user.GetBuffer());
	profile.WirteProfile("HOST_SET","pwd",m_pwd.GetBuffer());
	profile.WirteProfile("HOST_SET","port",m_port.GetBuffer());

	OnOK();
}
