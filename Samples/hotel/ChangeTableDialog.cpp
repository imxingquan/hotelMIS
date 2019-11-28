// ChangeTableDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ChangeTableDialog.h"
#include "HRoomCtrl.h"
#include ".\changetabledialog.h"
//#include ".\changetabledialog.h"


// CChangeTableDialog �Ի���

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


// CChangeTableDialog ��Ϣ�������

void CChangeTableDialog::OnBnClickedOk()
{
	// TODO: ����
	UpdateData(TRUE);
	//TRACE("Ҫ���Ĳ���Ϊ%d\n");
	if ( m_mapTable.size() != 0 ){  //����پͲ�����²��ɲ��������Ͳ���Ҫ�����������
		m_destTid = pChgTableBdy->chgTable(m_mapTable[m_GuiComboBox.GetCurSel()],m_roomMap[m_GuiRoomNoComBo.GetCurSel()]);
		if ( m_destTid != -1 )
			AfxMessageBox(_T("�����ɹ�!��ת����Ӧ����,����������ϵ�[ˢ��]��ť!"));
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
	// �쳣: OCX ����ҳӦ���� FALSE
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
	
	//// TODO:  ��ȡ���п������б�
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
	// TODO:��ȡ���п���

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
