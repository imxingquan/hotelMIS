// TabPageList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabPageList.h"


// CTabPageList �Ի���

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


// CTabPageList ��Ϣ�������
