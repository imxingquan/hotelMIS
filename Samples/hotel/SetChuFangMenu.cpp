// SetChuFangMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SetChuFangMenu.h"
#include ".\setchufangmenu.h"

#include "HFoodKindCtrl.h"
#include "HMenuInfoCtrl.h"
// CSetChuFangMenu �Ի���

IMPLEMENT_DYNAMIC(CSetChuFangMenu, CDialog)
CSetChuFangMenu::CSetChuFangMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CSetChuFangMenu::IDD, pParent)
{
}

CSetChuFangMenu::~CSetChuFangMenu()
{
}

void CSetChuFangMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENU_TREE, m_GuiTreeCtrlMenu);
	DDX_Control(pDX, IDC_LIST_CHUFANG, m_GuiListCtrlChuFangMenu);
	DDX_Control(pDX, IDC_BUTTON_MOVE_RIGHT, m_GuiButtonMoveR);
	DDX_Control(pDX, IDC_BUTTON_MOVE_LEFT, m_GuiButtonMoveL);
	DDX_Control(pDX, IDC_COMBO_CHUFANG, m_GuiComboChuFang);
}


BEGIN_MESSAGE_MAP(CSetChuFangMenu, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_RIGHT, OnBnClickedButtonMoveRight)
	ON_CBN_SELCHANGE(IDC_COMBO_CHUFANG, OnCbnSelchangeComboChufang)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_LEFT, OnBnClickedButtonMoveLeft)
	ON_NOTIFY(NM_CLICK, IDC_MENU_TREE, OnNMClickMenuTree)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_TREE, OnNMDblclkMenuTree)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CHUFANG, OnNMClickListChufang)
END_MESSAGE_MAP()


// CSetChuFangMenu ��Ϣ�������


BOOL CSetChuFangMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSetChuFangMenu::Init()
{
	//��ʼ��ListCtrl;
	int i = 0;
	m_GuiListCtrlChuFangMenu.InsertColumn(i,_T("���"),LVCFMT_LEFT,50);
	m_GuiListCtrlChuFangMenu.InsertColumn(++i,_T("����"),LVCFMT_LEFT,100);
	//m_GuiListCtrlChuFangMenu.InsertColumn(++i,_T("�۸�"),LVCFMT_LEFT,50);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlChuFangMenu.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//��ʼ����
	HTREEITEM hRoot,hChild;
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	hotelMIS::HFoodKindVec kindVec = foodKindCtrl.getAllKindExceptTs();
	hotelMIS::HFoodKindVec::iterator kIt;
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec menuVec; 
	hotelMIS::HMenuInfoVec::iterator mIt;
	for ( kIt = kindVec.begin(); kIt != kindVec.end(); kIt++)
	{
		hRoot = m_GuiTreeCtrlMenu.InsertItem(kIt->getKind_name().c_str(),TVI_ROOT);
		m_GuiTreeCtrlMenu.SetItemData(hRoot,(DWORD)kIt->getKind_id());
		m_GuiTreeCtrlMenu.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);
		menuVec = menuInfoCtrl.getMenuInfoByKind( kIt->getKind_id() );
		for ( mIt = menuVec.begin(); mIt != menuVec.end(); mIt++)
		{
			hChild = m_GuiTreeCtrlMenu.InsertItem(mIt->food_name.c_str(),hRoot);
			if ( hChild != NULL)
				m_GuiTreeCtrlMenu.SetItemData(hChild,(DWORD)mIt->food_id);
		}
		m_GuiTreeCtrlMenu.Expand(hRoot,TVE_EXPAND);
		
	}
	
	//��ʼ����ɫ��
	//hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	m_GuiComboChuFang.AddString(_T("������"));
	m_GuiComboChuFang.AddString(_T("���˳���"));
	m_GuiComboChuFang.AddString(_T("�Ȳ˳���"));
	
	m_GuiComboChuFang.SetCurSel(0);
	
	Refresh();
}

void CSetChuFangMenu::Refresh()
{
	//ˢ��LeftList
	m_GuiListCtrlChuFangMenu.DeleteAllItems();
	hotelMIS::HMenuInfoCtrl menuCtrl(m_con.get_con());
	int cookId = m_GuiComboChuFang.GetCurSel();
	TRACE("kind_id = %d\n",cookId);
	hotelMIS::HMenuInfoVec vec=menuCtrl.getMenuByCook(cookId);
	int i = 0;
	CString cnt;
	hotelMIS::HMenuInfoVec::iterator it;
	m_menuCookMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_menuCookMap.insert(make_pair(i,it->food_id));
		cnt.Format("%d",i+1);
		m_GuiListCtrlChuFangMenu.InsertItem(i,cnt);
		m_GuiListCtrlChuFangMenu.SetItemText(i,1,it->food_name.c_str());
		/*cnt.Format("%.2f",it->food_price);
		m_GuiListCtrlSpecialMenu.SetItemText(i,2,cnt);
		cnt.Format("%d",it->food_num);
		m_GuiListCtrlSpecialMenu.SetItemText(i,3,cnt);
		m_GuiListCtrlSpecialMenu.SetItemText(i,4,it->food_unit.c_str());
		m_GuiListCtrlSpecialMenu.SetItemText(i,5,it->ck_name.c_str());*/
		i++;
	}
}
void CSetChuFangMenu::OnCbnSelchangeComboChufang()
{
	// TODO: ѡ�иı�
	m_GuiButtonMoveR.EnableWindow(FALSE);
	m_GuiButtonMoveL.EnableWindow(FALSE);

	Refresh();
}

void CSetChuFangMenu::OnBnClickedButtonMoveRight()
{
	// TODO: ���
	UpdateData();
		/*DWORD dwPos = ::GetMessagePos();
		CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		m_GuiTreeCtrlMenu.ScreenToClient(&point);*/
		HTREEITEM hItem,hParent;
		if (hItem = m_GuiTreeCtrlMenu.HitTest(m_point)) {
			hParent = m_GuiTreeCtrlMenu.GetParentItem(hItem);
			if ( hParent != NULL ){
				//ѡ�е��ǲ���
				CString str = m_GuiTreeCtrlMenu.GetItemText(hItem);
				int foodId = m_GuiTreeCtrlMenu.GetItemData(hItem);
					
				TRACE("������%s,FOOD_ID = %d\n",str,foodId);
				
				hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
				int cookId = m_GuiComboChuFang.GetCurSel();
				menuInfoCtrl.AddToChuFang(cookId,foodId);
				//menuInfoCtrl.AddSpecialMenu(m_kindSpMap[m_kindSpPos],foodId);//m_GuiComboKind.GetCurSel() == m_kindSpPos;
			}else{
				//ѡ�е��ǲ���
				CString str = m_GuiTreeCtrlMenu.GetItemText(hItem);
				int kindId = m_GuiTreeCtrlMenu.GetItemData(hItem);
				TRACE("���������%s,KIND_ID = %d\n",str,kindId);
				
				hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
				int cookId = m_GuiComboChuFang.GetCurSel();
				menuInfoCtrl.AddToChuFangByKind(cookId,kindId);
			}
		}
	Refresh();
	m_GuiButtonMoveR.EnableWindow(FALSE);
}
void CSetChuFangMenu::OnBnClickedButtonMoveLeft()
{
	// TODO: ɾ��
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	//DWORD dwPos = ::GetMessagePos();
	//CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	////m_point = point;
	//m_GuiListCtrlSpecialMenu.ScreenToClient(&point);
	//int pos =  m_GuiListCtrlSpecialMenu.HitTest(point);
	int nIndex=0;
	if ( (nIndex = m_GuiListCtrlChuFangMenu.HitTest(m_point2))!=-1){
		TRACE("click pos= %d,food_id = %d \n",nIndex,m_menuCookMap[nIndex]);
		menuInfoCtrl.RemoveFromChuFang(m_menuCookMap[nIndex]);
		m_GuiButtonMoveL.EnableWindow(FALSE);
		Refresh();
	}
}

void CSetChuFangMenu::OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = ::GetMessagePos();
		CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		m_point = point;
		m_GuiTreeCtrlMenu.ScreenToClient(&m_point);
		HTREEITEM hItem;
		if (hItem = m_GuiTreeCtrlMenu.HitTest(m_point)) {
			/*hParent = m_GuiTreeCtrlMenu.GetParentItem(hItem);
			if ( hParent != NULL )*/
				m_GuiButtonMoveR.EnableWindow(TRUE);
		}
	*pResult = 0;
	
}

void CSetChuFangMenu::OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButtonMoveRight();
	*pResult = 0;
}

void CSetChuFangMenu::OnNMClickListChufang(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_point2 = point;
	m_GuiListCtrlChuFangMenu.ScreenToClient(&m_point2);
	int pos = 0;
	if ( (pos = m_GuiListCtrlChuFangMenu.HitTest(m_point2)) != -1)
		m_GuiButtonMoveL.EnableWindow(TRUE);

	*pResult = 0;
}
