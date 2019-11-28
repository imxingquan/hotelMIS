//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  RepNumWarning.cpp
// 
// Desc: 库存量警告对话框
//
// Author:  邢泉
//
// Modified: 2006年 6月 14日
//--------------------------------------------------------------------------------------

#include "stdafx.h"
#include "RepNumWarning.h"
#include ".\repnumwarning.h"

#include "KDBCon.h"
#include "HMenuInfoCtrl.h"
#include "HBeforeRepCtrl.h"

// CRepNumWarning 对话框

IMPLEMENT_DYNAMIC(CRepNumWarning, CDialog)
CRepNumWarning::CRepNumWarning(int food_id,BOOL tc,CWnd* pParent /*=NULL*/)
	: CDialog(CRepNumWarning::IDD, pParent),
	m_food_id(food_id)
	, m_bRepNumWarning(FALSE)
	, m_warning_msg(_T(""))
{
	hotelMIS::KDBCon con;
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(con.get_con());
	hotelMIS::HMenuInfo menu = menuInfoCtrl.getMenuInfo(m_food_id);
	hotelMIS::HBeforeRepCtrl beforeRepCtrl(con.get_con());
	float repNum = beforeRepCtrl.getCurRep(m_food_id);

	CString msg;
	if ( tc == TRUE)
	{
		msg.Format(_T("套餐中的 (%d)  %s \n库存量 %.2f %s,\n\n是否继续添加?"),
		m_food_id,menu.food_name.c_str(),repNum,menu.food_unit.c_str());

	}
	else
	{
		msg.Format(_T("(%d)  %s \n库存量 %.2f %s,\n\n是否继续添加?"),
		m_food_id,menu.food_name.c_str(),repNum,menu.food_unit.c_str());
	}
	m_warning_msg = msg;
}

CRepNumWarning::~CRepNumWarning()
{
}

void CRepNumWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_TS, m_bRepNumWarning);
	DDX_Text(pDX, IDC_STATIC_T, m_warning_msg);
}


BEGIN_MESSAGE_MAP(CRepNumWarning, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRepNumWarning 消息处理程序

void CRepNumWarning::OnBnClickedOk()
{
	UpdateData();
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "repNumWarning", m_bRepNumWarning);
	OnOK();
}

BOOL CRepNumWarning::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWinApp* pApp = AfxGetApp();
	m_bRepNumWarning = pApp->GetProfileInt("Settings", "repNumWarning",0);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
