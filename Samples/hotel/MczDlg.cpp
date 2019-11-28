// MczDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MczDlg.h"
#include ".\mczdlg.h"

#include "KDBCon.h"
#include "HMemberCtrl.h"
#include "HMember.h"
#include "HAdminBdy.h"

// CMczDlg 对话框

IMPLEMENT_DYNAMIC(CMczDlg, CDialog)
CMczDlg::CMczDlg(CWnd* pParent  ,CString bh,CString name)
	: CDialog(CMczDlg::IDD, pParent)
	, m_bh(_T(""))
	, m_mname(_T(""))
	, m_czmoney(0)
	, m_remark(_T(""))
{
	m_bh = bh;
	m_mname = name;
}

CMczDlg::~CMczDlg()
{
}

void CMczDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BH_EDIT, m_bh);
	DDX_Text(pDX, IDC_MNAME_EDIT, m_mname);
	DDX_Text(pDX, IDC_CZMONEY_EDIT, m_czmoney);
	DDV_MinMaxFloat(pDX,IDC_CZMONEY_EDIT,-9999,9999);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_remark);
}


BEGIN_MESSAGE_MAP(CMczDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CMczDlg 消息处理程序

void CMczDlg::OnBnClickedOk()
{
	UpdateData();
	
	if ( m_czmoney == 0.0f)
	{
		MessageBox(_T("请填写充值金额!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_CZMONEY_EDIT)->SetFocus();
		return ;
	}

	CString t;
	t.Format("确定要给会员[ %s ]充值 %.2f 元?",m_mname,m_czmoney);

	int r = MessageBox(t,_T("提示"),MB_ICONQUESTION|MB_YESNO);
	if ( r != IDYES){
		return;
	}
	
	hotelMIS::KDBCon con;
	hotelMIS::HMemberCtrl hMemberCtrl(con.get_con());
	hotelMIS::HMczCtrl hMczCtrl(con.get_con());

	
	hMemberCtrl.cz(m_bh.GetBuffer(),m_czmoney);
	hotelMIS::HMcz hmcz;
	hmcz.bh = m_bh;
	CTime cTime = CTime::GetCurrentTime();
	hmcz.czdate = cTime.Format("%Y-%m-%d %H:%M:%S");
	hmcz.czmoney = m_czmoney;
	hmcz.opname =  hotelMIS::HAdminBdy::_log_name;
	hmcz.remark = m_remark.Trim().GetBuffer();
	hMczCtrl.insert(hmcz);
	OnOK();
}
