// TabPageTree.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabPageTree.h"


// CTabPageTree �Ի���

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


// CTabPageTree ��Ϣ�������
