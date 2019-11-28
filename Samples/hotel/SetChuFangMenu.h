#pragma once


// CSetChuFangMenu 对话框
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "KDBCon.h"

#include <map>

using namespace std;

class CSetChuFangMenu : public CDialog
{
	DECLARE_DYNAMIC(CSetChuFangMenu)

public:
	CSetChuFangMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetChuFangMenu();

// 对话框数据
	enum { IDD = IDD_SET_CHUFANG_CAI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void Init();
	void Refresh();

	afx_msg void OnBnClickedButtonMoveRight();
	virtual BOOL OnInitDialog();
	CTreeCtrl m_GuiTreeCtrlMenu;
	CListCtrl m_GuiListCtrlChuFangMenu;
	CButton m_GuiButtonMoveR;
	CButton m_GuiButtonMoveL;
	CComboBox m_GuiComboChuFang;
	map<int,int> m_menuCookMap; // map<pos,food_id>
	hotelMIS::KDBCon m_con;
	CPoint m_point,m_point2;
	afx_msg void OnCbnSelchangeComboChufang();
	afx_msg void OnBnClickedButtonMoveLeft();
	afx_msg void OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListChufang(NMHDR *pNMHDR, LRESULT *pResult);
};
