// ArrPayDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ArrPayDialog.h"
#include "XFDetailsDlg.h"
#include ".\arrpaydialog.h"

// CArrPayDialog 对话框

IMPLEMENT_DYNAMIC(CArrPayDialog, CDialog)
CArrPayDialog::CArrPayDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CArrPayDialog::IDD, pParent)
	, m_ss(0)
	, m_ys(0)
	, m_zy(0)
	, m_jz_rest(0)
	, m_fp(FALSE)
	, m_arid(-1)
	,m_total(0.0f),
	m_onlyJzPos(-1)
{
}

CArrPayDialog::~CArrPayDialog()
{
}

void CArrPayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXLT, m_GuiGroupBoxLT);
	DDX_Control(pDX, IDC_GROUPBOXLB, m_GuiGroupBoxLB);
	DDX_Control(pDX, IDC_GROUPBOXR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_LIST_ARR, m_GuiListCtrlArr);
	DDX_Control(pDX, IDC_LIST_ARRXX, m_GuiListCtrlArrXX);
	DDX_Control(pDX, IDC_EDIT_SS, m_GuiEditSS);
	DDX_Control(pDX, IDC_EDIT_YS, m_GuiEditYS);
	DDX_Control(pDX, IDC_EDIT_ZY, m_GuiEditZY);
	DDX_Control(pDX, IDC_CHECK_FP, m_GuiButtonFP);
	DDX_Control(pDX, IDC_BUTTON_JZ, m_GuiButtonJZ);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiButtonPrint);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Text(pDX, IDC_EDIT_SS, m_ss);
	DDX_Text(pDX, IDC_EDIT_YS, m_ys);
	DDX_Text(pDX, IDC_EDIT_ZY, m_zy);
	DDX_Text(pDX, IDC_EDIT_JZ_REST,m_jz_rest);
	DDX_Check(pDX, IDC_CHECK_FP, m_fp);

}


BEGIN_MESSAGE_MAP(CArrPayDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT_SS, OnEnChangeEditSs)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ARR, OnNMClickListArr)
	ON_BN_CLICKED(IDC_BUTTON_JZ, OnBnClickedButtonJz)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARRXX, OnNMDblclkListArrxx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ARRXX, OnNMRclickListArrxx)
	ON_COMMAND(ID_ONLY_JZ, OnOnlyJz)
END_MESSAGE_MAP()


// CArrPayDialog 消息处理程序

void CArrPayDialog::OnEnChangeEditSs()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if ( m_onlyJzPos == -1){	
		m_zy = m_ss + m_jz_rest - m_total;
	}
	else{
		/*string arid = m_gzMap[m_onlyJzPos];
		m_ys = m_arrBdy.getPriceByAccountId(arid);*/
		m_zy = m_ss - m_ys;
	}

	
	UpdateData(FALSE);

}

void CArrPayDialog::OnNMClickListArr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 显示详细挂账金额及合计
	*pResult = 0;
	m_onlyJzPos = -1;

	m_ys = 0;
	m_ss=0;
	m_zy=0;
	UpdateData(false);

	Refresh2();
	m_GuiButtonJZ.EnableWindow(true);
}

void CArrPayDialog::OnBnClickedButtonJz()
{
	// TODO: 结账
	//1) 如果实收账款 够结一个账单的 就结一个账单，然后将剩余的暂存起来用于下一次的结账过程。
	//2) 如果实收账款 够全部的账单 将剩余的找还给客户
	//3) 如果实收账款不够结余一个账单的，不余处理。
	UpdateData(true);

	if ( m_ss <= 0){
		AfxMessageBox(_T("实收账款金额无效!"));
		m_GuiEditSS.SetFocus();
		return ;
	}

	SYSTEMTIME st;
	::GetLocalTime(&st);
	CString date,time;
	date.Format("%d-%d-%d",st.wYear,st.wMonth,st.wDay);
	time.Format("%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
	float oldSs=0.0f;

	if ( m_onlyJzPos == -1)
	{
		m_ss += m_arrBdy.getArrerageZHCtrl()->getJZRest(m_arid);
		oldSs = m_ss;
		bool bContinue = false;
		hotelMIS::HArrerageVec::iterator it;
		for ( it = m_gzList.begin(); it != m_gzList.end(); it++)
		{
			bContinue = m_arrBdy.getAccountCtrl()->gzJZ(it->account_id,&m_ss,m_fp,date.GetBuffer(),time.GetBuffer());
			if ( bContinue ){
				m_arrBdy.getArrerageCtrl()->DeleteByAccountId(it->account_id);
			}
			else{
				break;
			}
		}

		if ( oldSs == m_ss ){
			AfxMessageBox(_T("输入的金额至少要够结一次账单！"));
			m_GuiEditSS.SetFocus();
			return;
		}

		if ( bContinue == false ) // 结了一部分可能有剩余
		{
			assert(m_arid != -1);
			m_arrBdy.getArrerageZHCtrl()->setJZRest(m_arid,m_ss);
		}
		else{				//找余客户
			m_zy = m_ss;
			m_arrBdy.getArrerageZHCtrl()->setJZRest(m_arid,0);
		}
	}
	else
	{
		m_ss += m_arrBdy.getArrerageZHCtrl()->getJZRest(m_arid);
		
		bool bSucc = false;
		
			bSucc = m_arrBdy.getAccountCtrl()->gzJZ(m_gzMap[m_onlyJzPos],&m_ss,m_fp,date.GetBuffer(),time.GetBuffer());
			if ( bSucc ){
				m_arrBdy.getArrerageCtrl()->DeleteByAccountId(m_gzMap[m_onlyJzPos]);
				m_onlyJzPos = -1;
				m_ys=0;
				m_zy=0;
			}
			

		if ( m_ys > m_ss ){
			AfxMessageBox(_T("输入的金额至少要够结一次账单！"));
			m_GuiEditSS.SetFocus();
			return;
		}

		
	}
	m_GuiButtonJZ.EnableWindow(false);
	Refresh2();
	m_ss = oldSs;
	UpdateData(false);
	AfxMessageBox(_T("挂帐[结帐]操作成功!"));
}

void CArrPayDialog::OnBnClickedButtonPrint()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CArrPayDialog::Init()
{
	int i = 0;
	m_GuiListCtrlArr.InsertColumn(i,_T("序号"),LVCFMT_LEFT,40);
	m_GuiListCtrlArr.InsertColumn(++i,_T("挂账人"),LVCFMT_LEFT,100);
	m_GuiListCtrlArr.InsertColumn(++i,_T("电话"),LVCFMT_LEFT,70);
	m_GuiListCtrlArr.InsertColumn(++i,_T("单位"),LVCFMT_LEFT,120);
	m_GuiListCtrlArr.InsertColumn(++i,_T("备注"),LVCFMT_LEFT,80);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlArr.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	Refresh();

	i = 0;
	m_GuiListCtrlArrXX.InsertColumn(i,_T("账单号"),LVCFMT_LEFT,100);
	m_GuiListCtrlArrXX.InsertColumn(++i,_T("金额"),LVCFMT_LEFT,80);
	m_GuiListCtrlArrXX.InsertColumn(++i,_T("挂账日期"),LVCFMT_LEFT,120);
	m_GuiListCtrlArrXX.InsertColumn(++i,_T(""),LVCFMT_LEFT,80);

	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlArrXX.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_GuiButtonJZ.EnableWindow(false);
}

void CArrPayDialog::Refresh()
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

void CArrPayDialog::Refresh2()
{
	int nPos = -1;
	if (( nPos = m_GuiListCtrlArr.GetSelectionMark()) != -1 ){
		m_GuiListCtrlArrXX.DeleteAllItems();
		
		
		int arid = m_arid = m_arrZHMap[nPos];
		
		m_gzList.clear();
		m_gzMap.clear();
		m_gzList = m_arrBdy.getArrerageByArId(arid);
		hotelMIS::HArrerageVec::iterator it;
		
		if ( m_gzList.empty() ) return;
	
		string accountId;
		CString sPrice;
		m_total = 0.0f; //清空挂账合计重新计算
		int i = 0;
	
		for ( it = m_gzList.begin(); it!= m_gzList.end(); it++)
		{
			accountId = it->account_id.c_str();
			m_gzMap.insert(make_pair(i,accountId));
			m_GuiListCtrlArrXX.InsertItem(i,accountId.c_str());

			sPrice.Format("%.2f",m_arrBdy.getPriceByAccountId(accountId));
			m_total +=m_arrBdy.getPriceByAccountId(accountId);
			
			m_GuiListCtrlArrXX.SetItemText(i,1,sPrice);
			m_GuiListCtrlArrXX.SetItemText(i,2,it->ar_date.c_str());
			i++;
		}

		m_GuiListCtrlArrXX.InsertItem(i,_T("挂账合计:")); 
		sPrice.Format("%.2f",m_total);
		m_GuiListCtrlArrXX.SetItemText(i,1,sPrice);

		hotelMIS::HArrerageZH zh = m_arrBdy.getArrerageZH(arid);
				
		m_GuiListCtrlArrXX.InsertItem(i+1,_T("挂账人:"));
		m_GuiListCtrlArrXX.SetItemText(i+1,1,zh.guest_name.c_str());
		m_GuiListCtrlArrXX.InsertItem(i+2,_T("挂账单位:"));
		m_GuiListCtrlArrXX.SetItemText(i+2,1,zh.guest_dept.c_str());

		
		m_jz_rest = m_arrBdy.getArrerageZHCtrl()->getJZRest(arid);
		m_ys = m_total - m_jz_rest;
		
		
		UpdateData(false);
	
	}
}
BOOL CArrPayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CArrPayDialog::OnNMDblclkListArrxx(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int nPos = -1;
	if ( (nPos = m_GuiListCtrlArrXX.GetSelectionMark()) != -1  )
	{
		string accid = m_gzMap[nPos];
		CXFDetailsDlg dlg(this,accid.c_str());
		dlg.DoModal();
	}
}

//单笔结账
void CArrPayDialog::OnNMRclickListArrxx(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrlArrXX.ScreenToClient(&point);
	int nPos = m_GuiListCtrlArrXX.HitTest(point);
	if ( nPos != -1 ) {
		CMenu menu;
		CPoint pt = ::GetMessagePos();
		menu.LoadMenu(IDR_ONLY_JZ_POPUP_MENU);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);
	}

}

void CArrPayDialog::OnOnlyJz()
{
	//设置单笔结账标志位
	
	int nPos = m_GuiListCtrlArrXX.GetSelectionMark();
	if ( nPos !=-1){
		m_onlyJzPos = nPos;
		string arid = m_gzMap[m_onlyJzPos];
		m_ys = m_arrBdy.getPriceByAccountId(arid);
		UpdateData(FALSE);
	}
}
