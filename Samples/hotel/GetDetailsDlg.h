//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  GetDetailsDlg.h
// 
// Desc: 获取商品名称和编号
//
// Author:  邢泉
//
// Modified: 2006年 06月 15日
//--------------------------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


class CGetDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetDetailsDlg)

public:
	CGetDetailsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetDetailsDlg();

// 对话框数据
	enum { IDD = IDD_TABPAGE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_GuiBtnExt;
	CButton m_GuiBtnTree;
	CButton m_GuiBtnList;
	CEdit m_GuiEditPy;
	CListCtrl m_GuiMenuList;
	CTreeCtrl m_GuiMenuTree;
	CString m_py;
public:
	void InitIdle();
	void Refresh();

	afx_msg void OnBnClickedButtonExt();
	afx_msg void OnBnClickedButtonTree();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnEnChangeEditPy();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
