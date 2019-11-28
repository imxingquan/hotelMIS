// ChangeTableDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ChangeTableDialog.h"
#include "HRoomCtrl.h"
#include ".\changetabledialog.h"
//#include ".\changetabledialog.h"


// CChangeTableDialog 对话框

IMPLEMENT_DYNAMIC(CChangeTableDialog, CDialog)
CChangeTableDialog::CChangeTableDialog(CWnd* pParent /*=NULL*/,int tableId,int roomId)
	: CDialog(CChangeTableDialog::IDD, pParent)
	, m_destTableNo(0)
{
	pChgTableBdy = NULL;
	pChgTableBdy = new hotelMIS::HChgTableBdy(tableId,roomId);

}

CChangeTableDialog::~CChangeTableDialog()
{
	if ( pChgTableBdy )
	{
		delete pChgTableBdy;
		pChgTableBdy = NULL;
	}
}

void CChangeTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_COMBO_CHANGETABLE, m_GuiComboBox);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_CBIndex(pDX, IDC_COMBO_CHANGETABLE, m_destTableNo);
	DDX_Control(pDX, IDC_ROOMNO_COMBO, m_GuiRoomNoComBo);
}


BEGIN_MESSAGE_MAP(CChangeTableDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_ROOMNO_COMBO, OnCbnSelchangeRoomnoCombo)
END_MESSAGE_MAP()


// CChangeTableDialog 消息处理程序

void CChangeTableDialog::OnBnClickedOk()
{
	// TODO: 换桌
	UpdateData(TRUE);
	//TRACE("要换的餐桌为%d\n");
	if ( m_mapTable.size() != 0 ){  //如果再就餐情况下不可操作换桌就不需要加这个控制了
		m_destTid = pChgTableBdy->chgTable(m_mapTable[m_GuiComboBox.GetCurSel()],m_roomMap[m_GuiRoomNoComBo.GetCurSel()]);
		if ( m_destTid != -1 )
			AfxMessageBox(_T("换桌成功!请转到相应餐厅,点击工具栏上的[刷新]按钮!"));
	}
	OnOK();
}

BOOL CChangeTableDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.ShowText();
	m_GuiButtonOk.EnableWindow(false);

	InitRoomNoAndTalbeId();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CChangeTableDialog::InitRoomNoAndTalbeId()
{
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	hotelMIS::HRoomVector roomVec = roomCtrl.getAllRoom();
	hotelMIS::HRoomVector::iterator it;
	m_roomMap.clear();
	for ( it = roomVec.begin(); it != roomVec.end(); it++)
	{
		int pos = m_GuiRoomNoComBo.AddString(it->getName().c_str());
		m_roomMap.insert(make_pair(pos,it->getId()));
	}
	m_GuiRoomNoComBo.SetCurSel(-1);
	
	//// TODO:  提取所有空桌到列表
	//hotelMIS::TableCol tableCol = pChgTableBdy->getEmptyTable();
	//hotelMIS::TableCol::iterator tit;
	//CString tId;
	//int i = 0;
	//for ( tit = tableCol.begin(); tit != tableCol.end(); tit++)
	//{
	//	tId.Format("%d",*tit);
	//	int pos = m_GuiComboBox.AddString(tId);
	//	m_mapTable.insert(make_pair(pos,*tit));
	//}
	//m_GuiComboBox.SetCurSel(0);
}

void CChangeTableDialog::OnCbnSelchangeRoomnoCombo()
{
	// TODO:提取所有空桌

	m_GuiComboBox.ResetContent();

	int pos = m_GuiRoomNoComBo.GetCurSel();
	
	hotelMIS::HChgTableBdy tableBdy;

	hotelMIS::TableCol tableCol = tableBdy.getEmptyTable(m_roomMap[pos]);
	hotelMIS::TableCol::iterator it;
	CString tId;

	
	//int i = 0;
	m_mapTable.clear();
	for ( it = tableCol.begin(); it != tableCol.end(); it++)
	{
		tId.Format("%d",*it);
		pos = m_GuiComboBox.AddString(tId);
		m_mapTable.insert(make_pair(pos,*it));
	}

	m_GuiComboBox.SetCurSel(0);

	m_GuiButtonOk.EnableWindow(true);
}
