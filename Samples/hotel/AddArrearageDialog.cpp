
// AddArrearageDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "AddArrearageDialog.h"

#include <cassert>
using namespace std;
// CAddArrearageDialog 对话框

IMPLEMENT_DYNAMIC(CAddArrearageDialog, CDialog)
CAddArrearageDialog::CAddArrearageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddArrearageDialog::IDD, pParent)
	, m_gzName(_T(""))
	, m_gzPhone(_T(""))
	, m_gzDept(_T(""))
	, m_gzDemo(_T(""))
	, m_isModify(false)
	, m_nPos(-1)
	, m_cwCheck(FALSE)
{
}

CAddArrearageDialog::~CAddArrearageDialog()
{
}

void CAddArrearageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Control(pDX, IDC_GZ_NAME, m_GuiGZName);
	DDX_Control(pDX, IDC_GZ_PHONE, m_GuiGZPhone);
	DDX_Control(pDX, IDC_GZ_DEPT, m_GuiGZDept);
	DDX_Control(pDX, IDC_GZ_DEMO, m_GuiGZDemo);
	DDX_Text(pDX, IDC_GZ_NAME, m_gzName);
	DDX_Text(pDX, IDC_GZ_PHONE, m_gzPhone);
	DDX_Text(pDX, IDC_GZ_DEPT, m_gzDept);
	DDX_Text(pDX, IDC_GZ_DEMO, m_gzDemo);
	DDX_Control(pDX, IDC_ADD_GZZH, m_GuiBtnAddArr);
	DDX_Control(pDX, IDC_GZ_LIST, m_GuiArrZHListCtrl);
	DDX_Control(pDX, IDC_DELZH_BTN, m_GuiDelZHBtn);
	DDX_Check(pDX, IDC_CHECK1, m_cwCheck);
}


BEGIN_MESSAGE_MAP(CAddArrearageDialog, CDialog)
	ON_BN_CLICKED(IDC_ADD_GZZH, OnBnClickedAddGzzh)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DELZH_BTN, OnBnClickedDelzhBtn)
	ON_EN_CHANGE(IDC_GZ_NAME, OnEnChangeGzName)
	ON_NOTIFY(NM_CLICK, IDC_GZ_LIST, OnNMClickGzList)
	ON_NOTIFY(NM_DBLCLK, IDC_GZ_LIST, OnNMDblclkGzList)
END_MESSAGE_MAP()


// CAddArrearageDialog 消息处理程序

BOOL CAddArrearageDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Init();

	m_GuiButtonCancel.ShowText();
	m_GuiBtnAddArr.ShowText();
	m_GuiDelZHBtn.ShowText();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddArrearageDialog::OnBnClickedAddGzzh()
{
	UpdateData(true);
	if ( m_isModify ){	//修改
		assert(m_nPos != -1);
		m_arrBdy.Modify(m_arrZHMap[m_nPos],
			hotelMIS::ReplaceChar(m_gzName).GetBuffer(),
			hotelMIS::ReplaceChar(m_gzPhone).GetBuffer(),
			hotelMIS::ReplaceChar(m_gzDept).GetBuffer(),
			hotelMIS::ReplaceChar(m_gzDemo).GetBuffer(),m_cwCheck);
		m_GuiBtnAddArr.SetWindowText(_T("确定"));
		m_GuiBtnAddArr.EnableWindow(false);
		AfxMessageBox(_T("修改资料成功!"));
		//清空
		m_gzName.Empty();
		m_gzPhone.Empty();
		m_gzDept.Empty();
		m_gzDemo.Empty();
		UpdateData(false);
		m_isModify = false;
		Refresh();
	}
	else{	//添加
		if ( m_arrBdy.Add(hotelMIS::ReplaceChar(m_gzName).GetBuffer(),
			hotelMIS::ReplaceChar(m_gzPhone).GetBuffer(),
			hotelMIS::ReplaceChar(m_gzDept).GetBuffer(),
			hotelMIS::ReplaceChar(m_gzDemo).GetBuffer(),m_cwCheck) ){
			AfxMessageBox(_T("此用户已经存在!请重新输入用户名!"));
			m_gzName.Empty();
			UpdateData(false);
		}else{
			m_gzName.Empty();
			m_gzPhone.Empty();
			m_gzDept.Empty();
			m_gzDemo.Empty();

			MessageBox(_T("添加成功!"),_T("提示"),MB_OK|MB_ICONINFORMATION);
			m_GuiBtnAddArr.EnableWindow(false);

			UpdateData(false);
			Refresh();
		}
		m_GuiGZName.SetFocus();
	}
}

void CAddArrearageDialog::Init()
{
	int i = 0;
	m_GuiBtnAddArr.EnableWindow(false);
	m_GuiDelZHBtn.EnableWindow(false);
	m_GuiArrZHListCtrl.InsertColumn(i,_T("序号"),LVCFMT_LEFT,40);
	m_GuiArrZHListCtrl.InsertColumn(++i,_T("挂账人"),LVCFMT_LEFT,100);
	m_GuiArrZHListCtrl.InsertColumn(++i,_T("电话"),LVCFMT_LEFT,70);
	m_GuiArrZHListCtrl.InsertColumn(++i,_T("单位"),LVCFMT_LEFT,120);
	m_GuiArrZHListCtrl.InsertColumn(++i,_T("财务计算"),LVCFMT_LEFT,60);
	m_GuiArrZHListCtrl.InsertColumn(++i,_T("备注"),LVCFMT_LEFT,80);
	ListView_SetExtendedListViewStyleEx(m_GuiArrZHListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	Refresh();
}

void CAddArrearageDialog::Refresh()
{
	hotelMIS::HArrerageZHVec vec = m_arrBdy.getAllZH();
	hotelMIS::HArrerageZHVec::iterator it;
	int i = 0;
	CString t;
	m_arrZHMap.clear();
	m_GuiArrZHListCtrl.DeleteAllItems();
	int pos = 0;
	int j;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		t.Format("%d",i+1);
		pos = m_GuiArrZHListCtrl.InsertItem(i,t);
		m_arrZHMap.insert(make_pair(pos,it->arid));
		m_GuiArrZHListCtrl.SetItemText(i,j++,it->guest_name.c_str());
		m_GuiArrZHListCtrl.SetItemText(i,j++,it->guest_phone.c_str());
		m_GuiArrZHListCtrl.SetItemText(i,j++,it->guest_dept.c_str());
		t.Format("%s",it->cw==0 ?"√":"×");
		m_GuiArrZHListCtrl.SetItemText(i,j++,t);
		m_GuiArrZHListCtrl.SetItemText(i,j++,it->ar_memo.c_str());
		i++;
	}

}

void CAddArrearageDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CAddArrearageDialog::OnBnClickedDelzhBtn()
{
	// TODO: 删除挂账账户,
	//m_arrBdy.Delete(m_arrZHMap);
	int nPos = -1;
	if (( nPos = m_GuiArrZHListCtrl.GetSelectionMark()) != -1 ) {
		TRACE("nPos = %d\n",nPos);
		
		int retVal = m_arrBdy.Delete(m_arrZHMap[nPos]);
		if ( retVal == 0){
			MessageBox(_T("账户正在使用"));
			return;
		}

		m_GuiDelZHBtn.EnableWindow(false);
		Refresh();
	}else{
		AfxMessageBox(_T("请先选中要删除的数据!"));
	}
}

void CAddArrearageDialog::OnEnChangeGzName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if ( !m_gzName.Trim().IsEmpty() ){
		m_GuiBtnAddArr.EnableWindow(true);
	}else{
		m_GuiBtnAddArr.EnableWindow(false);
	}
}

void CAddArrearageDialog::OnNMClickGzList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiArrZHListCtrl.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiArrZHListCtrl.HitTest(point)) != -1 ) {
		TRACE("双击命中%d \n",nPos);

		m_GuiDelZHBtn.EnableWindow(true);
	}

}

void CAddArrearageDialog::OnNMDblclkGzList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (( m_nPos = m_GuiArrZHListCtrl.GetSelectionMark()) != -1 ) {
		hotelMIS::HArrerageZH arrZH = m_arrBdy.getArrerageZH(m_arrZHMap[m_nPos]);
		m_gzName = arrZH.guest_name.c_str();
		m_gzPhone = arrZH.guest_phone.c_str();
		m_gzDept = arrZH.guest_dept.c_str();
		m_gzDemo = arrZH.ar_memo.c_str();
		m_cwCheck = arrZH.cw;
		UpdateData(false);
		m_GuiBtnAddArr.SetWindowText(_T("修改"));
		m_GuiBtnAddArr.EnableWindow(true);
		m_GuiDelZHBtn.EnableWindow(false);
		m_isModify = true;
	}
}

