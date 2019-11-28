// TabPageTree.cpp : 实现文件
//

#include "stdafx.h"
#include "TabPageTree.h"


// CTabPageTree 对话框

IMPLEMENT_DYNAMIC(CTabPageTree, CDialog)
CTabPageTree::CTabPageTree(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTabPageTree::IDD, pParent)
{
}

CTabPageTree::~CTabPageTree()
{
}

void CTabPageTree::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabPageTree, CTabPageSSL)
END_MESSAGE_MAP()


// CTabPageTree 消息处理程序
