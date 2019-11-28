//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  GetDetailsDlg.h
// 
// Desc: ��ȡ��Ʒ���ƺͱ��
//
// Author:  ��Ȫ
//
// Modified: 2006�� 06�� 15��
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "GetDetailsDlg.h"
#include ".\getdetailsdlg.h"
#include "HFoodKindCtrl.h"

// CGetDetailsDlg �Ի���

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
	// ������Ʒ�б���
	int i = 0;
	m_GuiMenuList.InsertColumn(i,_T("���"),LVCFMT_LEFT,40);
	m_GuiMenuList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,160);
	m_GuiMenuList.InsertColumn(++i,_T("����"),LVCFMT_RIGHT,70);
	m_GuiMenuList.InsertColumn(++i,_T("��ǰ���"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiMenuList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		
	
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
		 if ( mIt->repertory_flag == hotelMIS::HMenuInfo::REP_CALC ||
			 mIt->repertory_flag == hotelMIS::HMenuInfo::REP_NOCALC) 
			{

				m_menuListMap.insert(make_pair(i,mIt->food_id));
				t.Format("%d",i+1);
				//���
				m_GuiMenuList.InsertItem(i,t);
				//����
				m_GuiMenuList.SetItemText(i,1,mIt->food_name.c_str());
				//����
				t.Format("%.2f",mIt->food_price);
				m_GuiMenuList.SetItemText(i,2,t);
				//��õ�ǰ���
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CGetDetailsDlg::OnBnClickedButtonExt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CGetDetailsDlg::OnBnClickedButtonTree()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CGetDetailsDlg::OnBnClickedButtonList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CGetDetailsDlg::OnEnChangeEditPy()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CGetDetailsDlg::OnBnClickedButtonGet()
{
	// ��ȡ food_id, �� food_name

}

void CGetDetailsDlg::OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// ���� List
	*pResult = 0;
}

void CGetDetailsDlg::OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CGetDetailsDlg::OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CGetDetailsDlg::OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

