// MyListCtrl.cpp : ʵ���ļ�
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



// CMyListCtrl ��Ϣ�������


void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
