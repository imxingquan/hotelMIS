// SpecialMenuDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "SpecialMenuDialog.h"
#include "HFoodKindCtrl.h"
#include "HBeforeRepCtrl.h"
#include ".\specialmenudialog.h"

// CSpecialMenuDialog �Ի���

IMPLEMENT_DYNAMIC(CSpecialMenuDialog, CDialog)
CSpecialMenuDialog::CSpecialMenuDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecialMenuDialog::IDD, pParent)
	, m_kindSpPos(0)
	, m_py(_T(""))
	,m_bIsTree(TRUE)
	, m_num(1)
{
	
}

CSpecialMenuDialog::~CSpecialMenuDialog()
{
}

void CSpecialMenuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXL, m_GuiGroupBoxL);
	DDX_Control(pDX, IDC_GROUPBOXR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_MENU_TREE, m_GuiTreeCtrlMenu);
	DDX_Control(pDX, IDC_COMBO_SPECIAL, m_GuiComboSpecial);
	DDX_Control(pDX, IDC_LIST_SPECIAL_MENU, m_GuiListCtrlSpecialMenu);
	DDX_Control(pDX, IDC_BUTTON_MOVE_RIGHT, m_GuiButtonMoveR);
	DDX_Control(pDX, IDC_BUTTON_MOVE_LEFT, m_GuiButtonMoveL);
	DDX_CBIndex(pDX, IDC_COMBO_SPECIAL, m_kindSpPos);
	DDX_Control(pDX, IDC_MENU_LIST, m_GuiMenuList);
	DDX_Control(pDX, IDC_EDIT_PY, m_GuiEditPy);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
	DDX_Control(pDX, IDC_BUTTON_TREE, m_GuiBtnTree);
	DDX_Control(pDX, IDC_BUTTON_LIST, m_GuiBtnList);
	DDX_Control(pDX, IDC_BUTTON_EXT, m_GuiBtnExt);
	DDX_Control(pDX, IDC_EDIT_NUM, m_GuiEditNum);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDV_MinMaxInt(pDX, m_num, 1, 999);
	DDX_Control(pDX, IDOK, m_GuiBtnExit);
}


BEGIN_MESSAGE_MAP(CSpecialMenuDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_RIGHT, OnBnClickedButtonMoveRight)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_LEFT, OnBnClickedButtonMoveLeft)
//	ON_CBN_EDITCHANGE(IDC_COMBO_SPECIAL, OnCbnEditchangeComboSpecial)
	ON_NOTIFY(NM_CLICK, IDC_MENU_TREE, OnNMClickMenuTree)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_TREE, OnNMDblclkMenuTree)
//	ON_CBN_SELENDCANCEL(IDC_COMBO_SPECIAL, OnCbnSelendcancelComboSpecial)
	ON_CBN_SELCHANGE(IDC_COMBO_SPECIAL, OnCbnSelchangeComboSpecial)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPECIAL_MENU, OnNMClickListSpecialMenu)
	ON_BN_CLICKED(IDC_BUTTON_TREE, OnBnClickedButtonTree)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnBnClickedButtonList)
	ON_BN_CLICKED(IDC_BUTTON_EXT, OnBnClickedButtonExt)
//	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_EDIT_PY, OnEnChangeEditPy)
	ON_NOTIFY(NM_CLICK, IDC_MENU_LIST, OnNMClickMenuList)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_LIST, OnNMDblclkMenuList)
END_MESSAGE_MAP()


//-----------------------------------------------------------------------------------------
// ���ײ������
void CSpecialMenuDialog::OnBnClickedButtonMoveRight()
{
	UpdateData();
	//Check Num
	if ( m_num <=0 ){
		//MessageBox(_T("��������С�ڻ������!"),_T("����"),MB_ICONWARNING|MB_OK);
		m_GuiEditNum.SetFocus();
		return;
	}

	if ( m_GuiComboSpecial.GetCount() <= 0){
		MessageBox(_T("�����ڲ��׹���������ײ�,Ȼ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if ( m_bIsTree )
	{
		HTREEITEM hItem,hParent;
		if (hItem = m_GuiTreeCtrlMenu.HitTest(m_point)) {  //��ⵥ�����ڵ�
			hParent = m_GuiTreeCtrlMenu.GetParentItem(hItem);
			if ( hParent != NULL ){
				//ѡ�е��ǲ���
				int food_id = m_GuiTreeCtrlMenu.GetItemData(hItem);
				int parent_food_id = m_taoCanKindMap[m_GuiComboSpecial.GetCurSel()];
				hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
				menuInfoCtrl.addToTaoCan(parent_food_id,food_id,m_num);
			}
		}
	}
	else
	{
		int nPos = m_GuiMenuList.GetSelectionMark();
		if ( nPos != -1 ){
			int food_id = m_menuListMap[nPos];
			int parent_food_id = m_taoCanKindMap[m_GuiComboSpecial.GetCurSel()];
			hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
			menuInfoCtrl.addToTaoCan(parent_food_id,food_id,m_num);
		}

	}

	Refresh();
	m_GuiButtonMoveR.EnableWindow(FALSE);
	m_num = 1;
	UpdateData(FALSE);
}

void CSpecialMenuDialog::OnBnClickedButtonMoveLeft()
{
	//ɾ���ײ�
	int nPos = m_GuiListCtrlSpecialMenu.GetSelectionMark();
	if ( nPos != -1){

		int r = MessageBox(_T("ȷ��Ҫɾ����?"),_T("����"),MB_ICONWARNING|MB_YESNO);
		if ( IDYES == r){
			hotelMIS::HMenuInfoCtrl hMenuInfo(m_con.get_con());
			int parent_food_id = m_taoCanKindMap[m_GuiComboSpecial.GetCurSel()];
			int food_id = m_menuSpMap[nPos];
			hMenuInfo.delTaoCan(parent_food_id,food_id);

			Refresh();
			m_GuiButtonMoveL.EnableWindow(FALSE);
		}
	}
}


BOOL CSpecialMenuDialog::OnInitDialog()
{
	::SetCursor(::LoadCursor(NULL,IDC_WAIT));
	CDialog::OnInitDialog();
	
	//������ʾ
	m_tip.Create(this);
	m_tip.AddTool(&m_GuiBtnExt,_T("����+�Ű�ť,��������չ���б�"));
	m_tip.AddTool(&m_GuiBtnTree,_T("����ͼ�ķ�ʽ�鿴!"));
	m_tip.AddTool(&m_GuiBtnList,_T("���б�ķ�ʽ�鿴!"));
	m_tip.Activate(TRUE);
	

	//Ĭ������	
	m_GuiMenuList.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PY)->ShowWindow(SW_HIDE);

	m_GuiButtonMoveR.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonMoveL.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnExit.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnExt.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiButtonMoveR.ShowText();
	m_GuiButtonMoveL.ShowText();
	m_GuiBtnExit.ShowText();
	m_GuiBtnExt.ShowText();

	m_GuiBtnTree.SetCheck(1);

	Init();
	InitTaoCan();

	::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void  CSpecialMenuDialog::Init()
{
		
	m_GuiButtonMoveR.EnableWindow(FALSE);
	m_GuiButtonMoveL.EnableWindow(FALSE);
	
	//��ʼ��ListCtrl;
	int i = 0;
	m_GuiListCtrlSpecialMenu.InsertColumn(i,_T("���"),LVCFMT_LEFT,50);
	m_GuiListCtrlSpecialMenu.InsertColumn(++i,_T("����"),LVCFMT_LEFT,170);
	m_GuiListCtrlSpecialMenu.InsertColumn(++i,_T("����"),LVCFMT_RIGHT,80);
	m_GuiListCtrlSpecialMenu.InsertColumn(++i,_T("����"),LVCFMT_CENTER,50);
	m_GuiListCtrlSpecialMenu.InsertColumn(++i,_T("��λ"),LVCFMT_CENTER,50);
	m_GuiListCtrlSpecialMenu.InsertColumn(++i,_T("��ʦ"),LVCFMT_LEFT,60);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlSpecialMenu.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	i = 0;
	m_GuiMenuList.InsertColumn(i,_T("���"),LVCFMT_LEFT,50);
	m_GuiMenuList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,170);
	m_GuiMenuList.InsertColumn(++i,_T("����"),LVCFMT_RIGHT,80);
	//m_GuiMenuList.InsertColumn(++i,_T("��ǰ���"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiMenuList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	

	CString temp;	//temp

	//��ʼ����
	HTREEITEM hRoot,hChild;
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	//hotelMIS::HFoodKindVec kindVec = foodKindCtrl.getAllKindExceptTs();
	hotelMIS::HFoodKindVec kindVec = foodKindCtrl.getAllKind();
	hotelMIS::HFoodKindVec::iterator kIt;
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec menuVec; 
	hotelMIS::HMenuInfoVec::iterator mIt;
	for ( kIt = kindVec.begin(); kIt != kindVec.end(); kIt++)
	{
		//���˵��ײ�
		//�����ײͺͺ����Ʒ
		if ( kIt->kind_id == hotelMIS::HFoodKind::TC ||
			kIt->kind_flag == hotelMIS::HFoodKind::HOUCHU_FLAG
			 ){ 
			 //m_menuVec.erase(mIt);
			 continue;
		}
		//������
		hRoot = m_GuiTreeCtrlMenu.InsertItem(kIt->getKind_name().c_str(),TVI_ROOT);

		m_GuiTreeCtrlMenu.SetItemData(hRoot,(DWORD)kIt->getKind_id());
		m_GuiTreeCtrlMenu.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);
		menuVec = menuInfoCtrl.getMenuInfoByKind( kIt->getKind_id() );
		for ( mIt = menuVec.begin(); mIt != menuVec.end(); mIt++)
		{
			temp.Format("%s   ��%.2f",mIt->food_name.c_str(),mIt->food_price);
			hChild = m_GuiTreeCtrlMenu.InsertItem(temp,hRoot);
			if ( hChild != NULL)
				m_GuiTreeCtrlMenu.SetItemData(hChild,(DWORD)mIt->food_id);
		}
		m_GuiTreeCtrlMenu.Expand(hRoot,TVE_EXPAND);
		
	}

	//��ʼ���б�
	//hotelMIS::HBeforeRepCtrl befCtrl(m_con.get_con());

	//��¼���������,�Ա�ӿ��ٶ�
	m_menuVec =menuInfoCtrl.getAllMenuInfo();	
	//m_menuVec = hotelMIS::HMenuInfoCtrl::menuInfoFactory();

	 i = 0;
	 m_menuListMap.clear();
	 CString t;
	 for ( mIt = m_menuVec.begin(); mIt != m_menuVec.end(); mIt++)
	 {
		 //�����ײͺͺ����Ʒ
		 if ( mIt->bTaocan ||
			 menuInfoCtrl.isHouChu(mIt->foodKind.kind_flag)
			 ){ 
			 //m_menuVec.erase(mIt);
			 continue;
			}

		 m_menuListMap.insert(make_pair(i,mIt->food_id));
		 t.Format("%d",mIt->food_id);
		 //���
		 m_GuiMenuList.InsertItem(i,t);
		 //����
		 m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
		 //����
		 t.Format("%.2f",mIt->food_price);
		 m_GuiMenuList.SetItemText(i,2,t);
		 ////��ǰ���
		 //t.Format("%d",befCtrl.getCurRep(mIt->food_id));
		 //m_GuiMenuList.SetItemText(i,3,t);
		 i++;
	 }
}

//--------------------------------------------------------------------------------------------------------------------
// ��ʼ���ײ�
//
void CSpecialMenuDialog::InitTaoCan()
{
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec vec = menuInfoCtrl.getTaoCanList();
	hotelMIS::HMenuInfoVec::iterator it;
	int pos = 0;
	m_taoCanKindMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		pos = m_GuiComboSpecial.AddString( it->food_name.c_str() );
		m_taoCanKindMap.insert(make_pair(pos,it->food_id));
	}
	m_GuiComboSpecial.SetCurSel(0);
	 //��ʼ���ײ��б�
	Refresh();
}

//---------------------------------------------------------------------------------------------------------------------
void  CSpecialMenuDialog::Refresh()
{
	//ˢ��LeftList
	m_GuiListCtrlSpecialMenu.DeleteAllItems();
	hotelMIS::HMenuInfoCtrl menuCtrl(m_con.get_con());
	
	//����ײ͵� food_id
	int parent_food_id = m_taoCanKindMap[m_GuiComboSpecial.GetCurSel()];

	TRACE("parent_food_id = %d\n",parent_food_id);

	hotelMIS::HMenuInfoVec vec=menuCtrl.getChildMenu(parent_food_id);
	int i = 0;
	CString cnt;
	hotelMIS::HMenuInfoVec::iterator it;
	m_menuSpMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_menuSpMap.insert(make_pair(i,it->food_id));
		cnt.Format("%d",it->food_id);
		m_GuiListCtrlSpecialMenu.InsertItem(i,cnt);
		m_GuiListCtrlSpecialMenu.SetItemText(i,1,it->food_name.c_str());
		cnt.Format("%.2f",it->food_price);
		m_GuiListCtrlSpecialMenu.SetItemText(i,2,cnt);
		cnt.Format("%d",menuCtrl.getNum(parent_food_id,it->food_id));
		m_GuiListCtrlSpecialMenu.SetItemText(i,3,cnt);
		m_GuiListCtrlSpecialMenu.SetItemText(i,4,it->food_unit.c_str());
		m_GuiListCtrlSpecialMenu.SetItemText(i,5,it->ck_name.c_str());
		i++;
	}
	
}

//------------------------------------------------------------------------------------------------------------------------
void CSpecialMenuDialog::OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		
		DWORD dwPos = ::GetMessagePos();
		CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		m_point = point;
		m_GuiTreeCtrlMenu.ScreenToClient(&m_point);
		HTREEITEM hItem,hParent;
		if (hItem = m_GuiTreeCtrlMenu.HitTest(m_point)) {
			hParent = m_GuiTreeCtrlMenu.GetParentItem(hItem);
			if ( hParent != NULL )
				m_GuiButtonMoveR.EnableWindow(TRUE);
		}
	*pResult = 0;
}

//---------------------------------------------------------------------------------------------------------------------
void CSpecialMenuDialog::OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:˫�����
	OnBnClickedButtonMoveRight();
	*pResult = 0;
}

void CSpecialMenuDialog::OnCbnSelchangeComboSpecial()
{
	// TODO: ѡ�иı�
	m_GuiButtonMoveR.EnableWindow(FALSE);
	m_GuiButtonMoveL.EnableWindow(FALSE);

	Refresh();
}

void CSpecialMenuDialog::OnNMClickListSpecialMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( m_GuiListCtrlSpecialMenu.GetSelectionMark() != -1)
		m_GuiButtonMoveL.EnableWindow(TRUE);

	*pResult = 0;
}


void CSpecialMenuDialog::OnBnClickedButtonTree()
{
	m_bIsTree = TRUE;
	m_GuiTreeCtrlMenu.ShowWindow(SW_SHOW);

	m_GuiMenuList.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PY)->ShowWindow(SW_HIDE);

	m_GuiBtnExt.EnableWindow(TRUE);
	m_GuiButtonMoveR.EnableWindow(FALSE);
}

void CSpecialMenuDialog::OnBnClickedButtonList()
{

	m_bIsTree = FALSE;
	m_GuiTreeCtrlMenu.ShowWindow(SW_HIDE);

	m_GuiMenuList.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_PY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_PY)->ShowWindow(SW_SHOW);

	m_GuiBtnExt.EnableWindow(FALSE);
	m_GuiButtonMoveR.EnableWindow(FALSE);
}

void CSpecialMenuDialog::OnBnClickedButtonExt()
{
	// չ��/���� ���б�
	HTREEITEM htreeItem = m_GuiTreeCtrlMenu.GetRootItem();;
	while ( htreeItem != NULL){
		m_GuiTreeCtrlMenu.Expand(htreeItem,TVE_TOGGLE);
		htreeItem = m_GuiTreeCtrlMenu.GetNextItem(htreeItem,TVGN_NEXT);
	}
}

BOOL CSpecialMenuDialog::PreTranslateMessage(MSG* pMsg)
{
	if ( m_tip.m_hWnd != NULL)
	{
		m_tip.RelayEvent(pMsg);
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//void CSpecialMenuDialog::OnMouseMove(UINT nFlags, CPoint point)
//{
//		DWORD dwPos = ::GetMessagePos();
//		CPoint pt((int)LOWORD(dwPos),(int)HIWORD(dwPos));
//		m_GuiTreeCtrlMenu.ScreenToClient(&pt);
//		HTREEITEM hItem,hParent;
//		if (hItem = m_GuiTreeCtrlMenu.HitTest(pt))
//		{
//			/*hParent = m_GuiTreeCtrlMenu.GetParentItem(hItem);
//			if ( hParent != NULL )
//				m_GuiButtonMoveR.EnableWindow(TRUE);*/
//			SetCursor(::LoadCursor(NULL,IDC_HAND));
//		}
//		else
//		{
//			SetCursor(::LoadCursor(NULL,IDC_ARROW));
//		}
//	CDialog::OnMouseMove(nFlags, point);
//}

void CSpecialMenuDialog::OnEnChangeEditPy()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	
	// ���� SQL �����ַ�
	CString py = hotelMIS::ReplaceChar(m_py.Trim());
	
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec vec;
	if ( ! py.IsEmpty() )
		vec = menuInfoCtrl.getMenuByPy(m_py.Trim().GetBuffer());
	else
		vec = m_menuVec;	//�ӻ�����ȡ��
	
	m_menuListMap.clear();
	m_GuiMenuList.DeleteAllItems();
	
	int i = 0;
	CString t;
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	
	hotelMIS::HMenuInfoVec::iterator it;
	
	for ( it = vec.begin(); it != vec.end(); it++)
	 {
		//�����ײͺͺ����Ʒ
		 if ( it->bTaocan || menuInfoCtrl.isHouChu(it->foodKind.kind_flag)){ 
				 continue;
		 }
	
		 m_menuListMap.insert(make_pair(i,it->food_id));
		 t.Format("%d",it->food_id);
		 //���
		 m_GuiMenuList.InsertItem(i,t);
		 //����
		 m_GuiMenuList.SetItemText(i,1,it->food_name.c_str());
		 //����
		 t.Format("%.2f",it->food_price);
		 m_GuiMenuList.SetItemText(i,2,t);
		 
		 i++;
	 }
}

void CSpecialMenuDialog::OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if ( m_GuiMenuList.GetSelectionMark() != -1)
		m_GuiButtonMoveR.EnableWindow(TRUE);
}

void CSpecialMenuDialog::OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ˫�����
	OnBnClickedButtonMoveRight();
	
	*pResult = 0;
}
