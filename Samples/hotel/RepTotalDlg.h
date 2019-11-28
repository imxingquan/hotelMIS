//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  ReptotalDlg.h
// 
// Desc: ������
//
// Author:  ��Ȫ
// 
// Modified: 2006��6��16�� 
//-----------------------------------------------------------------------
#pragma once

#include "resource.h"
#include "atlcomtime.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.H"

// CRepTotalDlg �Ի���

class CRepTotalDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepTotalDlg)

public:
	CRepTotalDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepTotalDlg();

// �Ի�������
	enum { IDD = IDD_TOTAL_PRINT_DLG };

public:
	hotelMIS::KDBCon m_con;
	static CString m_exp;
	static CString m_hotelname;

public:
	void InitIdle();
	
	void	PrintTotal();

	static void DrawByTotal(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
