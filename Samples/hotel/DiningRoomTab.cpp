// DiningRoomList.cpp : ʵ���ļ�
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



// CDiningRoomTab ��Ϣ�������
LRESULT CDiningRoomTab::OnReDraw(WPARAM wParam,LPARAM lParam)
{
	Invalidate();
	return 0;
}

void CDiningRoomTab::OnViewLarger()
{
	// TODO: ��ͼ�η�ʽ��ʾ
	ModifyStyle(LVS_TYPEMASK,LVS_ICON);
}

void CDiningRoomTab::OnViewList()
{
	// TODO: �б�ʽ
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
}

void CDiningRoomTab::OnViewSmall()
{
	// TODO: Сͼ�η�ʽ
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
	//����ͼ��״̬
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
		hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
		hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());

		int nState = repastCtrl.getRepastState(tableId,m_roomId); //�Ͳ�״̬
		
		string tableName = tableStatusCtrl.getTableName(tableId,m_roomId);
		int tableStatus = tableStatusCtrl.getTableStatus(tableId,m_roomId); //��������id
		
		LV_ITEM lvi;
		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		lvi.iItem = tableId-1;
		CString szText;

		if ( hotelMIS::HRepast::emptyState ==nState ){ //����
			if ( !tableName.empty())
				szText.Format("%d�š�%s��",tableId,tableName.c_str());
			else
				szText.Format("%d��",tableId);
			lvi.iImage =tableStatusSetCtrl.getTableEmptyBmp(tableStatus);
		}
		else if ( hotelMIS::HRepast::repastState == nState){
			if ( !tableName.empty())
				szText.Format("%d�š�%s���Ͳ���",tableId,tableName.c_str());
			else
				szText.Format("%d�žͲ���",tableId);
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
			TRACE("�Ͳ�: ����%s,������=%d,������ =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);
#endif
			CJCDialog m_jcDlg;
			m_jcDlg.m_roomId = m_roomId;
			m_jcDlg.m_tableId = m_tableId;
			m_jcDlg.DoModal();
			ChangeTableState(m_tableId);

		}

		RefreshDownList(); //ˢ���±ߵ��б�
	}
	else{
		MessageBox(_T("����ѡ����Ҫ�����Ĳ���!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
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
	// TODO:  �ڴ������ר�õĴ�������
	InsertColumn(0,_T("������"), LVCFMT_LEFT,200);
	InsertColumn(1,_T("���ѽ��"),LVCFMT_LEFT,120);
	
	Refresh();
}

void CDiningRoomTab::Refresh()
{
	//��ʼ������

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
		tableStatus = tableStatusCtrl.getTableStatus(it->table_id,m_roomId); //��������id
		
		if ( hotelMIS::HRepast::emptyState ==  nState){ //����
			if ( !tableName.empty())
				szText.Format("%d�š�%s��",it->table_id,tableName.c_str());
			else
				szText.Format("%d��",it->table_id);
			
			ASSERT(tableStatusSetCtrl.getTableEmptyBmp(tableStatus) != -1);;
			
			lvi.iImage =tableStatusSetCtrl.getTableEmptyBmp(tableStatus);
		}
		else if ( hotelMIS::HRepast::repastState == nState){
			if ( !tableName.empty())
				szText.Format("%d�š�%s���Ͳ���",it->table_id,tableName.c_str());
			else
				szText.Format("%d�žͲ���",it->table_id);
			
			ASSERT(tableStatusSetCtrl.getTableRepastBmp(tableStatus) != -1);
			
			lvi.iImage =tableStatusSetCtrl.getTableRepastBmp(tableStatus);
		}
		lvi.pszText = szText.GetBuffer();	//���ݵ�ǰ�Ͳ�״̬���ò�ͬ����
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
	// TODO: �ڴ˴������Ϣ����������
	TRACE("OnShowWindow��ǰ����%d\n",m_roomId);
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
	// TODO: ����ѡ��
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	ScreenToClient(&point);
	
	if (( m_nPos = HitTest(point)) != -1 ) {
		CString str = GetItemText(m_nPos,0);	
		m_tableId = m_tableInfoMap[m_nPos].getTable_id();
		TRACE("��������%s,������=%d,������ =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);	
		//������Ϣ�� �·��� CDetailsListView����ȡ��ǰ�����Ĳ˵�
		
		//this->GetParent()->GetParent()->PostMessage(WM_GETTABLEINFO,(WPARAM)m_roomId,(LPARAM)m_tableId);
			//
		RefreshDownList();
	}
	*pResult = 0;
}

void CDiningRoomTab::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ˫����
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	ScreenToClient(&point);
	
	if (( m_nPos = HitTest(point)) != -1 ) {
		CString str = GetItemText(m_nPos,0);	
		m_tableId = m_tableInfoMap[m_nPos].getTable_id();
		TRACE("��������%s,������=%d,������ =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);
		OnRepast();
	}
	*pResult = 0;
}

void CDiningRoomTab::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		TRACE("��������%s,������=%d,������ =%d \n",str,m_tableInfoMap[m_nPos].getTable_id(),m_roomId);
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
			m_ToolTipCtrl.SetTitle(1,_T("����"));
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
			m_ToolTipCtrl.SetTitle(1,_T("����"));
			//m_ToolTipCtrl.UpdateTipText(_T(""), this);
						
		}
		else
		{
			m_ToolTipCtrl.UpdateTipText(_T(""), this);/*m_ToolTipCtrl.UpdateTipText(lpMsg, this);*/
		}
		
		m_ToolTipCtrl.Activate(FALSE);
	}
}


//����ΪMenuӳ�����

void CDiningRoomTab::OnDestine()
{
	
	CYDXXDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnDestineManage()
{
	// TODO: Ԥ���͹���
	CYDDialog dlg;
	dlg.m_ListCtrl = this;
	dlg.DoModal();
}

void CDiningRoomTab::OnAccount()
{
	
	// TODO: ����

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
		MessageBox(_T("����ѡ����Ҫ�����ˡ��Ĳ���!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::OnChangetable()
{
	// TODO: �ڴ���������������
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
		RefreshDownList(); //ˢ���±ߵ��б�
	}else{
		MessageBox(_T("����ѡ����Ҫ���������Ĳ���!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::OnReInput()
{
	// TODO: ���Ǽ�
	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM1() ){ return; }

	CInRepDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnReOutput()
{
	
	// TODO: ���Ǽ�
	hotelMIS::HAdminBdy bdy(m_con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),m_con.get_con());
	if ( !op.getM1() ){ return; }
	COutRegDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnReSearch()
{
	// TODO: ����ѯ
	CRepertorySearchDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnSearchAccounts()
{
	// TODO: �˵���ѯ
	CSearchAccountDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpAdd()
{
	// TODO: �����Ա��
	CEmployeeDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpManage()
{
	// TODO: Ա������
	CEmpManagerDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpSearch()
{
	// TODO: Ա����ѯ
	CEmpManagerDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnEmpSetjob()
{
	// TODO: �ڴ���������������
	CEmpSetJobDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnMenuModify()
{
	// TODO: ����ά��
	CMenuManagerDialog dlg;
	dlg.DoModal();
}


void CDiningRoomTab::OnFeatureManage()
{
	// TODO: ��ɫ���׹���
	CSpecialMenuDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnKindSet()
{
	// TODO: ��λ����
	CKindUnitSetDialog dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnDayReport()
{
	// TODO: ����Ա����*********************************************
	
	CReportDayDialog dlg;
	dlg.DoModal();
}


void CDiningRoomTab::OnSysuserSet()
{
	// TODO: ϵͳ�û�����
	CSysUserManagerDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnSysparaSet()
{
	// TODO: ϵͳ��������*********************************************
	
	CSetpConfigDialog dlg(_T("ϵͳ����"),this);
	
	dlg.DoModal();
}

void CDiningRoomTab::OnOtherCalc()
{
	// TODO: ���ü�����
	hotelMIS::KProfile profile("set.ini");
	CString Path = profile.GetProfile("OTHER_APP","app1").c_str();
	WinExec(Path,SW_NORMAL);
}

void CDiningRoomTab::OnOtherNotepad()
{
	// TODO: ���ü��±�
	hotelMIS::KProfile profile("set.ini");
	CString Path = profile.GetProfile("OTHER_APP","app2").c_str();
	WinExec(Path,SW_NORMAL);

}

void CDiningRoomTab::OnOtherPaint()
{
	// TODO: ����ͼ��
	hotelMIS::KProfile profile("set.ini");
	CString Path = profile.GetProfile("OTHER_APP","app3").c_str();
	WinExec(Path,SW_NORMAL);
}



void CDiningRoomTab::OnRefresh()
{
	// TODO: �ڴ���������������
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
	// TODO: ����
	MyCdKey cdkey;
	if ( !cdkey.RegisterCdKey() ){
		CRegisterDialog dlg;
		dlg.DoModal();
	}

	if ( -1 != m_nPos )
	{
		hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		if ( repastCtrl.getRepastState(m_tableId,m_roomId) == hotelMIS::HRepast::repastState ) //����Ϊ�Ͳ�״̬
		{
			//1) �����˽������˻��С�
			CArrearageDialog dlg;
			hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
			HTotalPair t =repDeCtrl.getAllPrice(repastCtrl.getAccountId(m_tableId,m_roomId));
			dlg.m_arrMoney = t.first + t.second;
			if ( dlg.DoModal() == IDOK){ //����
				//1) �õ��� arid, accoundId
				//TRACE("arid = %d,accountid=%s\n,",dlg.m_callback_arid,repastCtrl.getAccountId(m_tableId,m_roomId).c_str());
				//2) �������˺ź��˵���д��������ݿ�
				hotelMIS::HArrerageBdy arrBdy;
				string accId = repastCtrl.getAccountId(m_tableId,m_roomId);
				arrBdy.gz(dlg.m_callback_arid,accId);
				//3) �����ݴӾͲͱ��е��뵽��ʷ��¼����
				arrBdy.tranToAcc(m_tableId,m_roomId,accId,dlg.m_arrMoney);
				//4) ���²�����
				ChangeTableState(m_tableId);
				//_CrtDumpMemoryLeaks();
			}
		}
		
	}
	else
	{
		MessageBox(_T("����ѡ��Ҫ�����Ĳ���!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
	}
}

void CDiningRoomTab::RepastToAccount()
{
   
}

void CDiningRoomTab::OnArrearageManage()
{
	// TODO:�����˻�����
	CAddArrearageDialog dlg;
	dlg.DoModal();
	
	//MessageBox(_T("��ʾ�汾û�д˹���!�빺���������!\n�����ܲ�:0411-84799689\n���ɴ���:0471-6350482"),_T("����"),MB_ICONINFORMATION|MB_OK);

}

void CDiningRoomTab::OnArrearageGzjz()
{
	// TODO: ���˽���
	CArrPayDialog dlg;
	dlg.DoModal();
}


BOOL CDiningRoomTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE && m_sFlag/*|| pMsg->message == WM_MOUSEHOVER*/)
	{
		if (m_ToolTipCtrl.GetSafeHwnd())
			m_ToolTipCtrl.RelayEvent(pMsg);
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CDiningRoomTab::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	 CWinApp* pApp = AfxGetApp();
	 m_sFlag = pApp->GetProfileInt("Settings", "AutoRefresh",0);
	 if ( 1 == m_sFlag){
		TRACKMOUSEEVENT tme;
		tme.cbSize=sizeof(tme);
		tme.dwFlags=TME_HOVER; //��������Ҫִ�еĲ���
		tme.hwndTrack=m_hWnd;    //���ھ��
		tme.dwHoverTime=HOVER_DEFAULT;//���ȴ�ʱ��,Ȼ����WM_MOUSEHOVER
		::TrackMouseEvent(&tme);
	 }
	CListCtrl::OnMouseMove(nFlags, point);
}

void CDiningRoomTab::OnNMHover(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	if ( 1 == m_sFlag){
		DWORD dwPos = ::GetMessagePos();
		CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		ScreenToClient(&point);

		if (( m_nPos = HitTest(point)) != -1 ) {
			TRACKMOUSEEVENT tme;
			tme.cbSize=sizeof(tme);
			tme.dwFlags=TME_HOVER; //��������Ҫִ�еĲ���
			tme.hwndTrack=m_hWnd;    //���ھ��
			tme.dwHoverTime=HOVER_DEFAULT;//���ȴ�ʱ��,Ȼ����WM_MOUSEHOVER
			::TrackMouseEvent(&tme);

			CTime t1=CTime::GetCurrentTime();

			CString str;
			str.Format("��ֹ�� %d:%.2d:%.2d  �˿͹����� %s Ԫ��",t1.GetHour(),t1.GetMinute(),t1.GetSecond(),GetItemText(m_nPos,1));

			SetToolTip(str);
		}else{
			SetToolTip(NULL);
		}
	}
}

void CDiningRoomTab::OnPopupSetTable()
{
	// TODO: ���ò���״̬
	if ( this->GetSelectionMark() != -1 ){
		CTableSetDialog dlg(this,m_tableId,m_roomId);
		if ( dlg.DoModal() == IDOK){
			ChangeTableState(m_tableId);
		}
	}
}	

void CDiningRoomTab::OnRegisterMenu()
{
	// TODO: ע��
	MyCdKey cdkey;
	if ( cdkey.RegisterCdKey() ){
		MessageBox(_T("�Ѿ�����Ȩ�û�,����Ҫ��ע��!"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_OK);
	}
	else
	{
		CRegisterDialog dlg;
		dlg.DoModal();
	}
}


void CDiningRoomTab::OnPopupPrint()
{
	// TODO: ��ӡ
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
				di.lpszDocName= _T("�����˵�");

				dc.StartDoc(&di);
				dc.StartPage();
				PrintReport(&dc);
				dc.EndPage();
				dc.EndDoc();

			}

		}
	}else{
			MessageBox(_T("����ѡ����Ҫ����ӡ���Ĳ���!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
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

	dc->SetMapMode(MM_LOMETRIC); //����Ϊ���׵�λ
	dc->SetTextAlign(TA_LEFT);
	
	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("����"));
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
		acc.Format("%s-%d����[%s]",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId,tableName.c_str());
	else
		acc.Format("%s-%d����",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId);

	//acc.Format("%s,%d�Ų���",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId);
	dc->TextOut(xPos,yPos,acc);
	dc->TextOut(xPos,yPos-fHeight,_T("--------------����СƱ----------------"));
	acc.Format("�˵���: %s ",accountId.c_str());
	dc->TextOut(xPos,yPos-fHeight*2,acc);
	acc.Format("����: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*3,acc);
	dc->TextOut(xPos,yPos-fHeight*4,_T("����"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*4,_T("����"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*4,_T("����"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*4,_T("�ܼ�"));
		
	CString cnt;
	int n = 5;
	int len = 0;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//����

		cnt.Format("%.2f",it->food_price);
		
		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;
		
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//����
		cnt.Format("%d",it->food_num);
		//dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//����
		cnt.Format("%.2f",it->food_price*it->food_num);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //�ܼ�
		
        n++;
	}
	
	HTotalPair t=  repDetailsCtrl.getAllPrice(accountId);
	float ys = t.first + t.second;
	cnt.Format("%.2f",ys);	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("�ϼ�:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	//n++;	
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));
	//
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("ʵ���տ�:"));
	//UpdateData(false);
	//cnt.Format("%.2f",atof(m_sj));
	//dc->SetTextAlign(TA_RIGHT);
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//
	//if ( atof(m_zk) > 0){
	//	n++;
	//	dc->SetTextAlign(TA_LEFT);
	//	dc->TextOut(xPos,yPos - fHeight*n,_T("�ۿ�״��:"));
	//	cnt.Format("%.1f��",atof(m_zk));
	//	dc->SetTextAlign(TA_RIGHT);
	//	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//}
	//
	//n++;
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("Ӧ���˿�:"));
	//cnt.Format("%.2f",m_ss);
	//dc->SetTextAlign(TA_RIGHT);
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	//
	//n++;
	//dc->SetTextAlign(TA_LEFT);
	//dc->TextOut(xPos,yPos - fHeight*n,_T("����˿�:"));
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
	//dc->TextOut(xPos,yPos - fHeight*n,_T("���͵绰:"));
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel.c_str());
	//}
	//if ( ! hotelMsg.hoteltel2.empty() && ! hotelMsg.hoteltel.empty()){
	//n++;
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel2.c_str());
	//}
	//if ( !hotelMsg.hotelhttp.empty()){
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("������ַ:"));
	//dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hotelhttp.c_str());
	//}
	//n++;
	//dc->TextOut(xPos,yPos -fHeight*n,_T("---------------------------------------"));
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("����֧��: ����������"));
	//n++;
	//dc->TextOut(xPos,yPos - fHeight*n,_T("HTTP://WWW.IDCWEST.NET"));
	////print space line
	n = n+7;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);
}
void CDiningRoomTab::OnRecalltable()
{
	// TODO: ȡ�����ھͲ͵Ĳ���
	if ( this->GetSelectionMark() != -1 ){
		
		int result = MessageBox(_T("ȷʵҪȡ����ǰ�ľͲ�?"),_T("����"),MB_ICONWARNING|MB_YESNO);
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
	// TODO: �ֳ����״�ӡ����
	CSetChuFangMenu dlg;
	dlg.DoModal();
}

void CDiningRoomTab::On2003()
{
	// TODO: �ڴ���������������
	/*CMainFrame* MainFrame=(CMainFrame*)AfxGetMainWnd();
	MainFrame->SendMessage(WM_COMMAND,ID_2003);*/
	
	//��ѭ��
}

void CDiningRoomTab::OnXp()
{
	// TODO: �ڴ���������������
}

void CDiningRoomTab::OnMemberManage()
{
	// TODO: ��Ա����
	CMemberInfoDlg dlg;
	dlg.DoModal();
}

//void CDiningRoomTab::OnMemberBirth()
//{
//	// TODO: ���ղ�ѯ
//	MessageBox(_T("�ǳ���Ǹ,���������ڿ�������!"));
//}

void CDiningRoomTab::OnMemberCastsearch()
{
	// TODO: ���Ѳ�ѯ
	CMemXFSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnMemberCz()
{
	// TODO: ��ֵ��ѯ
	CMemCZListDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnMemberZz()
{
	// TODO: ת�˲�ѯ
	CMemZZListDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnReportDetails()
{
	// ��Ӫ��ϸ��
	CReportDetailsDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnRepDetailsSearch()
{
	// �����Ʒ��ϸ��ѯ
	CRepProdDetailsSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnRepKindSet()
{
	// �����Ʒ������
	CKindUnitSetDialog dlg(TRUE);
	dlg.DoModal();
}

void CDiningRoomTab::OnRepPManag()
{
	//  �����Ʒά��
	CMenuManagerDialog dlg(TRUE);
	dlg.DoModal();
}

void CDiningRoomTab::OnRepTotalSearch()
{
	// ���ܲ�ѯ
	CRepTotalDlg dlg;
	dlg.DoModal();
}


void CDiningRoomTab::OnAppExit()
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

void CDiningRoomTab::OnInoutZdSearch()
{
	//�˵���ѯ 
	CInOutRepSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnCancelMenuSearch()
{
	//�˵���ѯ
	CCancelMenuSearchDlg dlg;
	dlg.DoModal();
}

void CDiningRoomTab::OnSkyMenu()
{
	CSyyReportDlg dlg;
	dlg.DoModal();
}
