//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  MemXFSearchDlg.h
// 
// Desc: 会员消费明细查询
//
// Author:  邢泉
//
// Modified: 2006年 06 月 21 日
//--------------------------------------------------------------------------------------
#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "atlcomtime.h"
#include "KDBCon.h"
#include <map>
#include <string>
#include "afxwin.h"
using namespace std;

// CMemXFSearchDlg 对话框

class CMemXFSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemXFSearchDlg)

public:
	CMemXFSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMemXFSearchDlg();

// 对话框数据
	enum { IDD = IDD_MEM_XFSEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_bh;
	CString m_name;
	CListCtrl m_GuiListZd;
	CListCtrl m_GuiListZdMx;
	COleDateTime m_d1;
	COleDateTime m_d2;
	
	hotelMIS::KDBCon m_con;
	map<int,string> m_mapzd;	//<pos,accountId>
	map<int,string> m_mapcombo; //<pos,bh>

public:
	void InitIdle();		//初始化list
	void RefreshZdList();	//刷新账单号
	void RefreshZdMxList(); //根据账单号刷新明细
public:
	//for print
	static CString m_exp;
	static CString m_hotelname;

	void PrintView();

	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //打印回调
public:

	afx_msg void OnBnClickedButtonSearch();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListZd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListZd(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_GuiComboBh;
	afx_msg void OnBnClickedButtonPrint();
};
