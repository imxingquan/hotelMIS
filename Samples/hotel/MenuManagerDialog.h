/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		菜单管理
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"
#include "HFoodKindCtrl.h"

#include <map>
using namespace std;
// CMenuManagerDialog 对话框

class CMenuManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(CMenuManagerDialog)

public:
	CMenuManagerDialog(BOOL bRep = FALSE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMenuManagerDialog();

// 对话框数据
	enum { IDD = IDD_MENU_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;
	//CGuiGroupBox m_GuiGroupBoxL;
	
	CGuiComboBoxExt m_GuiComboKind;
	
	CGuiComboBoxExt m_GuiComboUnit;
	CGuiComboBoxExt m_GuiComboCook;
	
	CListCtrl m_GuiListCtrl;
	
	CGuiEdit m_GuiEditName;
	CGuiEdit m_GuiEditPrice;
	CGuiEdit m_GuiEditKind;
	
	CButton m_GuiCheckRepertory; //checkbox
	CButton m_GuiCheckBoxRepNoCalc;

	CGuiButton m_GuiButtonAdd;
	CGuiButton m_GuiCheckAllAdd;
	CGuiButton m_GuiDelButton;
	CGuiEdit m_GuiPYEdit;
	CComboBox m_GuiComboFilter;
	CGuiButton m_GuiPrintMenuBtn;

	//bind var
	CString m_addKind;	//
	BOOL m_bAllAdd;	

	BOOL m_bSpecial;
	BOOL m_bRepNoCalc;
	
	BOOL m_bRepOpen;	//注册表项 用于控制库存
	BOOL m_bRep;
	
	int m_kindPos;
	CString m_foodName;	//菜名
	float m_price;		//价格
	CString m_unit;		//单位
	CString m_cook;		//厨师名
	BOOL m_repertory;	//是否入库
	CString m_py;
		
	CFont m_font;
	hotelMIS::HFoodKindVec m_foodVec;

	map<int,pair<int,int> > m_menuMap;	//map<pos,pair<food_id,kind_id> >
	map<int,pair<int,string> > m_kindMap; //map<pos,pair<kind_id,kind_name> >
	hotelMIS::KDBCon m_con;
	int m_nIndex; //命中pos
	BOOL m_isModify; //当前是否可修改


	//打印
	static CString m_exp;
	static CString m_hotelname;
	
	void 	PrintView();
	static void DrawView(CDC &memDC, PRNINFO PrnInfo);  //打印回调


public:
	void Init();
	void Refresh();
	
	afx_msg void OnBnClickedButtonAdd();
	//afx_msg void OnBnClickedButtonAddKind();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboKind();
	afx_msg void OnPopupModifymenu();
	afx_msg void OnPopupDelmenu();
	afx_msg void OnNMRclickListMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListMenu(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedDelButton();
	afx_msg void OnNMClickListMenu(NMHDR *pNMHDR, LRESULT *pResult);
		
	afx_msg void OnBnClickedCheckRepertory();
	afx_msg void OnBnClickedCheckRepertoryNocalc();
	

	afx_msg void OnCbnSelchangeComboFilter();
	afx_msg void OnBnClickedPrintMenuButton();
	
	// 统计分类
	CComboBox m_totalCombo;
	int m_totalfl;
};
