// SetDBDevDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "SetDBDevDlg.h"


// CSetDBDevDlg 对话框

IMPLEMENT_DYNAMIC(CSetDBDevDlg, CDialog)
CSetDBDevDlg::CSetDBDevDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDBDevDlg::IDD, pParent)
{
}

CSetDBDevDlg::~CSetDBDevDlg()
{
}

void CSetDBDevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetDBDevDlg, CDialog)
END_MESSAGE_MAP()


// CSetDBDevDlg 消息处理程序
