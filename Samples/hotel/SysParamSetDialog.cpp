// SysParamSetDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "SysParamSetDialog.h"
#include ".\sysparamsetdialog.h"
//#include "KDBCon.h"
#include "HRoomCtrl.h"
#include "HTableStatusSetCtrl.h"


// CSysParamSetDialog 对话框

IMPLEMENT_DYNAMIC(CSysParamSetDialog, CDialog)
CSysParamSetDialog::CSysParamSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSysParamSetDialog::IDD, pParent)
	, m_tableStatus(_T(""))
	, m_canTinName(_T(""))
	, m_tableNum(5)
	, m_canTinBh(0)
{
}

CSysParamSetDialog::~CSysParamSetDialog()
{
}

void CSysParamSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXL, m_GuiGroupBoxL);
	DDX_Control(pDX, IDC_GROUPBOXR, m_GuiGroupBoxR);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);
	DDX_Control(pDX, IDC_EDIT_TABLE_STATUS, m_GuiEditTableStatus);
	DDX_Control(pDX, IDC_LIST_TABLE_STATUS, m_GuiListBoxTableStatus);
	DDX_Control(pDX, IDC_BUTTON_ADD_TABLE_STATUS, m_GuiButtonAddTableStatus);
	DDX_Control(pDX, IDC_BUTTON_DEL_TABLE_STATUS, m_GuiButtonDelTableStatus);
	DDX_Control(pDX, IDC_EDIT_CANTIN_NAME, m_GuiEditCanTinName);
	DDX_Control(pDX, IDC_EDIT_TABLE_NUM, m_GuiEditTableNum);
	DDX_Control(pDX, IDC_LIST_CANTIN, m_GuiListCtrlCanTin);
	DDX_Control(pDX, IDC_BUTTON_ADD_CANTIN, m_GuiButtonAddCanTin);
	DDX_Control(pDX, IDC_BUTTON_DEL_CANTIN, m_GuiButtonDelCanTin);
	DDX_Control(pDX, IDC_COMBO_CANTIN, m_GuiComboBoxCanTin);
	DDX_Control(pDX, IDC_COMBO_TABLE_STATUS, m_GuiComboBoxTableStatus);
	DDX_Control(pDX, IDC_BUTTON_SET_TABLE_STATUS, m_GuiButtonSetTableStatus);
	DDX_Text(pDX, IDC_EDIT_TABLE_STATUS, m_tableStatus);
	DDX_Text(pDX, IDC_EDIT_CANTIN_NAME, m_canTinName);
	DDX_Text(pDX, IDC_EDIT_TABLE_NUM, m_tableNum);

	DDX_Text(pDX, IDC_EDIT_CANTINBH, m_canTinBh);
	DDX_Control(pDX, IDC_LIST_TABLE_FLAG, m_GuiListCtrlTableFlag);
}


BEGIN_MESSAGE_MAP(CSysParamSetDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CANTIN, OnBnClickedButtonAddCantin)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TABLE_STATUS, OnBnClickedButtonAddTableStatus)
END_MESSAGE_MAP()


// CSysParamSetDialog 消息处理程序

BOOL CSysParamSetDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitShell();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSysParamSetDialog::OnBnClickedButtonAddCantin()
{
	// TODO: 餐厅设置
    UpdateData(TRUE);
	if ( m_canTinName.IsEmpty() ){
		AfxMessageBox(_T("餐厅名不能为空!"));
		m_GuiEditCanTinName.SetFocus();
		return;
	}
	if ( m_tableNum <=0 ){
		AfxMessageBox(_T("餐桌数应该大于0!"));
		m_GuiEditTableNum.SetFocus();
		return;
	}

	
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	roomCtrl.insertRoom(m_canTinName.GetBuffer(),m_tableNum); //设置餐厅个数及每个餐厅的桌子数量
	//刷新餐厅裂表及桌子设置列表
}
void CSysParamSetDialog::InitShell()
{
	//初始化餐厅桌子列表的表头
	
	m_GuiListCtrlCanTin.InsertColumn(0,_T("编号"),LVCFMT_LEFT,40);
	m_GuiListCtrlCanTin.InsertColumn(1,_T("餐厅名"),LVCFMT_LEFT,80);
	
	m_GuiListCtrlTableFlag.InsertColumn(0,_T("桌号"),LVCFMT_LEFT,40);
	m_GuiListCtrlTableFlag.InsertColumn(1,_T("状态"),LVCFMT_LEFT,80);
	
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlCanTin.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlTableFlag.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	RefreshRoomList();
}

void CSysParamSetDialog::RefreshRoomList()
{
	//刷新餐厅裂表
	//hotelMIS::KDBCon con;
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	hotelMIS::HRoomVector vec = roomCtrl.getAllRoom();
	hotelMIS::HRoomVector::iterator it;
	int i = 0;
	CString cnt;
	for ( it = vec.begin(); it!=vec.end(); ++it)
	{
		cnt.Format("%d",i+1);
		m_GuiListCtrlCanTin.InsertItem(i,cnt);
		m_GuiListCtrlCanTin.SetItemText(i,1,(*it).getName().c_str());
		++i;
	}
}

void CSysParamSetDialog::RefreshTableComobBox()
{
	//桌子设置列表
}
void CSysParamSetDialog::OnBnClickedButtonAddTableStatus()
{
	// TODO: 添加餐桌状态
	UpdateData(TRUE);
	
	//hotelMIS::KDBCon con;
	hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());
	tableStatusSetCtrl.insert(m_tableStatus.GetBuffer());
    	
}
