//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  ReptotalDlg.h
// 
// Desc: 库存汇总
//
// Author:  邢泉
// 
// Modified: 2006年6月16日 
//-----------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "atlcomtime.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.H"

// CRepTotalDlg 对话框

class CRepTotalDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepTotalDlg)

public:
	CRepTotalDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRepTotalDlg();

// 对话框数据
	enum { IDD = IDD_TOTAL_PRINT_DLG };

public:
	hotelMIS::KDBCon m_con;
	static CString m_exp;
	static CString m_hotelname;

public:
	void InitIdle();
	
	void	PrintTotal();

	static void DrawByTotal(CDC &memDC, PRNINFO PrnInfo);  //打印回调

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_d1;
	COleDateTime m_d2;
	CGuiButton m_GuiTotalBtn;
	CGuiButton m_GuiPrintBtn;
	
	CListCtrl m_GuiTotalList;
	afx_msg void OnBnClickedTotalButton();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedPrintButton();
};
