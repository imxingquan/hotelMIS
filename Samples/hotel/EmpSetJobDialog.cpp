// EmpSetJobDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "EmpSetJobDialog.h"
//#include ".\empsetjobdialog.h"
#include "HJobSetCtrl.h"
#include ".\empsetjobdialog.h"

// CEmpSetJobDialog 对话框

IMPLEMENT_DYNAMIC(CEmpSetJobDialog, CDialog)
CEmpSetJobDialog::CEmpSetJobDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpSetJobDialog::IDD, pParent)
	, m_jobName(_T(""))
	,m_modifyFlag(false)
{
}

CEmpSetJobDialog::~CEmpSetJobDialog()
{
}

void CEmpSetJobDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_JOB_EDIT, m_GuiJobEdit);
	DDX_Control(pDX, IDC_ADD_JOB_BUTTON, m_GuiAddJobButton);
	DDX_Control(pDX, IDC_DEL_JOB_BUTTON, m_GuiDelJobButton);
	DDX_Control(pDX, IDC_JOB_LIST, m_GuiJobListCtrl);
	DDX_Text(pDX, IDC_JOB_EDIT, m_jobName);
	DDV_MaxChars(pDX, m_jobName, 20);
}


BEGIN_MESSAGE_MAP(CEmpSetJobDialog, CDialog)
	ON_BN_CLICKED(IDC_ADD_JOB_BUTTON, OnBnClickedAddJobButton)
	ON_BN_CLICKED(IDC_DEL_JOB_BUTTON, OnBnClickedDelJobButton)
	ON_NOTIFY(NM_CLICK, IDC_JOB_LIST, OnNMClickJobList)
	ON_EN_CHANGE(IDC_JOB_EDIT, OnEnChangeJobEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_JOB_LIST, OnNMDblclkJobList)
END_MESSAGE_MAP()


// CEmpSetJobDialog 消息处理程序
void CEmpSetJobDialog::Init()
{
	m_GuiJobListCtrl.InsertColumn(0,_T("编号"),LVCFMT_LEFT,40);
	m_GuiJobListCtrl.InsertColumn(1,_T("职位"),LVCFMT_LEFT,100);
	ListView_SetExtendedListViewStyleEx(m_GuiJobListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_GuiAddJobButton.EnableWindow(FALSE);
	m_GuiDelJobButton.EnableWindow(FALSE);
	Refresh();

}

void CEmpSetJobDialog::Refresh()
{	
	m_GuiJobListCtrl.DeleteAllItems();
	hotelMIS::HJobSetCtrl jobSetCtrl(m_con.get_con());
	hotelMIS::HJobSetVec vec = jobSetCtrl.getAllJob();
	hotelMIS::HJobSetVec::iterator it;
	int i =0;
	CString cnt;
	m_jobSetmap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_jobSetmap.insert(make_pair(i,it->getJob_id()));
		cnt.Format("%d",i+1);
		m_GuiJobListCtrl.InsertItem(i,cnt);
		m_GuiJobListCtrl.SetItemText(i,1,it->getJob_name().c_str());
		i++;
	}

}

void CEmpSetJobDialog::OnBnClickedAddJobButton()
{
	// TODO: 添加职位
	if ( false == m_modifyFlag)
	{
		UpdateData(TRUE);
		hotelMIS::HJobSetCtrl jobSetCtrl(m_con.get_con());
		jobSetCtrl.insert(hotelMIS::ReplaceChar(m_jobName).GetBuffer());
		Refresh();
		m_jobName.Empty();
		UpdateData(FALSE);
		m_GuiAddJobButton.EnableWindow(FALSE);
		m_modifyFlag = true;
	}
	else
	{
		UpdateData(TRUE);
		hotelMIS::HJobSetCtrl jobSetCtrl(m_con.get_con());
		hotelMIS::HJobSet jobset;
		jobset.setJob_id(m_jobSetmap[m_nIndex]);
		jobset.setJob_name(hotelMIS::ReplaceChar(m_jobName).GetBuffer());
		jobSetCtrl.Update(jobset);
		Refresh();
		m_jobName.Empty();
		UpdateData(FALSE);
		m_modifyFlag = false;
		m_GuiAddJobButton.SetWindowText(_T("添加"));
		m_GuiAddJobButton.EnableWindow(FALSE);
	}
}

void CEmpSetJobDialog::OnBnClickedDelJobButton()
{
	// TODO: 删除职位
	if ( m_nIndex != -1 ){
		TRACE("删除编号为:%d 的单位\n",m_jobSetmap[m_nIndex]);
		hotelMIS::HJobSetCtrl jobSetCtrl(m_con.get_con());
		jobSetCtrl.Delete(m_jobSetmap[m_nIndex]);
		Refresh();
		m_GuiDelJobButton.EnableWindow(FALSE);
	}
}

void CEmpSetJobDialog::OnNMClickJobList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 单击选中
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiJobListCtrl.ScreenToClient(&point);
	if (( m_nIndex = m_GuiJobListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelJobButton.EnableWindow(TRUE);
		TRACE("单击命中%d \n",m_nIndex);
	}
	*pResult = 0;
}

void CEmpSetJobDialog::OnEnChangeJobEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if ( m_jobName.Trim().GetLength() > 0 ){
		m_GuiAddJobButton.EnableWindow(TRUE);
	}else{
		m_GuiAddJobButton.EnableWindow(FALSE);
	}
}

BOOL CEmpSetJobDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiAddJobButton.ShowText();
	m_GuiDelJobButton.ShowText();
	
	// TODO:  在此添加额外的初始化
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEmpSetJobDialog::OnNMDblclkJobList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiJobListCtrl.ScreenToClient(&point);
	if (( m_nIndex = m_GuiJobListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelJobButton.EnableWindow(TRUE);
		m_GuiAddJobButton.EnableWindow(TRUE);
		m_GuiAddJobButton.SetWindowText(_T("修改"));
		m_modifyFlag = true;
		hotelMIS::HJobSetCtrl jobSetCtrl(m_con.get_con());
		hotelMIS::HJobSet jobSet = jobSetCtrl.get(m_jobSetmap[m_nIndex]);
		m_jobName.Format("%s",jobSet.getJob_name().c_str());
		UpdateData(FALSE);
	}
	*pResult = 0;
}
