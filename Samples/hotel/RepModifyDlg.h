//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File: RepModifyDlg.h
// 
// Desc: ���������
//
// Author:  xq
//
// Modified: 2006��6��30�� 6:25
//-----------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "KDBCon.h"

// CRepModifyDlg �Ի���

class CRepModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepModifyDlg)

public:
	CRepModifyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepModifyDlg();

// �Ի�������
	enum { IDD = IDD_REP_MODIFY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
