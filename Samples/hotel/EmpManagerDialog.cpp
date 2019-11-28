// EmpManagerDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "EmpManagerDialog.h"
//#include ".\empmanagerdialog.h"


// CEmpManagerDialog �Ի���

IMPLEMENT_DYNAMIC(CEmpManagerDialog, CDialog)
CEmpManagerDialog::CEmpManagerDialog(CWnd* pParent /*=NULL*/)
: CDialog(CEmpManagerDialog::IDD, pParent)
, m_editKey(_T(""))
{
}

CEmpManagerDialog::~CEmpManagerDialog()
{
}

void CEmpManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXT, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);
	DDX_Control(pDX, IDC_EDIT_KEY, m_GuiEditKey);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_GuiButtonSearch);
	DDX_Control(pDX, IDC_LIST_EMPLOYEE, m_GuiListCtrlEmployee);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Text(pDX, IDC_EDIT_KEY, m_editKey);
	DDX_Control(pDX, IDC_EDITANDDEL_EMP_BTN, m_GuiEditAndDelBtn);
}


BEGIN_MESSAGE_MAP(CEmpManagerDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EMPLOYEE, OnNMClickListEmployee)
	ON_BN_CLICKED(IDC_EDITANDDEL_EMP_BTN, OnEditAndDel)
END_MESSAGE_MAP()


// CEmpManagerDialog ��Ϣ�������

void CEmpManagerDialog::OnBnClickedButtonSearch()
{
	// TODO: ��ѯ
	Refresh();
	m_editKey.Empty();
	UpdateData(false);
}

void CEmpManagerDialog::OnNMClickListEmployee(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//Init();
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrlEmployee.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCtrlEmployee.HitTest(point)) != -1 ) {
		m_GuiEditAndDelBtn.EnableWindow(true);
	}

}

BOOL CEmpManagerDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonSearch.ShowText();
	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.ShowText();
	m_GuiEditAndDelBtn.ShowText();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CEmpManagerDialog::Init()
{
	int i = 0;
	m_GuiEditAndDelBtn.EnableWindow(false);
	m_GuiListCtrlEmployee.InsertColumn(i,_T("���"),LVCFMT_LEFT,40);
	m_GuiListCtrlEmployee.InsertColumn(++i,_T("Ա�����"),LVCFMT_LEFT,60);
	m_GuiListCtrlEmployee.InsertColumn(++i,_T("����"),LVCFMT_LEFT,70);
	m_GuiListCtrlEmployee.InsertColumn(++i,_T("�Ա�"),LVCFMT_LEFT,40);
	m_GuiListCtrlEmployee.InsertColumn(++i,_T("ְ��"),LVCFMT_LEFT,60);
	m_GuiListCtrlEmployee.InsertColumn(++i,_T("��ϵ�绰"),LVCFMT_LEFT,70);
	m_GuiListCtrlEmployee.InsertColumn(++i,_T("��ϵ��ַ"),LVCFMT_LEFT,100);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlEmployee.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	Refresh();
}

void CEmpManagerDialog::Refresh()
{
	UpdateData(true);
	hotelMIS::HEmployeeVec vec;
	if ( m_editKey.IsEmpty() )
		vec= m_empBdy.getAllEmp();
	else
		vec = m_empBdy.searchEmp(m_editKey.GetBuffer());

	hotelMIS::HEmployeeVec::iterator it;
	int i = 0;
	CString t;
	m_empMap.clear();
	m_GuiListCtrlEmployee.DeleteAllItems();
	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		t.Format("%d",i+1);
		int pos = m_GuiListCtrlEmployee.InsertItem(i,t);
		m_empMap.insert(make_pair(pos,it->getEmp_id()));
		m_GuiListCtrlEmployee.SetItemText(i,1,it->getEmp_id().c_str());
		m_GuiListCtrlEmployee.SetItemText(i,2,it->getEmp_name().c_str());
		m_GuiListCtrlEmployee.SetItemText(i,3,it->getEmp_sex().c_str());
		m_GuiListCtrlEmployee.SetItemText(i,4,it->getEmp_job_name().c_str());
		m_GuiListCtrlEmployee.SetItemText(i,5,it->getEmp_phone().c_str());
		m_GuiListCtrlEmployee.SetItemText(i,6,it->getEmp_address().c_str());
		i++;
	}
}
void CEmpManagerDialog::OnEditAndDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int pos;
	if ( (pos = m_GuiListCtrlEmployee.GetSelectionMark() ) != -1 )
	{
		CString t;
		t.Format("%s",m_empMap[pos].c_str());
		m_empBdy.delEmp(ReplaceChar(t).GetBuffer());
		Refresh();
		m_GuiEditAndDelBtn.EnableWindow(false);
	}
}
