// InRepDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "InRepDlg.h"
#include ".\outrepdlg.h"

#include "HFoodKindCtrl.h"
#include "HMenuInfoCtrl.h"
#include "HBeforeRepCtrl.h"
#include "HBehindRepCtrl.h"
#include "HAdminBdy.h"
#include "HInOutRepCtrl.h"
#include "RepDelDlg.h"
#include "InPrint.h"
#include "HBehindRepCtrl.h"
#include "HSetHotelPrintMsg.h"
#include "PreParent.h"

// COutRegDlg �Ի���
CString COutRegDlg::m_exp;
CString COutRegDlg::m_hotelname;

IMPLEMENT_DYNAMIC(COutRegDlg, CDialog)
COutRegDlg::COutRegDlg(CWnd* pParent /*=NULL*/)
: CDialog(COutRegDlg::IDD, pParent)
, m_py(_T(""))
,m_bIsTree(TRUE)
, m_title(_T(""))
, m_inout_dh(_T(""))
, m_bSendBefore(FALSE)
, isOut(false)
{
	m_listInOutRep.clear();
}

COutRegDlg::~COutRegDlg()
{
}

void COutRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PY, m_GuiEditPy);
	DDX_Control(pDX, IDC_BUTTON_EXT, m_GuiBtnExt);
	DDX_Control(pDX, IDC_BUTTON_TREE, m_GuiBtnTree);
	DDX_Control(pDX, IDC_BUTTON_LIST, m_GuiBtnList);
	DDX_Control(pDX, IDC_MENU_TREE, m_GuiMenuTree);
	DDX_Control(pDX, IDC_MENU_LIST, m_GuiMenuList);
	DDX_Control(pDX, IDC_BUTTON_MOVE_RIGHT, m_GuiBtnAdd);
	DDX_Control(pDX, IDC_BUTTON_MOVE_LEFT, m_GuiBtnDel);
	DDX_Control(pDX, IDC_LIST_INREP, m_GuiListRep);
	DDX_Control(pDX, IDC_BUTTON_INREP, m_GuiBtnInRep);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
	DDV_MaxChars(pDX, m_py, 20);
	DDX_Control(pDX, IDCANCEL, m_GuiBtnCancel);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiBtnPrint);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_GuiStaticTitle);
	DDX_Control(pDX, IDC_BUTTON_PERVIEW, m_GuiBtnPerView);
	DDX_Control(pDX, IDC_CHECK_SENDBEFORE, m_GuiCheckSendBefore);
	DDX_Check(pDX, IDC_CHECK_SENDBEFORE, m_bSendBefore);
}


BEGIN_MESSAGE_MAP(COutRegDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT_PY, OnEnChangeEditPy)
	ON_BN_CLICKED(IDC_BUTTON_EXT, OnBnClickedButtonExt)
	ON_BN_CLICKED(IDC_BUTTON_TREE, OnBnClickedButtonTree)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnBnClickedButtonList)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_RIGHT, OnBnClickedButtonMoveRight)
	ON_NOTIFY(NM_CLICK, IDC_MENU_TREE, OnNMClickMenuTree)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_TREE, OnNMDblclkMenuTree)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INREP, OnNMClickListInrep)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_LEFT, OnBnClickedButtonMoveLeft)
	ON_BN_CLICKED(IDC_BUTTON_INREP, OnBnClickedButtonInrep)
	ON_NOTIFY(NM_CLICK, IDC_MENU_LIST, OnNMClickMenuList)
	ON_NOTIFY(NM_DBLCLK, IDC_MENU_LIST, OnNMDblclkMenuList)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_PERVIEW, OnBnClickedButtonPerview)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COutRegDlg ��Ϣ�������

//-------------------------------------------------------------------------------------------------------------
BOOL COutRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWinApp* pApp = AfxGetApp();
	m_bRepOpen = pApp->GetProfileInt("Settings", "repOpen",0);
	if ( m_bRepOpen == TRUE) 
	{
		m_GuiCheckSendBefore.ShowWindow(SW_SHOW);
	}

	::SetCursor(::LoadCursor(NULL,IDC_WAIT));
	//��ʼ�� button style
	m_GuiBtnExt.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnAdd.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnDel.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnInRep.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnCancel.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnPrint.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnPerView.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiBtnExt.ShowText();
	m_GuiBtnAdd.ShowText();
	m_GuiBtnDel.ShowText();
	m_GuiBtnInRep.ShowText();
	m_GuiBtnCancel.ShowText();
	m_GuiBtnPrint.ShowText();
	m_GuiBtnPerView.ShowText();
	//Ĭ��Ϊ���б�
	m_GuiBtnTree.SetCheck(1);

	Init();
	//Ĭ�Ͻ��� ƴ������
	m_GuiEditPy.EnableWindow(FALSE);
	m_GuiBtnAdd.EnableWindow(FALSE);
	m_GuiBtnDel.EnableWindow(FALSE);

	m_font.CreatePointFont(180,_T("����"));
	m_GuiStaticTitle.SetFont(&m_font);

	m_GuiStaticTitle.SetWindowText(_T("��Ʒ����"));

	CTime t = CTime::GetCurrentTime();
	m_inout_dh.Format("%s",t.Format("CK%y%m%d%H%M%S"));

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	GetDlgItem(IDC_STATIC_ZDH)->SetWindowText(m_inout_dh);

	m_exp.Format("�˵���:%s  ��������:%s",m_inout_dh,t.Format("%y-%m-%d %H:%M:%S"));
	//m_exp.Format("%s ",m_hotelname);
	::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::Init()
{
	// ������Ʒ�б���
	int i = 0;
	m_GuiMenuList.InsertColumn(i,_T("���"),LVCFMT_LEFT,40);
	m_GuiMenuList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,160);
	m_GuiMenuList.InsertColumn(++i,_T("����"),LVCFMT_RIGHT,70);
	m_GuiMenuList.InsertColumn(++i,_T("��ǰ���"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiMenuList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	i = 0;
	m_GuiListRep.InsertColumn(i,_T("���"),LVCFMT_LEFT,40);
	m_GuiListRep.InsertColumn(++i,_T("����"),LVCFMT_LEFT,160);
	m_GuiListRep.InsertColumn(++i,_T("��λ"),LVCFMT_LEFT,40);
	m_GuiListRep.InsertColumn(++i,_T("����"),LVCFMT_LEFT,40);
	m_GuiListRep.InsertColumn(++i,_T("����"),LVCFMT_RIGHT,70);
	m_GuiListRep.InsertColumn(++i,_T("���"),LVCFMT_RIGHT,60);

	ListView_SetExtendedListViewStyleEx(m_GuiListRep.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	Refresh();

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
	//hotelMIS::HBehindRepCtrl bRepCtrl(m_con.get_con());
	for ( kIt = kindVec.begin(); kIt != kindVec.end(); kIt++)
	{
		//���˵��ײ����
		if ( kIt->kind_id == hotelMIS::HFoodKind::TC ){ 
			//m_menuVec.erase(mIt);
			continue;
		}

		if ( m_bRepOpen == FALSE){
			if ( kIt->kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG)
				continue;
		}
		//������
		hRoot = m_GuiMenuTree.InsertItem(kIt->getKind_name().c_str(),TVI_ROOT);

		m_GuiMenuTree.SetItemData(hRoot,(DWORD)kIt->getKind_id());
		m_GuiMenuTree.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);
		menuVec = menuInfoCtrl.getMenuInfoByKind( kIt->getKind_id() );
		for ( mIt = menuVec.begin(); mIt != menuVec.end(); mIt++)
		{
			//������ڿ��� �� ���ڿ������  ��ʾ
			if ( mIt->repertory_flag == hotelMIS::HMenuInfo::REP_CALC ||
				mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NOCALC) {
					//���� food_id ��� Ҫ�����Ʒ�Ŀ����������۸�
					//int nRep = bRepCtrl.getCurRep(mIt->food_id);
					temp.Format("%s",mIt->food_name.c_str());
					hChild = m_GuiMenuTree.InsertItem(temp,hRoot);
					if ( hChild != NULL)
						m_GuiMenuTree.SetItemData(hChild,(DWORD)mIt->food_id);
				}
		}
		m_GuiMenuTree.Expand(hRoot,TVE_EXPAND);

	}

	//��ʼ���б�

	//��̨���
	hotelMIS::HBehindRepCtrl bRepCtrl(m_con.get_con());

	//��¼���������,�Ա�ӿ��ٶ�
	m_menuVec =menuInfoCtrl.getAllMenuInfo();	
	//m_menuVec = hotelMIS::HMenuInfoCtrl::menuInfoFactory();

	i = 0;
	m_menuListMap.clear();
	CString t;
	for ( mIt = m_menuVec.begin(); mIt != m_menuVec.end(); mIt++)
	{
		//������ڿ��� �� ���ڿ������  ��ʾ
		//if ( mIt->repertory_flag == hotelMIS::HMenuInfo::REP_CALC ||
		// mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NOCALC) 
		//{

		//	m_menuListMap.insert(make_pair(i,mIt->food_id));
		//	t.Format("%d",i+1);
		//	//���
		//	m_GuiMenuList.InsertItem(i,t);
		//	//����
		//	m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
		//	//����
		//	t.Format("%.2f",mIt->food_price);
		//	m_GuiMenuList.SetItemText(i,2,t);
		//	//��õ�ǰ���
		//	t.Format("%d",bRepCtrl.getCurRep(mIt->food_id));
		//	m_GuiMenuList.SetItemText(i,3,t);
		//	i++;
		//}

		if ( m_bRepOpen == TRUE && mIt->foodKind.kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG){
			//ֻ��ʾ�����c
			continue;
		}else {
			//�����ײͺͷǿ��Ʒ
			if ( mIt->bTaocan || mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NO){ 
				continue;
			}
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
		//��ǰ���
		t.Format("%.2f",bRepCtrl.getCurRep(mIt->food_id));
		m_GuiMenuList.SetItemText(i,3,t);
		i++;

	}

}

//------------------------------------------------------------------------------------------------------------
void COutRegDlg::Refresh()
{
	int i = 0;
	CString temp;
	list<hotelMIS::HInOutRep>::iterator it = m_listInOutRep.begin();

	m_GuiListRep.DeleteAllItems();
	m_repListMap.clear();
	float fSum = 0.0f;
	for ( ; it != m_listInOutRep.end(); it++)
	{
		m_repListMap.insert(make_pair(i,it->food_id));
		//���
		temp.Format("%d",it->food_id);m_GuiListRep.InsertItem(i,temp);
		//����
		m_GuiListRep.SetItemText(i,1,it->food_name.c_str());
		//��λ
		m_GuiListRep.SetItemText(i,2,it->food_unit.c_str());
		//����
		temp.Format("%.2f",it->food_num);m_GuiListRep.SetItemText(i,3,temp);
		//����
		temp.Format("%.2f",it->food_price);	m_GuiListRep.SetItemText(i,4,temp);
		//���
		temp.Format("%.2f",it->food_price * it->food_num);m_GuiListRep.SetItemText(i,5,temp);
		fSum += it->food_price * it->food_num;
		i++;
	}
	//�ϼ�
	m_GuiListRep.InsertItem(i,_T("�ϼ�:"));
	temp.Format("%.2f",fSum);m_GuiListRep.SetItemText(i,5,temp);

	m_GuiBtnInRep.EnableWindow(m_listInOutRep.empty() ? FALSE : TRUE);
	m_GuiBtnPrint.EnableWindow(m_listInOutRep.empty() ? FALSE : TRUE);
	m_GuiBtnPerView.EnableWindow(m_listInOutRep.empty() ? FALSE : TRUE);

}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnEnChangeEditPy()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

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
	hotelMIS::HBehindRepCtrl behindRepCtrl(m_con.get_con());
	hotelMIS::HMenuInfoVec::iterator it;



	for ( it = vec.begin(); it != vec.end(); it++)
	{
		if ( m_bRepOpen == FALSE && it->foodKind.kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG){
			//ֻ��ʾ�����c
			continue;
		}else {
			//�����ײͺͷǿ��Ʒ
			if ( it->bTaocan || it->repertory_flag == hotelMIS::HMenuInfo::REP_NO){ 
				continue;
			}
		}

		m_menuListMap.insert(make_pair(i,it->food_id));

		//���
		t.Format("%d",it->food_id); m_GuiMenuList.InsertItem(i,t);
		//����
		m_GuiMenuList.SetItemText(i,1,it->food_name.c_str());
		//����
		t.Format("%.2f",it->food_price); m_GuiMenuList.SetItemText(i,2,t);
		//��ǰ���
		t.Format("%.2f",behindRepCtrl.getCurRep(it->food_id)); m_GuiMenuList.SetItemText(i,3,t);
		i++;
	}

}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnBnClickedButtonExt()
{
	// ��,������չ��
	HTREEITEM htreeItem = m_GuiMenuTree.GetRootItem();;
	while ( htreeItem != NULL){
		m_GuiMenuTree.Expand(htreeItem,TVE_TOGGLE);
		htreeItem = m_GuiMenuTree.GetNextItem(htreeItem,TVGN_NEXT);
	}
}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnBnClickedButtonTree()
{
	m_bIsTree = TRUE;
	m_GuiMenuTree.ShowWindow(SW_SHOW);

	m_GuiMenuList.ShowWindow(SW_HIDE);

	m_GuiEditPy.EnableWindow(FALSE);

	m_GuiBtnExt.EnableWindow(TRUE);
	m_GuiBtnAdd.EnableWindow(FALSE);
}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnBnClickedButtonList()
{
	m_bIsTree = FALSE;
	m_GuiMenuTree.ShowWindow(SW_HIDE);

	m_GuiMenuList.ShowWindow(SW_SHOW);

	m_GuiEditPy.EnableWindow(TRUE);

	m_GuiBtnExt.EnableWindow(FALSE);
	m_GuiBtnAdd.EnableWindow(FALSE);
}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnBnClickedButtonMoveRight()
{
	// ������б������

	if ( isOut == true ) return ;

	hotelMIS::HMenuInfo menuInfo;
	int food_id = 0;

	if ( m_bIsTree )
	{
		HTREEITEM hItem,hParent;
		if (hItem = m_GuiMenuTree.HitTest(m_point)) {  //��ⵥ�����ڵ�
			hParent = m_GuiMenuTree.GetParentItem(hItem);
			if ( hParent== NULL ){
				return;
			}
			else{
				//ѡ�е��ǲ���
				food_id = m_GuiMenuTree.GetItemData(hItem);
			}
		}
	}
	else
	{
		int nPos = m_GuiMenuList.GetSelectionMark();
		if ( nPos != -1 ){
			food_id = m_menuListMap[nPos];
		}else{
			MessageBox(_T("����ѡ��������Ʒ��"),_T("��ʾ"),MB_OK);
			return;
		}
	}
	ASSERT( food_id != 0);
	if ( food_id == 0) return;

	hotelMIS::HMenuInfoCtrl menuInfoCtrl(m_con.get_con());
	menuInfo = menuInfoCtrl.getMenuInfo(food_id);

	hotelMIS::HBehindRepCtrl behindRepCtrl(m_con.get_con());

	//��ȡ������Ϣ������ӶԻ���
	CRepDelDlg dlg;
	dlg.m_bh = menuInfo.food_id;
	dlg.m_kindName = menuInfo.foodKind.kind_name.c_str();
	dlg.m_name = menuInfo.food_name.c_str();
	float price = behindRepCtrl.getOutPrice(menuInfo.food_id);
	dlg.m_price = price;
	dlg.m_repNum = behindRepCtrl.getCurRep(menuInfo.food_id);
	if ( dlg.DoModal() == IDOK){

		hotelMIS::HBehindRepCtrl behindRepCtrl(m_con.get_con());

		CTime time=CTime::GetCurrentTime();
		float num = dlg.m_num;
		hotelMIS::HInOutRep inRep;
		inRep.food_id = food_id;
		inRep.inout_dh = m_inout_dh.GetBuffer();
		inRep.food_name = menuInfo.food_name;
		inRep.food_unit = menuInfo.food_unit;
		inRep.food_num = num;
		inRep.food_price = price;
		inRep.opdate = time.Format(_T("%Y-%m-%d %H:%M-%S")).GetBuffer();
		inRep.rep_flag = hotelMIS::HInOutRep::OUT_REP;
		hotelMIS::HBehindRep bRep = behindRepCtrl.calc(food_id,num,price,hotelMIS::HInOutRep::OUT_REP);
		inRep.t_num =	bRep.rep_num;
		inRep.t_price = bRep.food_price;
		inRep.t_sprice =bRep.total_price;
		inRep.ad_name = hotelMIS::HAdminBdy::_ad_name;

		list<hotelMIS::HInOutRep>::iterator it = m_listInOutRep.begin();
		for ( ; it != m_listInOutRep.end(); it++)
		{
			if ( it->food_id == food_id )
			{
				MessageBox(_T("�Ѿ�����!�޷����!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
				break;
			}
		}

		//�����б��г���
		if ( it == m_listInOutRep.end()){
			m_listInOutRep.push_back(inRep);
			Refresh();
		}

		m_GuiBtnAdd.EnableWindow(FALSE);
	}
}

//----------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( isOut == true ) return ;	

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

	*pResult = 0;
}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( isOut == true ) return ;

	OnBnClickedButtonMoveRight();

	*pResult = 0;
}



//------------------------------------------------------------------------------------------------------
void COutRegDlg::OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( isOut == true ) return ;

	// ���������Ʒ�б�
	*pResult = 0;
	if ( m_GuiMenuList.GetSelectionMark() != -1){
		m_GuiBtnAdd.EnableWindow(TRUE);
		m_GuiBtnDel.EnableWindow(FALSE);
	}

}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( isOut == true ) return ;
	// ��� ��Ʒ�б�
	*pResult = 0;
	OnBnClickedButtonMoveRight();
}

//--------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnBnClickedButtonMoveLeft()
{
	if ( isOut == true ) return ;

	int nPos = m_GuiListRep.GetSelectionMark();
	if ( nPos != -1){

		int r = MessageBox(_T("ȷ��Ҫ�Ƴ�������?"),_T("��ʾ"),MB_ICONINFORMATION|MB_YESNO);
		if ( r == IDNO)
			return;

		int food_id = m_repListMap[nPos];

		list<hotelMIS::HInOutRep>::iterator it = m_listInOutRep.begin();

		for ( ; it != m_listInOutRep.end(); it++)
		{
			if ( it->food_id == food_id ){
				m_listInOutRep.erase(it);
				break;
			}
		}
		Refresh();
		m_GuiBtnDel.EnableWindow(FALSE);
	}
}

//-------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnNMClickListInrep(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( isOut == true ) return ;

	*pResult = 0;
	if ( m_GuiListRep.GetSelectionMark() != -1){
		m_GuiBtnDel.EnableWindow(TRUE);
		m_GuiBtnAdd.EnableWindow(FALSE);
	}
}

//--------------------------------------------------------------------------------------------------------------
void COutRegDlg::OnBnClickedButtonInrep()
{
	if ( isOut == true ) return ;

	if ( m_listInOutRep.empty() )
	{
		MessageBox(_T("�������Ҫ�������Ʒ"),_T("��ʾ"),MB_OK);
		return;
	}

	UpdateData();
	//���
	int r = MessageBox(_T("ȷ��Ҫ������?"),_T("��ʾ"),MB_ICONQUESTION|MB_YESNO);
	if ( r == IDNO)
		return;

	hotelMIS::HInOutRepCtrl repCtrl(m_con.get_con());

	repCtrl.enter(m_listInOutRep);
	isOut = true;
	m_GuiBtnInRep.EnableWindow(FALSE);

	if ( m_bSendBefore ){
		repCtrl.updateBeforeRep(m_listInOutRep);
		MessageBox(_T("��Ʒ����ɹ�!ǰ̨����Ѿ�����!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);

	}else{

		MessageBox(_T("��Ʒ����ɹ�!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
	}
	//OnOK();
}

void COutRegDlg::OnBnClickedButtonPrint()
{
	/*InPrint print(m_listInOutRep);
	if ( print.CreateExcel() == true){
	print.LoadTemplate("\\tmpl\\outrep");
	print.SendExcel();
	print.SaveAs(_T("���ⵥ"));
	print.Print();
	}*/
	PrintView();
}

void COutRegDlg::OnBnClickedButtonPerview()
{
	//��ӡԤ�� 
	/*InPrint print(m_listInOutRep);
	if ( print.CreateExcel() == true){
	print.LoadTemplate("\\tmpl\\outrep");
	print.SendExcel();
	print.SaveAs();
	print.PrintPreview();
	}*/
}

void COutRegDlg::PrintView()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListRep.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListRep.GetItemCount();

	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawDC, PrnInfo);
	DlgPreView.DoModal();
}

void COutRegDlg::DrawDC(CDC &memDC, PRNINFO PrnInfo)
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
	wsprintf(szTitle,TEXT("%s ���ⵥ"),m_hotelname.GetBuffer());

	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, PFont,*oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//����������
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

	int xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	int yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

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

	DOUBLE nLeft = 15*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-15);	//������



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
					//ϸ��
					memDC.SelectObject(&DetailFont);
					rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
					//�Ϻ���
					memDC.MoveTo(rc.left, rc.top);
					memDC.LineTo(rc.right, rc.top);

					rt1.SetRect(nLeft, nTop, nLeft+20*xPix, nTop+fAdd);					
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
					rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
					rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
					/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
					rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
					//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

					memDC.DrawText("���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("��λ", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("����", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("����", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("���", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					/*memDC.DrawText("����ȯ", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("ʵ���˿�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
					//memDC.DrawText("�ϼ�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
					/*memDC.MoveTo(rt7.right, rt1.top);
					memDC.LineTo(rt7.right, rt1.bottom);*/
					memDC.MoveTo(rc.left, rt1.bottom);
					memDC.LineTo(rc.right, rt1.bottom);

					TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
					rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
					rt1.SetRect(nLeft, nTop+fAdd, nLeft+20*xPix, nTop+2*fAdd);					
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
					rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);	
					rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
					/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
					rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
					//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

					int nCountItem = ListView_GetItemCount(hList);
					for(int i=0;i<nItem; i++)
					{
						ListView_GetItemText(hList, i+iStart, 0, szID, 32);
						ListView_GetItemText(hList, i+iStart, 1, szName, 32);
						ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
						ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
						ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
						ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
						/*ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
						ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);*/

						memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						/*memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/

						//�º���
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
						/*memDC.MoveTo(rt7.right, rt1.top);
						memDC.LineTo(rt7.right, rt1.bottom);*/
						memDC.MoveTo(rc.left, rt1.bottom);
						memDC.LineTo(rc.right, rt1.bottom);

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
						rt8.bottom = rt1.bottom;*/

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
		//ϸ��
		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+20*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��λ", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		/*memDC.DrawText("����ȯ", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("ʵ���˿�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
		//memDC.DrawText("�ϼ�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
		/*memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);*/
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+20*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);	
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
			ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
			/*ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
			ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);*/

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			/*memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/

			//�º���
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
			/*memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);*/
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);

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
			rt8.bottom = rt1.bottom;*/

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

HBRUSH COutRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch ( pWnd->GetDlgCtrlID() )
	{
	case IDC_STATIC_TITLE:
		pDC->SetTextColor(RGB(0,0,255));
		break;
	case IDC_STATIC_ZDH:
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
	}
	return hbr;
}
