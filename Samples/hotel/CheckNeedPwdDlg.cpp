// CheckNeedPwdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckNeedPwdDlg.h"
#include ".\checkneedpwddlg.h"
#include "KDBCon.h"
#include "HPwdCtrl.h"


// CCheckNeedPwdDlg 对话框

IMPLEMENT_DYNAMIC(CCheckNeedPwdDlg, CDialog)
CCheckNeedPwdDlg::CCheckNeedPwdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckNeedPwdDlg::IDD, pParent)
	, m_pwd(_T(""))
	,m_pwdIsRight(FALSE)
{
}

CCheckNeedPwdDlg::~CCheckNeedPwdDlg()
{
}

void CCheckNeedPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PWD_EDIT, m_GuiPwdEdit);
	DDX_Text(pDX, IDC_PWD_EDIT, m_pwd);
}


BEGIN_MESSAGE_MAP(CCheckNeedPwdDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCheckNeedPwdDlg 消息处理程序

void CCheckNeedPwdDlg::OnBnClickedOk()
{
	// TODO: 检查密码是否正确
	hotelMIS::KDBCon con;
	hotelMIS::HPwdCtrl hPwdCtrl(con.get_con());
	CString pwd = hPwdCtrl.getAwardPwd().c_str();

	UpdateData();
	if ( pwd == m_pwd ){
		m_pwdIsRight = TRUE;
		OnOK();
	}
	else{
		MessageBox(_T("输入的密码不正确,请重新输入!"),_T("警告"),MB_ICONWARNING|MB_OK);
	}
}
