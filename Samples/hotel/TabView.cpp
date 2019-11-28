// TabView.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "TabView.h"
#include "GuiViewWorkTab.h"
#include "KDBCon.h"
#include ".\tabview.h"



// CTabView

IMPLEMENT_DYNCREATE(CTabView, CGuiViewWorkTab)

CTabView::CTabView()
:m_roomSize(0),m_curRoomNo(0)
{
	hotelMIS::KDBCon con;
	hotelMIS::HRoomCtrl roomCtrl(con.get_con());
	vec = roomCtrl.getAllRoom();
	m_roomSize = roomCtrl.getRoomCount();
	m_pDiningRoom = new CDiningRoomTab[m_roomSize];
}

CTabView::~CTabView()
{
	delete [] m_pDiningRoom;
}

BEGIN_MESSAGE_MAP(CTabView, CGuiViewWorkTab)
	ON_WM_CREATE()
	ON_MESSAGE(WM_GETROOMNO,OnSetRoomNo)
	ON_COMMAND(ID_ACCOUNT, OnAccount)
	ON_COMMAND(ID_VIEW_LARGER, OnViewLarger)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_COMMAND(ID_VIEW_SMALL, OnViewSmall)
	ON_MESSAGE(WM_ONREDRAW,OnReDraw)
	ON_COMMAND(ID_2003, On2003)
END_MESSAGE_MAP()


// CTabView 绘图

void CTabView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CTabView 诊断

#ifdef _DEBUG
void CTabView::AssertValid() const
{
	CGuiViewWorkTab::AssertValid();
}

void CTabView::Dump(CDumpContext& dc) const
{
	CGuiViewWorkTab::Dump(dc);
}
#endif //_DEBUG


// CTabView 消息处理程序

int CTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiViewWorkTab::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	const DWORD dwStyle =LBS_NOINTEGRALHEIGHT | LVS_REPORT| WM_NOTIFY|WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	//创建大堂餐厅
	//从t_roomSet表中取出餐厅设置
	int roomId = 0;
	for ( int i = 0; i < m_roomSize; i++)
	{
		//m_pDiningRoom[i].Create(dwStyle,CRect(0,0,0,0),&m_guiWorktab,0x5000+i);
		roomId = vec[i].getId();
		TRACE("OnCreate 餐厅=%d\n",roomId);
		m_pDiningRoom[i].CreateRoom(vec[i].getId(),dwStyle,CRect(0,0,0,0),&m_guiWorktab,0x5000+i);
		m_roomTabmap.insert(make_pair(roomId,&m_pDiningRoom[i]));
		ListView_SetExtendedListViewStyleEx(m_pDiningRoom[i].GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		m_guiWorktab.Addtab(&m_pDiningRoom[i],vec[i].getName().c_str(),-1);
	}
	m_guiWorktab.SetCurtab(0);
	if ( m_pDiningRoom[0].m_hWnd)
		m_pDiningRoom[0].PostMessage(WM_SHOWWINDOW);
	return 0;
}

void CTabView::OnInitialUpdate()
{
	CGuiViewWorkTab::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

}
LRESULT CTabView::OnSetRoomNo(WPARAM wParam,LPARAM lParam)
{
	m_curRoomNo = (int)wParam;
	CString str;
	str.Format("room %d ",m_curRoomNo);
	//AfxMessageBox(str);
	TRACE("OnSetRoomNo当前餐厅=%d\n",m_curRoomNo);
	return 0;
}
BOOL CTabView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	/*if ( m_curRoomNo >=0 && m_curRoomNo < m_roomSize)
	{
		TRACE("OnCmdMsg m_pDiningRoom[m_curRoomNo]=%d\n",m_curRoomNo);
		m_pDiningRoom[m_curRoomNo].OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
	}*/
	if ( m_curRoomNo > 0 ){
		//TRACE("OnCmdMsg m_pDiningRoom[m_curRoomNo]=%d\n",m_curRoomNo);
		m_roomTabmap[m_curRoomNo]->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
	}

	return TRUE ;//CGuiViewWorkTab::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CTabView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	return TRUE;//CGuiViewWorkTab::OnNotify(wParam, lParam, pResult);
}

LRESULT CTabView::OnReDraw(WPARAM wParam,LPARAM lParam)
{
	m_roomTabmap[m_curRoomNo]->Invalidate();
	return 0;
}

void CTabView::OnAccount()
{
	// TODO: 在此添加命令处理程序代码
}

void CTabView::OnViewLarger()
{
	// TODO: 在此添加命令处理程序代码
	
}

void CTabView::OnViewList()
{
	// TODO: 在此添加命令处理程序代码
	
}

void CTabView::OnViewSmall()
{
	// TODO: 在此添加命令处理程序代码
	
}

void CTabView::On2003()
{
	// TODO: 在此添加命令处理程序代码
	TRACE("On2003\n");
}
