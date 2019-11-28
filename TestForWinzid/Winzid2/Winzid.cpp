// Winzid.cpp : 实现文件
//

#include "stdafx.h"
#include "Winzid2.h"
#include "Winzid.h"


// CWinzid

IMPLEMENT_DYNAMIC(CWinzid, CPropertySheet)
CWinzid::CWinzid(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWinzid::CWinzid(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_step1);
	AddPage(&m_step2);
	AddPage(&m_step3);

}

CWinzid::~CWinzid()
{
}


BEGIN_MESSAGE_MAP(CWinzid, CPropertySheet)
END_MESSAGE_MAP()


// CWinzid 消息处理程序
