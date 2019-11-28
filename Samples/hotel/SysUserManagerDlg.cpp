// SysUserManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "SysUserManagerDlg.h"
//#include ".\sysusermanagerdlg.h"
#include "HOpType.h"
#include "HAdminBdy.h"

// CSysUserManagerDlg �Ի���

IMPLEMENT_DYNAMIC(CSysUserManagerDlg, CDialog)
CSysUserManagerDlg::CSysUserManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysUserManagerDlg::IDD, pParent)
	, m_logName(_T(""))
	, m_password(_T(""))
	, m_fname(_T(""))
	, m_remark(_T(""))
	, m_bM0(FALSE)
	, m_bM1(FALSE)
	, m_bM2(FALSE)
	, m_bM3(FALSE)
	, m_bM4(FALSE)
	, m_bM5(FALSE)
	, m_bM6(FALSE)
	, m_bM7(FALSE)
	, m_bM8(FALSE)
	, m_isModify(false)
	, m_nPos(-1)
	, m_purview(_T(""))
	, m_purviewr(_T(""))
	, m_purviewlist(_T(""))
{
}

CSysUserManagerDlg::~CSysUserManagerDlg()
{
}

void CSysUserManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GUPGROUPLT, m_GuiGroupBoxLT);
	DDX_Control(pDX, IDC_GUIGROUPLB, m_GuiGroupBoxLB);
	DDX_Control(pDX, IDC_GUIGROUPR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_EDIT1, m_GuiLogNameEdit);
	DDX_Control(pDX, IDC_EDIT2, m_GuiLogPwdEdit);
	DDX_Control(pDX, IDC_EDIT4, m_GuiNameEdit);
	DDX_Control(pDX, IDC_EDIT5, m_GuiRemarkEdit);
	DDX_Control(pDX, IDC_ADDSYS_BUTTON, m_GuiAddSysButton);
	DDX_Control(pDX, IDC_DELSYS_BUTTON, m_GuiDelSysButton);
	DDX_Control(pDX, IDC_SYS_LIST, m_GuiSysListCtrl);
	DDX_Control(pDX, IDC_BUTTON6, m_GuiToolButton);
	DDX_Control(pDX, IDC_PURVIEW_COMBO, m_GuiPurviewCombo);
	DDX_Control(pDX, IDC_ADDOPTYPE_BUTTON, m_GuiAddOpTypeButton);
	DDX_Control(pDX, IDC_DELOPTYPE_BUTTON, m_GuiDelOpTypeButton);
	DDX_Control(pDX, IDC_SETPURVIEW_BUTTON, m_GuiSetPurviewButton);
	DDX_Control(pDX, IDC_M0_CHECK, m_GuiM0Check);
	DDX_Control(pDX, IDC_M1_CHECK, m_GuiM1Check);
	DDX_Control(pDX, IDC_M2_CHECK, m_GuiM2Check);
	DDX_Control(pDX, IDC_M3_CHECK, m_GuiM3Check);
	DDX_Control(pDX, IDC_M4_CHECK, m_GuiM4Check);
	DDX_Control(pDX, IDC_M5_CHECK, m_GuiM5Check);
	DDX_Control(pDX, IDC_M6_CHECK, m_GuiM6Check);
	DDX_Control(pDX, IDC_M7_CHECK, m_GuiM7Check);
	DDX_Text(pDX, IDC_EDIT1, m_logName);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT4, m_fname);
	DDX_Text(pDX, IDC_EDIT5, m_remark);
	DDX_Check(pDX, IDC_M0_CHECK, m_bM0);
	DDX_Check(pDX, IDC_M1_CHECK, m_bM1);
	DDX_Check(pDX, IDC_M2_CHECK, m_bM2);
	DDX_Check(pDX, IDC_M3_CHECK, m_bM3);
	DDX_Check(pDX, IDC_M4_CHECK, m_bM4);
	DDX_Check(pDX, IDC_M5_CHECK, m_bM5);
	DDX_Check(pDX, IDC_M6_CHECK, m_bM6);
	DDX_Check(pDX, IDC_M7_CHECK, m_bM7);
	DDX_Check(pDX, IDC_M8_CHECK, m_bM8);
	DDX_Text(pDX, IDC_PURVIEW_COMBO, m_purview);
	DDX_Control(pDX, IDC_PURVIEW_LIST, m_GuiPurviewList);
	DDX_Control(pDX, IDC_PURVIEW_EDIT, m_GuiPurviewEdit);
	DDX_Text(pDX, IDC_PURVIEW_EDIT, m_purviewr);
	DDX_LBString(pDX, IDC_PURVIEW_LIST, m_purviewlist);
}


BEGIN_MESSAGE_MAP(CSysUserManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_ADDSYS_BUTTON, OnAddAndEditSys)
	ON_BN_CLICKED(IDC_DELSYS_BUTTON, OnDelSys)
	ON_BN_CLICKED(IDC_ADDOPTYPE_BUTTON, OnAddPurview)
	ON_BN_CLICKED(IDC_DELOPTYPE_BUTTON, OnDelPurview)
	ON_BN_CLICKED(IDC_SETPURVIEW_BUTTON, OnSetPurview)
	ON_BN_CLICKED(IDC_BUTTON6, OnDispAndHide)
	ON_NOTIFY(NM_DBLCLK, IDC_SYS_LIST, OnNMDblclkSysList)
//	ON_CBN_SELCHANGE(IDC_OPTYPE_COMBO, OnCbnSelchangeOptypeCombo)
	ON_NOTIFY(NM_CLICK, IDC_SYS_LIST, OnNMClickSysList)
//	ON_CBN_EDITCHANGE(IDC_OPTYPE_COMBO, OnCbnEditchangeOptypeCombo)
ON_LBN_SELCHANGE(IDC_PURVIEW_LIST, OnLbnSelchangePurviewList)
END_MESSAGE_MAP()


// CSysUserManagerDlg ��Ϣ�������

void CSysUserManagerDlg::OnAddAndEditSys()
{
	// TODO: ���ϵͳ�û�
	
	UpdateData(TRUE);
	if ( m_logName.Trim().IsEmpty() ){
		AfxMessageBox(_T("�������½����!"));
		m_GuiLogNameEdit.SetFocus();
		return ;
	}else if ( m_password.Trim().IsEmpty()){
		AfxMessageBox(_T("����������!"));
		m_GuiLogPwdEdit.SetFocus();
		return;
	}else if ( m_purview.IsEmpty() ){
		AfxMessageBox(_T("��ѡ��Ȩ����!"));
		return;
	}

	hotelMIS::HAdminBdy adminBdy(m_con.get_con());
	hotelMIS::HAdmin admin;
	admin.setLoginId(hotelMIS::ReplaceChar(m_logName).GetBuffer());
	admin.setPassword(hotelMIS::ReplaceChar(m_password).GetBuffer());
	admin.setOpType(hotelMIS::ReplaceChar(m_purview).GetBuffer());
	admin.setName(hotelMIS::ReplaceChar(m_fname).GetBuffer());
	admin.setDesc(hotelMIS::ReplaceChar(m_remark).GetBuffer());
	admin.setId(m_sysMap[m_nPos].getId());
	if ( m_isModify ){
		adminBdy.update(admin);
		m_isModify = false;
		m_GuiAddSysButton.SetWindowText(_T("���"));
		//m_GuiAddSysButton.EnableWindow(false);
		AfxMessageBox(_T("�����޸ĳɹ�!"));
	}
	else{
	   adminBdy.insert(admin);
	   //m_GuiAddSysButton.EnableWindow(false);
	    m_GuiDelSysButton.EnableWindow(false);
		AfxMessageBox(_T("������ӳɹ�!"));
	}
	//���	
	m_logName.Empty();
	m_password.Empty();
	m_purview.Empty();
	m_fname.Empty();
	m_remark.Empty();
	m_GuiLogNameEdit.SetFocus();
	UpdateData(false);
	RefreshSys();
}

void CSysUserManagerDlg::OnDelSys()
{
	// TODO: ɾ��ϵͳ�û�
	int result = AfxMessageBox(_T("ȷ��Ҫɾ������û�?"),MB_YESNO|MB_ICONWARNING);
	if ( result == IDYES){
		hotelMIS::HAdminBdy adminBdy(m_con.get_con());
		adminBdy.Delete(m_sysMap[m_nPos].getId());
		m_GuiDelSysButton.EnableWindow(false);

		m_logName.Empty();
		m_password.Empty();
		m_purview.Empty();
		m_fname.Empty();
		m_remark.Empty();
		m_GuiLogNameEdit.SetFocus();
		UpdateData(false);
		RefreshSys();
	}
}

void CSysUserManagerDlg::ResetComboBox()
{
	hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewr).GetBuffer(),m_con.get_con());
	//------------------------------------------------------
	//ɾ��ComboBox;
	for ( int i =  m_GuiPurviewCombo.GetCount()-1; i >=0; i--)
		m_GuiPurviewCombo.DeleteString(i);
	

	//����map
	m_purviewCombo.clear();
	hotelMIS::purviewList list= opType.getAllPurview();
	hotelMIS::purviewList::iterator it;
	int pos;
	for ( it = list.begin(); it != list.end(); it++)
	{
		pos = m_GuiPurviewCombo.AddString(it->c_str());
		m_purviewCombo.insert(make_pair(it->c_str(),pos));
	}
	m_GuiPurviewCombo.SetCurSel(0);
	//------------------------------------------------------- 

}
void CSysUserManagerDlg::OnAddPurview()
{
	// TODO: ���Ȩ��
	UpdateData(true);
	if ( m_purviewr.Trim().IsEmpty()){
		AfxMessageBox(_T("Ȩ��������Ϊ��!"));
		m_GuiPurviewEdit.SetFocus();
		return;
	}
	
	hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewr).GetBuffer(),m_con.get_con());
	
	if ( opType.isExist(m_purviewr.Trim().GetBuffer()) ){
		AfxMessageBox(_T("���Ȩ�����Ѿ����ڲ���������!,�뻻һ������!"));
		return;
	}
	//�����ݿ�������Ȩ����
	opType.addPurview();
	//��ListBox������Ȩ����
	m_GuiPurviewList.AddString(hotelMIS::ReplaceChar(m_purviewr));
	
	//��ComboBox������Ȩ����
	//int nPos = m_GuiPurviewCombo.AddString(m_purviewr.Trim()); //�ұߵ�Ҳһ��Ҫ���
	//��map������Ȩ����
	//m_purviewCombo.insert(make_pair(m_purview.Trim().GetBuffer(),nPos));
	
	//����ComBobx
	ResetComboBox();

	AfxMessageBox(_T("��ӳɹ�!"));

	m_purviewr.Empty();
	UpdateData(false);
}


void CSysUserManagerDlg::OnDelPurview()
{
	// TODO: ɾ��Ȩ��

	UpdateData(true);
	if ( m_purviewlist.Trim().IsEmpty() ){
		AfxMessageBox(_T("����ѡ��Ҫɾ����Ȩ����!"));
		return;
	}
	int result = AfxMessageBox(_T("ȷ�����Ҫɾ��!"),MB_YESNO|MB_ICONWARNING);
	if ( result == IDYES){
		if ( m_purviewlist.Trim() == _T("ϵͳ����Ա")){
			AfxMessageBox(_T("����ɾ��ϵͳ����Ա��Ȩ��!"));
			return;
		}
		
		//ɾ��Ȩ����
		hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewlist).GetBuffer(),m_con.get_con());
		opType.delPurview();
		//ɾ��ListBox�е�Ȩ����
		m_GuiPurviewList.DeleteString(m_GuiPurviewList.GetCurSel());
		
		ResetComboBox();
		
		//ɾ��ComboBox�е�Ȩ����
		//m_GuiPurviewCombo.DeleteString(m_purviewCombo[m_purviewlist.Trim().GetBuffer()]);
		////ɾ��map�е�Ȩ����
		//m_purviewCombo.erase(m_purviewlist.Trim().GetBuffer());
		//
		//m_GuiPurviewCombo.SetCurSel(0);

		m_GuiDelOpTypeButton.EnableWindow(false);
		//m_purview.Empty();
	}
}

void CSysUserManagerDlg::OnSetPurview()
{
	// TODO: ����Ȩ��
	UpdateData(true);
	int result = AfxMessageBox(_T("ȷʵҪ�ı䵱ǰȨ�����Ȩ��?"),MB_YESNO);
	if ( result == IDYES)
	{
		hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewlist).GetBuffer(),m_con.get_con());
		opType.setM0(m_bM0);	//��������
		opType.setM1(m_bM1);	//������
		opType.setM2(m_bM2);	//�˵���ѯ
		opType.setM3(m_bM3);	//Ա������
		opType.setM4(m_bM4);	//���׹���
		opType.setM5(m_bM5);	//ͳ�Ʊ���
		opType.setM6(m_bM6);	//ϵͳ����
		opType.setM7(m_bM7);	//��������
		opType.setM8(m_bM8);	//��Ա������
		m_GuiSetPurviewButton.EnableWindow(false);
	}

}

void CSysUserManagerDlg::OnLbnSelchangePurviewList()
{
	// TODO: ����ѡ��Ķ�checkbox�ؼ�����ʾ״̬
	UpdateData(true);
	TRACE("list =%s\n",m_purviewlist);
	if (m_GuiPurviewList.GetCurSel() != -1){
		m_GuiSetPurviewButton.EnableWindow(true);   //Ȩ�����ÿ���
		m_GuiDelOpTypeButton.EnableWindow(true);	//ɾ������
		hotelMIS::HOpType opType(hotelMIS::ReplaceChar(m_purviewlist).GetBuffer(),m_con.get_con());
		m_bM0 = opType.getM0();
		m_bM1 = opType.getM1();
		m_bM2 = opType.getM2();
		m_bM3 = opType.getM3();
		m_bM4 = opType.getM4();
		m_bM5 = opType.getM5();
		m_bM6 = opType.getM6();
		m_bM7 = opType.getM7();
		m_bM8 = opType.getM8();
		UpdateData(false);
	}

}

void CSysUserManagerDlg::OnDispAndHide()
{
	// TODO: ��ʾ������ Ȩ����
}

void CSysUserManagerDlg::InitSys()
{
	//1) ���Ȩ���б�
	hotelMIS::HOpType opType(m_con.get_con());
	hotelMIS::purviewList list= opType.getAllPurview();
	hotelMIS::purviewList::iterator it;
	int pos;
	for ( it = list.begin(); it != list.end(); it++)
	{
		pos = m_GuiPurviewCombo.AddString(it->c_str());
		m_purviewCombo.insert(make_pair(it->c_str(),pos));
		
	}
	m_GuiPurviewCombo.SetCurSel(0);
	//2) ����û��б�
	int i = 0;
	
	m_GuiSysListCtrl.InsertColumn(i++,_T("���"),LVCFMT_LEFT,40);
	m_GuiSysListCtrl.InsertColumn(i++,_T("��½��"),LVCFMT_LEFT,80);
	m_GuiSysListCtrl.InsertColumn(i++,_T("����"),LVCFMT_LEFT,70);
	m_GuiSysListCtrl.InsertColumn(i++,_T("Ȩ��"),LVCFMT_LEFT,70);
	m_GuiSysListCtrl.InsertColumn(i++,_T("����"),LVCFMT_LEFT,70);
	m_GuiSysListCtrl.InsertColumn(i++,_T("����"),LVCFMT_LEFT,100);
    ListView_SetExtendedListViewStyleEx(m_GuiSysListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	//ɾ���û���ť������
	m_GuiDelSysButton.EnableWindow(false);
	RefreshSys();
}

void CSysUserManagerDlg::RefreshSys()
{
	hotelMIS::HAdminBdy adminBdy(m_con.get_con());
	hotelMIS::HAdminVec vec= adminBdy.getAllAdminInfo();
	hotelMIS::HAdminVec::iterator it;
	int i = 0,j;
	CString t;
	m_GuiSysListCtrl.DeleteAllItems();
	m_sysMap.clear();
	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		j = 1;
		t.Format("%d",i+1);
		m_sysMap.insert(make_pair(i,*it));
		m_GuiSysListCtrl.InsertItem(i,t);
		m_GuiSysListCtrl.SetItemText(i,j++,it->getLoginId().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getPassword().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getOpType().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getName().c_str());
		m_GuiSysListCtrl.SetItemText(i,j++,it->getDesc().c_str());
		i++;
	}
}

void CSysUserManagerDlg::InitPurview()
{
	//Ȩ�����ò�����
	m_GuiSetPurviewButton.EnableWindow(false);
	//ɾ��������
	m_GuiDelOpTypeButton.EnableWindow(false);

	//1) ���Ȩ���б�
	hotelMIS::HOpType opType(m_con.get_con());
	hotelMIS::purviewList list= opType.getAllPurview();
	hotelMIS::purviewList::iterator it;
	for ( it = list.begin(); it != list.end(); it++)
	{
		m_GuiPurviewList.AddString(it->c_str());
	}

}
void CSysUserManagerDlg::OnNMDblclkSysList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiSysListCtrl.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiSysListCtrl.HitTest(point)) != -1 ) {
		hotelMIS::HAdmin admin = m_sysMap[nPos];
		m_logName = admin.getLoginId().c_str();
		m_password = admin.getPassword().c_str();
		m_purview = admin.getOpType().c_str();
		m_fname = admin.getName().c_str();
		m_remark = admin.getDesc().c_str();
        UpdateData(false);
		m_isModify = true;
		////DDX�� ComboBox �� DownList ������,���±ߵķ���
		m_GuiPurviewCombo.SetCurSel(m_purviewCombo[m_purview.GetBuffer()]);
		
		m_GuiAddSysButton.SetWindowText(_T("�޸�"));
	}

}



BOOL CSysUserManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiAddSysButton.ShowText();
	m_GuiDelSysButton.ShowText();
	m_GuiAddOpTypeButton.ShowText();
	m_GuiDelOpTypeButton.ShowText();
	m_GuiToolButton.ShowText();
	m_GuiSetPurviewButton.ShowText();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitSys();
	InitPurview();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSysUserManagerDlg::OnNMClickSysList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiSysListCtrl.ScreenToClient(&point);
	if (( m_nPos= m_GuiSysListCtrl.HitTest(point)) != -1 ) {
		m_GuiDelSysButton.EnableWindow(true);
	}
}



