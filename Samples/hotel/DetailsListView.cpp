// DetailsListView.cpp : 实现文件
//

#include "stdafx.h"
#include "KDBCon.h"
#include "HRepastCtrl.h"
#include "HRepDetailsCtrl.h"
#include "HRoomCtrl.h"
#include "DetailsListView.h"
#include ".\detailslistview.h"


// CDetailsListView

IMPLEMENT_DYNCREATE(CDetailsListView, CListView)

CDetailsListView::CDetailsListView()
{
}

CDetailsListView::~CDetailsListView()
{
}

BEGIN_MESSAGE_MAP(CDetailsListView, CListView)
	ON_WM_CREATE()
	ON_MESSAGE(WM_GETTABLEINFO,OnGetTableInfo)
END_MESSAGE_MAP()


// CDetailsListView 诊断

#ifdef _DEBUG
void CDetailsListView::AssertValid() const
{
	CListView::AssertValid();
}

void CDetailsListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG


// CDetailsListView 消息处理程序
void CDetailsListView::Init()
{
	m_pListCtrl = &GetListCtrl();
	m_pListCtrl->InsertColumn(0,_T("编号"), LVCFMT_LEFT,50);
	m_pListCtrl->InsertColumn(1,_T("菜名"),LVCFMT_LEFT,180);
	m_pListCtrl->InsertColumn(2,_T("价格"),LVCFMT_RIGHT,60);
	m_pListCtrl->InsertColumn(3,_T("数量"),LVCFMT_CENTER,40);
	m_pListCtrl->InsertColumn(4,_T("单位"),LVCFMT_CENTER,100);
	m_pListCtrl->InsertColumn(5,_T("厨师"),LVCFMT_LEFT,100);
	
	m_pListCtrl->ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	ListView_SetExtendedListViewStyleEx(m_pListCtrl->m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
int CDetailsListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	Init();
	return 0;
}

void CDetailsListView::Refresh(int roomId,int tableId)
{
	m_pListCtrl->DeleteAllItems();
	//刷新用户就餐列表
	hotelMIS::HRepastCtrl repCtrl(m_con.get_con());
	hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
	hotelMIS::HRepDetailsVec vec = repDeCtrl.getAllDetails(repCtrl.getAccountId(tableId,roomId));
	hotelMIS::HRepDetailsVec::iterator it;
	
	int i = 0;
	CString cnt;
	m_repMap.clear();
	m_repPosMap.clear();
	float sum = 0.0f;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_repMap.insert(make_pair(i,make_pair(it->account_id,it->food_id))); //先保留
		m_repPosMap.insert(make_pair(i,it->id));
		cnt.Format("%d",i+1);
		m_pListCtrl->InsertItem(i,cnt);
		m_pListCtrl->SetItemText(i,1,it->food_name.c_str());
		cnt.Format("%.2f",it->food_price);
		m_pListCtrl->SetItemText(i,2,cnt);
		cnt.Format("%d",it->food_num);
		m_pListCtrl->SetItemText(i,3,cnt);
		m_pListCtrl->SetItemText(i,4,it->food_unit.c_str());
		m_pListCtrl->SetItemText(i,5,it->ck_name.c_str());
		i++;
		sum += it->food_num * it->food_price;
	}

	

	m_pListCtrl->InsertItem(i,_T("合计:"));
	//cnt.Format("%.2f",repDeCtrl.getAllPrice(repCtrl.getAccountId(tableId,roomId)));
	cnt.Format("%.2f",sum);
	m_pListCtrl->SetItemText(i,2,cnt);
	
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	cnt.Format("%s",roomCtrl.getRoomName(roomId).c_str());
	m_pListCtrl->SetItemText(i,4,cnt);
	cnt.Format("%d号餐桌",tableId);
	m_pListCtrl->SetItemText(i,5,cnt);

    	
}

LRESULT CDetailsListView::OnGetTableInfo(WPARAM wParam,LPARAM lParam)
{
	int roomId = (int)wParam;
	int tableId = (int)lParam;

	TRACE("roomId=%d,tableId=%d\n",(int)wParam,(int)lParam);

	Refresh(roomId,tableId);
	return 0;
}
