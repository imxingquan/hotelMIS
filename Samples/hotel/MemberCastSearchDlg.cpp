// MemberCastSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberCastSearchDlg.h"


// CMemberCastSearchDlg 对话框

IMPLEMENT_DYNAMIC(CMemberCastSearchDlg, CDialog)
CMemberCastSearchDlg::CMemberCastSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemberCastSearchDlg::IDD, pParent)
{
}

CMemberCastSearchDlg::~CMemberCastSearchDlg()
{
}

void CMemberCastSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMemberCastSearchDlg, CDialog)
END_MESSAGE_MAP()


// CMemberCastSearchDlg 消息处理程序
