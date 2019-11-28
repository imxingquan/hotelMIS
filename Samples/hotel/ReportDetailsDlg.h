//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  ReprotDetailsDlg.h
// 
// Desc:  经营明细报表
//
// Author:  xq
// 
// Modified: 2005年6月14日 5:09
//-----------------------------------------------------------------------
#pragma once
#include "atlcomtime.h"
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"

#include "KDBCon.h"

// CReportDetailsDlg 对话框

class CReportDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportDetailsDlg)

public:
	CReportDetailsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportDetailsDlg();

// 对话框数据
	enum { IDD = IDD_REPORT_DETAILS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dateStart;
	COleDateTime m_timeStart;
	COleDateTime m_dateEnd;
	COleDateTime m_timeEnd;
	CGuiButton m_GuiButtonSearch;
	CGuiButton m_GuiButtonPrint;
	CGuiButton m_GuiButtonPreView;
	CListCtrl m_list;
	CGuiButton m_GuiBtnCancel;
protected:
	hotelMIS::KDBCon m_con;

public:
	void InitIdle();
	void Refresh();
public:
	static CString m_exp;
	static CString m_hotelname;
	void PrintView();
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //打印回调

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonPrint();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedButtonPreview();
	
};
