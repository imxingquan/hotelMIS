// DetailsListView.cpp : ʵ���ļ�
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


// CDetailsListView ���

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


// CDetailsListView ��Ϣ�������
void CDetailsListView::Init()
{
	m_pListCtrl = &GetListCtrl();
	m_pListCtrl->InsertColumn(0,_T("���"), LVCFMT_LEFT,50);
	m_pListCtrl->InsertColumn(1,_T("����"),LVCFMT_LEFT,180);
	m_pListCtrl->InsertColumn(2,_T("�۸�"),LVCFMT_RIGHT,60);
	m_pListCtrl->InsertColumn(3,_T("����"),LVCFMT_CENTER,40);
	m_pListCtrl->InsertColumn(4,_T("��λ"),LVCFMT_CENTER,100);
	m_pListCtrl->InsertColumn(5,_T("��ʦ"),LVCFMT_LEFT,100);
	
	m_pListCtrl->ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	ListView_SetExtendedListViewStyleEx(m_pListCtrl->m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
int CDetailsListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	Init();
	return 0;
}

void CDetailsListView::Refresh(int roomId,int tableId)
{
	m_pListCtrl->DeleteAllItems();
	//ˢ���û��Ͳ��б�
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
		m_repMap.insert(make_pair(i,make_pair(it->account_id,it->food_id))); //�ȱ���
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

	

	m_pListCtrl->InsertItem(i,_T("�ϼ�:"));
	//cnt.Format("%.2f",repDeCtrl.getAllPrice(repCtrl.getAccountId(tableId,roomId)));
	cnt.Format("%.2f",sum);
	m_pListCtrl->SetItemText(i,2,cnt);
	
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	cnt.Format("%s",roomCtrl.getRoomName(roomId).c_str());
	m_pListCtrl->SetItemText(i,4,cnt);
	cnt.Format("%d�Ų���",tableId);
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
