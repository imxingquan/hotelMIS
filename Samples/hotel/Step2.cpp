// Step2.cpp : 实现文件
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


// CStep2 对话框

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


// CStep2 消息处理程序

BOOL CStep2::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CPropertySheet* pParent=(CPropertySheet*)GetParent(); // 获得属性表的指针
	//pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); // 设置属性表的显示按钮只为下一步
	return CPropertyPage::OnSetActive();
}

BOOL CStep2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_GuiButtonDelCanTin.ShowText();
	m_GuiButtonAddCanTin.ShowText();

	// TODO:  在此添加额外的初始化
	Init();
	Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CStep2::Init()
{
	m_GuiListCanTin.InsertColumn(0,_T("编号"),LVCFMT_LEFT,40);
	m_GuiListCanTin.InsertColumn(1,_T("餐厅名"),LVCFMT_LEFT,80);
	m_GuiListCanTin.InsertColumn(2,_T("餐桌数量"),LVCFMT_LEFT,90);
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
	//// TODO: 添加
	////--------------------------------验证--------------------------
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
			MessageBox(_T("餐厅名不能为空!"),_T("警告"),MB_ICONWARNING|MB_OK);
			m_GuiEditCanTinName.SetFocus();
			return;
		}
		if ( m_tableNum <=0 ){
			MessageBox(_T("餐桌数应该大于0!"),_T("警告"),MB_ICONWARNING|MB_OK);
			m_GuiEditNum.SetFocus();
			return;
		}

		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		int id = roomCtrl.insertRoom(m_roomNo,hotelMIS::ReplaceChar(m_canTinName).GetBuffer(),m_tableNum); //设置餐厅个数及每个餐厅的桌子数量
		if ( -1 == id ){
			int n = roomCtrl.getRoomMax() +1 ;
			CString t;
			t.Format(_T("此餐厅已经存在,建议输入餐厅编号:%d"),n);
			MessageBox(t,_T("提醒"),MB_ICONINFORMATION|MB_OK);
			m_GuiRoomNoEdit.SetFocus();
			return;
		}
		//生成餐桌数量
		hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
		tableStatusCtrl.createTable(id,m_tableNum);

		Refresh();

		m_canTinName.Empty();
		m_tableNum = 1;
		m_roomNo = roomCtrl.getRoomMax() +1 ;
	}
	else //修改
	{
		if ( m_canTinName.IsEmpty() ){
			MessageBox(_T("餐厅名不能为空!"),_T("警告"),MB_ICONWARNING|MB_OK);
			m_GuiEditCanTinName.SetFocus();
			return;
		}
		if ( m_tableNum <=0 ){
			MessageBox(_T("餐桌数应该大于0!"),_T("警告"),MB_ICONWARNING|MB_OK);
			m_GuiEditNum.SetFocus();
			return;
		}

		m_GuiButtonAddCanTin.SetWindowText(_T("添加"));
		m_GuiRoomNoEdit.EnableWindow(TRUE); //不能修改房间号
		m_GuiButtonDelCanTin.EnableWindow(FALSE);

		//修改数据库
		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		hotelMIS::HRoom hRoom(m_roomNo,m_canTinName.GetBuffer(),m_tableNum);
		roomCtrl.updateRoom(hRoom);

		//生成餐桌数量
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
	// TODO: 删除操作
	int pos = m_GuiListCanTin.GetSelectionMark();
	if ( pos != -1){
		int result = AfxMessageBox(_T("确定要删除?"),MB_YESNO|MB_ICONWARNING);
		if ( result == IDYES){
			hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
			hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con()); 
			
			int roomId = m_roomMap[pos];
			roomCtrl.deleteRoom(roomId); //删除餐厅
			
			tableStatusCtrl.DeleteByRoomId(roomId);// 删除餐桌

			Refresh();
			m_GuiButtonDelCanTin.EnableWindow(false);

			CPropertySheet* pParent=(CPropertySheet*)GetParent();
			pParent->PostMessage(WM_MODIFIED);
		}	
	}
}

void CStep2::OnNMClickListCantin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCanTin.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCanTin.HitTest(point)) != -1 ) {
		TRACE("单击命中%d \n",nPos);
		m_GuiButtonDelCanTin.EnableWindow(true);
	}

}


void CStep2::OnNMDblclkListCantin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 双击修改
	*pResult = 0;

	m_isModify = TRUE;

	m_GuiRoomNoEdit.EnableWindow(FALSE); //不能修改房间号
	m_GuiButtonDelCanTin.EnableWindow(FALSE);

	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCanTin.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCanTin.HitTest(point)) != -1 ) {
		TRACE("双击命中%d \n",nPos);
		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		hotelMIS::HRoom hRoom = roomCtrl.getRoom(m_roomMap[nPos]);
		m_roomNo = hRoom.room_id;
		m_canTinName = hRoom.room_name.c_str();
		m_tableNum = hRoom.table_num;
		m_GuiButtonAddCanTin.SetWindowText(_T("修改"));
		UpdateData(FALSE);

	}

}
