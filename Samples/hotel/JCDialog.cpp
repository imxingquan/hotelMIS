// JCDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "JCDialog.h"
#include "CancelFoodDlg.h"
#include "HMenuInfoCtrl.h"
#include "HFoodKindCtrl.h"
#include "HRepBdy.h"
#include "HRepastCtrl.h"
#include "HRepDetailsCtrl.h"
#include "HRoomCtrl.h"
#include "CheckNeedPwdDlg.h"
#include "HBeforeRepCtrl.h"
#include "HTableStatusCtrl.h"
#include "ZdyPriceDlg.h"
#include "HFoodKindCtrl.h"
#include "HArrerageCtrl.h"
#include "HAccountCtrl.h"
#include ".\jcdialog.h"
// CJCDialog 对话框


IMPLEMENT_DYNAMIC(CJCDialog, CDialog)
CJCDialog::CJCDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CJCDialog::IDD, pParent)
	, m_num(1)
	, m_subscription(0.0f)
	, m_py(_T(""))
	, m_bIsTree(FALSE)
{
	 //m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_point.x=0;
	m_point.y=0;
}

CJCDialog::CJCDialog(int tableId,int roomId,float subscription ,CWnd* pParent )
: CDialog(CJCDialog::IDD, pParent)
	, m_num(1)
	, m_subscription(subscription)
	, m_tableId (tableId)
	, m_roomId(roomId)
	
	
{
	//m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_point.x=0;
	m_point.y=0;
}

CJCDialog::~CJCDialog()
{
}

void CJCDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX_LEFT, m_GuiGroupBoxLeft);
	DDX_Control(pDX, IDC_GROUPBOX_RIGHT, m_GuiGroupBoxRight);
	DDX_Control(pDX, IDC_LIST_LEFT, m_GuiList);
	DDX_Control(pDX, IDC_TREE_RIGHT, m_GiuiTree);
	DDX_Control(pDX, IDC_NUMBER, m_GuiEditNum);
	DDX_Control(pDX, IDC_SPINNUM, m_GuiSpinNum);
	DDX_Control(pDX, IDC_BUTTON_MOVEL, m_GuiButtonAdd);
	DDX_Control(pDX, IDC_BUTTON_MOVER, m_GuiButtonDel);
	DDX_Text(pDX, IDC_NUMBER, m_num);
	DDX_Control(pDX, IDC_BUTTON_EXPAND, m_GuiBtnExpand);
	DDX_Control(pDX, IDC_BUTTON_PRINTBEHIND, m_GuiButtonPrintBehind);
	DDX_Control(pDX, IDC_OK_BUTTON, m_GuiButtonOk);
	DDX_Control(pDX, IDC_MENU_LIST, m_GuiMenuList);
	DDX_Control(pDX, IDC_BUTTON_TREE, m_GuiBtnTree);
	DDX_Control(pDX, IDC_BUTTON_LIST, m_GuiBtnList);

	DDX_Control(pDX, IDC_EDIT_PY, m_GuiEditPy);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
	DDV_MinMaxInt(pDX,m_num,1,999);
	DDX_Control(pDX, IDC_COMBO1, m_dwCombo);
}


BEGIN_MESSAGE_MAP(CJCDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MOVEL, OnBnClickedButtonAdd)
	
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_RIGHT, OnNMDblclkTreeRight)
	ON_NOTIFY(NM_CLICK, IDC_TREE_RIGHT, OnNMClickTreeRight)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LEFT, OnNMClickListLeft)
	ON_BN_CLICKED(IDC_OK_BUTTON, OnBnClickedOkButton)
	ON_BN_CLICKED(IDC_BUTTON_PRINTBEHIND, OnBnClickedButtonPrintbehind)
	ON_COMMAND(ID_PRINTJCTOCOOK, OnPrintjctocook)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LEFT, OnNMRclickListLeft)
	ON_COMMAND(ID_PRINT_LIANGCAI, OnPrintLiangcai)
	ON_UPDATE_COMMAND_UI(ID_PRINT_LIANGCAI, OnUpdatePrintLiangcai)
	ON_COMMAND(ID_PRINT_MIANDIAN, OnPrintMiandian)
	ON_UPDATE_COMMAND_UI(ID_PRINT_MIANDIAN, OnUpdatePrintMiandian)
	ON_COMMAND(ID_PRINT_RECAI, OnPrintRecai)
	ON_UPDATE_COMMAND_UI(ID_PRINT_RECAI, OnUpdatePrintRecai)
	ON_COMMAND(ID_PRINT_ALLMENU, OnPrintAllmenu)
	ON_COMMAND(ID_CANCELMENU, OnCancelmenu)
//	ON_UPDATE_COMMAND_UI(ID_CANCELMENU, OnUpdateCancelmenu)
	ON_BN_CLICKED(IDC_BUTTON_EXPAND, OnBnClickedButtonExpand)
	ON_COMMAND(ID_DELETEMENU, OnDeletemenu)
	ON_COMMAND(ID_AWARDMENU, OnAwardmenu)
	ON_BN_CLICKED(IDC_BUTTON_TREE, OnBnClickedButtonTree)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnBnClickedButtonList)
	ON_NOTIFY(NM_CLICK, IDC_MENU_LIST, OnNMClickMenuList)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_LIST, OnNMDblclkMenuList)
	ON_EN_CHANGE(IDC_EDIT_PY, OnEnChangeEditPy)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CJCDialog 消息处理程序

void CJCDialog::OnBnClickedButtonAdd()
{
	//  添加用户菜单
	UpdateData();
	

	if ( m_bIsTree )
	{
		HTREEITEM hItem,hParent;
		if (hItem = m_GiuiTree.HitTest(m_point)) 
		{
			hParent = m_GiuiTree.GetParentItem(hItem);
			if ( hParent != NULL )
			{
				int foodId = m_GiuiTree.GetItemData(hItem);
				hotelMIS::HRepBdy repBdy(m_tableId,m_roomId,m_con.get_con());
				hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
				hotelMIS::HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(foodId);
				if ( menuInfo.kind_id == HFoodKind::SYS_MENU::ZDY|| menuInfo.foodKind.zdy_price==1)
				{
					CZdyPriceDlg dlg;
					if (  dlg.DoModal()== IDOK)
						repBdy.addRep(foodId,m_num,m_subscription,dlg.m_zdyPrice); 

				}
				else
					repBdy.addRep(foodId,m_num,m_subscription); 
				
				Refresh();
				m_num = 1;
				UpdateData(FALSE);
				
				//m_GuiButtonAdd.EnableWindow(FALSE);

			}
		}
	}
	else
	{
			int nPos = m_GuiMenuList.GetSelectionMark();
			if ( nPos != -1 )
			{
				int food_id = m_menuListMap[nPos];
				hotelMIS::HRepBdy repBdy(m_tableId,m_roomId,m_con.get_con());
				hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
				hotelMIS::HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(food_id);
				if ( menuInfo.kind_id == HFoodKind::SYS_MENU::ZDY || menuInfo.foodKind.zdy_price==1 )
				{
					CZdyPriceDlg dlg;
					if (  dlg.DoModal()== IDOK)
						repBdy.addRep(food_id,m_num,m_subscription,dlg.m_zdyPrice); 

				}	
				else
					repBdy.addRep(food_id,m_num,m_subscription); 

				Refresh();
				m_num = 1;
				UpdateData(FALSE);
				//m_GuiButtonAdd.EnableWindow(FALSE);
			}
			else
			  MessageBox(_T("请先选择要点的菜！"));
			
	}
	m_py.Empty();
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT_PY)->SetFocus();
}

void CJCDialog::Refresh()
{
	m_GuiList.DeleteAllItems();
	//刷新用户就餐列表
	hotelMIS::HRepastCtrl repCtrl(m_con.get_con());
	hotelMIS::HRepDetailsCtrl repDeCtrl(m_con.get_con());
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());

	hotelMIS::HRepDetailsVec vec = repDeCtrl.getAllDetails(repCtrl.getAccountId(m_tableId,m_roomId));
	hotelMIS::HRepDetailsVec::iterator it;
	
	

	int i = 0;
	CString cnt;
	m_repMap.clear();
	m_repPosMap.clear();
	
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_repMap.insert(make_pair(i,make_pair(it->account_id,it->food_id))); //先保留
		m_repPosMap.insert(make_pair(i,it->id));
		cnt.Format("%d",it->food_id);
		m_GuiList.InsertItem(i,cnt);
		m_GuiList.SetItemText(i,1,it->food_name.c_str());
		cnt.Format("%.2f",it->food_price);
		m_GuiList.SetItemText(i,2,cnt);
		cnt.Format("%d",it->food_num);
		m_GuiList.SetItemText(i,3,cnt);
		m_GuiList.SetItemText(i,4,it->food_unit.c_str());
	
		m_GuiList.SetItemText(i,5,foodKindCtrl.getKind(it->kind_id).kind_name.c_str());
		m_GuiList.SetItemText(i,6,it->ck_name.c_str());
		i++;
	}
	
	m_GuiList.InsertItem(i,_T("合计:"));
	hotelMIS::HTotalPair t = repDeCtrl.getAllPrice(repCtrl.getAccountId(m_tableId,m_roomId));
	cnt.Format("%.2f",t.first + t.second);
	m_GuiList.SetItemText(i,2,cnt);

	if ( vec.empty())
		m_GuiButtonPrintBehind.EnableWindow(FALSE);
	else
		m_GuiButtonPrintBehind.EnableWindow(TRUE);

}

//void CJCDialog::OnBnClickedButtonDel()
//{
//	
//	int res = MessageBox(_T("确定要删除?"),_T("警告"),MB_YESNO|MB_ICONWARNING);
//	if ( res == IDNO )
//		return ;
//	
//	int nPos = -1;
//	if ( (nPos = m_GuiList.GetSelectionMark()) != -1)
//	{
//		UpdateData(TRUE);
//		hotelMIS::HRepBdy repBdy(m_tableId,m_roomId,m_con.get_con());
//		repBdy.delRep(m_repPosMap[m_leftPos],m_num,m_repMap[m_leftPos].first,m_repMap[m_leftPos].second);
//		Refresh();
//		m_num = 1;
//		UpdateData(FALSE);
//		m_GuiButtonDel.EnableWindow(FALSE);
//	}
//}

void CJCDialog::OnNMDblclkTreeRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	/*DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_point = point;*/
	OnBnClickedButtonAdd();
	*pResult = 0;
}

void CJCDialog::InitIdle()
{
	//初始化用户就餐列表
	int i = 0;
	m_GuiList.InsertColumn(i,_T("编号"),LVCFMT_LEFT,40);
	m_GuiList.InsertColumn(++i,_T("名称"),LVCFMT_LEFT,130);
	m_GuiList.InsertColumn(++i,_T("价格"),LVCFMT_RIGHT,75);
	m_GuiList.InsertColumn(++i,_T("数量"),LVCFMT_CENTER,35);
	m_GuiList.InsertColumn(++i,_T("单位"),LVCFMT_CENTER,40);
	m_GuiList.InsertColumn(++i,_T("类别"),LVCFMT_LEFT,70);
	m_GuiList.InsertColumn(++i,_T("厨师"),LVCFMT_LEFT,60);
	ListView_SetExtendedListViewStyleEx(m_GuiList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	i = 0;
	m_GuiMenuList.InsertColumn(i,_T("编号"),LVCFMT_LEFT,40);
	m_GuiMenuList.InsertColumn(++i,_T("名称"),LVCFMT_LEFT,160);
	m_GuiMenuList.InsertColumn(++i,_T("单价"),LVCFMT_RIGHT,65);
	m_GuiMenuList.InsertColumn(++i,_T("类别"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiMenuList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	
	FillTreeMenu();
	FillListMenu();

	 //default select one
	/* if ( !m_menuListMap.empty() ){
		 m_GuiMenuList.SetSelectionMark(0);
		  m_GuiMenuList.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
	 }*/
	 //默认为树列表
	//m_GuiBtnTree.SetCheck(1);
	 m_GuiBtnList.SetCheck(1);
	 m_py.Empty();


	


	 UpdateData(FALSE);
	

}

void CJCDialog::FillTreeMenu()
{
	m_GiuiTree.DeleteAllItems();
	
	//初始化菜单列表
	//初始化树
	HTREEITEM hRoot,hChild;
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());	
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	
	hotelMIS::HFoodKindVec kindVec = foodKindCtrl.getAllKind();
	hotelMIS::HMenuInfoVec::const_iterator mIt;
	hotelMIS::HFoodKindVec::iterator kIt;
	hotelMIS::HMenuInfoVec menuVec; 
	

	CString temp;

	for ( kIt = kindVec.begin(); kIt != kindVec.end(); kIt++)
	{
		/*if (kIt->kind_flag == hotelMIS::HFoodKind::HOUCHU_FLAG ){ 
			 continue;
		}*/

		hRoot = m_GiuiTree.InsertItem(kIt->getKind_name().c_str(),TVI_ROOT);

		m_GiuiTree.SetItemData(hRoot,(DWORD)kIt->getKind_id());
		m_GiuiTree.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

		menuVec = menuInfoCtrl.getMenuInfoByKind(kIt->getKind_id());

		for ( mIt = menuVec.begin(); mIt != menuVec.end(); mIt++)
		{
			temp.Format("%s %d  ￥%.2f",mIt->food_name.c_str(),mIt->food_id,mIt->food_price);
			hChild = m_GiuiTree.InsertItem(temp,hRoot);
			if ( hChild != NULL)
				m_GiuiTree.SetItemData(hChild,(DWORD)mIt->food_id);
		}
		m_GiuiTree.Expand(hRoot,TVE_EXPAND);
	}	

	
}

void CJCDialog::FillListMenu()
{
	m_GuiMenuList.DeleteAllItems();
		//初始化列表
	hotelMIS::HBeforeRepCtrl befCtrl(m_con.get_con());
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	m_menuVec =menuInfoCtrl.getAllMenuInfo();	

	int i = 0;
	m_menuListMap.clear();
	CString t;
	hotelMIS::HMenuInfoVec::const_iterator mIt;
	for ( mIt = m_menuVec.begin(); mIt != m_menuVec.end(); mIt++)
	 {
		 //过虑套餐和后厨商品
		 /*if (  menuInfoCtrl.isHouChu(mIt->foodKind.kind_flag) ){ 
				 continue;
			}*/

		 m_menuListMap.insert(make_pair(i,mIt->food_id));
		 t.Format("%d",mIt->food_id);
		 //编号
		 m_GuiMenuList.InsertItem(i,t);
		 //名称
		 m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
		 //单价
		 t.Format("%.2f",mIt->food_price);
		 m_GuiMenuList.SetItemText(i,2,t);
		 //类别
		 t.Format("%s",mIt->foodKind.kind_name.c_str());
		 m_GuiMenuList.SetItemText(i,3,t);
		 i++;
	 }
}

BOOL CJCDialog::OnInitDialog()
{
	::SetCursor(::LoadCursor(NULL,IDC_WAIT));
	CDialog::OnInitDialog();
	
	//设置提示

	m_tip.Create(this);
	m_tip.AddTool(&m_GuiBtnExpand,_T("单击+号按钮,可收缩或展开列表"));
	m_tip.AddTool(&m_GuiBtnTree,_T("以树图的方式查看!"));
	m_tip.AddTool(&m_GuiBtnList,_T("以列表的方式查看!"));
	m_tip.Activate(TRUE);

	m_GuiButtonAdd.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonDel.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonPrintBehind.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonOk.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnExpand.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiButtonAdd.ShowText();
	m_GuiButtonDel.ShowText();
	m_GuiBtnExpand.ShowText();
	m_GuiButtonPrintBehind.ShowText();
	m_GuiButtonOk.ShowText();

	m_GuiSpinNum.SetRange(1,100);
	//m_GuiButtonAdd.EnableWindow(FALSE);
	m_GuiButtonDel.EnableWindow(FALSE);
	
	//m_GuiMenuList.ShowWindow(SW_HIDE);
	m_GiuiTree.ShowWindow(SW_HIDE);
    
	InitIdle();

	Refresh();

	HRoomCtrl hRoomCtrl(m_con.get_con());
	CString t;
	t.Format("餐厅:%s 号-餐桌号:%d 号",hRoomCtrl.getRoomName(m_roomId).c_str(),m_tableId);
	
	m_GuiGroupBoxLeft.SetCaption(t);

	//初始化挂账单位
	hotelMIS::HArrerageZHCtrl hArrZHCtrl(m_con.get_con());
	hotelMIS::HArrerageZHVec zhVec = hArrZHCtrl.getAll();
	hotelMIS::HArrerageZHVec::iterator it;
	int pos =m_dwCombo.AddString(_T("无"));
	m_dwCombo.SetItemData(pos,0);
	
	hotelMIS::HAccountCtrl hAccCtrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	int arid = hAccCtrl.getAccount(accountId).arid;
	if (arid==0) m_dwCombo.SetCurSel(0);
	for(it = zhVec.begin(); it!= zhVec.end(); it++)
	{
		pos = m_dwCombo.AddString(it->guest_name.c_str());
		m_dwCombo.SetItemData(pos,it->arid);
		
		if (arid==it->arid)
			m_dwCombo.SetCurSel(pos);
	}
	


	UpdateData(FALSE);

	::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CJCDialog::OnNMClickTreeRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_point = point;
	m_GiuiTree.ScreenToClient(&m_point);
	/*HTREEITEM hItem,hParent;
	if (hItem = m_GiuiTree.HitTest(m_point)) {
		hParent = m_GiuiTree.GetParentItem(hItem);
		if ( hParent != NULL )
			m_GuiButtonAdd.EnableWindow(TRUE);
	}*/
}


void CJCDialog::OnNMClickListLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//根据数量删除所点的菜谱
	
	/*int nPos = -1;
	if ((nPos = m_GuiList.GetSelectionMark()) != -1 ){
		m_GuiButtonDel.EnableWindow(TRUE);
	}*/
	*pResult = 0;
}

void CJCDialog::OnBnClickedOkButton()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CJCDialog::OnBnClickedButtonPrintbehind()
{
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_FENCHUPRINT);
	CPoint pt = ::GetMessagePos();
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);
}


void CJCDialog::FengChuPrintAll() //分厨打印全部
{
	CWinApp* pApp = AfxGetApp();
	BOOL bFenchu = pApp->GetProfileInt("Print", "bFenchu",0);
	if ( !bFenchu ){ //如果没有分厨
		PrintBehind();
	}
	else
	{
		//分厨打印
		BOOL bLiangCai = pApp->GetProfileInt("Print","bLiangCai",0);
		if ( bLiangCai){
			PrintLiangCai();
		}
		BOOL bMianDian = pApp->GetProfileInt("Print","bMianDian",0);
		if ( bMianDian){
			PrintMianDian();
		}
		BOOL bReCai = pApp->GetProfileInt("Print","bReCai",0);
		if ( bReCai){
			PrintReCai();
		}
	}
}

void CJCDialog::Print(CString pName,HDC hdc,FOOD_COOK food_cook)
{
	hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	hotelMIS::HRepDetailsVec vec = repDetailsCtrl.getFengchu(accountId,food_cook);
	hotelMIS::HRepDetailsVec::iterator it;
	if ( vec.empty()) //没有菜不用打印
		return ;

	CDC *dc = new CDC();
	dc->Attach(hdc);
	DOCINFO di;
	::ZeroMemory(&di,sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName= pName;
	dc->StartDoc(&di);
	dc->StartPage();
	//开始打印
		
	dc->SetMapMode(MM_LOMETRIC); //设置为厘米单位
	dc->SetTextAlign(TA_LEFT);
	
	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("宋体"));
	dc->SetTextColor(RGB(0,0,0));
	pOldFont = dc->SelectObject(&font);

	int xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",5);
	int yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	yPos = -yPos;
	int col_2_w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	int col_3_w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	int col_4_w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	int lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	int restline = pApp->GetProfileInt("Settings","PrintRestLine",6);

	CString acc;
	CTime t1=CTime::GetCurrentTime();
	
	TEXTMETRIC lpMetrics;
	
	dc->GetTextMetrics(&lpMetrics);
	int fHeight = lpMetrics.tmHeight + lineHeight;
	int n =2;
	/*acc.Format("%s",hotelMsg.hotelname.c_str());
	dc->TextOut(xPos,yPos,acc);*/
	acc.Format("--------------%s--------------",pName);
	dc->TextOut(xPos,yPos-fHeight,acc);

	HRoomCtrl roomCtrl(m_con.get_con());
	
	hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
	string tableName = tableStatusCtrl.getTableName(m_tableId,m_roomId);
	
	
	if( !tableName.empty())
		acc.Format("%s-%d号桌[%s]",roomCtrl.getRoomName(m_roomId).c_str(),m_tableId,tableName.c_str());
	else
		acc.Format("%s-%d号桌",roomCtrl.getRoomName(m_roomId).c_str(),m_tableId);

	dc->TextOut(xPos,yPos-fHeight*n++,acc);

	acc.Format("账单号: %s ",accountId.c_str());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	acc.Format("日期: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	
	dc->TextOut(xPos,yPos-fHeight*5,_T("菜名"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*n,_T("单价"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*n,_T("数量"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*n++,_T("总价"));
		
	CString cnt;
	float ys  = 0.0f;
	int len = 0;

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//菜名
		
		cnt.Format("%.2f",it->food_price);
		
		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;

		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//单价
		cnt.Format("%d",it->food_num);
		//dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//数量
		cnt.Format("%.2f",it->food_price*it->food_num);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //总价
		
		ys += it->food_num * it->food_price;
        n++;
	}
	
	//float ys = repDetailsCtrl.getAllPrice(accountId);
	
	cnt.Format("%.2f",ys);	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("合计:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	n++;	
	dc->SetTextAlign(TA_LEFT);
	COleDateTime t = COleDateTime::GetCurrentTime();
	acc.Format("-----------%-2d:%-2d:%-2d-----------",t.GetHour(),t.GetMinute(),t.GetSecond());
	dc->TextOut(xPos,yPos - fHeight*n,acc);

	n = n+restline;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);

	//结束打印
	dc->EndPage();
	dc->EndDoc();
	delete dc;
}


BOOL CJCDialog::PrintBehind()
{
	//打印到后厨
	CWinApp* pApp = AfxGetApp();
	CString sPrint = pApp->GetProfileString("Print","PrintBehind");
	HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
	if ( hdc != NULL){
		Print(_T("厨房菜单"),hdc,FOOD_COOK::ALL);
		return TRUE;
	}
    return FALSE;    
}

BOOL CJCDialog::PrintLiangCai()
{//打印凉菜

	CWinApp* pApp = AfxGetApp();
	CString sPrint = pApp->GetProfileString("Print","PrintLiangCai");
	HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
	if ( hdc != NULL){
		Print(_T("凉菜菜单"),hdc,FOOD_COOK::LIANGCAI);
		return TRUE;
	}
    return FALSE;

}

BOOL CJCDialog::PrintMianDian()
{
	//打印面点
	CWinApp* pApp = AfxGetApp();
	CString sPrint = pApp->GetProfileString("Print","PrintMianDian");
	HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
	if ( hdc != NULL){
		Print(_T("面案菜单"),hdc,FOOD_COOK::MIANDIAN);
		return TRUE;
	}
    return FALSE;

}

BOOL CJCDialog::PrintReCai()
{
	//打印热菜
	CWinApp* pApp = AfxGetApp();
	CString sPrint = pApp->GetProfileString("Print","PrintReCai");
	HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
	if ( hdc != NULL){
		Print(_T("热菜菜单"),hdc,FOOD_COOK::RECAI);
		return TRUE;
	}
    return FALSE;
	
}
void CJCDialog::OnPrintjctocook()
{
	// TODO: 将选中的菜打印到厨房
	//根据 id 打印一个菜到后厨

	POSITION pos = m_GuiList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		::LoadCursor(NULL,IDC_WAIT);
		vector<int> vecItem;
		while (pos)
		{
			int nItem = m_GuiList.GetNextSelectedItem(pos);
			vecItem.push_back(m_repPosMap[nItem]);
			TRACE("Item %d was selected! id = %d \n", nItem,m_repPosMap[nItem]);
			// you could do your own processing on nItem here
		}
		PrintSelectToCook(vecItem); //打印选中的到后厨

		::LoadCursor(NULL,IDC_ARROW);
		MessageBox(_T("打印完毕!"));
	}
}

void CJCDialog::Print(vector<HRepDetails> &vec,HDC hdc,CString pName,FOOD_COOK food_cook)
{
	vector<HRepDetails>::iterator tit ;
	/*for ( tit = vec.begin(); tit != vec.end(); tit++)
	{
		if ( tit->food_cook == food_cook )
			break;
	}
	if ( tit == vec.end() )
		return;*/

	CDC *dc = new CDC();
	dc->Attach(hdc);
	DOCINFO di;
	::ZeroMemory(&di,sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName= pName;
	dc->StartDoc(&di);
	dc->StartPage();
	//开始打印
		
	dc->SetMapMode(MM_LOMETRIC); //设置为厘米单位
	dc->SetTextAlign(TA_LEFT);
	
	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("宋体"));
	dc->SetTextColor(RGB(0,0,0));
	pOldFont = dc->SelectObject(&font);

	int xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",30);
	int yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	yPos = -yPos;
	int col_2_w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	int col_3_w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	int col_4_w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	int lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	int restline = pApp->GetProfileInt("Settings","PrintRestLine",6);

	CString acc;
	CTime t1=CTime::GetCurrentTime();
	
	TEXTMETRIC lpMetrics;
	
	dc->GetTextMetrics(&lpMetrics);
	int fHeight = lpMetrics.tmHeight + lineHeight;
	int n=2;
	/*acc.Format("%s",hotelMsg.hotelname.c_str());
	dc->TextOut(xPos,yPos,acc);*/
	acc.Format("--------------%s--------------",pName);
	dc->TextOut(xPos,yPos-fHeight,acc);

	HRoomCtrl roomCtrl(m_con.get_con());
	acc.Format("%s-%d号桌",roomCtrl.getRoomName(m_roomId).c_str(),m_tableId);
	dc->TextOut(xPos,yPos-fHeight*n++,acc);

	acc.Format("账单号: %s ",vec.begin()->account_id.c_str());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	acc.Format("日期: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	
	dc->TextOut(xPos,yPos-fHeight*5,_T("菜名"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*n,_T("单价"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*n,_T("数量"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*n++,_T("总价"));
		
	CString cnt;
	float sum = 0.0f;
	int len  = 0;
	for ( vector<HRepDetails>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		/*if ( it->food_cook == food_cook)
		{*/
			dc->SetTextAlign(TA_LEFT);
			dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//菜名
			
			cnt.Format("%.2f",it->food_price);
		
		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;

			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//单价
			cnt.Format("%d",it->food_num);
			//dc->SetTextAlign(TA_LEFT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//数量
			cnt.Format("%.2f",it->food_price*it->food_num);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //总价
			sum += it->food_num * it->food_price;
			n++;
		//}
		
	}
	
	//float ys = repDetailsCtrl.getAllPrice(accountId);
	cnt.Format("%.2f",sum);	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("合计:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	n++;	
	dc->SetTextAlign(TA_LEFT);
	COleDateTime t = COleDateTime::GetCurrentTime();
	acc.Format("-----------%-2d:%-2d:%-2d-----------",t.GetHour(),t.GetMinute(),t.GetSecond());
	dc->TextOut(xPos,yPos - fHeight*n,acc);

	n = n+restline;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);

	//结束打印
	dc->EndPage();
	dc->EndDoc();
	delete dc;	
}

void CJCDialog::PrintSelectToCook(vector<int> &vecItem)
{
	//根据所选的菜分别打印到厨房,如果是分厨的前提下
	hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	vector<HRepDetails> vec = repDetailsCtrl.getDetailsByIdVec(vecItem);
	CWinApp* pApp = AfxGetApp();
	BOOL bFenchu = pApp->GetProfileInt("Print", "bFenchu",0);
	if ( !bFenchu ){ //如果没有分厨
		CString sPrint = pApp->GetProfileString("Print","PrintBehind");
		HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
		if ( hdc != NULL)
			Print(vec,hdc,_T("厨房菜单"),FOOD_COOK::ALL);
	}
	else
	{
		//分厨打印
		BOOL bLiangCai = pApp->GetProfileInt("Print","bLiangCai",0);
		if ( bLiangCai){
			CString sPrint = pApp->GetProfileString("Print","PrintLiangCai");
			HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
			if ( hdc != NULL)
				Print(vec,hdc,_T("凉菜厨房"),FOOD_COOK::LIANGCAI);
		}
		BOOL bMianDian = pApp->GetProfileInt("Print","bMianDian",0);
		if ( bMianDian){
			CString sPrint = pApp->GetProfileString("Print","PrintMianDian");
			HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
			if ( hdc != NULL)
				Print(vec,hdc,_T("面案厨房"),FOOD_COOK::MIANDIAN);
		}
		BOOL bReCai = pApp->GetProfileInt("Print","bReCai",0);
		if ( bReCai){
			CString sPrint = pApp->GetProfileString("Print","PrintReCai");
			HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
			if ( hdc != NULL)
				Print(vec,hdc,_T("热菜厨房"),FOOD_COOK::RECAI);
		}
	}
}

void CJCDialog::OnNMRclickListLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//弹出右键菜单
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiList.ScreenToClient(&point);
	int nPos = m_GuiList.HitTest(point);
	if ( nPos != -1 && nPos != m_repPosMap.size()) {
		CString str = m_GuiList.GetItemText(nPos,0);	
		
		CMenu menu;
		CPoint pt = ::GetMessagePos();
		menu.LoadMenu(IDR_POPUP_JCPRINT);
		hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
		int id = m_repPosMap[nPos];
		if ( repDetailsCtrl.getDetailsById(id).food_num < 0 ){
			menu.EnableMenuItem(ID_CANCELMENU,MF_BYCOMMAND|MF_GRAYED);
			//menu.EnableMenuItem(ID_DELETEMENU,MF_BYCOMMAND|MF_GRAYED);
			menu.EnableMenuItem(ID_AWARDMENU,MF_BYCOMMAND|MF_GRAYED);   //退菜不能在赠送了
		}
		if ( repDetailsCtrl.getFoodStatus(id) == HRepDetails::FOOD_STATUS::FOOD_AWARD){
			menu.EnableMenuItem(ID_AWARDMENU,MF_BYCOMMAND|MF_GRAYED);
		}
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);
	}
	*pResult = 0;
}

void CJCDialog::OnPrintLiangcai()
{
	// TODO: 右键菜单
	::LoadCursor(NULL,IDC_WAIT);
	CWinApp* pApp = AfxGetApp();
	BOOL bLiangCai = pApp->GetProfileInt("Print","bLiangCai",0);
	if ( bLiangCai){
			PrintLiangCai();
	}
	::LoadCursor(NULL,IDC_ARROW);
	MessageBox(_T("打印完毕!"));
}

void CJCDialog::OnUpdatePrintLiangcai(CCmdUI *pCmdUI)
{
	// TODO: 右键菜单
	CWinApp* pApp = AfxGetApp();
	BOOL bLiangCai = pApp->GetProfileInt("Print","bLiangCai",0);
	pCmdUI->Enable(bLiangCai);
}

void CJCDialog::OnPrintMiandian()
{
	// TODO: 右键菜单
	::LoadCursor(NULL,IDC_WAIT);
	CWinApp* pApp = AfxGetApp();
	BOOL bMianDian = pApp->GetProfileInt("Print","bMianDian",0);
		if ( bMianDian){
			PrintMianDian();
		}
	::LoadCursor(NULL,IDC_ARROW);
	MessageBox(_T("打印完毕!"));
}

void CJCDialog::OnUpdatePrintMiandian(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CWinApp* pApp = AfxGetApp();
BOOL bMianDian = pApp->GetProfileInt("Print","bMianDian",0);
pCmdUI->Enable(bMianDian);
}

void CJCDialog::OnPrintRecai()
{
	// TODO: 右键菜单
	::LoadCursor(NULL,IDC_WAIT);
	CWinApp* pApp = AfxGetApp();
	BOOL bReCai = pApp->GetProfileInt("Print","bReCai",0);
		if ( bReCai){
			PrintReCai();
		}
	::LoadCursor(NULL,IDC_ARROW);
	MessageBox(_T("打印完毕!"));
}

void CJCDialog::OnUpdatePrintRecai(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CWinApp* pApp = AfxGetApp();
	BOOL bReCai = pApp->GetProfileInt("Print","bReCai",0);
	pCmdUI->Enable(bReCai);
}

void CJCDialog::OnPrintAllmenu()
{
	// TODO: 分厨打印全部
	::LoadCursor(NULL,IDC_WAIT);
	FengChuPrintAll();
	::LoadCursor(NULL,IDC_ARROW);
	MessageBox(_T("打印完毕!"));
}


void CJCDialog::OnCancelmenu()
{
	// TODO: 顾客退菜
	int nPos = m_GuiList.GetSelectionMark();
	if ( nPos != -1)
	{
		//将可以退菜的数量传给 对话框
		CCancelFoodDlg dlg;
		hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
		hotelMIS::HRepDetails repDetails = repDetailsCtrl.getDetailsById(m_repPosMap[nPos]);
		int cancelNum = repDetailsCtrl.getCancelNum(repDetails.account_id,repDetails.food_id);
		dlg.m_nNum = cancelNum;
		dlg.m_cancelSnum.Format("可以退菜的数量: %d ", cancelNum);
		if ( dlg.DoModal() == IDOK){
			repDetailsCtrl.foodCancel(m_repPosMap[nPos],dlg.m_cancelNum,dlg.m_cancelMsg.GetBuffer());
			hotelMIS::HRepBdy repBdy(m_tableId,m_roomId,m_con.get_con());
			repBdy.revert(repDetails.food_id,dlg.m_cancelNum);
			Refresh();
		}
	}
}


void CJCDialog::OnBnClickedButtonExpand()
{
	// TODO: //收缩
	HTREEITEM htreeItem = m_GiuiTree.GetRootItem();;
	while ( htreeItem != NULL){
		m_GiuiTree.Expand(htreeItem,TVE_TOGGLE);
		htreeItem = m_GiuiTree.GetNextItem(htreeItem,TVGN_NEXT);
	}
}

void CJCDialog::OnDeletemenu()
{
	// TODO: 删除菜
	int nPos = m_GuiList.GetSelectionMark();
	
	if ( nPos != -1)
	{
		int res = MessageBox(_T("确定要删除?"),_T("警告"),MB_YESNO|MB_ICONWARNING);
		if ( res == IDNO )
			return ;

		UpdateData(TRUE);
		hotelMIS::HRepBdy repBdy(m_tableId,m_roomId,m_con.get_con());
		//repBdy.delRep(m_repMap[m_leftPos].first,m_repMap[m_leftPos].second,m_num);
		repBdy.delRep(m_repPosMap[nPos],m_num,m_repMap[nPos].first,m_repMap[nPos].second);
		Refresh();
		m_num = 1;
		UpdateData(FALSE);
	}
}

void CJCDialog::OnAwardmenu()
{
	// 右键菜单
	// 赠送菜
	int nPos = m_GuiList.GetSelectionMark();
	if ( nPos != -1)
	{
		CWinApp* pApp = AfxGetApp();
		BOOL bNeedPwd = pApp->GetProfileInt("Settings","bNeedAwardPwd",1); 
		if ( bNeedPwd){
			CCheckNeedPwdDlg dlg;
			dlg.DoModal();
			if ( dlg.m_pwdIsRight == TRUE){
				// 赠菜
				hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
				int id = m_repPosMap[nPos];
				hotelMIS::HRepDetails repDetails = repDetailsCtrl.getDetailsById(id);
				repDetailsCtrl.foodAward(id);
				Refresh();
			}
		}
		else{
			//不需要验证密码
			// 赠菜
				hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
				int id = m_repPosMap[nPos];
				hotelMIS::HRepDetails repDetails = repDetailsCtrl.getDetailsById(id);
				repDetailsCtrl.foodAward(id);
				Refresh();
		}
	}
}

void CJCDialog::OnBnClickedButtonTree()
{
	m_bIsTree = TRUE;
	m_GiuiTree.ShowWindow(SW_SHOW);

	
	m_GuiMenuList.ShowWindow(SW_HIDE);
	
	GetDlgItem(IDC_EDIT_PY)->EnableWindow(FALSE);

	m_GuiBtnExpand.EnableWindow(TRUE);
	m_GuiButtonDel.EnableWindow(FALSE);
	//m_GuiButtonAdd.EnableWindow(FALSE);
	//FillTreeMenu();
}

void CJCDialog::OnBnClickedButtonList()
{
	m_bIsTree = FALSE;
	m_GiuiTree.ShowWindow(SW_HIDE);

	m_GuiMenuList.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_PY)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_PY)->EnableWindow(TRUE);

	m_GuiBtnExpand.EnableWindow(FALSE);
	//FillListMenu();
}

void CJCDialog::OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;
	/*if ( m_GuiMenuList.GetSelectionMark() != -1)
		m_GuiButtonAdd.EnableWindow(TRUE);*/
}

void CJCDialog::OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnBnClickedButtonAdd();
}

void CJCDialog::OnEnChangeEditPy()
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
	hotelMIS::HBeforeRepCtrl bRepCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec::iterator it;
	
	for ( it = vec.begin(); it != vec.end(); it++)
	 {
		//过虑套餐和后厨商品
		 /*if (  menuInfoCtrl.isHouChu(it->foodKind.kind_flag)){ 
				 continue;
		 }*/
	
		 m_menuListMap.insert(make_pair(i,it->food_id));
		 t.Format("%d",it->food_id);
		 //编号
		 m_GuiMenuList.InsertItem(i,t);
		 //名称
		 m_GuiMenuList.SetItemText(i,1,it->food_name.c_str());
		 //单价
		 t.Format("%.2f",it->food_price);
		 m_GuiMenuList.SetItemText(i,2,t);
		
		 t.Format("%s",it->foodKind.kind_name.c_str());
		 m_GuiMenuList.SetItemText(i,3,t);
		 i++;
	 }
	 if ( !m_menuListMap.empty() ){
		 m_GuiMenuList.SetSelectionMark(0);
		 m_GuiMenuList.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
	 }

}

BOOL CJCDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( m_tip.m_hWnd != NULL)
	{
		m_tip.RelayEvent(pMsg);
	}
 /*if (m_hAccelTable) {
      if (::TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg)) {
         return(TRUE);
      }
   }*/

	if(pMsg->message==WM_KEYDOWN) {  
		switch(pMsg->wParam)
		{
		case VK_F2:
			{
				m_GuiEditPy.SetFocus();
				m_GuiEditPy.SetSel(MAKELONG(0,-1));
			}
			break;
		case VK_F3:
			{
				m_GuiEditNum.SetFocus();
				m_GuiEditNum.SetSel(MAKELONG(0,-1));
			}
			break;
		case VK_F4:
			OnBnClickedButtonAdd();
			break;
		case VK_F5:
			{
			if(m_GuiMenuList.IsWindowVisible())
				m_GuiMenuList.SetFocus();
			if(m_GiuiTree.IsWindowVisible())
				m_GiuiTree.SetFocus();
			}
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CJCDialog::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int arid = m_dwCombo.GetItemData(m_dwCombo.GetCurSel());
	hotelMIS::HArrerageCtrl harreragectrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	harreragectrl.writeArrIdtoAccount(arid,accountId);

	CDialog::OnClose();
}
