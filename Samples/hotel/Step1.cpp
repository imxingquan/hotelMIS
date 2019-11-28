// Step1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "Step1.h"
#include ".\step1.h"
#include "HTableStatusSetCtrl.h"
#include "HTableStatusCtrl.h"
#include "TableSetBmpDialog.h"

// CStep1 �Ի���

IMPLEMENT_DYNAMIC(CStep1, CPropertyPage)
CStep1::CStep1(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CStep1::IDD)
	, m_tableStatus(_T(""))
	, m_personNum(3)
{
	m_nPos=-1;
}

CStep1::~CStep1()
{
}

void CStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXL, m_GuiGroupBoxL);
	DDX_Control(pDX, IDC_EDIT_TABLE_STATUS, m_GuiEditTableStatus);
	DDX_Control(pDX, IDC_EDIT_PERSON_NUM, m_GuiEditPersonNum);
	DDX_Control(pDX, IDC_BUTTON_ADD_TABLE_STATUS, m_GuiButtonAddTableStatus);
	DDX_Control(pDX, IDC_BUTTON_DEL_TABLE_STATUS, m_GuiButtonDelTableStatus);
	DDX_Control(pDX, IDC_LIST_TABLE_STATUS, m_GuiListCtrlTableStatus);
	DDX_Text(pDX, IDC_EDIT_TABLE_STATUS, m_tableStatus);
	DDX_Text(pDX, IDC_EDIT_PERSON_NUM, m_personNum);
	DDX_Control(pDX, IDC_SET_TABLEBMP_BUTTON, m_GuiSetTableBmpBtn);
}


BEGIN_MESSAGE_MAP(CStep1, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TABLE_STATUS, OnBnClickedButtonAddTableStatus)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TABLE_STATUS, OnBnClickedButtonDelTableStatus)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TABLE_STATUS, OnNMClickListTableStatus)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TABLE_STATUS, OnNMDblclkListTableStatus)
	ON_BN_CLICKED(IDC_SET_TABLEBMP_BUTTON, OnBnClickedSetTablebmpButton)
END_MESSAGE_MAP()


// CStep1 ��Ϣ�������

BOOL CStep1::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//CPropertySheet* pParent=(CPropertySheet*)GetParent(); // ������Ա��ָ��
	//pParent->SetWizardButtons(PSWIZB_NEXT); // �������Ա����ʾ��ťֻΪ��һ��
	return CPropertyPage::OnSetActive();
}

BOOL CStep1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_GuiButtonAddTableStatus.ShowText();
	m_GuiButtonDelTableStatus.ShowText();
	m_GuiSetTableBmpBtn.ShowText();
	m_GuiButtonDelTableStatus.EnableWindow(false);
	m_GuiSetTableBmpBtn.EnableWindow(false);
	// TODO:  ��ʼ��
	Init();
	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CStep1::Init()
{
	m_GuiListCtrlTableStatus.InsertColumn(0,_T("���"),LVCFMT_LEFT,40);
	m_GuiListCtrlTableStatus.InsertColumn(1,_T("�ͺ�"),LVCFMT_LEFT,80);
	//m_GuiListCtrlTableStatus.InsertColumn(2,_T("����(��)"),LVCFMT_LEFT,80);
	m_GuiListCtrlTableStatus.InsertColumn(2,_T("ͼ���"),LVCFMT_LEFT,80);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlTableStatus.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
}

void CStep1::Refresh()
{
	
	hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());
	hotelMIS::HTableStatusSetVec vec = tableStatusSetCtrl.getAllTableStatusSet();
	hotelMIS::HTableStatusSetVec::iterator it;
	int i = 0;
	CString cnt;
	m_GuiListCtrlTableStatus.DeleteAllItems();
	m_tableStatusMap.clear();
	for ( it = vec.begin(); it!=vec.end(); ++it)
	{
		cnt.Format("%d",i+1);
		m_tableStatusMap.insert(make_pair(i,it->table_state));
		m_GuiListCtrlTableStatus.InsertItem(i,cnt);
		m_GuiListCtrlTableStatus.SetItemText(i,1,it->state_name.c_str());
		/*cnt.Format("%d",(*it).getPerson_num());
		m_GuiListCtrlTableStatus.SetItemText(i,2,cnt);*/
		cnt.Format("%d-%d",it->empty_bmp,it->repast_bmp);
		m_GuiListCtrlTableStatus.SetItemText(i,2,cnt);
		++i;
	}
}
void CStep1::OnBnClickedButtonAddTableStatus()
{
	// TODO: ��Ӳ���״̬
	UpdateData();
	if ( m_tableStatus.IsEmpty() ){
		AfxMessageBox(_T("����״̬����Ϊ��!"),MB_ICONINFORMATION|MB_OK);
		m_GuiEditTableStatus.SetFocus();
		return;
	}
	if ( m_personNum <= 0){
		AfxMessageBox(_T("��������С��0!"),MB_ICONINFORMATION|MB_OK);
		m_GuiEditPersonNum.SetFocus();
		return;
	}
	hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());
	tableStatusSetCtrl.insert(hotelMIS::ReplaceChar(m_tableStatus).GetBuffer(),m_personNum);
	Refresh();
	m_tableStatus.Empty();
	UpdateData(false);
	CPropertySheet* pParent=(CPropertySheet*)GetParent();
	pParent->PostMessage(WM_MODIFIED);
}

void CStep1::OnBnClickedButtonDelTableStatus()
{
	// TODO: ɾ������״̬
	int pos =  m_GuiListCtrlTableStatus.GetSelectionMark();
	if ( pos != -1 ){
		int result = MessageBox(_T("ȷ��Ҫɾ��?"),_T("ϵͳ����"),MB_YESNO|MB_ICONWARNING);
		if ( result == IDYES){
			hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
			if ( tableStatusCtrl.isExistTableState(m_tableStatusMap[pos])){
				MessageBox(_T("�������ѱ�Ӧ��,���ܱ�ɾ����"),_T("ϵͳ����"),MB_OK|MB_ICONWARNING);
				return;
			}
			hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());
			tableStatusSetCtrl.delete0(m_tableStatusMap[pos]);
			Refresh();
			m_GuiButtonDelTableStatus.EnableWindow(false);
			CPropertySheet* pParent=(CPropertySheet*)GetParent();
			pParent->PostMessage(WM_MODIFIED);
		}
	}
}

void CStep1::OnNMClickListTableStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrlTableStatus.ScreenToClient(&point);
	if (( m_nPos= m_GuiListCtrlTableStatus.HitTest(point)) != -1 ) {
		m_GuiButtonDelTableStatus.EnableWindow(true);
		m_GuiSetTableBmpBtn.EnableWindow(true);
		TRACE("��������%d \n",m_nPos);
	}else{
		m_GuiButtonDelTableStatus.EnableWindow(false);
		m_GuiSetTableBmpBtn.EnableWindow(false);
	}
}

void CStep1::OnNMDblclkListTableStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrlTableStatus.ScreenToClient(&point);
	if (( m_nPos= m_GuiListCtrlTableStatus.HitTest(point)) != -1 ) {
		OnBnClickedSetTablebmpButton();
		TRACE("��������%d \n",m_nPos);
	}
}

void CStep1::OnBnClickedSetTablebmpButton()
{
	// TODO: 
	ASSERT( m_nPos != -1 ) ;
	CTableSetBmpDialog bmpDlg;
	bmpDlg.m_nState = m_tableStatusMap[m_nPos];
	if ( bmpDlg.DoModal() == IDOK){
		//ASSERT(m_nPos != -1);
		hotelMIS::HTableStatusSetCtrl tabelStatusSetCtrl(m_con.get_con());
		tabelStatusSetCtrl.SetTaleBmp(bmpDlg.m_nState,bmpDlg.m_nPos);
		Refresh();
		CPropertySheet* pParent=(CPropertySheet*)GetParent();
		pParent->PostMessage(WM_MODIFIED);
	}
}
