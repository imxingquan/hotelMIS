//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File: RepModifyDlg.cpp
// 
// Desc: 调整库存量
//
// Author:  xq
//
// Modified: 2006年6月30日 6:25
//-----------------------------------------------------------------------
#include "stdafx.h"
#include ".\repmodifydlg.h"
#include "HMenuInfoCtrl.h"
#include "HBehindRepCtrl.h"


// CRepModifyDlg 对话框

IMPLEMENT_DYNAMIC(CRepModifyDlg, CDialog)
CRepModifyDlg::CRepModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRepModifyDlg::IDD, pParent)
	, m_bh(0)
	, m_foodName(_T(""))
	, m_repNum(0)
	, m_price(0)
	, m_tPrice(0)
{
}

CRepModifyDlg::~CRepModifyDlg()
{
}

void CRepModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_BH, m_bh);
	DDX_Text(pDX, IDC_STATIC_NAME, m_foodName);
	DDX_Text(pDX, IDC_EDIT_REP_NUM, m_repNum);
	DDX_Text(pDX, IDC_EDIT_REP_PRICE, m_price);
	DDX_Text(pDX, IDC_EDIT_REP_TOTAL, m_tPrice);
}


BEGIN_MESSAGE_MAP(CRepModifyDlg, CDialog)
	ON_BN_CLICKED(IDC_REP_MODIFY_BTN, OnBnClickedRepModifyBtn)
END_MESSAGE_MAP()


// CRepModifyDlg 消息处理程序

BOOL CRepModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//初始化,根据 food_id;
	if (  m_bh != 0){
		hotelMIS::HBehindRepCtrl bhRepCtrl(m_con.get_con());
		hotelMIS::HBehindRepVec vec;

		vec = bhRepCtrl.search(m_bh);
		hotelMIS::HBehindRepVec::iterator it = vec.begin();

		hotelMIS::HMenuInfoCtrl menuCtrl(m_con.get_con());
		hotelMIS::HMenuInfo m;
		m = menuCtrl.getMenuInfo(it->food_id);

		m_foodName = m.food_name.c_str();
		m_repNum = it->rep_num;
		m_price = it->food_price;
		m_tPrice = it->total_price;
		UpdateData(FALSE);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRepModifyDlg::OnBnClickedRepModifyBtn()
{
	// TODO: 调整库存
	UpdateData(TRUE);
	hotelMIS::HBehindRepCtrl bRepCtrl(m_con.get_con());
	hotelMIS::HBehindRep rep;
	rep.food_id = m_bh;
	rep.food_price = m_price;
	rep.rep_num = m_repNum;
	rep.total_price = m_tPrice;
	bRepCtrl.update(rep);
	MessageBox(_T("修改成功"),_T("提示"),MB_ICONINFORMATION|MB_OK);
	OnOK();
}
