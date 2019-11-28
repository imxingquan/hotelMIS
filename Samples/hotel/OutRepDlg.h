#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "MyTreeCtrl.h"
#include "KDBCon.h"
#include "HMenuInfoCtrl.h"

#include "HInOutRep.h"

#include <string>
#include <map>
#include <list>
using namespace std;

// COutRegDlg 对话框

class COutRegDlg : public CDialog
{
	DECLARE_DYNAMIC(COutRegDlg)

public:
	COutRegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COutRegDlg();

// 对话框数据
	enum { IDD = IDD_OUTREP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiEdit m_GuiEditPy;
	CGuiButton m_GuiBtnExt;
	CButton m_GuiBtnTree;
	CButton m_GuiBtnList;
	CGuiButton m_GuiBtnAdd;
	CGuiButton m_GuiBtnDel;
	CGuiButton m_GuiBtnInRep;
	CGuiButton m_GuiBtnCancel;
	CGuiButton m_GuiBtnPrint;
	CGuiButton m_GuiBtnPerView;

	CMyTreeCtrl m_GuiMenuTree;
	CListCtrl m_GuiMenuList;
	CListCtrl m_GuiListRep;
	CStatic m_GuiStaticTitle;
	CButton m_GuiCheckSendBefore;
	
	BOOL m_bSendBefore;
	CString m_py;
	CString m_title;
private:
	hotelMIS::KDBCon m_con;
	hotelMIS::HMenuInfoVec m_menuVec; 
	bool m_bIsTree;	
	
	CPoint m_point;
	map<int,int> m_menuListMap; // 左侧菜单列表
	list<hotelMIS::HInOutRep> m_listInOutRep;
	map<int,int> m_repListMap; //右侧列表

	CFont m_font;

	CString m_inout_dh;		//本次操作的账单号
	
	BOOL	m_bRepOpen;		//只用于库存版本
	bool isOut;

//for print
	static CString m_exp;
	static CString m_hotelname;

	void PrintView();
	static void DrawDC(CDC &memDC, PRNINFO PrnInfo);  //打印回调

public:
	//初始化树和列表
	void Init();
	
	void Refresh();

	afx_msg void OnEnChangeEditPy();
	afx_msg void OnBnClickedButtonExt();
	afx_msg void OnBnClickedButtonTree();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnBnClickedButtonMoveRight();
	afx_msg void OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListInrep(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonMoveLeft();
	afx_msg void OnBnClickedButtonInrep();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonPerview();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
