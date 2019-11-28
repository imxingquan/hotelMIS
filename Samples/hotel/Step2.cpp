// Step2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "Step2.h"
#include ".\step2.h"
#include "HRoomCtrl.h"
#include "HTableStatusCtrl.h"
#include "MyCdKey.h"
#include "RegisterDialog.h"
#include <cassert>


// CStep2 �Ի���

IMPLEMENT_DYNAMIC(CStep2, CPropertyPage)
CStep2::CStep2(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CStep2::IDD)
	, m_canTinName(_T(""))
	, m_tableNum(1)
	, m_roomNo(0)
	,m_isModify(FALSE)
{
}

CStep2::~CStep2()
{
}

void CStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_DEL_CANTIN, m_GuiButtonDelCanTin);
	DDX_Control(pDX, IDC_EDIT_CANTIN_NAME, m_GuiEditCanTinName);
	DDX_Control(pDX, IDC_EDIT_TABLE_NUM, m_GuiEditNum);
	DDX_Control(pDX, IDC_BUTTON_ADD_CANTIN, m_GuiButtonAddCanTin);
	DDX_Control(pDX, IDC_LIST_CANTIN, m_GuiListCanTin);
	DDX_Text(pDX, IDC_EDIT_CANTIN_NAME, m_canTinName);
	DDX_Text(pDX, IDC_EDIT_TABLE_NUM, m_tableNum);
	DDX_Control(pDX, IDC_ROOMNO_EDIT, m_GuiRoomNoEdit);
	DDX_Text(pDX, IDC_ROOMNO_EDIT, m_roomNo);
	DDV_MinMaxInt(pDX, m_roomNo, 1, 10);
}


BEGIN_MESSAGE_MAP(CStep2, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CANTIN, OnBnClickedButtonAddCantin)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CANTIN, OnDeleteRoom)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CANTIN, OnNMClickListCantin)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CANTIN, OnNMDblclkListCantin)
END_MESSAGE_MAP()


// CStep2 ��Ϣ�������

BOOL CStep2::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//CPropertySheet* pParent=(CPropertySheet*)GetParent(); // ������Ա��ָ��
	//pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); // �������Ա����ʾ��ťֻΪ��һ��
	return CPropertyPage::OnSetActive();
}

BOOL CStep2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_GuiButtonDelCanTin.ShowText();
	m_GuiButtonAddCanTin.ShowText();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Init();
	Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CStep2::Init()
{
	m_GuiListCanTin.InsertColumn(0,_T("���"),LVCFMT_LEFT,40);
	m_GuiListCanTin.InsertColumn(1,_T("������"),LVCFMT_LEFT,80);
	m_GuiListCanTin.InsertColumn(2,_T("��������"),LVCFMT_LEFT,90);
	ListView_SetExtendedListViewStyleEx(m_GuiListCanTin.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_GuiButtonDelCanTin.EnableWindow(false);

	hotelMIS::HRoomCtrl hRoomCtrl(m_con.get_con());
	m_roomNo = hRoomCtrl.getRoomMax() +1;
		
	UpdateData(false);
}
void CStep2::Refresh()
{
	hotelMIS::HRoomCtrl hRoomCtrl(m_con.get_con());
	hotelMIS::HRoomVector vec = hRoomCtrl.getAllRoom();
	hotelMIS::HRoomVector::iterator it;
	int i = 0;
	CString cnt;
	m_GuiListCanTin.DeleteAllItems();
	m_roomMap.clear();
	for ( it = vec.begin(); it!=vec.end(); ++it)
	{
		cnt.Format("%d",i+1);
		m_roomMap.insert(make_pair(i,it->getId()));
		m_GuiListCanTin.InsertItem(i,cnt);
		m_GuiListCanTin.SetItemText(i,1,(*it).getName().c_str());
		cnt.Format("%d",(*it).getTableNum());
		m_GuiListCanTin.SetItemText(i,2,cnt);
		++i;
	}
}

void CStep2::OnBnClickedButtonAddCantin()
{
	//// TODO: ���
	////--------------------------------��֤--------------------------
	//MyCdKey cdkey;
	//if ( !cdkey.RegisterCdKey()){
	//	CRegisterDialog dlg;
	//	dlg.DoModal();
	//	return;
	//}
	////------------------------------------------------------

	UpdateData(TRUE);
	if ( m_isModify == FALSE)
	{
		if ( m_canTinName.IsEmpty() ){
			MessageBox(_T("����������Ϊ��!"),_T("����"),MB_ICONWARNING|MB_OK);
			m_GuiEditCanTinName.SetFocus();
			return;
		}
		if ( m_tableNum <=0 ){
			MessageBox(_T("������Ӧ�ô���0!"),_T("����"),MB_ICONWARNING|MB_OK);
			m_GuiEditNum.SetFocus();
			return;
		}

		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		int id = roomCtrl.insertRoom(m_roomNo,hotelMIS::ReplaceChar(m_canTinName).GetBuffer(),m_tableNum); //���ò���������ÿ����������������
		if ( -1 == id ){
			int n = roomCtrl.getRoomMax() +1 ;
			CString t;
			t.Format(_T("�˲����Ѿ�����,��������������:%d"),n);
			MessageBox(t,_T("����"),MB_ICONINFORMATION|MB_OK);
			m_GuiRoomNoEdit.SetFocus();
			return;
		}
		//���ɲ�������
		hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
		tableStatusCtrl.createTable(id,m_tableNum);

		Refresh();

		m_canTinName.Empty();
		m_tableNum = 1;
		m_roomNo = roomCtrl.getRoomMax() +1 ;
	}
	else //�޸�
	{
		if ( m_canTinName.IsEmpty() ){
			MessageBox(_T("����������Ϊ��!"),_T("����"),MB_ICONWARNING|MB_OK);
			m_GuiEditCanTinName.SetFocus();
			return;
		}
		if ( m_tableNum <=0 ){
			MessageBox(_T("������Ӧ�ô���0!"),_T("����"),MB_ICONWARNING|MB_OK);
			m_GuiEditNum.SetFocus();
			return;
		}

		m_GuiButtonAddCanTin.SetWindowText(_T("���"));
		m_GuiRoomNoEdit.EnableWindow(TRUE); //�����޸ķ����
		m_GuiButtonDelCanTin.EnableWindow(FALSE);

		//�޸����ݿ�
		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		hotelMIS::HRoom hRoom(m_roomNo,m_canTinName.GetBuffer(),m_tableNum);
		roomCtrl.updateRoom(hRoom);

		//���ɲ�������
		hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
		tableStatusCtrl.DeleteByRoomId(m_roomNo);
		tableStatusCtrl.createTable(m_roomNo,m_tableNum);

		Refresh();

		m_canTinName.Empty();
		m_tableNum = 1;
		m_roomNo = roomCtrl.getRoomMax() +1 ;

		m_isModify = FALSE;
	}
	UpdateData(FALSE);




	CPropertySheet* pParent=(CPropertySheet*)GetParent();
	pParent->PostMessage(WM_MODIFIED);

}

void CStep2::OnDeleteRoom()
{
	// TODO: ɾ������
	int pos = m_GuiListCanTin.GetSelectionMark();
	if ( pos != -1){
		int result = AfxMessageBox(_T("ȷ��Ҫɾ��?"),MB_YESNO|MB_ICONWARNING);
		if ( result == IDYES){
			hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
			hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con()); 
			
			int roomId = m_roomMap[pos];
			roomCtrl.deleteRoom(roomId); //ɾ������
			
			tableStatusCtrl.DeleteByRoomId(roomId);// ɾ������

			Refresh();
			m_GuiButtonDelCanTin.EnableWindow(false);

			CPropertySheet* pParent=(CPropertySheet*)GetParent();
			pParent->PostMessage(WM_MODIFIED);
		}	
	}
}

void CStep2::OnNMClickListCantin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCanTin.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCanTin.HitTest(point)) != -1 ) {
		TRACE("��������%d \n",nPos);
		m_GuiButtonDelCanTin.EnableWindow(true);
	}

}


void CStep2::OnNMDblclkListCantin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ˫���޸�
	*pResult = 0;

	m_isModify = TRUE;

	m_GuiRoomNoEdit.EnableWindow(FALSE); //�����޸ķ����
	m_GuiButtonDelCanTin.EnableWindow(FALSE);

	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCanTin.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCanTin.HitTest(point)) != -1 ) {
		TRACE("˫������%d \n",nPos);
		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		hotelMIS::HRoom hRoom = roomCtrl.getRoom(m_roomMap[nPos]);
		m_roomNo = hRoom.room_id;
		m_canTinName = hRoom.room_name.c_str();
		m_tableNum = hRoom.table_num;
		m_GuiButtonAddCanTin.SetWindowText(_T("�޸�"));
		UpdateData(FALSE);

	}

}
