//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  GetDetailsDlg.h
// 
// Desc: ��ȡ��Ʒ���ƺͱ��
//
// Author:  ��Ȫ
//
// Modified: 2006�� 06�� 15��
//--------------------------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


class CGetDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetDetailsDlg)

public:
	CGetDetailsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetDetailsDlg();

// �Ի�������
	enum { IDD = IDD_TABPAGE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
