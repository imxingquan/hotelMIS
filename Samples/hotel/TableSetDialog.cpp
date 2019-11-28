// TableSetDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TableSetDialog.h"
#include ".\tablesetdialog.h"
#include "HTableStatusSetCtrl.h"
#include "HTableStatusCtrl.h"


// CTableSetDialog �Ի���

IMPLEMENT_DYNAMIC(CTableSetDialog, CDialog)
CTableSetDialog::CTableSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTableSetDialog::IDD, pParent)
	, m_curTableMsg(_T(""))
	, m_tableName(_T(""))
{
}
CTableSetDialog::CTableSetDialog(CWnd* pParent,int tableId,int roomId)
	: CDialog(CTableSetDialog::IDD, pParent)
{
	m_tableId = tableId;
	m_roomId = roomId;

}
CTableSetDialog::~CTableSetDialog()
{
}

void CTableSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CURRENT_TABLE_MSG, m_curTableMsg);
	DDX_Control(pDX, IDC_TABLE_NAME_EDIT, m_GuiTableNameEdit);
	DDX_Control(pDX, IDC_TABLE_STATUS, m_GuiComboTableStatus);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Text(pDX, IDC_TABLE_NAME_EDIT, m_tableName);
}


BEGIN_MESSAGE_MAP(CTableSetDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTableSetDialog ��Ϣ�������

BOOL CTableSetDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ��ʼ��

	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.ShowText();
	m_curTableMsg.Format("%d�Ų���,%d�Ų���״̬:",m_roomId,m_tableId);
	UpdateData(false);

	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CTableSetDialog::Init()
{
	//��ʼ��������״̬�ͱ�
	//���ò���״̬�б�
	hotelMIS::HTableStatusSetCtrl tableStatusSetCtrl(m_con.get_con());
	hotelMIS::HTableStatusSetVec vec2 = tableStatusSetCtrl.getAllTableStatusSet();
	hotelMIS::HTableStatusSetVec::iterator it2;
	int nPos = -1;
	m_GuiComboTableStatus.ResetContent();
	m_map_tableStatus.clear();
	m_map_tableStatus2.clear();
	for ( it2 = vec2.begin(); it2!=vec2.end(); ++it2)
	{
		nPos = m_GuiComboTableStatus.AddString((*it2).getState_name().c_str());
		m_map_tableStatus.insert(make_pair(nPos,(*it2).getTable_state()));
		m_map_tableStatus2.insert(make_pair((*it2).getTable_state(),nPos));
	}

	hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
	//ȡ�ò���������
	m_tableName = tableStatusCtrl.getTableName(m_tableId,m_roomId).c_str();
	UpdateData(false);
	//���ò�����״̬
	
	int state = tableStatusCtrl.getTableStatus(m_tableId,m_roomId);
	m_GuiComboTableStatus.SetCurSel(m_map_tableStatus2[state]);
    
}
void CTableSetDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����������д�����ݿ�
	UpdateData(true);
	hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
	tableStatusCtrl.setTableName(hotelMIS::ReplaceChar(m_tableName).GetBuffer(),m_tableId,m_roomId);

	//������״̬д�����ݿ�
	int nPos = m_GuiComboTableStatus.GetCurSel();
	tableStatusCtrl.setTableState(m_map_tableStatus[nPos],m_tableId,m_roomId);
	OnOK();
}
