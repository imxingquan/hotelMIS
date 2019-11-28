// MemZZDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "MemZZDlg.h"
#include ".\memzzdlg.h"
#include "HMemberCtrl.h"


// CMemZZDlg 对话框

IMPLEMENT_DYNAMIC(CMemZZDlg, CDialog)
CMemZZDlg::CMemZZDlg(CWnd* pParent,CString bh,CString name,float money)
	: CDialog(CMemZZDlg::IDD, pParent)
	, m_OutBh(bh)
	, m_OutName(name)
	, m_OutRestMoney(money)
	, m_OutMoney(0)
	, m_InBh(_T(""))
	, m_InName(_T(""))
	, m_remark(_T(""))
{
}

CMemZZDlg::~CMemZZDlg()
{
}

void CMemZZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ZZOUT_BH, m_GuiEditOutBh);
	DDX_Text(pDX, IDC_EDIT_ZZOUT_BH, m_OutBh);
	DDX_Text(pDX, IDC_STATIC_OUTZZ_NAME, m_OutName);
	DDX_Text(pDX, IDC_STATIC_OUTZZ_REST, m_OutRestMoney);
	DDX_Text(pDX, IDC_EDIT_OUTZZ_MONERY, m_OutMoney);
	DDX_Text(pDX, IDC_EDIT_INZZ_BH, m_InBh);
	DDX_Text(pDX, IDC_STATIC_INZZ_NAME, m_InName);
	DDX_Text(pDX, IDC_EDIT5, m_remark);
}


BEGIN_MESSAGE_MAP(CMemZZDlg, CDialog)
	ON_BN_CLICKED(IDC_ZZOUT_BTN, OnBnClickedZzoutBtn)
	ON_EN_CHANGE(IDC_EDIT_INZZ_BH, OnEnChangeEditInzzBh)
	ON_EN_CHANGE(IDC_EDIT_ZZOUT_BH, OnEnChangeEditZzoutBh)
END_MESSAGE_MAP()


// CMemZZDlg 消息处理程序

void CMemZZDlg::OnBnClickedZzoutBtn()
{
	UpdateData(TRUE);
	if ( m_OutName.IsEmpty() ){
		MessageBox(_T("转出账户不存在,请重新输入!"),_T("提示"),MB_OK|MB_ICONINFORMATION);
		GetDlgItem(IDC_EDIT_ZZOUT_BH)->SetFocus();
		return ;
	}
	if ( m_InName.IsEmpty()){
		MessageBox(_T("转入账户不存在,请重新输入!"),_T("提示"),MB_OK|MB_ICONINFORMATION);
		GetDlgItem(IDC_EDIT_INZZ_BH)->SetFocus();
		return ;

	}
	if ( m_OutBh == m_InBh )
	{
		MessageBox(_T("转出和转入账号不能相同!"),_T("提示"),_T("提示")||MB_OK|MB_ICONINFORMATION);
		GetDlgItem(IDC_EDIT_INZZ_BH)->SetFocus();
		return ;
	}
	
	if ( m_OutMoney < 0)
	{
		MessageBox(_T("转出金额不在取值范围!"),_T("提示"),MB_OK|MB_ICONINFORMATION);
		return ;
	}
	if ( m_OutMoney > m_OutRestMoney )
	{
		MessageBox(_T("转出的金额大于账户的余额,不能操做．请重新输入转出金额!"),_T("提示"),
			MB_OK|MB_ICONINFORMATION);
		GetDlgItem(IDC_EDIT_OUTZZ_MONERY)->SetFocus();
		return ;
	}

	


	hotelMIS::HMzz mzz;
	mzz.sbh = hotelMIS::ReplaceChar(m_OutBh);
	mzz.dbh = hotelMIS::ReplaceChar(m_InBh);
	mzz.zzmoney = m_OutMoney;
	CTime t = CTime::GetCurrentTime();
	CString dt = t.Format("%Y-%m-%d %H:%M:%S");
	mzz.zzdate = dt.GetBuffer();
	mzz.remark = m_remark.GetBuffer();

	hotelMIS::HMemberCtrl memberCtrl(m_con.get_con());
	hotelMIS::HMzzCtrl zzCtrl(m_con.get_con());
	memberCtrl.zz(mzz.sbh,mzz.dbh,mzz.zzmoney);
	zzCtrl.insert(mzz);

	MessageBox(_T("转账成功!"),_T("提示"),MB_OK|MB_ICONINFORMATION);
	m_OutBh.Empty();
	m_OutName.Empty();
	m_OutRestMoney = 0;
	m_OutMoney = 0;
	m_InBh.Empty();
	m_InName.Empty();
	UpdateData(0);
}

void CMemZZDlg::OnEnChangeEditInzzBh()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	// 提取转入用户名
	UpdateData();

	string bh = m_InBh.Trim().GetBuffer();
	hotelMIS::HMemberCtrl memCtrl(m_con.get_con());
	hotelMIS::HMember m = memCtrl.getMember(bh);
	if ( !m.mname.empty() ){
		m_InName = m.mname.c_str();
		UpdateData(FALSE);
	}

}

void CMemZZDlg::OnEnChangeEditZzoutBh()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData();
	string bh = m_OutBh.Trim().GetBuffer();
	hotelMIS::HMemberCtrl memCtrl(m_con.get_con());
	hotelMIS::HMember m = memCtrl.getMember(bh);
	if ( !m.mname.empty() ){
		m_OutName = m.mname.c_str();
		m_OutRestMoney = m.czmoney;
		UpdateData(FALSE);
	}
}
