// DiningRoomList.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "DiningRoomTab.h"
#include "YDDialog.h"
#include "YDXXDialog.h"
#include "PayDialog.h"
#include "ChangeTableDialog.h"
#include "EmployeeDialog.h"
#include "EmpManagerDialog.h"
#include "EmpSetJobDialog.h"
#include "MenuManagerDialog.h"
#include "SpecialMenuDialog.h"
#include "KindUnitSetDialog.h"
#include "ReportDayDialog.h"
#include "SysUserManagerDlg.h"
#include "SetpConfigDialog.h"
#include "RepertorySearchDialog.h"
#include "SearchAccountDlg.h"
#include "ArrearageDialog.h"
#include "AddArrearageDialog.h"
#include "ArrPayDialog.h"
#include "TableSetDialog.h"
#include "RegisterDialog.h"
#include "SetChuFangMenu.h"
#include "MainFrm.h"
#include "DetailsListView.h"
#include "InRepDlg.h"
#include "OutRepDlg.h"
#include "KProfile.h"
#include "HTableStatusCtrl.h"
#include "HTableStatusSetCtrl.h"
#include "HRepastCtrl.h"
#include "HRepDetailsCtrl.h"
#include "HRepast.h"
#include "HAccountCtrl.h"
#include "HRoomCtrl.h"
#include "MyCdkey.h"
#include "MemberInfoDlg.h"
#include "HAdmin.h"
#include "HOpType.h"
#include "HAdminBdy.h"
#include "ReportDetailsDlg.h"
#include "RepProdDetailsSearchDlg.h"
#include "RepTotalDlg.h"
#include "InOutRepSearchDlg.h"
#include "CancelMenuSearchDlg.h"
#include "MemZZListDlg.h"
#include "MemCZListDlg.h"
#include "MemXFSearchDlg.H"
#include "SyyReportDlg.h"

//#include "atlcomtime.h"
// CDiningRoomTab
//hotelMIS::KDBCon CDiningRoomTab::m_con;
int CDiningRoomTab::m_nPos =-1;

IMPLEMENT_DYNAMIC(CDiningRoomTab, CListCtrl)
CDiningRoomTab::CDiningRoomTab()
{
	m_pCon = m_con.get_con();
	m_lpMsg        = _T("");
	m_sFlag = 1;
}

CDiningRoomTab::~CDiningRoomTab()
{
}


BEGIN_MESSAGE_MAP(CDiningRoomTab, CListCtrl)
	ON_COMMAND(ID_VIEW_LARGER, OnViewLarger)
	ON_COMMAND(ID_REPAST, OnRepast)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY_REFLECT(NM_CLICK, OnNMClick)
	ON_MESSAGE(WM_ONREDRAW,OnReDraw)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnNMDblclk)
	ON_COMMAND(ID_DESTINE, OnDestine)
	ON_COMMAND(ID_DESTINE_MANAGE, OnDestineManage)
	ON_COMMAND(ID_ACCOUNT, OnAccount)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
	ON_COMMAND(ID_CHANGETABLE, OnChangetable)
	ON_COMMAND(ID_RE_INPUT, OnReInput)
	ON_COMMAND(ID_RE_OUTPUT, OnReOutput)
	ON_COMMAND(ID_RE_SEARCH, OnReSearch)
	ON_COMMAND(ID_EMP_ADD, OnEmpAdd)
	ON_COMMAND(ID_EMP_MANAGE, OnEmpManage)
	ON_COMMAND(ID_EMP_SEARCH, OnEmpSearch)
	ON_COMMAND(ID_EMP_SETJOB, OnEmpSetjob)
	ON_COMMAND(ID_MENU_MODIFY, OnMenuModify)
	//ON_COMMAND(ID_SNACK_MANAGE, OnSnackManage)
	ON_COMMAND(ID_FEATURE_MANAGE, OnFeatureManage)
	ON_COMMAND(ID_KIND_SET, OnKindSet)
	ON_COMMAND(ID_DAY_REPORT, OnDayReport)
	ON_COMMAND(ID_SYSUSER_SET, OnSysuserSet)
	ON_COMMAND(ID_SYSPARA_SET, OnSysparaSet)
	ON_COMMAND(ID_OTHER_CALC, OnOtherCalc)
	ON_COMMAND(ID_OTHER_NOTEPAD, OnOtherNotepad)
	ON_COMMAND(ID_OTHER_PAINT, OnOtherPaint)
	ON_COMMAND(ID_SEARCH_ACCOUNTS, OnSearchAccounts)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_LESSON, OnLesson)
	ON_COMMAND(ID_ARREARAGE, OnArrearage)
	ON_COMMAND(ID_ARREARAGE_MANAGE, OnArrearageManage)
	ON_COMMAND(ID_ARREARAGE_GZJZ, OnArrearageGzjz)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_COMMAND(ID_VIEW_SMALL, OnViewSmall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGER, OnUpdateViewLarger)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALL, OnUpdateViewSmall)
//	ON_WM_TIMER()

	ON_WM_MOUSEMOVE()

	ON_NOTIFY_REFLECT(NM_HOVER, OnNMHover)
//	ON_NOTIFY_REFLECT(LVN_HOTTRACK, OnLvnHotTrack)
ON_COMMAND(ID_POPUP_SET_TABLE, OnPopupSetTable)
ON_COMMAND(ID_REGISTER_MENU, OnRegisterMenu)

ON_COMMAND(ID_POPUP_PRINT, OnPopupPrint)
ON_COMMAND(ID_RECALLTABLE, OnRecalltable)
ON_COMMAND(ID_FENGCHU_PRINT, OnFengchuPrint)
ON_COMMAND(ID_2003, On2003)
ON_COMMAND(ID_XP, OnXp)
ON_COMMAND(ID_MEMBER_MANAGE, OnMemberManage)
//ON_COMMAND(ID_MEMBER_BIRTH, OnMemberBirth)
ON_COMMAND(ID_MEMBER_CASTSEARCH, OnMemberCastsearch)
ON_COMMAND(ID_MEMBER_CZ, OnMemberCz)
ON_COMMAND(ID_MEMBER_ZZ, OnMemberZz)
ON_COMMAND(ID_REPORT_DETAILS, OnReportDetails)
ON_COMMAND(ID_REP_DETAILS_SEARCH, OnRepDetailsSearch)
ON_COMMAND(ID_REP_KIND_SET, OnRepKindSet)
ON_COMMAND(ID_REP_P_MANAG, OnRepPManag)
ON_COMMAND(ID_REP_TOTAL_SEARCH, OnRepTotalSearch)
ON_COMMAND(ID_APP_EXIT, OnAppExit)
ON_COMMAND(ID_INOUT_ZD_SEARCH, OnInoutZdSearch)
ON_COMMAND(ID_CANCEL_MENU_SEARCH, OnCancelMenuSearch)
ON_COMMAND(ID_SKY_MENU, OnSkyMenu)
END_MESSAGE_MAP()



// CDiningRoomTab 消息处理程序
LRESULT CDiningRoomTab::OnReDraw(WPARAM wParam,LPARAM lParam)
{
	Invalidate();
	return 0;
}

void CDiningRoomTab::OnViewLarger()
{
	// TODO: 大图形方式显示
	ModifyStyle(LVS_TYPEMASK,LVS_ICON);
}

void CDiningRoomTab::OnViewList()
{
	// TODO: 列表方式
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
}

void CDiningRoomTab::OnViewSmall()
{
	// TODO: 小图形方式
	ModifyStyle(LVS_TYPEMASK,LVS_SMALLICON);
}
void CDiningRoomTab::OnUpdateViewList(CCmdUI *pCmdUI)
{
	DWORD dwCurrStyle = GetStyle()&LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrStyle == LVS_REPORT);
}

void CDiningRoomTab::OnUpdateViewLarger(CCmdUI *pCmdUI)
{

	DWORD dwCurrStyle = GetStyle()&LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrStyle == LVS_ICON);
}

void CDiningRoomTab::OnUpdateViewSmall(CCmdUI *pCmdUI)
{
	DWORD dwCurrStyle = GetStyle()&LVS_TYPEMASK;

	pCmdUI->SetRadio(dwCurrStyle == LVS_SMALLICON/*LVS_LIST*/);
}


BOOL CDiningRoomTab::CreateRoom(int roomNo,DWORD dwStyle,const RECT &rect, CWnd *pParentWnd,UINT nID)
{
	this->m_roomId = roomNo;
	return Create(dwStyle,rect,pParentWnd,nID);
}

void CDiningRoomTab::ChangeTableState(int tableId)
{
	//设置图形状态
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
		hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
		hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());

		int nState = repastCtrl.getRepastState(tableId,m_roomId); //就餐状态
		
		string tableName = tableStatusCtrl.getTableName(tableId,m_roomId);
		int tableStatus = tableStatusCtrl.getTableStatus(tableId,m_roomId); //餐桌类型id
		
		LV_ITEM lvi;
		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		lvi.iItem = tableId-1;
		CString szText;

		if ( hotelMIS::HRepast::emptyState ==nState ){ //空桌
			if ( !tableName.empty())
				szText.Format("%d号【%s】",tableId,tableName.c_str());
			else
				szText.Format("%d号",tableId);
			lvi.iImage =tableStatusSetCtrl.getTableEmptyBmp(tableStatus);
		}
		else if ( hotelMIS::HRepast::repastState == nState){
			if ( !tableName.empty())
				szText.Format("%d号【%s】就餐中",tableId,tableName.c_str());
			else
				szText.Format("%d号就餐中",tableId);
			lvi.iImage =tableStatusSetCtrl.getTableRepastBmp(tableStatus);
		}
		
		lvi.pszText = szText.GetBuffer(1);
		lvi.iSubItem=0;
		SetItem(&lvi);
		
		lvi.mask = LVIF_TEXT;
		lvi.iSubItem = 1;
		szText.Format("%.2f",repDeCtrl.getAllPrice(repastCtrl.getAccountId(tableId,m_roomId)));
		lvi.pszText = szText.GetBuffer();
		SetItem(&lvi);
	
}

void CDiningRoomTab::OnRepast()
{
	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM0() ){ return; }

	
	if (  -1 != m_nPos ) {
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		int status = repastCtrl.getRepastState(m_tableId,m_roomId);
		if ( status == hotelMIS::HRepast::emptyState || status == hotelMIS::HRepast::repastState)
		{
				
			m_tableId = m_tableInfoMap[m_nPos].getTable_id();
#ifdef _DEBUG
			CString str = GetItemText(m_nPos,0);
			TRACE("就餐: 命中%s,餐桌号=%d,餐厅号 =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);
#endif
			CJCDialog m_jcDlg;
			m_jcDlg.m_roomId = m_roomId;
			m_jcDlg.m_tableId = m_tableId;
			m_jcDlg.DoModal();
			ChangeTableState(m_tableId);

		}

		RefreshDownList(); //刷新下边的列表
	}
	else{
		MessageBox(_T("请先选择您要操作的餐桌!"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
	
}


void CDiningRoomTab::Init()
{
	/*hotelMIS::KProfile profile("set.ini");
	string flag =  profile.GetProfile("REFRESH","rflag");
	string second = profile.GetProfile("REFRESH","second");
	int nSec = atoi(second.c_str());
	if ( flag == "true")
		SetTimer(1,nSec*1000,NULL);*/
		
	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,"res/table.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Attach(hbitmap);

	m_ImageList.Create(64, 64, TRUE | ILC_COLOR24, 4, 0); 
	m_ImageList.Add(&m_bitmap,RGB(255,255,255));
	
	HBITMAP hbitmap2 = (HBITMAP)LoadImage(NULL,"res/bitmap2.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap2.Attach(hbitmap2);
	m_ImageSmall.Create(16,16,TRUE|ILC_COLOR24,16,0);
	m_ImageSmall.Add(&m_bitmap2,RGB(255,255,255));

	SetImageList(&m_ImageList,LVSIL_NORMAL);
	SetImageList(&m_ImageSmall,LVSIL_SMALL);
	ModifyStyle(LVS_TYPEMASK,LVS_ICON);
	// TODO:  在此添加您专用的创建代码
	InsertColumn(0,_T("餐桌号"), LVCFMT_LEFT,200);
	InsertColumn(1,_T("消费金额"),LVCFMT_LEFT,120);
	
	Refresh();
}

void CDiningRoomTab::Refresh()
{
	//初始化餐桌

	hotelMIS::HTableStatusCtrl tableStatusCtrl(m_pCon);
	hotelMIS::HTableInfoVec vec = tableStatusCtrl.getAllTableInfo(m_roomId);
	hotelMIS::HTableInfoVec::iterator it;
	hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_pCon);
	CString szText;
	int i = 0;
	LV_ITEM lvi;
	DeleteAllItems();
	int nState;
	string tableName ;
	int tableStatus;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		tableName = tableStatusCtrl.getTableName(it->table_id,m_roomId);
		m_tableInfoMap.insert(make_pair(i,(*it)));
		lvi.iItem = i+1;
		lvi.iSubItem = 0;
		
		nState = it->re_state;
		tableStatus = tableStatusCtrl.getTableStatus(it->table_id,m_roomId); //餐桌类型id
		
		if ( hotelMIS::HRepast::emptyState ==  nState){ //空桌
			if ( !tableName.empty())
				szText.Format("%d号【%s】",it->table_id,tableName.c_str());
			else
				szText.Format("%d号",it->table_id);
			
			ASSERT(tableStatusSetCtrl.getTableEmptyBmp(tableStatus) != -1);;
			
			lvi.iImage =tableStatusSetCtrl.getTableEmptyBmp(tableStatus);
		}
		else if ( hotelMIS::HRepast::repastState == nState){
			if ( !tableName.empty())
				szText.Format("%d号【%s】就餐中",it->table_id,tableName.c_str());
			else
				szText.Format("%d号就餐中",it->table_id);
			
			ASSERT(tableStatusSetCtrl.getTableRepastBmp(tableStatus) != -1);
			
			lvi.iImage =tableStatusSetCtrl.getTableRepastBmp(tableStatus);
		}
		lvi.pszText = szText.GetBuffer();	//根据当前就餐状态设置不同文字
		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		InsertItem(&lvi);
		ChangeTableState(it->table_id);
		i++;
	}
}

int CDiningRoomTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Init();
	SetTimer(1,1000,NULL);
	return 0;
}

void CDiningRoomTab::OnShowWindow(BOOL bShow, UINT nStatus)
{
	//CListCtrl::OnShowWindow(bShow, nStatus);
	// TODO: 在此处添加消息处理程序代码
	TRACE("OnShowWindow当前餐厅%d\n",m_roomId);
	m_nPos = -1;
	this->GetParent()->GetParent()->PostMessage(WM_GETROOMNO,(WPARAM)m_roomId);
	
}

void CDiningRoomTab::RefreshDownList()
{
	CMainFrame* MainFrame1=(CMainFrame*)AfxGetMainWnd();//this->GetParent()->GetParent()->GetParent()->GetParent(); 
		CDetailsListView* pListView=(CDetailsListView*)MainFrame1->GetSplitterWnd2().GetPane(1,0);	
		pListView->PostMessage(WM_GETTABLEINFO,(WPARAM)m_roomId,(LPARAM)m_tableId);
}

void CDiningRoomTab::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 单击选中
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	ScreenToClient(&point);
	
	if (( m_nPos = HitTest(point)) != -1 ) {
		CString str = GetItemText(m_nPos,0);	
		m_tableId = m_tableInfoMap[m_nPos].getTable_id();
		TRACE("单击命中%s,餐桌号=%d,餐厅号 =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);	
		//发送消息到 下方的 CDetailsListView中提取当前餐桌的菜单
		
		//this->GetParent()->GetParent()->PostMessage(WM_GETTABLEINFO,(WPARAM)m_roomId,(LPARAM)m_tableId);
			//
		RefreshDownList();
	}
	*pResult = 0;
}

void CDiningRoomTab::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 双击打开
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	ScreenToClient(&point);
	
	if (( m_nPos = HitTest(point)) != -1 ) {
		CString str = GetItemText(m_nPos,0);	
		m_tableId = m_tableInfoMap[m_nPos].getTable_id();
		TRACE("单击命中%s,餐桌号=%d,餐厅号 =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);
		OnRepast();
	}
	*pResult = 0;
}

void CDiningRoomTab::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM0() ){ return; }

	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	ScreenToClient(&point);
	
	if (( m_nPos = HitTest(point)) != -1 ) {
		CString str = GetItemText(m_nPos,0);	
		m_tableId = m_tableInfoMap[m_nPos].getTable_id();
		TRACE("单击命中%s,餐桌号=%d,餐厅号 =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);
		CMenu menu;
		CPoint pt = ::GetMessagePos();
		menu.LoadMenu(IDR_POPUP_DRTAB);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);

		RefreshDownList();
	}
	*pResult = 0;
}

void CDiningRoomTab::SetToolTip(LPCTSTR lpMsg)
{
	CRect rc;
	m_lpMsg = lpMsg;
	if (GetSafeHwnd()== NULL)
		return;
	
	if (m_lpMsg != NULL)
	{
		if (m_ToolTipCtrl.GetSafeHwnd() == NULL) 
		{
			m_ToolTipCtrl.Create(this, TTS_ALWAYSTIP);
			//m_ToolTipCtrl.Activate(TRUE);
			m_ToolTipCtrl.AddTool(this, lpMsg);
			m_ToolTipCtrl.SetTitle(1,_T("提醒"));
			//m_ToolTipCtrl.UpdateTipText(lpMsg, this);
		}
		else
		{
			m_ToolTipCtrl.UpdateTipText(lpMsg, this);	
		}
		m_ToolTipCtrl.Activate(TRUE);
	}
	else
	{
		if (m_ToolTipCtrl.GetSafeHwnd() == NULL) 
		{
			m_ToolTipCtrl.Create(this, TTS_ALWAYSTIP);
			m_ToolTipCtrl.AddTool(this, _T(""));
			//m_ToolTipCtrl.AddTool(this, lpMsg);
			m_ToolTipCtrl.SetTitle(1,_T("提醒"));
			//m_ToolTipCtrl.UpdateTipText(_T(""), this);
						
		}
		else
		{
			m_ToolTipCtrl.UpdateTipText(_T(""), this);/*m_ToolTipCtrl.UpdateTipText(lpMsg, this);*/
		}
		
		m_ToolTipCtrl.Activate(FALSE);
	}
}


//以下为Menu映射操作

void CDiningRoomTab::OnDestine()
{
	
	CYDXXDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnDestineManage()
{
	// TODO: 预定餐管理
	CYDDialog dlg;
	dlg.m_ListCtrl = this;
	dlg.DoModal();
}

void CDiningRoomTab::OnAccount()
{
	
	// TODO: 结账

	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM0() ){ return; }

	if ( this->GetSelectionMark() != -1 ){
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		int status = repastCtrl.getRepastState(m_tableId,m_roomId);
		if (  status == hotelMIS::HRepast::repastState )
		{
			CPayDialog dlg(this,m_tableId,m_roomId);
			dlg.m_pRoomTab = this;
			dlg.DoModal();
			ChangeTableState(m_tableId);
			
		}
	}else{
		MessageBox(_T("请先选择您要『结账』的餐桌!"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::OnChangetable()
{
	// TODO: 在此添加命令处理程序代码
	if ( this->GetSelectionMark() != -1){
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		int status = repastCtrl.getRepastState(m_tableId,m_roomId);
		if (  status == hotelMIS::HRepast::repastState || status == hotelMIS::HRepast::destineState )
		{
			CChangeTableDialog dlg(this,m_tableId,m_roomId);
			dlg.DoModal();
			ChangeTableState(m_tableId);
			ChangeTableState(dlg.getDestTable());
		}
		RefreshDownList(); //刷新下边的列表
	}else{
		MessageBox(_T("请先选择您要『换桌』的餐桌!"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::OnReInput()
{
	// TODO: 入库登记
	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM1() ){ return; }

	CInRepDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnReOutput()
{
	
	// TODO: 入库登记
	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM1() ){ return; }
	COutRegDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnReSearch()
{
	// TODO: 库存查询
	CRepertorySearchDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnSearchAccounts()
{
	// TODO: 账单查询
	CSearchAccountDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpAdd()
{
	// TODO: 添加新员工
	CEmployeeDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpManage()
{
	// TODO: 员工管理
	CEmpManagerDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpSearch()
{
	// TODO: 员工查询
	CEmpManagerDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpSetjob()
{
	// TODO: 在此添加命令处理程序代码
	CEmpSetJobDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnMenuModify()
{
	// TODO: 菜谱维护
	CMenuManagerDialog dlg;
	dlg.DoModal();
}


void CDiningRoomTab::OnFeatureManage()
{
	// TODO: 特色菜谱管理
	CSpecialMenuDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnKindSet()
{
	// TODO: 单位设置
	CKindUnitSetDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnDayReport()
{
	// TODO: 收银员报表*********************************************
	
	CReportDayDialog dlg;
	dlg.DoModal();
}


void CDiningRoomTab::OnSysuserSet()
{
	// TODO: 系统用户设置
	CSysUserManagerDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnSysparaSet()
{
	// TODO: 系统参数设置*********************************************
	
	CSetpConfigDialog dlg(_T("系统设置"),this);
	
	dlg.DoModal();
}

void CDiningRoomTab::OnOtherCalc()
{
	// TODO: 调用计算器
	hotelMIS::KProfile profile("set.ini");
	CString Path = profile.GetProfile("OTHER_APP","app1").c_str();
	WinExec(Path,SW_NORMAL);
}

void CDiningRoomTab::OnOtherNotepad()
{
	// TODO: 调用记事本
	hotelMIS::KProfile profile("set.ini");
	CString Path = profile.GetProfile("OTHER_APP","app2").c_str();
	WinExec(Path,SW_NORMAL);

}

void CDiningRoomTab::OnOtherPaint()
{
	// TODO: 调用图画
	hotelMIS::KProfile profile("set.ini");
	CString Path = profile.GetProfile("OTHER_APP","app3").c_str();
	WinExec(Path,SW_NORMAL);
}



void CDiningRoomTab::OnRefresh()
{
	// TODO: 在此添加命令处理程序代码
	Refresh();
}


void CDiningRoomTab::OnLesson()
{
	//hotelMIS::KProfile profile("set.ini");
	//CString Path = profile.GetProfile("SELF_IE","path").c_str();
	////WinExec(Path,SW_NORMAL);
	////ShellExecute(NULL,_T("open"),Path,NULL,NULL,SW_SHOWNORMAL);
	//WinExec(Path,SW_SHOWMAXIMIZED);
}

void CDiningRoomTab::OnArrearage()
{
	// TODO: 挂账
	MyCdKey cdkey;
	if ( !cdkey.RegisterCdKey() ){
		CRegisterDialog dlg;
		dlg.DoModal();
	}

	if ( -1 != m_nPos )
	{
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		if ( repastCtrl.getRepastState(m_tableId,m_roomId) == hotelMIS::HRepast::repastState ) //必须为就餐状态
		{
			//1) 将挂账金额挂账账户中。
			CArrearageDialog dlg;
			hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
			HTotalPair t =repDeCtrl.getAllPrice(repastCtrl.getAccountId(m_tableId,m_roomId));
			dlg.m_arrMoney = t.first + t.second;
			if ( dlg.DoModal() == IDOK){ //挂账
				//1) 得到了 arid, accoundId
				//TRACE("arid = %d,accountid=%s\n,",dlg.m_callback_arid,repastCtrl.getAccountId(m_tableId,m_roomId).c_str());
				//2) 将挂账账号和账单号写入挂账数据库
				hotelMIS::HArrerageBdy arrBdy;
				string accId = repastCtrl.getAccountId(m_tableId,m_roomId);
				arrBdy.gz(dlg.m_callback_arid,accId);
				//3) 将数据从就餐表中导入到历史记录表中
				arrBdy.tranToAcc(m_tableId,m_roomId,accId,dlg.m_arrMoney);
				//4) 更新餐桌面
				ChangeTableState(m_tableId);
				//_CrtDumpMemoryLeaks();
			}
		}
		
	}
	else
	{
		MessageBox(_T("请先选中要操作的餐桌!"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::RepastToAccount()
{
   
}

void CDiningRoomTab::OnArrearageManage()
{
	// TODO:挂账账户管理
	CAddArrearageDialog dlg;
	dlg.DoModal();
	
	//MessageBox(_T("演示版本没有此功能!请购买正版软件!\n大连总部:0411-84799689\n内蒙大区:0471-6350482"),_T("提醒"),MB_ICONINFORMATION|MB_OK);

}

void CDiningRoomTab::OnArrearageGzjz()
{
	// TODO: 挂账结账
	CArrPayDialog dlg;
	dlg.DoModal();
}


BOOL CDiningRoomTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE && m_sFlag/*|| pMsg->message == WM_MOUSEHOVER*/)
	{
		if (m_ToolTipCtrl.GetSafeHwnd())
			m_ToolTipCtrl.RelayEvent(pMsg);
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CDiningRoomTab::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	 CWinApp* pApp = AfxGetApp();
	 m_sFlag = pApp->GetProfileInt("Settings", "AutoRefresh",0);
	 if ( 1 == m_sFlag){
		TRACKMOUSEEVENT tme;
		tme.cbSize=sizeof(tme);
		tme.dwFlags=TME_HOVER; //调用者想要执行的操作
		tme.hwndTrack=m_hWnd;    //窗口句柄
		tme.dwHoverTime=HOVER_DEFAULT;//光标等待时间,然后发送WM_MOUSEHOVER
		::TrackMouseEvent(&tme);
	 }
	CListCtrl::OnMouseMove(nFlags, point);
}

void CDiningRoomTab::OnNMHover(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	if ( 1 == m_sFlag){
		DWORD dwPos = ::GetMessagePos();
		CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		ScreenToClient(&point);

		if (( m_nPos = HitTest(point)) != -1 ) {
			TRACKMOUSEEVENT tme;
			tme.cbSize=sizeof(tme);
			tme.dwFlags=TME_HOVER; //调用者想要执行的操作
			tme.hwndTrack=m_hWnd;    //窗口句柄
			tme.dwHoverTime=HOVER_DEFAULT;//光标等待时间,然后发送WM_MOUSEHOVER
			::TrackMouseEvent(&tme);

			CTime t1=CTime::GetCurrentTime();

			CString str;
			str.Format("结止到 %d:%.2d:%.2d  顾客共消费 %s 元！",t1.GetHour(),t1.GetMinute(),t1.GetSecond(),GetItemText(m_nPos,1));

			SetToolTip(str);
		}else{
			SetToolTip(NULL);
		}
	}
}

void CDiningRoomTab::OnPopupSetTable()
{
	// TODO: 设置餐桌状态
	if ( this->GetSelectionMark() != -1 ){
		CTableSetDialog dlg(this,m_tableId,m_roomId);
		if ( dlg.DoModal() == IDOK){
			ChangeTableState(m_tableId);
		}
	}
}	

void CDiningRoomTab::OnRegisterMenu()
{
	// TODO: 注册
	MyCdKey cdkey;
	if ( cdkey.RegisterCdKey() ){
		MessageBox(_T("已经是授权用户,不需要在注册!"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
	}
	else
	{
		CRegisterDialog dlg;
		dlg.DoModal();
	}
}


void CDiningRoomTab::OnPopupPrint()
{
	// TODO: 打印
	if ( this->GetSelectionMark() != -1 ){
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		int status = repastCtrl.getRepastState(m_tableId,m_roomId);
		if (  status == hotelMIS::HRepast::repastState )
		{
			CPrintDialog dlg(false);
			CDC dc;
			if ( dlg.DoModal()== IDOK)
			{
				dc.Attach(dlg.GetPrinterDC());

				DOCINFO di;
				::ZeroMemory(&di,sizeof(DOCINFO));
				di.cbSize = sizeof(DOCINFO);
				di.lpszDocName= _T("消费账单");

				dc.StartDoc(&di);
				dc.StartPage();
				PrintReport(&dc);
				dc.EndPage();
				dc.EndDoc();

			}

		}
	}else{
			MessageBox(_T("请先选择您要『打印』的餐桌!"),_T("系统提醒"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::PrintReport(CDC *dc)
{
	
	hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	hotelMIS::HRepDetailsVec vec = repDetailsCtrl.getAllDetails(accountId);
	hotelMIS::HRepDetailsVec::iterator it;
	
	//hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	//hotelMIS::HotelMsg hotelMsg = s.getHotelMsg();

	dc->SetMapMode(MM_LOMETRIC); //设置为厘米单位
	dc->SetTextAlign(TA_LEFT);
	
	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("宋体"));
	dc->SetTextColor(RGB(0,0,0));
	pOldFont = dc->SelectObject(&font);

	int xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",30);
	int yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	yPos = -yPos;
	int col_2_w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	int col_3_w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	int col_4_w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	int lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	
	CString acc;
	CTime t1=CTime::GetCurrentTime();
	
	TEXTMETRIC lpMetrics;
	
	dc->GetTextMetrics(&lpMetrics);
	int fHeight = lpMetrics.tmHeight + lineHeight;
	HRoomCtrl hRoomCtrl(m_con.get_con());
hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
	string tableName = tableStatusCtrl.getTableName(m_tableId,m_roomId);

	if( !tableName.empty())
		acc.Format("%s-%d号桌[%s]",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId,tableName.c_str());
	else
		acc.Format("%s-%d号桌",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId);

	//acc.Format("%s,%d号餐桌",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId);
	dc->TextOut(xPos,yPos,acc);
	dc->TextOut(xPos,yPos-fHeight,_T("--------------消费小票----------------"));
	acc.Format("账单号: %s ",accountId.c_str());
	dc->TextOut(xPos,yPos-fHeight*2,acc);
	acc.Format("日期: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*3,acc);
	dc->TextOut(xPos,yPos-fHeight*4,_T("菜名"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*4,_T("单价"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*4,_T("数量"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*4,_T("总价"));
		
	CString cnt;
	int n = 5;
	int len = 0;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//菜名

		cnt.Format("%.2f",it->food_price);
		
		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;
		
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//单价
		cnt.Format("%d",it->food_num);
		//dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//数量
		cnt.Format("%.2f",it->food_price*it->food_num);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //总价
		
        n++;
	}
	
	HTotalPair t=  repDetailsCtrl.getAllPrice(accountId);
	float ys = t.first + t.second;
	cnt.Format("%.2f",ys);	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("合计:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	//n++;	
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));
	//
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("实际收款:"));
	//UpdateData(false);
	//cnt.Format("%.2f",atof(m_sj));
	//dc->SetTextAlign(TA_RIGHT);
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//
	//if ( atof(m_zk) > 0){
	//	n++;
	//	dc->SetTextAlign(TA_LEFT);
	//	dc->TextOut(xPos,yPos - fHeight*n,_T("折扣状况:"));
	//	cnt.Format("%.1f折",atof(m_zk));
	//	dc->SetTextAlign(TA_RIGHT);
	//	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//}
	//
	//n++;
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("应收账款:"));
	//cnt.Format("%.2f",m_ss);
	//dc->SetTextAlign(TA_RIGHT);
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//
	//n++;
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("找余顾客:"));
	//cnt.Format("%.2f",m_zy);
	//dc->SetTextAlign(TA_RIGHT);
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//
	//
	//n++;
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));

	//if ( ! hotelMsg.hoteltel.empty() ){
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("订餐电话:"));
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel.c_str());
	//}
	//if ( ! hotelMsg.hoteltel2.empty() && ! hotelMsg.hoteltel.empty()){
	//n++;
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel2.c_str());
	//}
	//if ( !hotelMsg.hotelhttp.empty()){
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("餐厅网址:"));
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hotelhttp.c_str());
	//}
	//n++;
	//dc->TextOut(xPos,yPos -fHeight*n,_T("---------------------------------------"));
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("技术支持: 西部数字网"));
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("HTTP://WWW.IDCWEST.NET"));
	////print space line
	n = n+7;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);
}
void CDiningRoomTab::OnRecalltable()
{
	// TODO: 取消正在就餐的餐桌
	if ( this->GetSelectionMark() != -1 ){
		
		int result = MessageBox(_T("确实要取消当前的就餐?"),_T("警告"),MB_ICONWARNING|MB_YESNO);
		if ( result == IDYES){
			hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
			string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);

			hotelMIS::HAccountCtrl accountCtrl(m_con.get_con());
			accountCtrl.cancel(accountId);
			ChangeTableState(m_tableId);
		}
	}

}

void CDiningRoomTab::OnFengchuPrint()
{
	// TODO: 分厨菜谱打印设置
	CSetChuFangMenu dlg;
	dlg.DoModal();
}

void CDiningRoomTab::On2003()
{
	// TODO: 在此添加命令处理程序代码
	/*CMainFrame* MainFrame=(CMainFrame*)AfxGetMainWnd();
	MainFrame->SendMessage(WM_COMMAND,ID_2003);*/
	
	//死循环
}

void CDiningRoomTab::OnXp()
{
	// TODO: 在此添加命令处理程序代码
}

void CDiningRoomTab::OnMemberManage()
{
	// TODO: 会员管理
	CMemberInfoDlg dlg;
	dlg.DoModal();
}

//void CDiningRoomTab::OnMemberBirth()
//{
//	// TODO: 生日查询
//	MessageBox(_T("非常报歉,本功能正在开发当中!"));
//}

void CDiningRoomTab::OnMemberCastsearch()
{
	// TODO: 消费查询
	CMemXFSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnMemberCz()
{
	// TODO: 充值查询
	CMemCZListDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnMemberZz()
{
	// TODO: 转账查询
	CMemZZListDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnReportDetails()
{
	// 经营详细表
	CReportDetailsDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnRepDetailsSearch()
{
	// 库存商品明细查询
	CRepProdDetailsSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnRepKindSet()
{
	// 库存商品类别管理
	CKindUnitSetDialog dlg(TRUE);
	dlg.DoModal();
}

void CDiningRoomTab::OnRepPManag()
{
	//  库存商品维护
	CMenuManagerDialog dlg(TRUE);
	dlg.DoModal();
}

void CDiningRoomTab::OnRepTotalSearch()
{
	// 汇总查询
	CRepTotalDlg dlg;
	dlg.DoModal();
}


void CDiningRoomTab::OnAppExit()
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

void CDiningRoomTab::OnInoutZdSearch()
{
	//账单查询 
	CInOutRepSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnCancelMenuSearch()
{
	//退单查询
	CCancelMenuSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnSkyMenu()
{
	CSyyReportDlg dlg;
	dlg.DoModal();
}
