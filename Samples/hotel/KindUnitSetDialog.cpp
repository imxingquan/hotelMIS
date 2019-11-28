// KindUnitSetDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "KindUnitSetDialog.h"
//#include ".\kindunitsetdialog.h"

#include "HUnitCtrl.h"
#include "HFoodKindCtrl.h"
#include "MyCdKey.h"
#include "RegisterDialog.h"

// CKindUnitSetDialog �Ի���

IMPLEMENT_DYNAMIC(CKindUnitSetDialog, CDialog)
CKindUnitSetDialog::CKindUnitSetDialog(BOOL IsBehindKc, CWnd* pParent /*=NULL*/)
	: CDialog(CKindUnitSetDialog::IDD, pParent)
	, m_unit(_T("")),
	m_nIndex(-1),
	m_modifyFlag(false)
	, m_kindName(_T(""))
	, m_allAdd(FALSE)
	, m_ts(FALSE)
	, m_bKcKind(FALSE)
	,m_isBehindKc(IsBehindKc)
	, m_kindZK(FALSE)
	, m_zdyCheck(FALSE)
{
}

CKindUnitSetDialog::~CKindUnitSetDialog()
{
}

void CKindUnitSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_EDIT_UNIT, m_GuiEditUnit);
	DDX_Control(pDX, IDC_BUTTON_UNIT_ADD, m_GuiButtonAddUnit);
	DDX_Control(pDX, IDC_BUTTON_UNIT_DEL, m_GuiButtonDelUnit);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_unit);
	DDX_Control(pDX, IDC_UNIT_LIST, m_GuiUnitListCtrl);
	DDX_Control(pDX, IDC_GROUPBOXL, m_GuiGroupBoxL);
	DDX_Control(pDX, IDC_KIND_EDIT, m_GuiKindEdit);
	DDX_Control(pDX, IDC_ADDKIND_BUTTON, m_GuiAddKindButton);
	DDX_Control(pDX, IDC_DELKIND_BUTTON, m_GuiDelKindButton);
	DDX_Control(pDX, IDC_KIND_LIST, m_GuiKindListCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_GuiAllAddCheck);
	DDX_Control(pDX, IDC_CHECK2, m_GuiTsCheck);
	DDX_Text(pDX, IDC_KIND_EDIT, m_kindName);
	DDX_Check(pDX, IDC_CHECK1, m_allAdd);
	DDX_Check(pDX, IDC_CHECK2, m_ts);
	DDX_Check(pDX, IDC_CHECK_KCKIND, m_bKcKind);
	DDX_Check(pDX, IDC_KIND_ZK_CHECK, m_kindZK);
	DDX_Check(pDX, IDC_ZDY_CHECK, m_zdyCheck);
}


BEGIN_MESSAGE_MAP(CKindUnitSetDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UNIT_ADD, OnBnClickedButtonUnitAdd)
	ON_BN_CLICKED(IDC_BUTTON_UNIT_DEL, OnBnClickedButtonUnitDel)
	ON_NOTIFY(NM_CLICK, IDC_UNIT_LIST, OnNMClickUnitList)
	ON_EN_CHANGE(IDC_EDIT_UNIT, OnEnChangeEditUnit)
	ON_BN_CLICKED(IDC_ADDKIND_BUTTON, OnBnClickedAddkindButton)
	ON_BN_CLICKED(IDC_DELKIND_BUTTON, OnBnClickedDelkindButton)
	ON_EN_CHANGE(IDC_KIND_EDIT, OnEnChangeKindEdit)
	ON_NOTIFY(NM_CLICK, IDC_KIND_LIST, OnNMClickKindList)
	ON_NOTIFY(NM_DBLCLK, IDC_KIND_LIST, OnNMDblclkKindList)
END_MESSAGE_MAP()


// CKindUnitSetDialog ��Ϣ�������
void CKindUnitSetDialog::Init()
{
	m_GuiUnitListCtrl.InsertColumn(0,_T("���"),LVCFMT_LEFT,40);
	m_GuiUnitListCtrl.InsertColumn(1,_T("��λ"),LVCFMT_LEFT,100);
	
	ListView_SetExtendedListViewStyleEx(m_GuiUnitListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_GuiButtonDelUnit.EnableWindow(FALSE);
	m_GuiButtonAddUnit.EnableWindow(FALSE);
	Refresh();
}

void CKindUnitSetDialog::Refresh()
{
	m_GuiUnitListCtrl.DeleteAllItems();
	hotelMIS::HUnitCtrl unitCtrl(m_con.get_con());
	hotelMIS::HUnitVec vec = unitCtrl.getAllUnit();
	hotelMIS::HUnitVec::iterator it;
	int i =0;
	CString cnt;
	m_unitMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_unitMap.insert(make_pair(i,it->getUnit_id()));
		cnt.Format("%d",i+1);
		m_GuiUnitListCtrl.InsertItem(i,cnt);
		m_GuiUnitListCtrl.SetItemText(i,1,it->getUnit_name().c_str());
		i++;
	}
}
void CKindUnitSetDialog::Init2()
{
	m_GuiKindListCtrl.InsertColumn(0,_T("���"),LVCFMT_LEFT,35);
	m_GuiKindListCtrl.InsertColumn(1,_T("����"),LVCFMT_LEFT,120);
	m_GuiKindListCtrl.InsertColumn(2,_T("�ۿ�"),LVCFMT_LEFT,60);
	m_GuiKindListCtrl.InsertColumn(3,_T("�Զ���۸�"),LVCFMT_LEFT,90);
	ListView_SetExtendedListViewStyleEx(m_GuiKindListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_GuiAddKindButton.EnableWindow(FALSE);
	m_GuiDelKindButton.EnableWindow(FALSE);

	GetDlgItem(IDC_CHECK_KCKIND)->ShowWindow(SW_HIDE);
	
	if ( m_isBehindKc == TRUE){
		
		SetWindowText(_T("���������"));
		m_GuiGroupBoxL.SetWindowText(_T("������"));
	}
	Refresh2();
}

void CKindUnitSetDialog::Refresh2()
{
	m_GuiKindListCtrl.DeleteAllItems();
	hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	hotelMIS::HFoodKindVec vec = foodKindCtrl.getAllKind();
	hotelMIS::HFoodKindVec::iterator  it;
	int i = 0;
	CString cnt;
	m_kindMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		//---------���ں��������---------------------------------------
		if ( m_isBehindKc == TRUE){
			if ( it->kind_flag != hotelMIS::HFoodKind::HOUCHU_FLAG)
				continue;
		}else if ( m_isBehindKc == FALSE && it->kind_flag == hotelMIS::HFoodKind::HOUCHU_FLAG){
				continue;
		}
		m_kindMap.insert(make_pair(i,it->getKind_id()));
		cnt.Format("%d",i+1);
		if(it->getKind_id()<0)
			cnt="*";
					
		m_GuiKindListCtrl.InsertItem(i,cnt);
		m_GuiKindListCtrl.SetItemText(i,1,it->getKind_name().c_str());
		m_GuiKindListCtrl.SetItemText(i,2,(it->getKind_zk() == 0 ?"��" : "��"));
		m_GuiKindListCtrl.SetItemText(i,3,(it->getZdy_price() == 0 ?"��" : "��"));
		
		i++;
	}
}

void CKindUnitSetDialog::OnBnClickedButtonUnitAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	hotelMIS::HUnitCtrl unitCtrl(m_con.get_con());
	unitCtrl.insert(hotelMIS::ReplaceChar(m_unit).GetBuffer());
	Refresh();
	m_unit.Empty();
	UpdateData(FALSE);
	m_GuiButtonAddUnit.EnableWindow(FALSE);
	
}

void CKindUnitSetDialog::OnBnClickedButtonUnitDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( m_nIndex != -1 ){
		TRACE("ɾ�����Ϊ:%d �ĵ�λ\n",m_unitMap[m_nIndex]);
		int result = AfxMessageBox(_T("ȷ��Ҫɾ��?"),MB_YESNO|MB_ICONWARNING);
		if ( result == IDYES){
			//Delete Code.....
			hotelMIS::HUnitCtrl unitCtrl(m_con.get_con());
			unitCtrl.Delete(m_unitMap[m_nIndex]);
			m_nIndex = -1;
			Refresh();
			m_GuiButtonDelUnit.EnableWindow(FALSE);
		}
	}
}

BOOL CKindUnitSetDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_GuiButtonAddUnit.ShowText();
	m_GuiButtonDelUnit.ShowText();
	m_GuiAddKindButton.ShowText();
	m_GuiDelKindButton.ShowText();
	
	Init();
	Init2();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CKindUnitSetDialog::OnNMClickUnitList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiUnitListCtrl.ScreenToClient(&point);
	if (( m_nIndex = m_GuiUnitListCtrl.HitTest(point)) != -1 ) {
		m_GuiButtonDelUnit.EnableWindow(TRUE);
		TRACE("��������%d \n",m_nIndex);
	}
	*pResult = 0;
}

void CKindUnitSetDialog::OnEnChangeEditUnit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if ( m_unit.Trim().GetLength() > 0 ){
		m_GuiButtonAddUnit.EnableWindow(TRUE);
	}else{
		m_GuiButtonAddUnit.EnableWindow(FALSE);
	}
}


void CKindUnitSetDialog::OnBnClickedAddkindButton()
{
	// TODO: ��Ӳ��� 
	//--------------------------------------------------------------------
	/*MyCdKey cdkey;
	if (!cdkey.RegisterCdKey() )
	{
		CRegisterDialog dlg;
		dlg.DoModal();
		return;
	}*/

		//-----------------------------------------------------------------------
		if ( false == m_modifyFlag){
			UpdateData(TRUE);
			hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
			
			// ���ں�̨���
			if ( m_isBehindKc == TRUE) m_bKcKind = true;
			
			foodKindCtrl.insert(hotelMIS::ReplaceChar(m_kindName).GetBuffer(),m_bKcKind,m_kindZK,m_zdyCheck);
			m_kindName.Empty();
			Refresh2();
			m_bKcKind = false;
			UpdateData(FALSE);
			m_GuiAddKindButton.EnableWindow(FALSE);
		}else {
			//�޸�
			UpdateData(TRUE);
			hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
			
			int kindId = m_kindMap[m_nIndex2];
			
			/*if ( foodKindCtrl.isInnerKind(kindId)){
				MessageBox(_T("ϵͳ������,�����޸�"),_T("����"),MB_ICONWARNING|MB_OK);
				return ;
			}*/

			hotelMIS::HFoodKind foodKind;
			foodKind.setKind_id(kindId);
			foodKind.setKind_name(hotelMIS::ReplaceChar(m_kindName).GetBuffer());
			// ���ں�̨���
			if ( m_isBehindKc == TRUE) m_bKcKind = true;
			foodKind.setKind_flag(m_bKcKind);
			foodKind.setKind_zk(m_kindZK);
			foodKind.setZdy_price(m_zdyCheck);

			foodKindCtrl.update(foodKind);
			m_kindName.Empty();
			Refresh2();
			m_modifyFlag = false;
			m_bKcKind = false;
			m_kindZK = false;
			m_zdyCheck = false;

			UpdateData(FALSE);
			m_GuiAddKindButton.SetWindowText(_T("���"));
			m_GuiAddKindButton.EnableWindow(FALSE);
		}
}

void CKindUnitSetDialog::OnBnClickedDelkindButton()
{
	// TODO: ɾ����
	//if ( m_nIndex2 != -1 ){
	//	TRACE("ɾ�����Ϊ:%d �Ĳ���\n",m_kindMap[m_nIndex2]);
	//	int result = AfxMessageBox(_T("ɾ�����ʱ,��ɾ����˹��������в�,ȷ��Ҫɾ��?"),MB_YESNO|MB_ICONWARNING);
	//	if ( result == IDYES){
	//		//Delete Code
	//		hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
	//		foodKindCtrl.Delete(m_kindMap[m_nIndex2]);
	//		m_nIndex2 = -1;
	//		m_modifyFlag = false;
	//		m_GuiAddKindButton.SetWindowText(_T("���"));
	//		m_kindName.Empty();
	//		m_allAdd = false;
	//		m_ts = false;
	//		UpdateData(FALSE);
	//		m_GuiAddKindButton.EnableWindow(FALSE);
	//		m_GuiDelKindButton.EnableWindow(FALSE);
	//		Refresh2();	
	//	}
	//}

	if ( m_nIndex2 != -1 ){
		
			hotelMIS::HFoodKindCtrl foodKindCtrl(m_con.get_con());
			int kindId = m_kindMap[m_nIndex2];
			
			if ( foodKindCtrl.isInnerKind(kindId) ){
				MessageBox(_T("ϵͳ������,����ɾ��!"),_T("����"),MB_ICONWARNING|MB_OK);
				return;
			}
					
			if ( foodKindCtrl.haveChild(kindId) ){
				MessageBox(_T("��������ʹ�ô���,����ɾ��!"),_T("��ʾ"),MB_ICONWARNING|MB_OK);
				return;
			}
			
			foodKindCtrl.Delete(kindId);
			m_nIndex2 = -1;
			m_modifyFlag = false;
			m_GuiAddKindButton.SetWindowText(_T("���"));
			m_kindName.Empty();
			m_allAdd = false;
			m_ts = false;
			UpdateData(FALSE);
			m_GuiAddKindButton.EnableWindow(FALSE);
			m_GuiDelKindButton.EnableWindow(FALSE);
			Refresh2();	
		
	}
}

void CKindUnitSetDialog::OnEnChangeKindEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if ( m_kindName.Trim().GetLength() > 0 ){
		m_GuiAddKindButton.EnableWindow(TRUE);
	}else{
		m_GuiAddKindButton.EnableWindow(FALSE);
	}
}

void CKindUnitSetDialog::OnNMClickKindList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiKindListCtrl.ScreenToClient(&point);
	if (( m_nIndex2 = m_GuiKindListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelKindButton.EnableWindow(TRUE);
	/*	m_GuiAddKindButton.EnableWindow(TRUE);
		m_GuiAddKindButton.SetWindowText(_T("�޸�"));
		m_modifyFlag = true;
		hotelMIS::HFoodKindCtrl foodCtrl(m_con.get_con());
		hotelMIS::HFoodKind foodKind= foodCtrl.getKind(m_kindMap[m_nIndex2]);
		m_kindName.Format("%s",foodKind.getKind_name().c_str());
		m_allAdd = foodKind.getKind_flag();
		m_ts = foodKind.getKind_ts();
		UpdateData(FALSE);*/
		TRACE("��������%d \n",m_nIndex2);
	}
	*pResult = 0;
}

void CKindUnitSetDialog::OnNMDblclkKindList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiKindListCtrl.ScreenToClient(&point);
	if (( m_nIndex2 = m_GuiKindListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelKindButton.EnableWindow(TRUE);
		m_GuiAddKindButton.EnableWindow(TRUE);
		m_GuiAddKindButton.SetWindowText(_T("�޸�"));
		m_modifyFlag = true;
		hotelMIS::HFoodKindCtrl foodCtrl(m_con.get_con());
		hotelMIS::HFoodKind foodKind= foodCtrl.getKind(m_kindMap[m_nIndex2]);
		m_kindName.Format("%s",foodKind.getKind_name().c_str());
		m_bKcKind = foodKind.kind_flag;
		m_kindZK = foodKind.kind_zk;
		m_zdyCheck = foodKind.zdy_price;
		
		UpdateData(FALSE);
		TRACE("��������%d \n",m_nIndex2);
	}
	*pResult = 0;
}
