//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  RepProdDetailsSearchDlg.h
// 
// Desc:  库存明细统计
//
// Author:  邢泉
// 
// Modified: 2006年6月16日 01:15:42
//-----------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "atlcomtime.h"
#include "KDBCon.h"
#include "HMenuInfoCtrl.h"



class CRepProdDetailsSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepProdDetailsSearchDlg)

public:
	CRepProdDetailsSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRepProdDetailsSearchDlg();

// 对话框数据
	enum { IDD = IDD_REP_DETAILS_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiEdit m_GuiSNameEdit;
	CGuiEdit m_GuiEditPy;

	CGuiButton m_GuiGetSBtn;
	CGuiButton m_GuiSearchBtn;
	CGuiButton m_GuiPrintBtn;
	CGuiButton m_GuiBtnExt;
	CGuiButton m_GuiBtnAdd;

	CButton m_GuiBtnTree;
	CButton m_GuiBtnList;

	CListCtrl m_GuiListRep;
	COleDateTime m_d1;
	COleDateTime m_t1;
	COleDateTime m_d2;
	COleDateTime m_t2;
	CString m_sName;
	
	CTreeCtrl m_GuiMenuTree;
	CListCtrl m_GuiMenuList;
	
	CToolTipCtrl m_tip;

protected:
	map<int,int> m_menuListMap; // 左侧菜单列表
	hotelMIS::KDBCon m_con;
	hotelMIS::HMenuInfoVec m_menuVec; 

	BOOL	m_bRepOpen;

	bool m_bIsTree;	
	
	CPoint m_point;
	CString m_py;

	int m_food_id;

	void InitIdle();
	void Refresh();

	int BuilderHeader();

	//打印
	static CString m_exp;
	static CString m_hotelname;
	static CString m_pname;

	void 	PrintView();
	static void DrawView(CDC &memDC, PRNINFO PrnInfo);  //打印回调
public:
	afx_msg void OnBnClickedGetSBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedPrintBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonExt2();
	afx_msg void OnBnClickedButtonTree();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnBnClickedButtonMoveRight();
	afx_msg void OnEnChangeEditPy();
	afx_msg void OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
