// TabPageList.cpp : 实现文件
//

#include "stdafx.h"
#include "TabPageList.h"


// CTabPageList 对话框

IMPLEMENT_DYNAMIC(CTabPageList, CDialog)
CTabPageList::CTabPageList(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTabPageList::IDD, pParent)
{
}

CTabPageList::~CTabPageList()
{
}

void CTabPageList::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabPageList, CTabPageSSL)
END_MESSAGE_MAP()


// CTabPageList 消息处理程序
