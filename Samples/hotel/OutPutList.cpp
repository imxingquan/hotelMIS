// OutPutList.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "OutPutList.h"
//#include ".\outputlist.h"


// COutPutList

IMPLEMENT_DYNAMIC(COutPutList, CListCtrl)
COutPutList::COutPutList()
{
}

COutPutList::~COutPutList()
{
}


BEGIN_MESSAGE_MAP(COutPutList, CListCtrl)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



// COutPutList 消息处理程序


void COutPutList::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CListCtrl::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	//MessageBox("ff");
}

void COutPutList::OnShowWindow(BOOL bShow, UINT nStatus)
{
	//

	// TODO: 在此处添加消息处理程序代码
	if ( bShow == TRUE)
		MessageBox("ff");
	CListCtrl::OnShowWindow( bShow, nStatus);
}
