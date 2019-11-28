// ArrearageDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ArrearageDialog.h"
#include <cassert>
using namespace std;

// CArrearageDialog 对话框

IMPLEMENT_DYNAMIC(CArrearageDialog, CDialog)
CArrearageDialog::CArrearageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CArrearageDialog::IDD, pParent)
	, m_arrDept(_T(""))
	, m_arrMoney(0)
{
}

CArrearageDialog::~CArrearageDialog()
{
}

void CArrearageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_LIST_ARR, m_GuiListCtrlArr);
	DDX_Control(pDX, IDC_EDIT_ARRDEPT, m_GuiEditArrDept);
	DDX_Control(pDX, IDC_EDIT_ARRMONEY, m_GuiEditArrMoney);
	DDX_Text(pDX, IDC_EDIT_ARRDEPT, m_arrDept);
	DDX_Text(pDX, IDC_EDIT_ARRMONEY, m_arrMoney);
	DDX_Control(pDX, IDC_ARR_GZ, m_GuiArrGZ);
	DDX_Control(pDX, IDCANCEL, m_GuiCancel);
}


BEGIN_MESSAGE_MAP(CArrearageDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARR, OnNMDblclkListArr)
	ON_BN_CLICKED(IDC_ARR_GZ, OnBnClickedArrGz)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CArrearageDialog 消息处理程序

void CArrearageDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CArrearageDialog::Init()
{
	int i = 0;
	m_GuiArrGZ.ShowText();
	m_GuiCancel.ShowText();
	m_GuiArrGZ.EnableWindow(false);
	
	m_GuiListCtrlArr.InsertColumn(i,_T("序号"),LVCFMT_LEFT,40);
	m_GuiListCtrlArr.InsertColumn(++i,_T("挂账人"),LVCFMT_LEFT,130);
	m_GuiListCtrlArr.InsertColumn(++i,_T("电话"),LVCFMT_LEFT,100);
	m_GuiListCtrlArr.InsertColumn(++i,_T("单位"),LVCFMT_LEFT,120);
	m_GuiListCtrlArr.InsertColumn(++i,_T("备注"),LVCFMT_LEFT,80);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlArr.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	Refresh();
}

void CArrearageDialog::Refresh()
{
	hotelMIS::HArrerageZHVec vec = m_arrBdy.getAllZH();
	hotelMIS::HArrerageZHVec::iterator it;
	int i = 0;
	CString t;
	m_arrZHMap.clear();
	m_GuiListCtrlArr.DeleteAllItems();
	int pos = 0;
	int j;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		t.Format("%d",i+1);
		pos = m_GuiListCtrlArr.InsertItem(i,t);
		m_arrZHMap.insert(make_pair(pos,it->arid));
		m_GuiListCtrlArr.SetItemText(i,j++,it->guest_name.c_str());
		m_GuiListCtrlArr.SetItemText(i,j++,it->guest_phone.c_str());
		m_GuiListCtrlArr.SetItemText(i,j++,it->guest_dept.c_str());
		m_GuiListCtrlArr.SetItemText(i,j++,it->ar_memo.c_str());
		i++;
	}
}

BOOL CArrearageDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CArrearageDialog::OnNMDblclkListArr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrlArr.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCtrlArr.HitTest(point)) != -1 ) {
		m_callback_arid = m_arrZHMap[nPos];
		m_arrDept=m_arrBdy.getArrerageZH(m_callback_arid).guest_dept.c_str();
		/*m_arrBdy.writeArrIdtoAccount(m_callback_arid,m_accountId);*/
		UpdateData(FALSE);
		m_GuiArrGZ.EnableWindow(true);
	}

}

void CArrearageDialog::OnBnClickedArrGz()
{
	// TODO: 在此添加控件通知处理程序代码
	int result = AfxMessageBox(_T("确定要挂账?"),MB_ICONINFORMATION|MB_YESNO);
	if ( result == IDYES){
		OnOK();
	}
}

HBRUSH CArrearageDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	 if (   pWnd->GetDlgCtrlID() == IDC_EDIT_ARRDEPT || pWnd->GetDlgCtrlID() ==IDC_EDIT_ARRMONEY){
		pDC->SetTextColor(RGB(255,0,0));
		
	}

	return hbr;
}
