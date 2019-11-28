// MyTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "MyTreeCtrl.h"
#include ".\mytreectrl.h"


// CMyTreeCtrl

IMPLEMENT_DYNAMIC(CMyTreeCtrl, CTreeCtrl)
CMyTreeCtrl::CMyTreeCtrl()
{
}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyTreeCtrl 消息处理程序


void CMyTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	/*DWORD dwPos = ::GetMessagePos();
		CPoint pt((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		ScreenToClient(&pt);*/
		HTREEITEM hItem,hParent;
		if (hItem = HitTest(point))
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
	CTreeCtrl::OnMouseMove(nFlags, point);
}
