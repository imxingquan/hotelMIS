//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  RepProdDetailsSearchDlg.cpp
// 
// Desc:  库存明细统计
//
// Author:  邢泉
// 
// Modified: 2006年6月16日 01:15:42
//-----------------------------------------------------------------------
#include "stdafx.h"

#include "RepProdDetailsSearchDlg.h"
#include ".\repproddetailssearchdlg.h"
#include "HFoodKind.h"
#include "HFoodKindCtrl.h"
#include "HBehindRepCtrl.h"
#include "HInOutRepCtrl.h"
#include "HSetHotelPrintMsg.h"
#include "PreParent.h"		//打印预览父窗口

// CRepProdDetailsSearchDlg 对话框
CString CRepProdDetailsSearchDlg::m_hotelname;
CString CRepProdDetailsSearchDlg::m_exp;
CString CRepProdDetailsSearchDlg::m_pname;
IMPLEMENT_DYNAMIC(CRepProdDetailsSearchDlg, CDialog)
CRepProdDetailsSearchDlg::CRepProdDetailsSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRepProdDetailsSearchDlg::IDD, pParent)
	, m_d1(COleDateTime::GetCurrentTime())
	, m_t1(COleDateTime::GetCurrentTime())
	, m_d2(COleDateTime::GetCurrentTime())
	, m_t2(COleDateTime::GetCurrentTime())
	, m_sName(_T(""))
	, m_bRepOpen(FALSE)
	, m_bIsTree(TRUE)
	, m_py(_T(""))
	, m_food_id(-1)
{
}

CRepProdDetailsSearchDlg::~CRepProdDetailsSearchDlg()
{
}

void CRepProdDetailsSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SNAME_EDIT, m_GuiSNameEdit);
	DDX_Control(pDX, IDC_GET_S_BTN, m_GuiGetSBtn);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_GuiSearchBtn);
	DDX_Control(pDX, IDC_PRINT_BTN, m_GuiPrintBtn);
	DDX_Control(pDX, IDC_REP_INOUT_LIST, m_GuiListRep);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_d1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_t1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_d2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_t2);
	DDX_Text(pDX, IDC_SNAME_EDIT, m_sName);
	DDX_Control(pDX, IDC_EDIT_PY, m_GuiEditPy);
	DDX_Control(pDX, IDC_BUTTON_EXT2, m_GuiBtnExt);
	DDX_Control(pDX, IDC_BUTTON_TREE, m_GuiBtnTree);
	DDX_Control(pDX, IDC_BUTTON_LIST, m_GuiBtnList);

	DDX_Control(pDX, IDC_BUTTON_MOVE_RIGHT, m_GuiBtnAdd);
	DDX_Control(pDX, IDC_MENU_TREE, m_GuiMenuTree);
	DDX_Control(pDX, IDC_MENU_LIST, m_GuiMenuList);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
}


BEGIN_MESSAGE_MAP(CRepProdDetailsSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_GET_S_BTN, OnBnClickedGetSBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_PRINT_BTN, OnBnClickedPrintBtn)
	ON_BN_CLICKED(IDC_BUTTON_EXT2, OnBnClickedButtonExt2)
	ON_BN_CLICKED(IDC_BUTTON_TREE, OnBnClickedButtonTree)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnBnClickedButtonList)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_RIGHT, OnBnClickedButtonMoveRight)
	ON_EN_CHANGE(IDC_EDIT_PY, OnEnChangeEditPy)
	ON_NOTIFY(NM_CLICK, IDC_MENU_TREE, OnNMClickMenuTree)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_TREE, OnNMDblclkMenuTree)
	ON_NOTIFY(NM_CLICK, IDC_MENU_LIST, OnNMClickMenuList)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_LIST, OnNMDblclkMenuList)
END_MESSAGE_MAP()


//-----------------------------------------------------------------------------------------------
BOOL CRepProdDetailsSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWinApp* pApp = AfxGetApp();
	m_bRepOpen = pApp->GetProfileInt("Settings", "repOpen",0);
	
	::SetCursor(::LoadCursor(NULL,IDC_WAIT));
	
	m_tip.Create(this);
	m_tip.AddTool(&m_GuiBtnExt,_T("单击+号按钮,可收缩或展开列表"));
	m_tip.AddTool(&m_GuiBtnTree,_T("以树图的方式查看!"));
	m_tip.AddTool(&m_GuiBtnList,_T("以列表的方式查看!"));
	m_tip.AddTool(&m_GuiMenuTree,_T("双击商品可直接查询!"));
	m_tip.AddTool(&m_GuiMenuList,_T("双击商品可直接查询!"));
	m_tip.Activate(TRUE);

	m_GuiGetSBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiSearchBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnExt.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnAdd.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiGetSBtn.ShowText();
	m_GuiSearchBtn.ShowText();
	m_GuiPrintBtn.ShowText();
	m_GuiBtnExt.ShowText();
	m_GuiBtnAdd.ShowText();
	
	//默认禁用 拼音简码
	m_GuiEditPy.EnableWindow(FALSE);
	m_GuiBtnAdd.EnableWindow(FALSE);
	
	InitIdle();
	
	//默认为树列表
	m_GuiBtnTree.SetCheck(1);

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	::SetCursor(::LoadCursor(NULL,IDC_ARROW));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CRepProdDetailsSearchDlg::BuilderHeader()
{
	
	int i = 0;
	int j = 1;
	m_GuiListRep.InsertItem(i,_T(""));

	m_GuiListRep.SetItemText(i,j++,("数量"));
	m_GuiListRep.SetItemText(i,j++,("单价"));
	m_GuiListRep.SetItemText(i,j++,_T("金额"));

	m_GuiListRep.SetItemText(i,j++,("数量"));
	m_GuiListRep.SetItemText(i,j++,_T("单价"));
	m_GuiListRep.SetItemText(i,j++,("金额"));

	m_GuiListRep.SetItemText(i,j++,("数量"));
	m_GuiListRep.SetItemText(i,j++,_T("单价"));
	m_GuiListRep.SetItemText(i,j++,("金额"));

	i++;
	return i;

}

void CRepProdDetailsSearchDlg::InitIdle()
{
// 设置商品列表列
	int nCol = 0;
	m_GuiMenuList.InsertColumn(nCol,_T("编号"),LVCFMT_LEFT,40);
	m_GuiMenuList.InsertColumn(++nCol,_T("名称"),LVCFMT_LEFT,160);
	m_GuiMenuList.InsertColumn(++nCol,_T("单价"),LVCFMT_RIGHT,70);
	m_GuiMenuList.InsertColumn(++nCol,_T("当前库存"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiMenuList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	nCol = 0;
	m_GuiListRep.InsertColumn(nCol,_T("摘要"),LVCFMT_LEFT,40);
	m_GuiListRep.InsertColumn(++nCol,_T(""),LVCFMT_CENTER,50);
	m_GuiListRep.InsertColumn(++nCol,_T("入库"),LVCFMT_RIGHT,60);
	m_GuiListRep.InsertColumn(++nCol,_T(""),LVCFMT_RIGHT,70);

	m_GuiListRep.InsertColumn(++nCol,_T(""),LVCFMT_CENTER,50);
	m_GuiListRep.InsertColumn(++nCol,_T("出库"),LVCFMT_RIGHT,60);
	m_GuiListRep.InsertColumn(++nCol,_T(""),LVCFMT_RIGHT,70);

	m_GuiListRep.InsertColumn(++nCol,_T(""),LVCFMT_CENTER,50);
	m_GuiListRep.InsertColumn(++nCol,_T("统计"),LVCFMT_RIGHT,60);
	m_GuiListRep.InsertColumn(++nCol,_T(""),LVCFMT_RIGHT,70);
	
	BuilderHeader();

				
    ListView_SetExtendedListViewStyleEx(m_GuiListRep.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		
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
		
		if ( m_bRepOpen == FALSE){
			if ( kIt->kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG)
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

	 int i = 0;
	 m_menuListMap.clear();
	 CString t;
	 for ( mIt = m_menuVec.begin(); mIt != m_menuVec.end(); mIt++)
	 {
		 //如果参于库存的 或 参于库存计算的  显示
		 //if ( mIt->repertory_flag == hotelMIS::HMenuInfo::REP_CALC ||
			// mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NOCALC) 
			//{

			//	m_menuListMap.insert(make_pair(i,mIt->food_id));
			//	t.Format("%d",i+1);
			//	//编号
			//	m_GuiMenuList.InsertItem(i,t);
			//	//名称
			//	m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
			//	//单价
			//	t.Format("%.2f",mIt->food_price);
			//	m_GuiMenuList.SetItemText(i,2,t);
			//	//获得当前库存
			//	t.Format("%d",bRepCtrl.getCurRep(mIt->food_id));
			//	m_GuiMenuList.SetItemText(i,3,t);
			//	i++;
		 //}
		 if ( m_bRepOpen == FALSE && mIt->foodKind.kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG){
			//只显示后厨的c
			 continue;
		 }else {
		//过虑套餐和非库存品
		 if ( mIt->bTaocan || mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NO){ 
				 continue;
			}
		 }
	
		 m_menuListMap.insert(make_pair(i,mIt->food_id));
		 t.Format("%d",mIt->food_id);
		 //编号
		 m_GuiMenuList.InsertItem(i,t);
		 //名称
		 m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
		 //单价
		 t.Format("%.2f",mIt->food_price);
		 m_GuiMenuList.SetItemText(i,2,t);
		 //当前库存
		 t.Format("%.2f",bRepCtrl.getCurRep(mIt->food_id));
		 m_GuiMenuList.SetItemText(i,3,t);
		 i++;
	 }
}

void CRepProdDetailsSearchDlg::Refresh()
{
	CString dt1,dt2;
	UpdateData();
	dt1.Format("%s %s",m_d1.Format("%y/%m/%d"),m_t1.Format("%H:%M:%S"));
	dt2.Format("%s %s",m_d2.Format("%y/%m/%d"),m_t2.Format("%H:%M:%S"));
	
	m_exp = dt1 + " 至 " + dt2;
	m_pname.Format("品名:%s 编号:%d  统计日期:%s",m_sName,m_food_id,m_exp);

	hotelMIS::HInOutRepCtrl inOutRepCtrl(m_con.get_con());
	hotelMIS::HInOutRepVec vec ;


	if ( !m_sName.Trim().IsEmpty()){
		vec = inOutRepCtrl.search(m_food_id,dt1.GetBuffer(),dt2.GetBuffer());
		m_pname.Format("品名:%s 编号:%d  统计日期:%s",m_sName,m_food_id,m_exp);
	}
	else{
		vec = inOutRepCtrl.getAllInOutRec(dt1.GetBuffer(),dt2.GetBuffer());
		m_pname.Format("品名:全部 统计日期:%s",m_exp);
	}


	hotelMIS::HInOutRepVec::iterator it;
	//清空
	m_GuiListRep.DeleteAllItems();
	//创建标题并返回下一行
	CString t;
	int i = BuilderHeader();
	int j = 1;
	float inSumNum=0,inSumTotalPrice=0,outSumNum=0,outSumTotalPrice=0;
	for ( it = vec.begin(); it != vec.end(); it++)
	{	
		if ( it->rep_flag == hotelMIS::HInOutRep::IN_REP ){
			m_GuiListRep.InsertItem(i,_T("入库"));
            j = 1;
			t.Format("%.2f",it->food_num); m_GuiListRep.SetItemText(i,j++,t); //数量
			t.Format("%.2f",it->food_price); m_GuiListRep.SetItemText(i,j++,t); //单价
			t.Format("%.2f",it->food_num * it->food_price) ; m_GuiListRep.SetItemText(i,j++,t); //金额
			j += 3;

			//统计
			inSumNum += it->food_num;
			inSumTotalPrice += (it->food_num * it->food_price);	
		}
		else if ( it->rep_flag == hotelMIS::HInOutRep::OUT_REP){
			m_GuiListRep.InsertItem(i,_T("出库"));
			j = 4;
			t.Format("%.2f",it->food_num); m_GuiListRep.SetItemText(i,j++,t); //数量
			t.Format("%.2f",it->food_price); m_GuiListRep.SetItemText(i,j++,t); //单价
			t.Format("%.2f",it->food_num * it->food_price) ; m_GuiListRep.SetItemText(i,j++,t); //金额

			//统计
			outSumNum += it->food_num;
			outSumTotalPrice += (it->food_num * it->food_price);
		}
			
		t.Format("%.2f",it->t_num); m_GuiListRep.SetItemText(i,j++,t); //数量
		t.Format("%.2f",it->t_price); m_GuiListRep.SetItemText(i,j++,t); //单价
		t.Format("%.2f",it->t_sprice) ; m_GuiListRep.SetItemText(i,j++,t); //金额

		i++;

	}
    
	//统计
	if ( !vec.empty() )
	{
		m_GuiListRep.InsertItem(i,_T("合计:"));
		t.Format("%.2f",inSumNum); m_GuiListRep.SetItemText(i,1,t);
		t.Format("%.2f",inSumTotalPrice);m_GuiListRep.SetItemText(i,3,t);

		t.Format("%.2f",outSumNum);m_GuiListRep.SetItemText(i,4,t);
		t.Format("%.2f",outSumTotalPrice);m_GuiListRep.SetItemText(i,6,t);
	}
}

void CRepProdDetailsSearchDlg::OnBnClickedGetSBtn()
{
	// 提取
}

void CRepProdDetailsSearchDlg::OnBnClickedSearchBtn()
{
	// 查询
	/*if ( m_food_id == -1)
		return;*/
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	m_sName = hotelMIS::ReplaceChar(m_sName);
	hotelMIS::HMenuInfo menuInfo = menuInfoCtrl.getMenuInfoByName(m_sName.GetBuffer());
	m_food_id = menuInfo.food_id;
	Refresh();
}

void CRepProdDetailsSearchDlg::OnBnClickedPrintBtn()
{
	//打印
	PrintView();
}


void CRepProdDetailsSearchDlg::OnBnClickedButtonExt2()
{
	HTREEITEM htreeItem = m_GuiMenuTree.GetRootItem();;
	while ( htreeItem != NULL){
		m_GuiMenuTree.Expand(htreeItem,TVE_TOGGLE);
		htreeItem = m_GuiMenuTree.GetNextItem(htreeItem,TVGN_NEXT);
	}
}

void CRepProdDetailsSearchDlg::OnBnClickedButtonTree()
{
	m_bIsTree = TRUE;
	m_GuiMenuTree.ShowWindow(SW_SHOW);

	m_GuiMenuList.ShowWindow(SW_HIDE);
	
	m_GuiEditPy.EnableWindow(FALSE);

	m_GuiBtnExt.EnableWindow(TRUE);
	m_GuiBtnAdd.EnableWindow(FALSE);
}

void CRepProdDetailsSearchDlg::OnBnClickedButtonList()
{
	
	// 单击左边商品列表
	m_bIsTree = FALSE;
	m_GuiMenuTree.ShowWindow(SW_HIDE);

	m_GuiMenuList.ShowWindow(SW_SHOW);
	
	m_GuiEditPy.EnableWindow(TRUE);

	m_GuiBtnExt.EnableWindow(FALSE);
	m_GuiBtnAdd.EnableWindow(FALSE);

}

void CRepProdDetailsSearchDlg::OnBnClickedButtonMoveRight()
{
	hotelMIS::HMenuInfo menuInfo;
	
	if ( m_bIsTree )
	{
		HTREEITEM hItem,hParent;
		if (hItem = m_GuiMenuTree.HitTest(m_point)) {  //检测单击到节点
			hParent = m_GuiMenuTree.GetParentItem(hItem);
			if ( hParent== NULL ){
				return;
			}
			else{
				//选中的是菜谱
				m_food_id = m_GuiMenuTree.GetItemData(hItem);
				m_sName = m_GuiMenuTree.GetItemText(hItem);
			}
		}
	}
	else
	{
		int nPos = m_GuiMenuList.GetSelectionMark();
		if ( nPos != -1 ){
			m_food_id = m_menuListMap[nPos];
			m_sName = m_GuiMenuList.GetItemText(nPos,1);
		}

	}
	GetDlgItem(IDC_SNAME_EDIT)->SetWindowText(m_sName);
	ASSERT( m_food_id != -1);
	
	//传入到 m_sname 中
	Refresh();
}

void CRepProdDetailsSearchDlg::OnEnChangeEditPy()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	
	// 过滤 SQL 特殊字符
	CString py = hotelMIS::ReplaceChar(m_py.Trim());
	
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec vec;
	if ( ! py.IsEmpty() )
		vec = menuInfoCtrl.getMenuByPy(m_py.Trim().GetBuffer());
	else
		vec = m_menuVec;	//从缓存中取出
	
	m_menuListMap.clear();
	m_GuiMenuList.DeleteAllItems();
	
	int i = 0;
	CString t;
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	hotelMIS::HBehindRepCtrl behindRepCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec::iterator it;

	for ( it = vec.begin(); it != vec.end(); it++)
	 {
		if ( m_bRepOpen == FALSE && it->foodKind.kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG){
			//只显示后厨的c
			 continue;
		 }else {
		//过虑套餐和非库存品
		 if ( it->bTaocan || it->repertory_flag == hotelMIS::HMenuInfo::REP_NO){ 
				 continue;
			}
		 }
	
		 m_menuListMap.insert(make_pair(i,it->food_id));
		 t.Format("%d",i+1);
		 //编号
		 m_GuiMenuList.InsertItem(i,t);
		 //名称
		 m_GuiMenuList.SetItemText(i,1,it->food_name.c_str());
		 //单价
		 t.Format("%.2f",it->food_price);
		 m_GuiMenuList.SetItemText(i,2,t);
		 //当前库存
		 t.Format("%.2f",behindRepCtrl.getCurRep(it->food_id));
		 m_GuiMenuList.SetItemText(i,3,t);
		 i++;
	 }
}

//------------------------------------------------------------------------------------------------
void CRepProdDetailsSearchDlg::OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_point = point;
	m_GuiMenuTree.ScreenToClient(&m_point);
	HTREEITEM hItem,hParent;
	if (hItem = m_GuiMenuTree.HitTest(m_point)) {
		hParent = m_GuiMenuTree.GetParentItem(hItem);
		if ( hParent != NULL )
			m_GuiBtnAdd.EnableWindow(TRUE);
	}

}

//------------------------------------------------------------------------------------------------
void CRepProdDetailsSearchDlg::OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnBnClickedButtonMoveRight();

}

void CRepProdDetailsSearchDlg::OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if ( m_GuiMenuList.GetSelectionMark() != -1){
		m_GuiBtnAdd.EnableWindow(TRUE);
	}
}

void CRepProdDetailsSearchDlg::OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnBnClickedButtonMoveRight();
}

BOOL CRepProdDetailsSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( m_tip.m_hWnd != NULL)
	{
		m_tip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//-------------------------------------------------------------------------------------------------------
void CRepProdDetailsSearchDlg::PrintView()
{
	
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListRep.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListRep.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawView, PrnInfo);
	DlgPreView.DoModal();
}

//---------------------------------------------------------------------------------------------------------
void CRepProdDetailsSearchDlg::DrawView(CDC &memDC, PRNINFO PrnInfo)
{
	if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//当前页
	BOOL IsPrint = PrnInfo.IsPrint;		//是否打印
	int nMaxPage = PrnInfo.nCountPage;	//最大页码
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("打印日期:%Y-%m-%d %H:%M:%S");
	csRFinality.Format("第 %i 页/共 %i 页", nCurPage, nMaxPage);

	
	TCHAR szTitle[255];
	wsprintf(szTitle,TEXT("%s 商品出入库明细报表"),m_hotelname.GetBuffer());
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8,rt9,rt10;
	int w1=13,w2=14,w3=18,w4=22,w5=14,w6=18,w7=22,w8=18,w9=22,w10=30;

	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont,PFont, *oldfont;
	//标题字体
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("黑体"));
	//品名字体
	PFont.CreateFont(-MulDiv(11,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("黑体"));
	//细节字体
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("宋体"));
	//粗笔
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

 	DOUBLE xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x方向每英寸像素点数
	DOUBLE yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y方向每英寸像素点数

	DOUBLE xPix = (DOUBLE)xP*10/254;	//每 mm 宽度的像素
	DOUBLE yPix = (DOUBLE)yP*10/254;	//每 mm 高度的像素
	DOUBLE fAdd = 7*yPix;		//每格递增量
	DOUBLE nTop = 32*yPix;		//第一页最上线
	int	  iStart = 0;			//从第几行开始读取
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//非第一页最上线
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 12*xPix;			//最左线
	DOUBLE nRight = xPix*(B5_W-12);	//最右线



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//真正打印部分
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//开始文档打印
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "连接到打印机化败!", "错误", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 30*yPix;		//第一页最上线
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("第 %i 页/共 %i 页", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("打印日期:%Y-%m-%d %H:%M:%S");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//非第一页最上线
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//开始页
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("打印失败!"), "错误", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//打印
				//标题
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10,B5_W*xPix,yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,B5_W*xPix,yPix*40);
			memDC.DrawText(m_pname,&rc,DT_LEFT|DT_VCENTER | DT_SINGLELINE);
		}
		//细节
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//上横线
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+w1*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + w2*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + w3*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + w4*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + w5*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + w6*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);
		

		memDC.DrawText("摘要", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("入库", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("出库", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("统计", &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		memDC.MoveTo(rt4.right, rt1.top);
		memDC.LineTo(rt4.right, rt1.bottom);
		memDC.MoveTo(rt5.right, rt1.top);
		memDC.LineTo(rt5.right, rt1.bottom);
		memDC.MoveTo(rt6.right, rt1.top);
    	memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);
		memDC.MoveTo(rt8.right, rt1.top);
		memDC.LineTo(rt8.right, rt1.bottom);
		memDC.MoveTo(rt9.right, rt1.top);
		memDC.LineTo(rt9.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);
				

		TCHAR sz1[32]={0}, sz2[32]={0}, sz3[32]={0}, sz4[32]={0}, sz5[32]={0},
			sz6[32]={0},sz7[32]={0},sz8[32]={0},sz9[32]={0},sz10[32];
		
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+w1*xPix, nTop+2*fAdd);						
		rt2.SetRect(rt1.right, rt1.top, rt1.right + w2*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + w3*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + w4*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + w5*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + w6*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);
			

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, sz1, 32);
			ListView_GetItemText(hList, i+iStart, 1, sz2, 32);
			ListView_GetItemText(hList, i+iStart, 2, sz3, 32);
			ListView_GetItemText(hList, i+iStart, 3, sz4, 32);
			ListView_GetItemText(hList, i+iStart, 4, sz5, 32);
			ListView_GetItemText(hList, i+iStart, 5, sz6, 32);
			ListView_GetItemText(hList, i+iStart, 6, sz7, 32);
			ListView_GetItemText(hList, i+iStart, 7, sz8, 32);
			ListView_GetItemText(hList, i+iStart, 8, sz9, 32);
			ListView_GetItemText(hList, i+iStart, 9, sz10, 32);


			memDC.DrawText(sz1, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz2, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz3, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz4, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz5, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz6, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz7, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz8, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz9, &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz10, &rt10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
		//	//下横线
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rt8.right, rt1.top);
			memDC.LineTo(rt8.right, rt1.bottom);
			memDC.MoveTo(rt9.right, rt1.top);
			memDC.LineTo(rt9.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
		//	
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;
			rt9.top = rt1.top;
			rt9.bottom = rt1.bottom;
			rt10.top = rt1.top;
			rt10.bottom = rt1.bottom;

			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//结尾
					memDC.MoveTo(rc.left, nTop);
					memDC.LineTo(rc.left, rc.top);
					memDC.MoveTo(rc.right, nTop);
					memDC.LineTo(rc.right, rc.top);
					memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
					memDC.EndPage();
					memDC.SelectObject(oldfont);
				}
			}
			memDC.EndDoc();
		}
	}
	else
	{
		//打印预览
		
		
		//边框线
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	
		
		//标题
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,B5_W*xPix,yPix*40);
			memDC.DrawText(m_pname,&rc,DT_LEFT|DT_VCENTER | DT_SINGLELINE);
		}
		
		//细节
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//上横线
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+w1*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + w2*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + w3*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + w4*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + w5*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + w6*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);
		

		memDC.DrawText("摘要", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("入库", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("出库", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("统计", &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("", &rt10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		memDC.MoveTo(rt4.right, rt1.top);
		memDC.LineTo(rt4.right, rt1.bottom);
		memDC.MoveTo(rt5.right, rt1.top);
		memDC.LineTo(rt5.right, rt1.bottom);
		memDC.MoveTo(rt6.right, rt1.top);
    	memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);
		memDC.MoveTo(rt8.right, rt1.top);
		memDC.LineTo(rt8.right, rt1.bottom);
		memDC.MoveTo(rt9.right, rt1.top);
		memDC.LineTo(rt9.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);
				

		TCHAR sz1[32]={0}, sz2[32]={0}, sz3[32]={0}, sz4[32]={0}, sz5[32]={0},
			sz6[32]={0},sz7[32]={0},sz8[32]={0},sz9[32]={0},sz10[32];
		
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+w1*xPix, nTop+2*fAdd);						
		rt2.SetRect(rt1.right, rt1.top, rt1.right + w2*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + w3*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + w4*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + w5*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + w6*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);
			

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, sz1, 32);
			ListView_GetItemText(hList, i+iStart, 1, sz2, 32);
			ListView_GetItemText(hList, i+iStart, 2, sz3, 32);
			ListView_GetItemText(hList, i+iStart, 3, sz4, 32);
			ListView_GetItemText(hList, i+iStart, 4, sz5, 32);
			ListView_GetItemText(hList, i+iStart, 5, sz6, 32);
			ListView_GetItemText(hList, i+iStart, 6, sz7, 32);
			ListView_GetItemText(hList, i+iStart, 7, sz8, 32);
			ListView_GetItemText(hList, i+iStart, 8, sz9, 32);
			ListView_GetItemText(hList, i+iStart, 9, sz10, 32);


			memDC.DrawText(sz1, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz2, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz3, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz4, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz5, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz6, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz7, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz8, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz9, &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz10, &rt10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
		//	//下横线
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rt8.right, rt1.top);
			memDC.LineTo(rt8.right, rt1.bottom);
			memDC.MoveTo(rt9.right, rt1.top);
			memDC.LineTo(rt9.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
		//	
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;
			rt9.top = rt1.top;
			rt9.bottom = rt1.bottom;
			rt10.top = rt1.top;
			rt10.bottom = rt1.bottom;

			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//结尾

		memDC.MoveTo(rc.left, nTop);
		memDC.LineTo(rc.left, rc.top);
		memDC.MoveTo(rc.right, nTop);
		memDC.LineTo(rc.right, rc.top);
		memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);

		memDC.SelectObject(oldfont);
		memDC.SelectObject(hPenOld);
	}
	TitleFont.DeleteObject();
	DetailFont.DeleteObject();
	cPen.DeleteObject();
}
