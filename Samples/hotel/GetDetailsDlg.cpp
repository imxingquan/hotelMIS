//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  GetDetailsDlg.h
// 
// Desc: 获取商品名称和编号
//
// Author:  邢泉
//
// Modified: 2006年 06月 15日
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "GetDetailsDlg.h"
#include ".\getdetailsdlg.h"
#include "HFoodKindCtrl.h"

// CGetDetailsDlg 对话框

IMPLEMENT_DYNAMIC(CGetDetailsDlg, CDialog)
CGetDetailsDlg::CGetDetailsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetDetailsDlg::IDD, pParent)
	, m_py(_T(""))
{
}

CGetDetailsDlg::~CGetDetailsDlg()
{
}

void CGetDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EXT, m_GuiBtnExt);
	DDX_Control(pDX, IDC_BUTTON_TREE, m_GuiBtnTree);
	DDX_Control(pDX, IDC_BUTTON_LIST, m_GuiBtnList);

	DDX_Control(pDX, IDC_EDIT_PY, m_GuiEditPy);
	DDX_Control(pDX, IDC_MENU_LIST, m_GuiMenuList);
	DDX_Control(pDX, IDC_MENU_TREE, m_GuiMenuTree);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
}


BEGIN_MESSAGE_MAP(CGetDetailsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_EXT, OnBnClickedButtonExt)
	ON_BN_CLICKED(IDC_BUTTON_TREE, OnBnClickedButtonTree)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnBnClickedButtonList)
	ON_EN_CHANGE(IDC_EDIT_PY, OnEnChangeEditPy)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnBnClickedButtonGet)
	ON_NOTIFY(NM_CLICK, IDC_MENU_LIST, OnNMClickMenuList)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_LIST, OnNMDblclkMenuList)
	ON_NOTIFY(NM_CLICK, IDC_MENU_TREE, OnNMClickMenuTree)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_TREE, OnNMDblclkMenuTree)
END_MESSAGE_MAP()



//-----------------------------------------------------------------------------------------------
void  CGetDetailsDlg::InitIdle()
{
	// 设置商品列表列
	int i = 0;
	m_GuiMenuList.InsertColumn(i,_T("编号"),LVCFMT_LEFT,40);
	m_GuiMenuList.InsertColumn(++i,_T("名称"),LVCFMT_LEFT,160);
	m_GuiMenuList.InsertColumn(++i,_T("单价"),LVCFMT_RIGHT,70);
	m_GuiMenuList.InsertColumn(++i,_T("当前库存"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiMenuList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		
	
	Refresh();

	CString temp;	//temp

	//初始化树
	HTREEITEM hRoot,hChild;
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	//hotelMIS::HFoodKindVec kindVec = foodKindCtrl.getAllKindExceptTs();
	hotelMIS::HFoodKindVec kindVec = foodKindCtrl.getAllKind();
	hotelMIS::HFoodKindVec::iterator kIt;
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec menuVec; 
	hotelMIS::HMenuInfoVec::iterator mIt;
	//hotelMIS::HBehindRepCtrl bRepCtrl(m_con.get_con());
	for ( kIt = kindVec.begin(); kIt != kindVec.end(); kIt++)
	{
		//过滤掉套餐类别
		if ( kIt->kind_id == hotelMIS::HFoodKind::TC ){ 
			 //m_menuVec.erase(mIt);
			 continue;
		}
		//创建根
		hRoot = m_GuiMenuTree.InsertItem(kIt->getKind_name().c_str(),TVI_ROOT);

		m_GuiMenuTree.SetItemData(hRoot,(DWORD)kIt->getKind_id());
		m_GuiMenuTree.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);
		menuVec = menuInfoCtrl.getMenuInfoByKind( kIt->getKind_id() );
		for ( mIt = menuVec.begin(); mIt != menuVec.end(); mIt++)
		{
			//如果参于库存的 或 参于库存计算的  显示
			if ( mIt->repertory_flag == hotelMIS::HMenuInfo::REP_CALC ||
				mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NOCALC) {
					//根据 food_id 求出 要出库产品的库存量及出库价格
					//int nRep = bRepCtrl.getCurRep(mIt->food_id);
					temp.Format("%s",mIt->food_name.c_str());
					hChild = m_GuiMenuTree.InsertItem(temp,hRoot);
					if ( hChild != NULL)
						m_GuiMenuTree.SetItemData(hChild,(DWORD)mIt->food_id);
				}
		}
		m_GuiMenuTree.Expand(hRoot,TVE_EXPAND);
		
	}

	//初始化列表
	hotelMIS::HBehindRepCtrl bRepCtrl(m_con.get_con());

	//记录到类变量中,以便加快速度
	m_menuVec =menuInfoCtrl.getAllMenuInfo();	
	//m_menuVec = hotelMIS::HMenuInfoCtrl::menuInfoFactory();

	 i = 0;
	 m_menuListMap.clear();
	 CString t;
	 for ( mIt = m_menuVec.begin(); mIt != m_menuVec.end(); mIt++)
	 {
		 //如果参于库存的 或 参于库存计算的  显示
		 if ( mIt->repertory_flag == hotelMIS::HMenuInfo::REP_CALC ||
			 mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NOCALC) 
			{

				m_menuListMap.insert(make_pair(i,mIt->food_id));
				t.Format("%d",i+1);
				//编号
				m_GuiMenuList.InsertItem(i,t);
				//名称
				m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
				//单价
				t.Format("%.2f",mIt->food_price);
				m_GuiMenuList.SetItemText(i,2,t);
				//获得当前库存
				t.Format("%d",bRepCtrl.getCurRep(mIt->food_id));
				m_GuiMenuList.SetItemText(i,3,t);
				i++;
		 }
	 }
}

//-------------------------------------------------------------------------------------------------
void  CGetDetailsDlg::Refresh()
{
}

BOOL CGetDetailsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGetDetailsDlg::OnBnClickedButtonExt()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGetDetailsDlg::OnBnClickedButtonTree()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGetDetailsDlg::OnBnClickedButtonList()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGetDetailsDlg::OnEnChangeEditPy()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CGetDetailsDlg::OnBnClickedButtonGet()
{
	// 提取 food_id, 和 food_name

}

void CGetDetailsDlg::OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 单击 List
	*pResult = 0;
}

void CGetDetailsDlg::OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CGetDetailsDlg::OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CGetDetailsDlg::OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

