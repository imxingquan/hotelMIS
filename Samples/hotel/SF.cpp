// SF.cpp : 实现文件
//

#include "stdafx.h"
#include "SF.h"


// SF 对话框

IMPLEMENT_DYNAMIC(SF, CDialog)
SF::SF(CWnd* pParent /*=NULL*/)
	: CDialog(SF::IDD, pParent)
{
}

SF::~SF()
{
}

void SF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SF, CDialog)
END_MESSAGE_MAP()


// SF 消息处理程序
