//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  MemXFSearchDlg.h
// 
// Desc: ��Ա������ϸ��ѯ
//
// Author:  ��Ȫ
//
// Modified: 2006�� 06 �� 21 ��
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

// CMemXFSearchDlg �Ի���

class CMemXFSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemXFSearchDlg)

public:
	CMemXFSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMemXFSearchDlg();

// �Ի�������
	enum { IDD = IDD_MEM_XFSEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	void InitIdle();		//��ʼ��list
	void RefreshZdList();	//ˢ���˵���
	void RefreshZdMxList(); //�����˵���ˢ����ϸ
public:
	//for print
	static CString m_exp;
	static CString m_hotelname;

	void PrintView();

	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�
public:

	afx_msg void OnBnClickedButtonSearch();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListZd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListZd(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_GuiComboBh;
	afx_msg void OnBnClickedButtonPrint();
};
