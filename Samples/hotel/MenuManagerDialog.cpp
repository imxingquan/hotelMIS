// MenuManagerDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "MenuManagerDialog.h"


//#include "HFoodKindCtrl.h"
#include "HUnitCtrl.h"
#include "HEmployeeCtrl.h"
#include "HMenuInfoCtrl.h"
#include "MyCdKey.h"
#include "RegisterDialog.h"
#include "HBeforeRepCtrl.h"
#include "HBehindRepCtrl.h"
#include "PreParent.h"	
#include "HSetHotelPrintMsg.h"
#include "HAdminBdy.h"

// CMenuManagerDialog �Ի���
CString CMenuManagerDialog::m_hotelname;
CString CMenuManagerDialog::m_exp;
IMPLEMENT_DYNAMIC(CMenuManagerDialog, CDialog)
CMenuManagerDialog::CMenuManagerDialog(BOOL bRep,CWnd* pParent /*=NULL*/)
	: CDialog(CMenuManagerDialog::IDD, pParent)
	, m_kindPos(0)
	, m_foodName(_T(""))
	, m_price(0.00f)
	, m_unit(_T(""))
	, m_cook(_T(""))
	, m_repertory(FALSE)
	, m_addKind(_T(""))
	, m_bAllAdd(FALSE)
	, m_bSpecial(FALSE)
	, m_isModify(FALSE)
	, m_py(_T(""))
	, m_bRepNoCalc(FALSE)
	, m_bRepOpen(FALSE)
	, m_bRep( bRep)
	, m_totalfl(0)
{
}

CMenuManagerDialog::~CMenuManagerDialog()
{
}

void CMenuManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXT, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_COMBO_KIND, m_GuiComboKind);
	DDX_Control(pDX, IDC_EDIT_MENU_NAME, m_GuiEditName);
	DDX_Control(pDX, IDC_EDIT_MENU_PRICE, m_GuiEditPrice);
	DDX_Control(pDX, IDC_COMBO_MENU_UNIT, m_GuiComboUnit);
	DDX_Control(pDX, IDC_COMBO_COOK, m_GuiComboCook);
	DDX_Control(pDX, IDC_CHECK_REPERTORY, m_GuiCheckRepertory);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_GuiButtonAdd);
	DDX_Control(pDX, IDC_LIST_MENU, m_GuiListCtrl);
	DDX_CBIndex(pDX, IDC_COMBO_KIND, m_kindPos);
	DDX_Text(pDX, IDC_EDIT_MENU_NAME, m_foodName);
	DDX_Text(pDX, IDC_EDIT_MENU_PRICE, m_price);
	DDX_CBString(pDX, IDC_COMBO_MENU_UNIT, m_unit);
	DDX_CBString(pDX, IDC_COMBO_COOK, m_cook);
	DDX_Check(pDX, IDC_CHECK_REPERTORY, m_repertory);
	DDX_Control(pDX, IDC_DEL_BUTTON, m_GuiDelButton);
	DDX_Control(pDX, IDC_PY_EDIT, m_GuiPYEdit);
	DDX_Text(pDX, IDC_PY_EDIT, m_py);
	DDX_Control(pDX, IDC_CHECK_REPERTORY_NOCALC, m_GuiCheckBoxRepNoCalc);
	DDX_Check(pDX, IDC_CHECK_REPERTORY_NOCALC, m_bRepNoCalc);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_GuiComboFilter);
	DDX_Control(pDX, IDC_PRINT_MENU_BUTTON, m_GuiPrintMenuBtn);
	DDX_Control(pDX, IDC_TOTAL_COMBO, m_totalCombo);
	DDX_CBIndex(pDX, IDC_TOTAL_COMBO, m_totalfl);
}


BEGIN_MESSAGE_MAP(CMenuManagerDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_KIND, OnCbnSelchangeComboKind)
	ON_COMMAND(ID_POPUP_MODIFYMENU, OnPopupModifymenu)
	ON_COMMAND(ID_POPUP_DELMENU, OnPopupDelmenu)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MENU, OnNMRclickListMenu)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MENU, OnNMDblclkListMenu)
	ON_BN_CLICKED(IDC_DEL_BUTTON, OnBnClickedDelButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MENU, OnNMClickListMenu)
	ON_BN_CLICKED(IDC_CHECK_REPERTORY, OnBnClickedCheckRepertory)
	ON_BN_CLICKED(IDC_CHECK_REPERTORY_NOCALC, OnBnClickedCheckRepertoryNocalc)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER, OnCbnSelchangeComboFilter)
	ON_BN_CLICKED(IDC_PRINT_MENU_BUTTON, OnBnClickedPrintMenuButton)
END_MESSAGE_MAP()


// CMenuManagerDialog ��Ϣ�������

void CMenuManagerDialog::OnBnClickedButtonAdd()
{
	// TODO: ��Ӳ�����Ϣ
	/*MyCdKey cdkey;
	if (!cdkey.RegisterCdKey() )
	{
		CRegisterDialog dlg;
		dlg.DoModal();
		return;
	}*/

	UpdateData(TRUE);
	if ( m_foodName.Trim().IsEmpty() ){
		MessageBox(_T("��Ʒ���Ʋ���Ϊ��!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_GuiEditName.SetFocus();
		return;
	}
	
	if ( m_price < 0.00f ){
		MessageBox(_T("�۸���Ϊ��,����������!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_GuiEditPrice.SetFocus();
		return;
	}
	
	
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfo menuInfo;
	menuInfo.kind_id = m_kindMap[m_kindPos].first;
	menuInfo.food_name = hotelMIS::ReplaceChar(m_foodName).GetBuffer();
	menuInfo.food_price = m_price;
	menuInfo.food_unit = hotelMIS::ReplaceChar(m_unit).GetBuffer();
	menuInfo.ck_name = hotelMIS::ReplaceChar(m_cook).GetBuffer();
	menuInfo.food_py = hotelMIS::ReplaceChar(m_py).GetBuffer();
	menuInfo.total_fl = m_totalCombo.GetCurSel();
	/*if ( m_bRep == TRUE){
		m_repertory = FALSE;
		m_bRepNoCalc = TRUE;
	}*/

	/*if ( m_repertory == TRUE) 
		menuInfo.repertory_flag = hotelMIS::HMenuInfo::REP_CALC;
	else if ( m_bRepNoCalc == TRUE)
		menuInfo.repertory_flag = hotelMIS::HMenuInfo::REP_NOCALC;
	else
		menuInfo.repertory_flag = hotelMIS::HMenuInfo::REP_NO;*/

	if ( ! m_isModify ){//����
		menuInfoCtrl.insert(menuInfo);
		Refresh();
	}else{	//�޸�
		menuInfo.food_id = m_menuMap[m_nIndex].first;
		menuInfoCtrl.update(menuInfo);
		m_GuiButtonAdd.SetWindowText(_T("���"));
		m_isModify = FALSE;

		Refresh();
		m_GuiComboKind.EnableWindow(TRUE);
		//m_GuiButtonAdd.EnableWindow(FALSE);
		m_GuiDelButton.SetWindowText(_T("ɾ��"));
		m_GuiDelButton.EnableWindow(FALSE);
	}
	
	//���
	m_foodName.Empty();
	m_price = 0.0f;
	m_py.Empty();
	m_repertory = FALSE;
	m_bRepNoCalc = FALSE;
	UpdateData(FALSE);
	m_GuiEditName.SetFocus();

}

//void CMenuManagerDialog::OnBnClickedButtonAddKind()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}

void CMenuManagerDialog::Init()
{
	//*******************���ð�**********************************
#ifdef _FREE_EDITION
	m_GuiButtonAdd.ShowWindow(SW_HIDE);
	m_GuiDelButton.ShowWindow(SW_HIDE);
	//*************************************************************
#endif
	//��ʼ��
	//0) ��ʼ����
	m_GuiListCtrl.InsertColumn(0,_T("���"),LVCFMT_LEFT,50);
	m_GuiListCtrl.InsertColumn(1,_T("����"),LVCFMT_LEFT,170);
	m_GuiListCtrl.InsertColumn(2,_T("����"),LVCFMT_RIGHT,70);
	m_GuiListCtrl.InsertColumn(3,_T("��λ"),LVCFMT_CENTER,40);
	m_GuiListCtrl.InsertColumn(4,_T("��ʦ"),LVCFMT_CENTER,40);
	//m_GuiListCtrl.InsertColumn(5,_T("����"),LVCFMT_LEFT,45);
	m_GuiListCtrl.InsertColumn(5,_T("����"),LVCFMT_LEFT,90);
	m_GuiListCtrl.InsertColumn(6,_T("ͳ�Ʒ���"),LVCFMT_LEFT,90);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//1) ��� ���
	hotelMIS::HFoodKindCtrl kindCtrl(m_con.get_con());
	m_foodVec = kindCtrl.getAllKind();
	hotelMIS::HFoodKindVec::iterator kit;
	m_GuiComboKind.AddString(_T("ȫ ��"));
	int pos = -1;
	if ( m_bRep == FALSE)
	{
		for ( kit = m_foodVec.begin(); kit != m_foodVec.end(); kit++)
		{
			if ( m_bRepOpen == FALSE){
				if ( kit->kind_flag == hotelMIS::HFoodKind::HOUCHU_FLAG )
					continue;
			}
			pos = m_GuiComboKind.AddString(kit->getKind_name().c_str());
			m_kindMap.insert(make_pair(pos,make_pair(kit->getKind_id(),kit->getKind_name())));
		}
	}
	else
	{
		for ( kit = m_foodVec.begin(); kit != m_foodVec.end(); kit++)
		{

			if ( kit->kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG )
				continue;

			pos = m_GuiComboKind.AddString(kit->getKind_name().c_str());
			m_kindMap.insert(make_pair(pos,make_pair(kit->getKind_id(),kit->getKind_name())));
		}
	}
	m_GuiComboKind.SetCurSel(0);
	m_GuiButtonAdd.EnableWindow(FALSE);	//ȫ����𲻿�����
	m_GuiDelButton.EnableWindow(FALSE);
	//2) ��� ��λ
	hotelMIS::HUnitCtrl unitCtrl(m_con.get_con());
	hotelMIS::HUnitVec unitVec = unitCtrl.getAllUnit();
	hotelMIS::HUnitVec::iterator uit;
	
	for ( uit = unitVec.begin(); uit != unitVec.end(); uit++)
		m_GuiComboUnit.AddString(uit->getUnit_name().c_str());

	m_GuiComboUnit.SetCurSel(0);

	//3) ��� ��ʦ
	hotelMIS::HEmployeeCtrl empCtrl(m_con.get_con());
	hotelMIS::HEmployeeVec empVec = empCtrl.getAllCook();
	hotelMIS::HEmployeeVec::iterator eit;
	m_GuiComboCook.AddString(_T("��"));
	for (eit = empVec.begin(); eit != empVec.end(); eit++)
		m_GuiComboCook.AddString(eit->getEmp_name().c_str());
	
	m_GuiComboCook.SetCurSel(0);

	m_GuiComboFilter.AddString(_T("������"));
	m_GuiComboFilter.AddString(_T("����ʾǰ̨���"));
	m_GuiComboFilter.AddString(_T("����ʾ��̨���"));
	m_GuiComboFilter.SetCurSel(0);
	
	m_totalCombo.AddString(_T("�޷���"));
	m_totalCombo.AddString(_T("ʳ��"));
	m_totalCombo.AddString(_T("����"));
	m_totalCombo.AddString(_T("����"));
	m_totalCombo.AddString(_T("����"));
	m_totalCombo.AddString(_T("����"));
	m_totalCombo.AddString(_T("�����"));
	m_totalCombo.AddString(_T("��"));
	m_totalCombo.SetCurSel(0);
	


	//3) ˢ�� �б�
	Refresh();	

}

void CMenuManagerDialog::Refresh()
{
	if ( m_isModify) return;

	m_GuiListCtrl.DeleteAllItems();
	hotelMIS::HMenuInfoCtrl menuCtrl(m_con.get_con());
	int kindId = m_kindMap[m_GuiComboKind.GetCurSel()].first;
	TRACE("kind_id = %d,kind_name = %s \n",kindId,m_kindMap[m_GuiComboKind.GetCurSel()].second.c_str());
	hotelMIS::HMenuInfoVec vec;
	int i = 0;
	CString cnt;
	if ( 0 != kindId){  //�����ǰ�������޸���Ϊ���� ���� ���޸��ҷ���
		vec = menuCtrl.getMenuInfoByKind(kindId);
	}
	else {
		vec = menuCtrl.getAllMenuInfo();
	}

	hotelMIS::HMenuInfoVec::iterator it;
	m_menuMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{	
		/*if ( m_bRep == FALSE){
			if ( it->foodKind.food_flag == hotelMIS::HFoodKind::HOUCHU_FLAG)
		}*/
		m_menuMap.insert(make_pair(i,make_pair(it->food_id,it->kind_id)));
		cnt.Format("%d",it->food_id);
		m_GuiListCtrl.InsertItem(i,cnt);
		m_GuiListCtrl.SetItemText(i,1,it->food_name.c_str());
		cnt.Format("%.2f",it->food_price);
		m_GuiListCtrl.SetItemText(i,2,cnt);
		m_GuiListCtrl.SetItemText(i,3,it->food_unit.c_str());
		m_GuiListCtrl.SetItemText(i,4,it->ck_name.c_str());
	/*	if ( 0 ==it->repertory_flag )
			m_GuiListCtrl.SetItemText(i,5,_T("��"));
		else
			m_GuiListCtrl.SetItemText(i,5,_T("��"));*/
	
		//����������
		map<int,pair<int,string> >::iterator pos;
		for ( pos = m_kindMap.begin(); pos != m_kindMap.end(); pos++)
		{
			if ( pos->second.first == it->kind_id ){
				m_GuiListCtrl.SetItemText(i,5,pos->second.second.c_str());
				break;
			}
		}

		switch(it->total_fl)
		{
		case 0:
			cnt = "��";
			break;
		case 1:
			cnt="ʳ��";
			break;
		case 2:
			cnt="����";
			break;
		case 3:
			cnt="����";
			break;
		case 4:
			cnt="����";
			break;
		case 5:
			cnt="����";
			break;
		case 6:
			cnt="�����";
			break;
		case 7:
			cnt="��";
			break;
		}
		m_GuiListCtrl.SetItemText(i,6,cnt);

		i++;
	}

}

BOOL CMenuManagerDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonAdd.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonAdd.ShowText();;
	m_GuiCheckAllAdd.ShowText();
	m_GuiDelButton.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiDelButton.ShowText();
	m_GuiPrintMenuBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintMenuBtn.ShowText();
	
	//���������ļ��������Ƿ���ʾ���
	CWinApp* pApp = AfxGetApp();
	m_bRepOpen = pApp->GetProfileInt("Settings", "repOpen",0);
	if ( m_bRepOpen == TRUE){
		m_GuiCheckRepertory.ShowWindow(SW_SHOW);
		m_GuiCheckBoxRepNoCalc.ShowWindow(SW_SHOW);
		m_GuiComboFilter.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FILTER_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TIP)->ShowWindow(SW_SHOW);
	}
	
	Init();
	
	m_font.CreatePointFont(150,_T("����"));
	GetDlgItem(IDC_STATIC_T)->SetFont(&m_font);
	
	
	if ( m_bRep == TRUE){
		GetDlgItem(IDC_STATIC_T)->SetWindowText(_T("�����Ʒ����"));
		SetWindowText(_T("�����Ʒ����"));
		
	}else
	{
		GetDlgItem(IDC_STATIC_T)->SetWindowText(_T("��Ʒ����"));
	}

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMenuManagerDialog::OnCbnSelchangeComboKind()
{
	//ˢ��
	Refresh();
	
	m_exp.Format(" ����:[ %s ]" , m_kindMap[m_GuiComboKind.GetCurSel()].second.c_str());
	m_GuiButtonAdd.EnableWindow(m_kindMap[m_GuiComboKind.GetCurSel()].first); 
	m_GuiDelButton.EnableWindow(FALSE);
}

void CMenuManagerDialog::OnPopupModifymenu()
{
	// TODO: popup menu �޸�
	int nPos = m_GuiListCtrl.GetSelectionMark();
	if ( nPos == -1 )
		return;

	m_GuiButtonAdd.SetWindowText(_T("�޸�"));
	m_GuiDelButton.SetWindowText(_T("ȡ��"));

	m_GuiButtonAdd.EnableWindow(true);
	
	//��Ҫ�޸ĵ���Ϣ�����ȥ
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	hotelMIS::HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(m_menuMap[nPos].first);

	m_foodName = menuInfo.food_name.c_str();
	m_price = menuInfo.food_price;
	m_unit = menuInfo.food_unit.c_str();
	m_cook = menuInfo.ck_name.c_str();
	m_repertory = menuInfo.repertory_flag;
	//m_kindPos = menuInfo.kind_id; error
	m_py = menuInfo.food_py.c_str();

	std::map<int, std::pair<int,string> >::iterator it;
	for ( it = m_kindMap.begin(); it != m_kindMap.end(); it++)
	{
		if ( it->second.first == menuInfo.kind_id ){
			m_kindPos = it->first;
			break;
		}
	}
	m_totalfl = menuInfo.total_fl;

	m_isModify = TRUE;	
	
	m_GuiComboCook.EnableWindow(TRUE);
	UpdateData(FALSE);
	
}

void CMenuManagerDialog::OnPopupDelmenu()
{
	int nPos = m_GuiListCtrl.GetSelectionMark();
	if ( nPos == -1 )
		return;

	if ( m_isModify == TRUE)
	{
		//���
		m_foodName.Empty();
		m_price = 0.0f;
		m_py.Empty();
		m_repertory = FALSE;
		UpdateData(FALSE);
		m_GuiEditName.SetFocus();
		m_GuiDelButton.SetWindowText(_T("ɾ��"));
		m_GuiDelButton.EnableWindow(FALSE);
		m_GuiButtonAdd.SetWindowText(_T("���"));
		m_isModify = FALSE;
		m_GuiComboKind.EnableWindow(TRUE);

	}
	else
	{
		int result = MessageBox(_T("ȷ��Ҫɾ��?"),_T("��ʾ"),MB_ICONINFORMATION|MB_YESNO);
		if ( IDYES  == result ){
			
			hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
			
			//DELETE
			menuInfoCtrl.Delete(m_menuMap[nPos].first);

			int food_id = m_menuMap[nPos].first;
			/* ����� �ײ�ҲҪɾ��*/
			if ( m_menuMap[nPos].second == hotelMIS::HFoodKind::TC)
				menuInfoCtrl.delTaoCan(m_menuMap[nPos].first);
			//��ǰ��̨�����Ҳɾ�� 
			hotelMIS::HBeforeRepCtrl beforeRepCtrl(m_con.get_con());
			hotelMIS::HBehindRepCtrl behindRepCtrl(m_con.get_con());
			beforeRepCtrl.Delete(food_id);
			behindRepCtrl.Delete(food_id);

			m_GuiDelButton.EnableWindow(FALSE);
		
			Refresh();
		}
	}
}

void CMenuManagerDialog::OnNMRclickListMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrl.ScreenToClient(&point);
	if (( m_nIndex = m_GuiListCtrl.HitTest(point)) != -1/*m_GuiListCtrl.GetSelectionMark())!= -1*/  ) {
		m_GuiListCtrl.ClientToScreen(&point);
		CMenu m_popupMenu;
		m_popupMenu.LoadMenu(IDR_MANAGER_MENU);
		m_popupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
		TRACE("�һ�����%d \n",m_nIndex);
	}
	*pResult = 0;
}

void CMenuManagerDialog::OnNMDblclkListMenu(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: �޸�
	/*DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrl.ScreenToClient(&point);
	if (( m_nIndex = m_GuiListCtrl.HitTest(point)) != -1 ) {
		OnPopupModifymenu();
		TRACE("˫������%d \n",m_nIndex);
	}*/
	
	int nPos = m_GuiListCtrl.GetSelectionMark();
	if ( nPos != -1 ){
		int food_id = m_menuMap[nPos].first;
		int kind_id = m_menuMap[nPos].second;
		OnPopupModifymenu();
		hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
		if ( foodKindCtrl.isInnerKind(kind_id) )
			m_GuiComboKind.EnableWindow(FALSE);
		else
			m_GuiComboKind.EnableWindow(TRUE);
		
	}
	
	*pResult = 0;
}

void CMenuManagerDialog::OnBnClickedDelButton()
{
	// TODO: 
	OnPopupDelmenu();
	
}

void CMenuManagerDialog::OnNMClickListMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrl.ScreenToClient(&point);
	if (( m_nIndex = m_GuiListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelButton.EnableWindow(TRUE);
		TRACE("��������%d \n",m_nIndex);
	}
	
	*pResult = 0;
}

void CMenuManagerDialog::OnBnClickedCheckRepertory()
{
	m_GuiCheckRepertory.SetCheck(m_GuiCheckRepertory.GetCheck() ? FALSE : TRUE);
	m_GuiCheckBoxRepNoCalc.SetCheck(FALSE);
}

void CMenuManagerDialog::OnBnClickedCheckRepertoryNocalc()
{
	m_GuiCheckBoxRepNoCalc.SetCheck(m_GuiCheckBoxRepNoCalc.GetCheck()? FALSE : TRUE);
	m_GuiCheckRepertory.SetCheck(FALSE);
}

void CMenuManagerDialog::OnCbnSelchangeComboFilter()
{
	// �������
	int nPos = m_GuiComboFilter.GetCurSel();
	if ( nPos == 0)	//��ʾȫ�����
	{
		m_GuiComboKind.ResetContent();
		m_kindMap.clear();
		hotelMIS::HFoodKindVec::iterator kit;
		m_GuiComboKind.AddString(_T("ȫ�����"));
		for ( kit = m_foodVec.begin(); kit != m_foodVec.end(); kit++)
		{
			int pos = m_GuiComboKind.AddString(kit->getKind_name().c_str());
			m_kindMap.insert(make_pair(pos,make_pair(kit->getKind_id(),kit->getKind_name())));
		}
		m_GuiComboKind.SetCurSel(0);
		m_GuiButtonAdd.EnableWindow(FALSE);	//ȫ����𲻿�����
		m_GuiDelButton.EnableWindow(FALSE);
		
	}
	else if ( nPos == 1) //����ʾǰ̨
	{
		m_GuiComboKind.ResetContent();
		m_kindMap.clear();
		hotelMIS::HFoodKindVec::iterator kit;
		m_GuiComboKind.AddString(_T("��ѡ��"));
		int pos = 0;
		for ( kit = m_foodVec.begin(); kit != m_foodVec.end(); kit++)
		{
			if ( kit->kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG)
			{
				pos = m_GuiComboKind.AddString(kit->getKind_name().c_str());
				m_kindMap.insert(make_pair(pos,make_pair(kit->getKind_id(),kit->getKind_name())));
			}
		}
		m_GuiComboKind.SetCurSel(0);
		m_GuiButtonAdd.EnableWindow(FALSE);	//��ѡ�񲻿���
		m_GuiDelButton.EnableWindow(FALSE);
	}
	else if ( nPos == 2)	//����ʾ��̨
	{
		m_GuiComboKind.ResetContent();
		m_kindMap.clear();
		hotelMIS::HFoodKindVec::iterator kit;
		m_GuiComboKind.AddString(_T("��ѡ��"));
		int pos = 0;
		for ( kit = m_foodVec.begin(); kit != m_foodVec.end(); kit++)
		{
			if ( kit->kind_flag == hotelMIS::HFoodKind::HOUCHU_FLAG)
			{
				pos = m_GuiComboKind.AddString(kit->getKind_name().c_str());
				m_kindMap.insert(make_pair(pos,make_pair(kit->getKind_id(),kit->getKind_name())));
			}
		}
		m_GuiComboKind.SetCurSel(0);
		m_GuiButtonAdd.EnableWindow(FALSE);	
		m_GuiDelButton.EnableWindow(FALSE);
	}
	
}

void CMenuManagerDialog::PrintView()
{
	
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListCtrl.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListCtrl.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawView, PrnInfo);
	DlgPreView.DoModal();
}

void CMenuManagerDialog::OnBnClickedPrintMenuButton()
{
	//��ӡ�˵�
	PrintView();
}

void CMenuManagerDialog::DrawView(CDC &memDC, PRNINFO PrnInfo)
{
	if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//��ǰҳ
	BOOL IsPrint = PrnInfo.IsPrint;		//�Ƿ��ӡ
	int nMaxPage = PrnInfo.nCountPage;	//���ҳ��
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");
	csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);

	
	TCHAR szTitle[255];
	wsprintf(szTitle,TEXT("%s ���ױ���"),m_hotelname.GetBuffer());
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8,rt9,rt10;
	int w1=13,w2=50,w3=18,w4=22,w5=14,w6=18,w7=22,w8=18,w9=22,w10=30;

	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont,PFont, *oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//Ʒ������
	PFont.CreateFont(-MulDiv(11,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//ϸ������
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//�ֱ�
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

 	DOUBLE xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	DOUBLE yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

	DOUBLE xPix = (DOUBLE)xP*10/254;	//ÿ mm ��ȵ�����
	DOUBLE yPix = (DOUBLE)yP*10/254;	//ÿ mm �߶ȵ�����
	DOUBLE fAdd = 7*yPix;		//ÿ�������
	DOUBLE nTop = 32*yPix;		//��һҳ������
	int	  iStart = 0;			//�ӵڼ��п�ʼ��ȡ
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 12*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-12);	//������



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//������ӡ����
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//��ʼ�ĵ���ӡ
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "���ӵ���ӡ������!", "����", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 30*yPix;		//��һҳ������
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//��ʼҳ
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("��ӡʧ��!"), "����", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//��ӡ
				//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,nRight,yPix*40);
			memDC.DrawText(m_exp,&rc,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			CString t;
			t.Format("�Ʊ���:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		
		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+w1*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + w2*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + w3*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + w4*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + w5*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);*/
		

		memDC.DrawText("���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��λ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ʦ", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		

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
		rt6.SetRect(rt5.right, rt1.top,rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);*/
			

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, sz1, 32);
			ListView_GetItemText(hList, i+iStart, 1, sz2, 32);
			ListView_GetItemText(hList, i+iStart, 2, sz3, 32);
			ListView_GetItemText(hList, i+iStart, 3, sz4, 32);
			ListView_GetItemText(hList, i+iStart, 4, sz5, 32);
			ListView_GetItemText(hList, i+iStart, 5, sz6, 32);
			/*ListView_GetItemText(hList, i+iStart, 6, sz7, 32);
			ListView_GetItemText(hList, i+iStart, 7, sz8, 32);
			ListView_GetItemText(hList, i+iStart, 8, sz9, 32);
			ListView_GetItemText(hList, i+iStart, 9, sz10, 32);*/


			memDC.DrawText(sz1, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz2, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz3, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz4, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz5, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz6, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			/*memDC.DrawText(sz7, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz8, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz9, &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz10, &rt10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
			
		//	//�º���
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
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			/*memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rt8.right, rt1.top);
			memDC.LineTo(rt8.right, rt1.bottom);
			memDC.MoveTo(rt9.right, rt1.top);
			memDC.LineTo(rt9.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);*/
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
			/*rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;
			rt9.top = rt1.top;
			rt9.bottom = rt1.bottom;
			rt10.top = rt1.top;
			rt10.bottom = rt1.bottom;*/

			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β
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
		//��ӡԤ��
		
		
		//�߿���
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	
		
		//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,nRight,yPix*40);
			memDC.DrawText(m_exp,&rc,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			CString t;
			t.Format("�Ʊ���:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		
		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+w1*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + w2*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + w3*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + w4*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + w5*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);*/
		

		memDC.DrawText("���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��λ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ʦ", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		

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
		rt6.SetRect(rt5.right, rt1.top,rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + w7*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + w8*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rt8.right + w9*xPix, rt1.bottom);
		rt10.SetRect(rt9.right,rt1.top, rc.right , rt1.bottom);*/
			

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, sz1, 32);
			ListView_GetItemText(hList, i+iStart, 1, sz2, 32);
			ListView_GetItemText(hList, i+iStart, 2, sz3, 32);
			ListView_GetItemText(hList, i+iStart, 3, sz4, 32);
			ListView_GetItemText(hList, i+iStart, 4, sz5, 32);
			ListView_GetItemText(hList, i+iStart, 5, sz6, 32);
			/*ListView_GetItemText(hList, i+iStart, 6, sz7, 32);
			ListView_GetItemText(hList, i+iStart, 7, sz8, 32);
			ListView_GetItemText(hList, i+iStart, 8, sz9, 32);
			ListView_GetItemText(hList, i+iStart, 9, sz10, 32);*/


			memDC.DrawText(sz1, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz2, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz3, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz4, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz5, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz6, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			/*memDC.DrawText(sz7, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz8, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz9, &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(sz10, &rt10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
			
		//	//�º���
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
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			/*memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rt8.right, rt1.top);
			memDC.LineTo(rt8.right, rt1.bottom);
			memDC.MoveTo(rt9.right, rt1.top);
			memDC.LineTo(rt9.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);*/
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
			/*rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;
			rt9.top = rt1.top;
			rt9.bottom = rt1.bottom;
			rt10.top = rt1.top;
			rt10.bottom = rt1.bottom;*/

			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β

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
