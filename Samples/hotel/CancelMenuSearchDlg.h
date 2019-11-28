#pragma once
#include "atlcomtime.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "KDBCon.h"
// CCancelMenuSearchDlg 对话框

class CCancelMenuSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CCancelMenuSearchDlg)

public:
	CCancelMenuSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCancelMenuSearchDlg();

// 对话框数据
	enum { IDD = IDD_CANCELMENU_DLG };
private:
	hotelMIS::KDBCon m_con;
protected:
	void Init();
	void Refresh();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dTime1;
	COleDateTime m_dTime2;
	CGuiButton m_GuiButtonSearch;
	CGuiButton m_GuiPrintBtn;
	CListCtrl m_GuiListCtrl;
public:
	//print
	static CString m_hotelname;
	static CString m_exp;

	void PrintView();
	
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //打印回调
	
	afx_msg void OnBnClickedButtonCsearch();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedPrintButton();
};
