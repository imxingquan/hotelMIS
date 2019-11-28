//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File: RepModifyDlg.cpp
// 
// Desc: ���������
//
// Author:  xq
//
// Modified: 2006��6��30�� 6:25
//-----------------------------------------------------------------------
#include "stdafx.h"
#include ".\repmodifydlg.h"
#include "HMenuInfoCtrl.h"
#include "HBehindRepCtrl.h"


// CRepModifyDlg �Ի���

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


// CRepModifyDlg ��Ϣ�������

BOOL CRepModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//��ʼ��,���� food_id;
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CRepModifyDlg::OnBnClickedRepModifyBtn()
{
	// TODO: �������
	UpdateData(TRUE);
	hotelMIS::HBehindRepCtrl bRepCtrl(m_con.get_con());
	hotelMIS::HBehindRep rep;
	rep.food_id = m_bh;
	rep.food_price = m_price;
	rep.rep_num = m_repNum;
	rep.total_price = m_tPrice;
	bRepCtrl.update(rep);
	MessageBox(_T("�޸ĳɹ�"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
	OnOK();
}
