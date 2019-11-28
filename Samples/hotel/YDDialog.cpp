// YDDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "YDDialog.h"
//#include ".\yddialog.h"
#include "HDestineCtrl.h"
#include "YDXXDialog.h"
#include "HRepastCtrl.h"
#include "HAccountCtrl.h"
#include "HRoomCtrl.h"
#include "HChgTableBdy.h"
#include "HRepastCtrl.h"
#include "HRepDetailsCtrl.h"
#include "HTableStatusCtrl.h"
#include "JCDialog.h"

// CYDDialog 对话框

IMPLEMENT_DYNAMIC(CYDDialog, CDialog)
CYDDialog::CYDDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CYDDialog::IDD, pParent)
{
	m_nPos = -1;
}

CYDDialog::~CYDDialog()
{
}

void CYDDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_LIST_YD, m_GuiListYd);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_GuiButtonAdd);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_GuiButtonDel);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Control(pDX, IDC_ROOMNO_COMBO, m_GuiRoomNoComBo);
	DDX_Control(pDX, IDC_TABLEID_COMBO, m_GuiTableIDComBo);
	DDX_Control(pDX, IDC_REPAST_BUTTON, m_GuiRepastBtn);
}


BEGIN_MESSAGE_MAP(CYDDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_YD, OnNMClickListYd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_YD, OnNMDblclkListYd)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_ROOMNO_COMBO, OnCbnSelchangeRoomnoCombo)
	ON_BN_CLICKED(IDC_REPAST_BUTTON, OnBnClickedRepastButton)
END_MESSAGE_MAP()


// CYDDialog 消息处理程序

void CYDDialog::OnBnClickedButtonAdd()
{
	// TODO: 修改
	if ( -1 != m_nPos){
		
		CYDXXDialog dlg(0,m_accountMap[m_nPos],true);
		dlg.DoModal();
		Refresh();
		m_GuiButtonDel.EnableWindow(false);
		m_GuiButtonAdd.EnableWindow(false);

	}else{
		MessageBox(_T("请先选中要操作的行!"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
}

void CYDDialog::OnBnClickedButtonDel()
{
	// TODO: 删除 
	if ( -1 != m_nPos){
		int result = MessageBox(_T("确定要删除预定吗!"),_T("系统提醒"),MB_ICONWARNING|MB_YESNO);
		if ( result == IDYES){
			int Id = m_accountMap[m_nPos];
			//1) 删除订餐表中的记录
			hotelMIS::HDestineCtrl destineCtrl(m_con.get_con());
			destineCtrl.Delete(Id);
			////2) 删除就餐表中的记录
			//hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
			//repastCtrl.Delete(accountId);
			////3) 删除账单表中的记录
			//hotelMIS::HAccountCtrl accountCtrl(m_con.get_con());
			//accountCtrl.Delete(accountId);
			//AfxMessageBox(_T("删除成功!"),MB_ICONINFORMATION|MB_OK);
			m_GuiButtonDel.EnableWindow(false);
			m_GuiButtonAdd.EnableWindow(false);
			Refresh();
		}
	}	
}

BOOL CYDDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonAdd.ShowText();
	m_GuiButtonDel.ShowText();
	m_GuiButtonCancel.ShowText();
	
	m_GuiButtonAdd.EnableWindow(false);
	m_GuiButtonDel.EnableWindow(false);
	m_GuiRepastBtn.EnableWindow(false);

	Init();

	InitRoomNoAndTalbeId();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CYDDialog::Init()
{
	int i = 0;
	m_GuiListYd.InsertColumn(i,_T("编号"),LVCFMT_LEFT,50);
	//m_GuiListYd.InsertColumn(++i,_T("账单号"),LVCFMT_LEFT,120);
	m_GuiListYd.InsertColumn(++i,_T("顾客姓名"),LVCFMT_LEFT,60);
	m_GuiListYd.InsertColumn(++i,_T("电话"),LVCFMT_LEFT,90);
	m_GuiListYd.InsertColumn(++i,_T("定餐日期"),LVCFMT_LEFT,70);
	m_GuiListYd.InsertColumn(++i,_T("定餐时间"),LVCFMT_LEFT,70);
	m_GuiListYd.InsertColumn(++i,_T("人数"),LVCFMT_LEFT,50);
	m_GuiListYd.InsertColumn(++i,_T("定金"),LVCFMT_RIGHT,60);
	m_GuiListYd.InsertColumn(++i,_T("备注"),LVCFMT_LEFT,90);
	ListView_SetExtendedListViewStyleEx(m_GuiListYd.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	Refresh();
}

void CYDDialog::InitRoomNoAndTalbeId()
{
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	hotelMIS::HRoomVector roomVec = roomCtrl.getAllRoom();
	hotelMIS::HRoomVector::iterator it;
	m_roomMap.clear();
	for ( it = roomVec.begin(); it != roomVec.end(); it++)
	{
		int pos = m_GuiRoomNoComBo.AddString(it->getName().c_str());
		m_roomMap.insert(make_pair(pos,it->getId()));
	}
	m_GuiRoomNoComBo.SetCurSel(-1);
}

void CYDDialog::Refresh()
{
	hotelMIS::HDestineCtrl destineCtrl(m_con.get_con());
	hotelMIS::HDestineVec vec = destineCtrl.getAllDestine();
	hotelMIS::HDestineVec::iterator it;
	int i = 0,j;
	CString cnt;
	m_accountMap.clear();
	m_GuiListYd.DeleteAllItems();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		m_accountMap.insert(make_pair(i,it->id));
		cnt.Format("%d",i+1);
		m_GuiListYd.InsertItem(i,cnt);
		//m_GuiListYd.SetItemText(i,j,it->account_id.c_str());
		m_GuiListYd.SetItemText(i,j,it->guest_name.c_str());	
		m_GuiListYd.SetItemText(i,++j,it->guest_phone.c_str());
		m_GuiListYd.SetItemText(i,++j,it->come_date.c_str());
		m_GuiListYd.SetItemText(i,++j,it->come_time.c_str());
		cnt.Format("%d",it->person_num);
		m_GuiListYd.SetItemText(i,++j,cnt);
		cnt.Format("%.2f",it->subscription);
		m_GuiListYd.SetItemText(i,++j,cnt);
		m_GuiListYd.SetItemText(i,++j,it->remark.c_str());
		i++;
	}
}
void CYDDialog::OnNMClickListYd(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListYd.ScreenToClient(&point);
	if (( m_nPos = m_GuiListYd.HitTest(point)) != -1 ) {
		TRACE("双击命中%d \n",m_accountMap[m_nPos]);
		/*hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		m_tableIdAndRoomId = repastCtrl.getTableIdAndRoomId(m_accountMap[m_nPos].c_str());*/
		m_GuiButtonDel.EnableWindow(true);
		m_GuiButtonAdd.EnableWindow(true);
	}

	*pResult = 0;
}

void CYDDialog::OnNMDblclkListYd(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListYd.ScreenToClient(&point);
	if (( m_nPos = m_GuiListYd.HitTest(point)) != -1 ) {
		OnBnClickedButtonAdd();
	}
	*pResult = 0;
}

void CYDDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CYDDialog::OnCbnSelchangeRoomnoCombo()
{
	// TODO: 根据当前选定的餐厅,将其可用的餐桌取出来
	//清空
	
	m_GuiTableIDComBo.ResetContent();

	int pos = m_GuiRoomNoComBo.GetCurSel();
	
	hotelMIS::HChgTableBdy tableBdy;

	hotelMIS::TableCol tableCol = tableBdy.getEmptyTable(m_roomMap[pos]);
	hotelMIS::TableCol::iterator it;
	CString tId;

	
	//int i = 0;
	m_mapTable.clear();
	for ( it = tableCol.begin(); it != tableCol.end(); it++)
	{
		tId.Format("%d",*it);
		pos = m_GuiTableIDComBo.AddString(tId);
		m_mapTable.insert(make_pair(pos,*it));
	}

	m_GuiTableIDComBo.SetCurSel(0);

	m_GuiRepastBtn.EnableWindow(true);
}
void CYDDialog::ChangeTableState(int tableId,int roomId)
{
	//设置图形状态
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
		hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
		int nState = repastCtrl.getRepastState(tableId,roomId);
		string tableName = tableStatusCtrl.getTableStateName(tableId,roomId);
		LV_ITEM lvi;
		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		lvi.iItem = tableId-1;
		CString szText;
		if ( 0 ==nState ) //空桌
			szText.Format("%d号-%s",tableId,tableName.c_str());
		else if ( 1 == nState)
			szText.Format("%d号-%s就餐",tableId,tableName.c_str());
		else if ( 2 == nState)
			szText.Format("%d号-%s预定",tableId,tableName.c_str());
				
		lvi.pszText = szText.GetBuffer(1);
		lvi.iSubItem=0;
		lvi.iImage =nState;
		m_ListCtrl->SetItem(&lvi);
		
		lvi.mask = LVIF_TEXT;
		lvi.iSubItem = 1;
		szText.Format("%.2f",repDeCtrl.getAllPrice(repastCtrl.getAccountId(tableId,roomId)));
		lvi.pszText = szText.GetBuffer();
		m_ListCtrl->SetItem(&lvi);
}

void CYDDialog::OnBnClickedRepastButton()
{
	// TODO: 
	if ( -1 != m_nPos)
	{
		int result = MessageBox(_T("确定要开始就餐?"),_T("系统提醒"),MB_ICONINFORMATION|MB_YESNO);
		if ( result == IDYES){
			//开始就餐
			ASSERT(m_GuiRoomNoComBo.GetCount() > 0 && m_GuiTableIDComBo> 0);

			int roomId = m_roomMap[m_GuiRoomNoComBo.GetCurSel()];
			int tableId = m_mapTable[m_GuiTableIDComBo.GetCurSel()];
			TRACE("你选择了 %d 号餐厅,%d号餐桌就餐!\n",roomId,tableId);
			hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
			hotelMIS::HDestineCtrl destineCtrl(m_con.get_con());
			int id = m_accountMap[m_nPos];
			hotelMIS::HDestine destine = destineCtrl.getDestine(id);
			if ( repastCtrl.getRepastState(tableId,roomId) == hotelMIS::HRepast::emptyState )
			{
				CJCDialog jcDlg(tableId,roomId,destine.subscription);
				/*jcDlg.m_roomId = roomId;
				jcDlg.m_tableId = tableId;
				jcDlg.m_subscription = destine.subscription;*/
				jcDlg.DoModal();
				ChangeTableState(tableId,roomId);
				if ( repastCtrl.getRepastState(tableId,roomId) == hotelMIS::HRepast::repastState){ 
					//如果是就餐状态则, 删除预定消息
					destineCtrl.Delete(id);
					Refresh();
					//m_ListCtrl->Invalidate();
					m_GuiRoomNoComBo.SetCurSel(-1);
					m_GuiTableIDComBo.SetCurSel(-1);
				}
			}

		}

	}
}
