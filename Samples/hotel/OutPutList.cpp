// OutPutList.cpp : ʵ���ļ�
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



// COutPutList ��Ϣ�������


void COutPutList::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CListCtrl::OnActivate(nState, pWndOther, bMinimized);

	// TODO: �ڴ˴������Ϣ����������
	//MessageBox("ff");
}

void COutPutList::OnShowWindow(BOOL bShow, UINT nStatus)
{
	//

	// TODO: �ڴ˴������Ϣ����������
	if ( bShow == TRUE)
		MessageBox("ff");
	CListCtrl::OnShowWindow( bShow, nStatus);
}
