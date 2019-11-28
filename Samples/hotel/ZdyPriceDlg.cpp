// ZdyPriceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZdyPriceDlg.h"
#include ".\zdypricedlg.h"


// CZdyPriceDlg 对话框

IMPLEMENT_DYNAMIC(CZdyPriceDlg, CDialog)
CZdyPriceDlg::CZdyPriceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZdyPriceDlg::IDD, pParent)
	, m_zdyPrice(0)
{
}

CZdyPriceDlg::~CZdyPriceDlg()
{
}

void CZdyPriceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZDY_PRICE_EDIT, m_zdyPrice);
}


BEGIN_MESSAGE_MAP(CZdyPriceDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CZdyPriceDlg 消息处理程序

void CZdyPriceDlg::OnBnClickedOk()
{
	UpdateData(true);
	if ( this->m_zdyPrice <= 0)
		MessageBox(_T("请输入金额!"));
	else
		OnOK();
}
