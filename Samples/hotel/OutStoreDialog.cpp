// OutStoreDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "OutStoreDialog.h"
//#include ".\outstoredialog.h"
#include "HMenuInfoCtrl.h"
#include "HUnitCtrl.h"
#include "HOutStoreCtrl.h"
#include "HAdminBdy.h"
// COutStoreDialog �Ի���

IMPLEMENT_DYNAMIC(COutStoreDialog, CDialog)
COutStoreDialog::COutStoreDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COutStoreDialog::IDD, pParent)
	, m_id(0)
	, m_num(0)
	, m_price(0)
	, m_unit(_T(""))
	, m_dateTime(COleDateTime::GetCurrentTime())
	, m_opType(0)
{
}

COutStoreDialog::~COutStoreDialog()
{
}

void COutStoreDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_COMBO_OS_ID, m_GuiComboOutStoreId);
	DDX_Control(pDX, IDC_EDIT_OS_NUM, m_GuiEditNum);
	DDX_Control(pDX, IDC_EDIT_OS_PRICE, m_GuiEditPrice);
	DDX_Control(pDX, IDC_COMBO_OS_UNIT, m_GuiComboBoxUnit);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_GuiDateTimeCtrl);
	DDX_Control(pDX, IDC_COMBO_OPTYPE, m_GuiComboOpType);
	DDX_CBIndex(pDX, IDC_COMBO_OS_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_OS_NUM, m_num);
	DDX_Text(pDX, IDC_EDIT_OS_PRICE, m_price);
	DDX_CBString(pDX, IDC_COMBO_OS_UNIT, m_unit);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_dateTime);
	DDX_CBIndex(pDX, IDC_COMBO_OPTYPE, m_opType);
	DDX_Control(pDX, IDOK, m_GuiOkBtn);
	DDX_Control(pDX, IDCANCEL, m_GuiCancelBtn);
}


BEGIN_MESSAGE_MAP(COutStoreDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_OS_ID, OnCbnSelchangeComboOsId)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// COutStoreDialog ��Ϣ�������

void COutStoreDialog::Init()
{
	//��ʼ������,�������Ʒ
	hotelMIS::HMenuInfoCtrl menuInfoCtrl( m_con.get_con());
	hotelMIS::HMenuInfoVec vec = menuInfoCtrl.getAllMenuInfoRep();
	hotelMIS::HMenuInfoVec::iterator it;
	int pos = 0;
	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		m_GuiComboOutStoreId.AddString(it->food_name.c_str());
		m_mapout.insert(make_pair(pos,make_pair(it->food_id,it->food_unit)));
		TRACE("pos = %d,food_id = %d,food_unit=%s\n",pos,it->food_id,it->food_unit.c_str());
		pos++;
	}
	m_GuiComboOutStoreId.SetCurSel(0);
	
	//��ʼ����λ
	hotelMIS::HUnitCtrl unitCtrl(m_con.get_con());
	hotelMIS::HUnitVec uVec = unitCtrl.getAllUnit();
	hotelMIS::HUnitVec::iterator uIt;
	for ( uIt = uVec.begin(); uIt != uVec.end(); uIt++)
	{
		m_GuiComboBoxUnit.AddString(uIt->getUnit_name().c_str());
	}
	m_unit = m_mapout[0].second.c_str();
	UpdateData(FALSE);
	//m_GuiComboReUnit.SetWindowText(m_maprep[0].second.c_str());
	m_GuiComboBoxUnit.EnableWindow(FALSE);
	m_GuiDateTimeCtrl.EnableWindow(FALSE);

	m_GuiComboOpType.AddString(_T("����"));
	m_GuiComboOpType.AddString(_T("�������"));
	m_GuiComboOpType.SetCurSel(0);
}

void COutStoreDialog::OnCbnSelchangeComboOsId()
{
	// TODO: 	// TODO: ѡ��ʱ�ı䵽���յ�λ
	TRACE("UNIT= %s\n",m_mapout[m_GuiComboOutStoreId.GetCurSel()].second.c_str());
	//m_GuiComboReUnit.SetWindowText(m_maprep[m_GuiComboReId.GetCurSel()].second.c_str());
	m_unit = m_mapout[m_GuiComboOutStoreId.GetCurSel()].second.c_str();
	m_id = m_GuiComboOutStoreId.GetCurSel();
	UpdateData(FALSE);
}

void COutStoreDialog::OnBnClickedOk()
{
	// TODO: �������
	UpdateData(TRUE);
	//������

	if ( m_num <=0 ){
		AfxMessageBox(_T("��������С�ڵ�����!"));
		return;
	}
	if ( m_price <=0 ){
		AfxMessageBox(_T("�۸���С�ڵ�����!"));
		return;
	}
	

	CString date,tmp;
	hotelMIS::HOutStoreCtrl outCtrl(m_con.get_con());
	hotelMIS::HOutStore out;
	out.food_id = m_mapout[m_GuiComboOutStoreId.GetCurSel()].first;
	m_GuiComboOutStoreId.GetWindowText(tmp);
	out.food_name = hotelMIS::ReplaceChar(tmp).GetBuffer();
	out.out_num = m_num;
	out.out_price = m_price;
	out.out_unit = hotelMIS::ReplaceChar(m_unit).GetBuffer();
	
	date.Format("%d-%d-%d",m_dateTime.GetYear(),m_dateTime.GetMonth(),m_dateTime.GetDay());
	out.out_date = date.GetBuffer();
	out.ad_name = hotelMIS::HAdminBdy::_log_name;
	if ( 0 == m_opType ){ //�������
		out.out_flag = m_opType;
		tmp.Format("�����Ʒ: %s\n����:%d\n����:%.2f\nȷʵ��ȷ����[ȷ��]��ť����!",out.food_name.c_str(),out.out_num,out.out_price);
		int result = AfxMessageBox(tmp,MB_YESNO);
		if ( IDYES == result ){
			int num = outCtrl.insert(out,0);
			if ( num != -1 ){
				CString tmp;
				tmp.Format("��ǰ�����Ϊ%d,��������,���������!",num);
				AfxMessageBox(tmp);
			}else
				AfxMessageBox(_T("����ɹ�!"));
		}
	}else{	//�������
		out.out_flag = m_opType;
		tmp.Format("��������::%s\n����:%d\n����:%.2f\nȷʵ��Ҫ���Ӹò�Ʒ�Ŀ��\n����[ȷ��]��ť��������!",out.food_name.c_str(),out.out_num,out.out_price);
		int result = AfxMessageBox(tmp,MB_YESNO);
		if ( IDYES == result ){
			outCtrl.insert(out,1);
			AfxMessageBox(_T("�����ɹ�!"));
		}
	}
	//OnOK();
	m_num = 0;
	m_price =0.0f;
	UpdateData(FALSE);
	
}

BOOL COutStoreDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiOkBtn.ShowText();
	m_GuiCancelBtn.ShowText();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
