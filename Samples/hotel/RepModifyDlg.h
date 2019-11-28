//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File: RepModifyDlg.h
// 
// Desc: 调整库存量
//
// Author:  xq
//
// Modified: 2006年6月30日 6:25
//-----------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "KDBCon.h"

// CRepModifyDlg 对话框

class CRepModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepModifyDlg)

public:
	CRepModifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRepModifyDlg();

// 对话框数据
	enum { IDD = IDD_REP_MODIFY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_bh;
	CString m_foodName;
	float m_repNum;
	float m_price;
	float m_tPrice;
	hotelMIS::KDBCon m_con;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRepModifyBtn();
};
