// SetMemDjDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SetMemDjDlg.h"

#include "HMemberCtrl.h"

#include ".\setmemdjdlg.h"


// CSetMemDjDlg 对话框

IMPLEMENT_DYNAMIC(CSetMemDjDlg, CDialog)
CSetMemDjDlg::CSetMemDjDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetMemDjDlg::IDD, pParent)
	, m_djname(_T(""))
	, m_zhekou(0),
	m_isDel(true),
	m_nPos(-1)
{
}

CSetMemDjDlg::~CSetMemDjDlg()
{
}

void CSetMemDjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DJNAME_EDIT, m_djname);
	DDX_Text(pDX, IDC_ZK_EDIT, m_zhekou);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_ADDDJ_BUTTON, m_GuiAddBtn);
	DDX_Control(pDX, IDC_MD_BUTTON, m_GuiMDBtn);
}


BEGIN_MESSAGE_MAP(CSetMemDjDlg, CDialog)
	ON_BN_CLICKED(IDC_ADDDJ_BUTTON, OnBnClickedAdddjButton)
	ON_BN_CLICKED(IDC_MD_BUTTON, OnBnClickedMdButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnNMClickList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
END_MESSAGE_MAP()


// CSetMemDjDlg 消息处理程序

void CSetMemDjDlg::OnBnClickedAdddjButton()
{
	// TODO: 添加
	UpdateData();
	if ( m_djname.Trim().IsEmpty())
	{
		MessageBox(_T("等级名称不能不空!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_DJNAME_EDIT)->SetFocus();
		return ;
	}
	if ( m_zhekou < 0 || m_zhekou >9.9){
		MessageBox(_T("折扣值超出范围,请重新填写!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_ZK_EDIT)->SetFocus();
		return ;
	}
	hotelMIS::HMdjCtrl hMdjCtrl(m_con.get_con());
	hMdjCtrl.insert(m_djname.GetBuffer(),m_zhekou);

	m_djname.Empty();
	m_zhekou=0.0f;
	UpdateData(FALSE);

	Refresh();

}

void CSetMemDjDlg::OnBnClickedMdButton()
{
	// TODO: 删除和修改
	
	if ( m_nPos != -1){
		hotelMIS::HMdjCtrl hMdjCtrl(m_con.get_con());
		if ( m_isDel ){
			hMdjCtrl.Delete(m_map[m_nPos]);
		}
		else{
			m_isDel = true;
			UpdateData();
			
			if ( m_zhekou < 0 || m_zhekou >9.9){
				MessageBox(_T("折扣值超出范围,请重新填写!"),_T("提示"),MB_ICONINFORMATION|MB_OK);
				GetDlgItem(IDC_ZK_EDIT)->SetFocus();
				return ;
			}
			hMdjCtrl.Update(m_map[m_nPos],m_djname.GetBuffer(),m_zhekou);
			m_GuiMDBtn.SetWindowText(_T("删除"));
			m_djname.Empty();
			m_zhekou=0.0f;
			UpdateData(FALSE);
		}
		Refresh();
	}
}

BOOL CSetMemDjDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	Init();

	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetMemDjDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_list.GetSelectionMark();
	if ( nPos != -1){
		m_nPos =nPos;
		m_GuiMDBtn.EnableWindow(TRUE);
	}

	*pResult = 0;
}

void CSetMemDjDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int nPos = m_list.GetSelectionMark();
	if ( nPos != -1){
		m_nPos =nPos;
		m_GuiMDBtn.EnableWindow(TRUE);
		m_GuiMDBtn.SetWindowText(_T("修改"));
		m_isDel = false;

		m_djname= m_list.GetItemText(nPos,1);
		CString zk = m_list.GetItemText(nPos,2);

		m_zhekou = atof(zk);
		UpdateData(FALSE);

		Refresh();
	}
}

//
// 初始化列表
//
void CSetMemDjDlg::Init()
{
	m_list.InsertColumn(0,_T("编号"),LVCFMT_LEFT,50);
	m_list.InsertColumn(1,_T("等级名称"),LVCFMT_LEFT,100);
	m_list.InsertColumn(2,_T("折扣值"),LVCFMT_RIGHT,70);
	
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}

//
// 刷新列表
//
void CSetMemDjDlg::Refresh()
{
	m_list.DeleteAllItems();
	m_map.clear();

	hotelMIS::HMdjCtrl hMdjCtrl(m_con.get_con());
	hotelMIS::HMdjVec vec = hMdjCtrl.getAllMdj();
	hotelMIS::HMdjVec::iterator it;
	int i = 0;
	CString t;

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_map.insert(make_pair(i,it->id));
	
		t.Format("%d",it->id);
		m_list.InsertItem(i,t);
		m_list.SetItemText(i,1,it->djname.c_str());
		t.Format("%.2f",it->zhekou);
		m_list.SetItemText(i,2,t);
		i++;
	}
}
