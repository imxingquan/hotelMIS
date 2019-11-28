// SysUserManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "SysUserManagerDlg.h"
//#include ".\sysusermanagerdlg.h"
#include "HOpType.h"
#include "HAdminBdy.h"

// CSysUserManagerDlg 对话框

IMPLEMENT_DYNAMIC(CSysUserManagerDlg, CDialog)
CSysUserManagerDlg::CSysUserManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysUserManagerDlg::IDD, pParent)
	, m_logName(_T(""))
	, m_password(_T(""))
	, m_fname(_T(""))
	, m_remark(_T(""))
	, m_bM0(FALSE)
	, m_bM1(FALSE)
	, m_bM2(FALSE)
	, m_bM3(FALSE)
	, m_bM4(FALSE)
	, m_bM5(FALSE)
	, m_bM6(FALSE)
	, m_bM7(FALSE)
	, m_bM8(FALSE)
	, m_isModify(false)
	, m_nPos(-1)
	, m_purview(_T(""))
	, m_purviewr(_T(""))
	, m_purviewlist(_T(""))
{
}

CSysUserManagerDlg::~CSysUserManagerDlg()
{
}

void CSysUserManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GUPGROUPLT, m_GuiGroupBoxLT);
	DDX_Control(pDX, IDC_GUIGROUPLB, m_GuiGroupBoxLB);
	DDX_Control(pDX, IDC_GUIGROUPR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_EDIT1, m_GuiLogNameEdit);
	DDX_Control(pDX, IDC_EDIT2, m_GuiLogPwdEdit);
	DDX_Control(pDX, IDC_EDIT4, m_GuiNameEdit);
	DDX_Control(pDX, IDC_EDIT5, m_GuiRemarkEdit);
	DDX_Control(pDX, IDC_ADDSYS_BUTTON, m_GuiAddSysButton);
	DDX_Control(pDX, IDC_DELSYS_BUTTON, m_GuiDelSysButton);
	DDX_Control(pDX, IDC_SYS_LIST, m_GuiSysListCtrl);
	DDX_Control(pDX, IDC_BUTTON6, m_GuiToolButton);
	DDX_Control(pDX, IDC_PURVIEW_COMBO, m_GuiPurviewCombo);
	DDX_Control(pDX, IDC_ADDOPTYPE_BUTTON, m_GuiAddOpTypeButton);
	DDX_Control(pDX, IDC_DELOPTYPE_BUTTON, m_GuiDelOpTypeButton);
	DDX_Control(pDX, IDC_SETPURVIEW_BUTTON, m_GuiSetPurviewButton);
	DDX_Control(pDX, IDC_M0_CHECK, m_GuiM0Check);
	DDX_Control(pDX, IDC_M1_CHECK, m_GuiM1Check);
	DDX_Control(pDX, IDC_M2_CHECK, m_GuiM2Check);
	DDX_Control(pDX, IDC_M3_CHECK, m_GuiM3Check);
	DDX_Control(pDX, IDC_M4_CHECK, m_GuiM4Check);
	DDX_Control(pDX, IDC_M5_CHECK, m_GuiM5Check);
	DDX_Control(pDX, IDC_M6_CHECK, m_GuiM6Check);
	DDX_Control(pDX, IDC_M7_CHECK, m_GuiM7Check);
	DDX_Text(pDX, IDC_EDIT1, m_logName);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT4, m_fname);
	DDX_Text(pDX, IDC_EDIT5, m_remark);
	DDX_Check(pDX, IDC_M0_CHECK, m_bM0);
	DDX_Check(pDX, IDC_M1_CHECK, m_bM1);
	DDX_Check(pDX, IDC_M2_CHECK, m_bM2);
	DDX_Check(pDX, IDC_M3_CHECK, m_bM3);
	DDX_Check(pDX, IDC_M4_CHECK, m_bM4);
	DDX_Check(pDX, IDC_M5_CHECK, m_bM5);
	DDX_Check(pDX, IDC_M6_CHECK, m_bM6);
	DDX_Check(pDX, IDC_M7_CHECK, m_bM7);
	DDX_Check(pDX, IDC_M8_CHECK, m_bM8);
	DDX_Text(pDX, IDC_PURVIEW_COMBO, m_purview);
	DDX_Control(pDX, IDC_PURVIEW_LIST, m_GuiPurviewList);
	DDX_Control(pDX, IDC_PURVIEW_EDIT, m_GuiPurviewEdit);
	DDX_Text(pDX, IDC_PURVIEW_EDIT, m_purviewr);
	DDX_LBString(pDX, IDC_PURVIEW_LIST, m_purviewlist);
}


BEGIN_MESSAGE_MAP(CSysUserManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_ADDSYS_BUTTON, OnAddAndEditSys)
	ON_BN_CLICKED(IDC_DELSYS_BUTTON, OnDelSys)
	ON_BN_CLICKED(IDC_ADDOPTYPE_BUTTON, OnAddPurview)
	ON_BN_CLICKED(IDC_DELOPTYPE_BUTTON, OnDelPurview)
	ON_BN_CLICKED(IDC_SETPURVIEW_BUTTON, OnSetPurview)
	ON_BN_CLICKED(IDC_BUTTON6, OnDispAndHide)
	ON_NOTIFY(NM_DBLCLK, IDC_SYS_LIST, OnNMDblclkSysList)
//	ON_CBN_SELCHANGE(IDC_OPTYPE_COMBO, OnCbnSelchangeOptypeCombo)
	ON_NOTIFY(NM_CLICK, IDC_SYS_LIST, OnNMClickSysList)
//	ON_CBN_EDITCHANGE(IDC_OPTYPE_COMBO, OnCbnEditchangeOptypeCombo)
ON_LBN_SELCHANGE(IDC_PURVIEW_LIST, OnLbnSelchangePurviewList)
END_MESSAGE_MAP()


// CSysUserManagerDlg 消息处理程序

void CSysUserManagerDlg::OnAddAndEditSys()
{
	// TODO: 添加系统用户
	
	UpdateData(TRUE);
	if ( m_logName.Trim().IsEmpty() ){
		AfxMessageBox(_T("请输入登陆姓名!"));
		m_GuiLogNameEdit.SetFocus();
		return ;
	}else if ( m_password.Trim().IsEmpty()){
		AfxMessageBox(_T("请输入密码!"));
		m_GuiLogPwdEdit.SetFocus();
		return;
	}else if ( m_purview.IsEmpty() ){
		AfxMessageBox(_T("请选择权限名!"));
		return;
	}

	hotelMIS::HAdminBdy adminBdy(m_con.get_con());
	hotelMIS::HAdmin admin;
	admin.setLoginId(hotelMIS::ReplaceChar(m_logName).GetBuffer());
	admin.setPassword(hotelMIS::ReplaceChar(m_password).GetBuffer());
	admin.setOpType(hotelMIS::ReplaceChar(m_purview).GetBuffer());
	admin.setName(hotelMIS::ReplaceChar(m_fname).GetBuffer());
	admin.setDesc(hotelMIS::ReplaceChar(m_remark).GetBuffer());
	admin.setId(m_sysMap[m_nPos].getId());
	if ( m_isModify ){
		adminBdy.update(admin);
		m_isModify = false;
		m_GuiAddSysButton.SetWindowText(_T("添加"));
		//m_GuiAddSysButton.EnableWindow(false);
		AfxMessageBox(_T("资料修改成功!"));
	}
	else{
	   adminBdy.insert(admin);
	   //m_GuiAddSysButton.EnableWindow(false);
	    m_GuiDelSysButton.EnableWindow(false);
		AfxMessageBox(_T("资料添加成功!"));
	}
	//清空	
	m_logName.Empty();
	m_password.Empty();
	m_purview.Empty();
	m_fname.Empty();
	m_remark.Empty();
	m_GuiLogNameEdit.SetFocus();
	UpdateData(false);
	RefreshSys();
}

void CSysUserManagerDlg::OnDelSys()
{
	// TODO: 删除系统用户
	int result = AfxMessageBox(_T("确定要删除这个用户?"),MB_YESNO|MB_ICONWARNING);
	if ( result == IDYES){
		hotelMIS::HAdminBdy adminBdy(m_con.get_con());
		adminBdy.Delete(m_sysMap[m_nPos].getId());
		m_GuiDelSysButton.EnableWindow(false);

		m_logName.Empty();
		m_password.Empty();
		m_purview.Empty();
		m_fname.Empty();
		m_remark.Empty();
		m_GuiLogNameEdit.SetFocus();
		UpdateData(false);
		RefreshSys();
	}
}

void CSysUserManagerDlg::ResetComboBox()
{
	hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewr).GetBuffer(),m_con.get_con());
	//------------------------------------------------------
	//删除ComboBox;
	for ( int i =  m_GuiPurviewCombo.GetCount()-1; i >=0; i--)
		m_GuiPurviewCombo.DeleteString(i);
	

	//重置map
	m_purviewCombo.clear();
	hotelMIS::purviewList list= opType.getAllPurview();
	hotelMIS::purviewList::iterator it;
	int pos;
	for ( it = list.begin(); it != list.end(); it++)
	{
		pos = m_GuiPurviewCombo.AddString(it->c_str());
		m_purviewCombo.insert(make_pair(it->c_str(),pos));
	}
	m_GuiPurviewCombo.SetCurSel(0);
	//------------------------------------------------------- 

}
void CSysUserManagerDlg::OnAddPurview()
{
	// TODO: 添加权限
	UpdateData(true);
	if ( m_purviewr.Trim().IsEmpty()){
		AfxMessageBox(_T("权限名不能为空!"));
		m_GuiPurviewEdit.SetFocus();
		return;
	}
	
	hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewr).GetBuffer(),m_con.get_con());
	
	if ( opType.isExist(m_purviewr.Trim().GetBuffer()) ){
		AfxMessageBox(_T("这个权限组已经存在不能在增加!,请换一个名字!"));
		return;
	}
	//在数据库中增加权限名
	opType.addPurview();
	//在ListBox中增加权限名
	m_GuiPurviewList.AddString(hotelMIS::ReplaceChar(m_purviewr));
	
	//在ComboBox中增加权限名
	//int nPos = m_GuiPurviewCombo.AddString(m_purviewr.Trim()); //右边的也一样要添加
	//在map中增加权限名
	//m_purviewCombo.insert(make_pair(m_purview.Trim().GetBuffer(),nPos));
	
	//重置ComBobx
	ResetComboBox();

	AfxMessageBox(_T("添加成功!"));

	m_purviewr.Empty();
	UpdateData(false);
}


void CSysUserManagerDlg::OnDelPurview()
{
	// TODO: 删除权限

	UpdateData(true);
	if ( m_purviewlist.Trim().IsEmpty() ){
		AfxMessageBox(_T("请先选中要删除的权限名!"));
		return;
	}
	int result = AfxMessageBox(_T("确定真的要删除!"),MB_YESNO|MB_ICONWARNING);
	if ( result == IDYES){
		if ( m_purviewlist.Trim() == _T("系统管理员")){
			AfxMessageBox(_T("不能删除系统管理员的权限!"));
			return;
		}
		
		//删除权限名
		hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewlist).GetBuffer(),m_con.get_con());
		opType.delPurview();
		//删除ListBox中的权限名
		m_GuiPurviewList.DeleteString(m_GuiPurviewList.GetCurSel());
		
		ResetComboBox();
		
		//删除ComboBox中的权限名
		//m_GuiPurviewCombo.DeleteString(m_purviewCombo[m_purviewlist.Trim().GetBuffer()]);
		////删除map中的权限名
		//m_purviewCombo.erase(m_purviewlist.Trim().GetBuffer());
		//
		//m_GuiPurviewCombo.SetCurSel(0);

		m_GuiDelOpTypeButton.EnableWindow(false);
		//m_purview.Empty();
	}
}

void CSysUserManagerDlg::OnSetPurview()
{
	// TODO: 设置权限
	UpdateData(true);
	int result = AfxMessageBox(_T("确实要改变当前权限组的权限?"),MB_YESNO);
	if ( result == IDYES)
	{
		hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewlist).GetBuffer(),m_con.get_con());
		opType.setM0(m_bM0);	//餐饮管理
		opType.setM1(m_bM1);	//库存管理
		opType.setM2(m_bM2);	//账单查询
		opType.setM3(m_bM3);	//员工管理
		opType.setM4(m_bM4);	//菜谱管理
		opType.setM5(m_bM5);	//统计报表
		opType.setM6(m_bM6);	//系统设置
		opType.setM7(m_bM7);	//其它功能
		opType.setM8(m_bM8);	//会员工管理
		m_GuiSetPurviewButton.EnableWindow(false);
	}

}

void CSysUserManagerDlg::OnLbnSelchangePurviewList()
{
	// TODO: 根据选择改动checkbox控件的显示状态
	UpdateData(true);
	TRACE("list =%s\n",m_purviewlist);
	if (m_GuiPurviewList.GetCurSel() != -1){
		m_GuiSetPurviewButton.EnableWindow(true);   //权限设置可用
		m_GuiDelOpTypeButton.EnableWindow(true);	//删除可用
		hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewlist).GetBuffer(),m_con.get_con());
		m_bM0 = opType.getM0();
		m_bM1 = opType.getM1();
		m_bM2 = opType.getM2();
		m_bM3 = opType.getM3();
		m_bM4 = opType.getM4();
		m_bM5 = opType.getM5();
		m_bM6 = opType.getM6();
		m_bM7 = opType.getM7();
		m_bM8 = opType.getM8();
		UpdateData(false);
	}

}

void CSysUserManagerDlg::OnDispAndHide()
{
	// TODO: 显示或隐藏 权限栏
}

void CSysUserManagerDlg::InitSys()
{
	//1) 填充权限列表
	hotelMIS::HOpType opType(m_con.get_con());
	hotelMIS::purviewList list= opType.getAllPurview();
	hotelMIS::purviewList::iterator it;
	int pos;
	for ( it = list.begin(); it != list.end(); it++)
	{
		pos = m_GuiPurviewCombo.AddString(it->c_str());
		m_purviewCombo.insert(make_pair(it->c_str(),pos));
		
	}
	m_GuiPurviewCombo.SetCurSel(0);
	//2) 填充用户列表
	int i = 0;
	
	m_GuiSysListCtrl.InsertColumn(i++,_T("编号"),LVCFMT_LEFT,40);
	m_GuiSysListCtrl.InsertColumn(i++,_T("登陆名"),LVCFMT_LEFT,80);
	m_GuiSysListCtrl.InsertColumn(i++,_T("密码"),LVCFMT_LEFT,70);
	m_GuiSysListCtrl.InsertColumn(i++,_T("权限"),LVCFMT_LEFT,70);
	m_GuiSysListCtrl.InsertColumn(i++,_T("姓名"),LVCFMT_LEFT,70);
	m_GuiSysListCtrl.InsertColumn(i++,_T("描述"),LVCFMT_LEFT,100);
    ListView_SetExtendedListViewStyleEx(m_GuiSysListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//删除用户按钮不可用
	m_GuiDelSysButton.EnableWindow(false);
	RefreshSys();
}

void CSysUserManagerDlg::RefreshSys()
{
	hotelMIS::HAdminBdy adminBdy(m_con.get_con());
	hotelMIS::HAdminVec vec= adminBdy.getAllAdminInfo();
	hotelMIS::HAdminVec::iterator it;
	int i = 0,j;
	CString t;
	m_GuiSysListCtrl.DeleteAllItems();
	m_sysMap.clear();
	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		j = 1;
		t.Format("%d",i+1);
		m_sysMap.insert(make_pair(i,*it));
		m_GuiSysListCtrl.InsertItem(i,t);
		m_GuiSysListCtrl.SetItemText(i,j++,it->getLoginId().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getPassword().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getOpType().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getName().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getDesc().c_str());
		i++;
	}
}

void CSysUserManagerDlg::InitPurview()
{
	//权限设置不可用
	m_GuiSetPurviewButton.EnableWindow(false);
	//删除不可用
	m_GuiDelOpTypeButton.EnableWindow(false);

	//1) 填充权限列表
	hotelMIS::HOpType opType(m_con.get_con());
	hotelMIS::purviewList list= opType.getAllPurview();
	hotelMIS::purviewList::iterator it;
	for ( it = list.begin(); it != list.end(); it++)
	{
		m_GuiPurviewList.AddString(it->c_str());
	}

}
void CSysUserManagerDlg::OnNMDblclkSysList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiSysListCtrl.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiSysListCtrl.HitTest(point)) != -1 ) {
		hotelMIS::HAdmin admin = m_sysMap[nPos];
		m_logName = admin.getLoginId().c_str();
		m_password = admin.getPassword().c_str();
		m_purview = admin.getOpType().c_str();
		m_fname = admin.getName().c_str();
		m_remark = admin.getDesc().c_str();
        UpdateData(false);
		m_isModify = true;
		////DDX对 ComboBox 的 DownList 不可用,用下边的方法
		m_GuiPurviewCombo.SetCurSel(m_purviewCombo[m_purview.GetBuffer()]);
		
		m_GuiAddSysButton.SetWindowText(_T("修改"));
	}

}



BOOL CSysUserManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiAddSysButton.ShowText();
	m_GuiDelSysButton.ShowText();
	m_GuiAddOpTypeButton.ShowText();
	m_GuiDelOpTypeButton.ShowText();
	m_GuiToolButton.ShowText();
	m_GuiSetPurviewButton.ShowText();

	// TODO:  在此添加额外的初始化
	InitSys();
	InitPurview();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSysUserManagerDlg::OnNMClickSysList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiSysListCtrl.ScreenToClient(&point);
	if (( m_nPos= m_GuiSysListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelSysButton.EnableWindow(true);
	}
}



