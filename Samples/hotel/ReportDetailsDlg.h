//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  ReprotDetailsDlg.h
// 
// Desc:  ��Ӫ��ϸ����
//
// Author:  xq
// 
// Modified: 2005��6��14�� 5:09
//-----------------------------------------------------------------------
#pragma once
#include "atlcomtime.h"
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"

#include "KDBCon.h"

// CReportDetailsDlg �Ի���

class CReportDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportDetailsDlg)

public:
	CReportDetailsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportDetailsDlg();

// �Ի�������
	enum { IDD = IDD_REPORT_DETAILS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonPrint();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedButtonPreview();
	
};
