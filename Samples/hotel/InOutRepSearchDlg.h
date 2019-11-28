#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "atlcomtime.h"
#include "KDBCon.h"

#include <string>
#include <map>
using namespace std;
// CInOutRepSearchDlg 对话框

class CInOutRepSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CInOutRepSearchDlg)

public:
	CInOutRepSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInOutRepSearchDlg();

// 对话框数据
	enum { IDD = IDD_REP_INOUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiComboBoxExt m_GuiRepStatusCombo;
	CGuiButton m_CGuiSearchBtn;
	CGuiButton m_GuiPrintBtn;
	CGuiButton m_GuiExitBtn;
	CListCtrl m_GuiRepList;
	CListCtrl m_GuiRepDetailsList;
	COleDateTime m_d1;
	COleDateTime m_d2;
	int m_inOutFlag;
	
	CFont m_font;

	hotelMIS::KDBCon m_con;
	
	map<int,pair<string,string> > m_zdmap;  //<int,<inout_dh,opdate>>

	static CString m_exp;
	static CString m_hotelname;
	static CString m_inout;

	void PrintView();
	static void DrawDC(CDC &memDC, PRNINFO PrnInfo);  //打印回调

public:
	void InitIdle();
	void RefreshRep();
	void RefreshDetails(string inout_dh);

	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnBnClickedPrintButton();
	afx_msg void OnNMClickRepList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkRepList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLvnItemchangedRepList(NMHDR *pNMHDR, LRESULT *pResult);
};
