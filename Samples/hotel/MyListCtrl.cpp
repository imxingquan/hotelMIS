// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "MyListCtrl.h"
#include ".\mylistctrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)
CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序


void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		DWORD dwPos = ::GetMessagePos();
		CPoint pt((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		ScreenToClient(&pt);
		HTREEITEM hItem,hParent;
		if (hItem = this->HitTest(pt))
		{
			/*hParent = m_GuiTreeCtrlMenu.GetParentItem(hItem);
			if ( hParent != NULL )
				m_GuiButtonMoveR.EnableWindow(TRUE);*/
			SetCursor(::LoadCursor(NULL,IDC_HAND));
		}
		else
		{
			SetCursor(::LoadCursor(NULL,IDC_ARROW));
		}
	CListCtrl::OnMouseMove(nFlags, point);
}
