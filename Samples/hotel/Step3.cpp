// Step3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "Step3.h"
#include ".\step3.h"
#include "HRoomCtrl.h"
#include "HTableStatusSetCtrl.h"
#include "HTableStatusCtrl.h"

// CStep3 �Ի���

IMPLEMENT_DYNAMIC(CStep3, CPropertyPage)
CStep3::CStep3(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CStep3::IDD)
{
}

CStep3::~CStep3()
{
}

void CStep3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_COMBO_CANTIN, m_GuiComboBoxCanTin);
	DDX_Control(pDX, IDC_COMBO_TABLE_STATUS, m_GuiComboBoxTableStatus);
	DDX_Control(pDX, IDC_BUTTON_SET_TABLE_STATUS, m_GuiButtonSetTableStatus);
	DDX_Control(pDX, IDC_LIST_TABLE_FLAG, m_GuiListTableFlag);
}


BEGIN_MESSAGE_MAP(CStep3, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_CANTIN, OnCbnSelchangeComboCantin)
	ON_BN_CLICKED(IDC_BUTTON_SET_TABLE_STATUS, OnSetTableStatus)
END_MESSAGE_MAP()


// CStep3 ��Ϣ�������

BOOL CStep3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//CPropertySheet* pParent=(CPropertySheet*)GetParent(); // ������Ա��ָ��
	//pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); // �������Ա����ʾ��ťֻΪ��һ��
//CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
//	pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK); 
	//OnInitDialog();
	return CPropertyPage::OnSetActive();
}

BOOL CStep3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_GuiButtonSetTableStatus.ShowText();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void  CStep3::Init()
{
	//��� combobox
	
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	hotelMIS::HRoomVector vec = roomCtrl.getAllRoom();
	hotelMIS::HRoomVector::iterator it;

	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		/*string name = (*it).getName();
		int id = (*it).getId();*/

		m_GuiComboBoxCanTin.AddString((*it).getName().c_str());
		m_map_room.insert(make_pair((*it).getName(),(*it).getId()));
	}
	
	/*map<string,int>::iterator mit;
	for ( mit = m_map_room.begin(); mit!= m_map_room.end(); mit++)
	{
		string first = mit->first;
		int second = mit->second;
		TRACE("%s,%d\n",first.c_str() , second );
	}*/
	m_GuiComboBoxCanTin.AddString(_T("ȫ��"));
	m_GuiComboBoxCanTin.SetCurSel(0);

	//���ò���״̬�б�
	hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());
	hotelMIS::HTableStatusSetVec vec2 = tableStatusSetCtrl.getAllTableStatusSet();
	hotelMIS::HTableStatusSetVec::iterator it2;
	for ( it2 = vec2.begin(); it2!=vec2.end(); ++it2)
	{
		m_GuiComboBoxTableStatus.AddString((*it2).getState_name().c_str());
		m_map_tableSet[(*it2).getState_name()] = (*it2).getTable_state();
	}
	m_GuiComboBoxTableStatus.SetCurSel(0);

	//��ʼ��list
	m_GuiListTableFlag.InsertColumn(0,_T("����"),LVCFMT_LEFT,50);
	m_GuiListTableFlag.InsertColumn(1,_T("������"),LVCFMT_LEFT,80);
	m_GuiListTableFlag.InsertColumn(2,_T("״̬��"),LVCFMT_LEFT,100);

	ListView_SetExtendedListViewStyleEx(m_GuiListTableFlag.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	Refresh();
}

void  CStep3::Refresh()
{
	m_GuiListTableFlag.DeleteAllItems();
	m_GuiComboBoxCanTin.GetWindowText(m_canTinName);
	int roomId = m_map_room[m_canTinName.GetBuffer()];
	hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
	hotelMIS::HTableStatusSetCtrl tableSetCtrl(m_con.get_con());
	CString tmp;
	if ( roomId == 0 ){
		hotelMIS::HTableStatusVec vec = tableStatusCtrl.getAllTableStatus();
		hotelMIS::HTableStatusVec::iterator it;
		int i =0;
		for (it = vec.begin(); it != vec.end(); ++it)
		{
			tmp.Format("%d",it->getTable_id());
			m_GuiListTableFlag.InsertItem(i,tmp);
			m_GuiListTableFlag.SetItemText(i,1,tableStatusCtrl.getRoomName(it->getRoom_id()).c_str());
			//m_GuiListTableFlag.SetItemText(2,tableSetCtrl.getHTableStatus(it->getTable_id()).getState_name().c_str());
			m_GuiListTableFlag.SetItemText(i,2,tableStatusCtrl.getTableStateName(it->getTable_state()).c_str());
			++i;
		}

	}
	else{
		hotelMIS::HTableStatusVec vec = tableStatusCtrl.getTableStatusSpecial(roomId);
		hotelMIS::HTableStatusVec::iterator it;
		int i =0;
		for (it = vec.begin(); it != vec.end(); ++it)
		{
			tmp.Format("%d",it->getTable_id());
			m_GuiListTableFlag.InsertItem(i,tmp);
			m_GuiListTableFlag.SetItemText(i,1,tableStatusCtrl.getRoomName(it->getRoom_id()).c_str());
			//m_GuiListTableFlag.SetItemText(2,tableSetCtrl.getHTableStatus(it->getTable_id()).getState_name().c_str());
			m_GuiListTableFlag.SetItemText(i,2,tableStatusCtrl.getTableStateName(it->getTable_state()).c_str());
			++i;
		}
	}
}
void CStep3::OnCbnSelchangeComboCantin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Refresh();
	TRACE("%s,%d\n",m_canTinName,m_map_room[m_canTinName.GetBuffer()]);
}

//void CStep3::OnOK()
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	AfxMessageBox(_T("ϵͳ���ñ��ı�����Զ��ر�!����������!"));
//
//	CPropertyPage::OnOK();
//}

void CStep3::OnSetTableStatus()
{
	// TODO: 
	CPropertySheet* pParent=(CPropertySheet*)GetParent();
	pParent->PostMessage(WM_MODIFIED);
}
