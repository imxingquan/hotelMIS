#pragma once

#include "resource.h"
#include "atlcomtime.h"
#include "afxcmn.h"
#include "KDBCon.h"

// CMemZZListDlg 对话框

class CMemZZListDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemZZListDlg)

public:
	CMemZZListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMemZZListDlg();

// 对话框数据
	enum { IDD = IDD_MEM_ZZLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_d1;
	COleDateTime m_d2;
	CString m_bh;
	CListCtrl m_GuiZZList;

	hotelMIS::KDBCon m_con;
public:
	void Refresh();
	void InitIdle();
public:
	static CString m_exp;
	static CString m_hotelname;
	void PrintView();
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //打印回调

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonPrint();
};
