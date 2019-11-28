// AddMemberDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AddMemberDlg.h"
#include ".\addmemberdlg.h"
#include "HMemberCtrl.h"
#include "HMember.h"

// CAddMemberDlg 对话框

IMPLEMENT_DYNAMIC(CAddMemberDlg, CDialog)
CAddMemberDlg::CAddMemberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddMemberDlg::IDD, pParent)
	, m_bh(_T(""))
	, m_mname(_T(""))
	, m_sex(_T(""))
	, m_birth(_T(""))
	, m_telphone(_T(""))
	, m_mdjname(_T(""))
	, m_zhekou(0)
	, m_czmoney(0)
	, m_remark(_T(""))
{
}

CAddMemberDlg::~CAddMemberDlg()
{
}

void CAddMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BH_EDIT, m_GuiBhEdit);
	DDX_Control(pDX, IDC_MNAME_EDIT2, m_GuiMnameEdit);
	DDX_Control(pDX, IDC_SEXCOMBO, m_GuiSexCombo);
	DDX_Control(pDX, IDC_BIRTH_EDIT, m_GuiBirthEdit);
	DDX_Control(pDX, IDC_TEL_EDIT, m_GuiTelEdit);
	DDX_Control(pDX, IDC_MDJ_COMBO, m_GuiMDJCombo);
	DDX_Control(pDX, IDC_ZK_EDIT, m_GuiZKEdit);
	DDX_Control(pDX, IDC_CZMONEY_EDIT, m_GuiCzMoneyEdit);
	DDX_Control(pDX, IDC_REMARK_EDIT, m_GuiRemarkEdit);
	DDX_Text(pDX, IDC_BH_EDIT, m_bh);
	DDX_Text(pDX, IDC_MNAME_EDIT2, m_mname);
	DDX_CBString(pDX, IDC_SEXCOMBO, m_sex);
	DDX_Text(pDX, IDC_BIRTH_EDIT, m_birth);
	DDX_Text(pDX, IDC_TEL_EDIT, m_telphone);
	DDX_CBString(pDX, IDC_MDJ_COMBO, m_mdjname);
	DDX_Text(pDX, IDC_ZK_EDIT, m_zhekou);
	DDX_Text(pDX, IDC_CZMONEY_EDIT, m_czmoney);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_remark);
}


BEGIN_MESSAGE_MAP(CAddMemberDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_MDJ_COMBO, OnCbnSelchangeMdjCombo)
END_MESSAGE_MAP()


// CAddMemberDlg 消息处理程序

void CAddMemberDlg::OnBnClickedOk()
{
	// TODO: 保存
	UpdateData();

	//错误处理

	hotelMIS::HMemberCtrl hMemberCtrl(m_con.get_con());
	
	//验证会员编号
	if ( m_bh.Trim().IsEmpty())
	{
		MessageBox(_T("请输入会员编号!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		m_GuiBhEdit.SetFocus();
		return;
	}

	if ( hMemberCtrl.isExist(m_bh.Trim().GetBuffer()))
	{
		MessageBox(_T("此编号的会员已经存在,请重新输入编号!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		m_GuiBhEdit.SetFocus();
		return;
	}
	
	//验证会员姓名
	if ( m_mname.Trim().IsEmpty())
	{
		MessageBox(_T("请输入会员姓名!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		m_GuiMnameEdit.SetFocus();
		return;
	}
	
	//
	hotelMIS::HMember hMember;
	hMember.bh = hotelMIS::ReplaceChar(m_bh).GetBuffer();
	hMember.mbirth = hotelMIS::ReplaceChar(m_birth).GetBuffer();

	int nPos =m_GuiMDJCombo.GetCurSel();
	hMember.mdjid = m_map[nPos].first;
	hMember.mdjname = hotelMIS::ReplaceChar(m_mdjname).GetBuffer();
	hMember.zhekou = m_map[nPos].second;
	hMember.mname = hotelMIS::ReplaceChar(m_mname).GetBuffer();
	
	CTime time=CTime::GetCurrentTime();
	hMember.rhdate = time.Format("%Y-%m-%d");
	hMember.remark = hotelMIS::ReplaceChar(m_remark).GetBuffer();
	hMember.telphone = hotelMIS::ReplaceChar(m_telphone).GetBuffer();
	hMember.sex = hotelMIS::ReplaceChar(m_sex).GetBuffer();

	hMemberCtrl.insert(hMember);

	OnOK();
}

BOOL CAddMemberDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  初始化 性别, 等级,折扣
	m_GuiSexCombo.AddString(_T("男"));
	m_GuiSexCombo.AddString(_T("女"));
	m_GuiSexCombo.SetCurSel(0);

	hotelMIS::HMdjCtrl hMdjCtrl(m_con.get_con());
	hotelMIS::HMdjVec vec = hMdjCtrl.getAllMdj();
	hotelMIS::HMdjVec::iterator it;

	int nPos = -1;
	m_map.clear();

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		nPos = m_GuiMDJCombo.AddString(it->djname.c_str());
		m_map.insert(make_pair(nPos,make_pair(it->id,it->zhekou)));
	}
	
	m_GuiMDJCombo.SetCurSel(0);

	m_zhekou = m_map[0].second;
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddMemberDlg::OnCbnSelchangeMdjCombo()
{
	// TODO: 随之更改折扣值
	UpdateData(TRUE);

	int nPos = m_GuiMDJCombo.GetCurSel();
	
	m_zhekou = m_map[nPos].second;
	
	UpdateData(FALSE);

}
