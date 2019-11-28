// YDXXDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "YDXXDialog.h"
#include ".\ydxxdialog.h"

#include "HRepastCtrl.h"

// CYDXXDialog �Ի���

IMPLEMENT_DYNAMIC(CYDXXDialog, CDialog)
CYDXXDialog::CYDXXDialog(CWnd* pParent /*=NULL*/,int id,bool bModify)
	: CDialog(CYDXXDialog::IDD, pParent)
	, m_name(_T(""))
	, m_personNum(2)
	, m_ydDate(COleDateTime::GetCurrentTime())
	, m_subscription(0)
	, m_remark(_T(""))
	, m_bModify(bModify)
	, m_phone(_T(""))
	, m_id(id)
	
{
	
	m_hour = m_ydDate.GetHour();
	m_min = m_ydDate.GetMinute();
}

CYDXXDialog::~CYDXXDialog()
{
	
}

void CYDXXDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_EDIT_NAME, m_GuiEditName);
	DDX_Control(pDX, IDC_EDIT_PERSON_NUM, m_GuiEditPersonNum);
	DDX_Control(pDX, IDC_EDIT_YDDATE, m_GuiDTCtrlYDDate);
	DDX_Control(pDX, IDC_EDIT_YDTIME, m_GuiEditYDTime);
	DDX_Control(pDX, IDC_EDIT_SUBSCRIPTION, m_GuiEditSubScription);
	DDX_Control(pDX, IDC_EDIT_REMARK, m_GuiEditRemark);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PERSON_NUM, m_personNum);
	DDX_DateTimeCtrl(pDX, IDC_EDIT_YDDATE, m_ydDate);
	DDX_Text(pDX, IDC_EDIT_YDTIME, m_hour);
	DDX_Text(pDX, IDC_EDIT_SUBSCRIPTION, m_subscription);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_remark);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_GuiPhoneEdit);
	DDX_Text(pDX, IDC_PHONE_EDIT, m_phone);
	DDX_Control(pDX, IDC_SPIN1, m_hourSpinBtn);
	DDX_Control(pDX, IDC_SPIN2, m_minSpinBtn);
	DDX_Text(pDX, IDC_MIN_EDIT, m_min);
	DDX_Control(pDX, IDC_MIN_EDIT, m_GuiMinEdit);
}


BEGIN_MESSAGE_MAP(CYDXXDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_EDITCHANGE(IDC_COMBO_HALL_NO, OnCbnEditchangeComboHallNo)
END_MESSAGE_MAP()


// CYDXXDialog ��Ϣ�������


void CYDXXDialog::OnBnClickedOk()
{
	// TODO:Ԥ��
	UpdateData(TRUE);
	if ( m_name.Trim().IsEmpty() ){
		MessageBox(_T("������˿�����!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
		m_GuiEditName.SetFocus();
		return;
	}
	if ( m_hour <0 || m_hour > 23 ){
		MessageBox(_T("Сʱ��0 - 23 ֮��!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
		m_GuiEditYDTime.SetFocus();
		return;
	}
	if ( m_min < 0 || m_min > 59){
		MessageBox(_T("������0 - 59 ֮��!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
		m_GuiMinEdit.SetFocus();
		return;
	}
	if ( m_subscription < 0 || m_subscription > 10000){
		MessageBox(_T("������Ч��Χ,����������!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
		return;
	}


	CString date = m_ydDate.Format("%Y-%m-%d");
	CString ydTime;
	ydTime.Format("%d:%d",m_hour,m_min);
	if ( ! m_bModify ){	
		m_pDestineBdy.destine(hotelMIS::ReplaceChar(m_name).GetBuffer(),hotelMIS::ReplaceChar(m_phone).GetBuffer(),
		date.Trim().GetBuffer(),ydTime.Trim().GetBuffer(),
		m_personNum,m_subscription,hotelMIS::ReplaceChar(m_remark).GetBuffer());
		MessageBox(_T("Ԥ�������ɹ�!"),_T("ϵͳ����"),MB_ICONINFORMATION|MB_OK);
		
	}
	else{
		m_pDestineBdy.modify(m_id,hotelMIS::ReplaceChar(m_name).GetBuffer(),hotelMIS::ReplaceChar(m_phone).GetBuffer(),
			date.Trim().GetBuffer(),ydTime.Trim().GetBuffer(),
			m_personNum,m_subscription,hotelMIS::ReplaceChar(m_remark).GetBuffer());
		
	}
	OnOK();
}

void CYDXXDialog::OnCbnEditchangeComboHallNo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CYDXXDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.ShowText();
	
	if ( m_bModify ) m_GuiButtonOk.SetWindowText(_T("�޸�"));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	m_hourSpinBtn.SetRange(0,23);
	m_minSpinBtn.SetRange(0,59);
	
	if (true  == m_bModify){
		hotelMIS::HDestineCtrl destineCtrl(m_con.get_con());
		//hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
		hotelMIS::HDestine destine = destineCtrl.getDestine(m_id);
		m_name = destine.guest_name.c_str();
		m_personNum = destine.person_num;
		vector<int> vd;
		string::size_type pos =0 ,prev_pos  = 0;
		while ( (pos = destine.come_date.find('-',pos))
			!= string::npos)
		{
			vd.push_back(atoi(destine.come_date.substr(prev_pos,pos-prev_pos).c_str()));
			prev_pos = ++pos;
		}
		vd.push_back(atoi(destine.come_date.substr(prev_pos,pos-prev_pos).c_str())); //get last one.
		
		TRACE("%d-%d-%d\n",vd[0],vd[1],vd[2]);
		m_ydDate.SetDate(vd[0],vd[1],vd[2]);
		pos=0;
		pos = destine.come_time.find_first_of(":",pos);
		//CString hourmin;
		//hourmin.Format("%d",destine.come_time.substr(0,pos).c_str());
		m_hour = static_cast<int>(atoi(destine.come_time.substr(0,pos).c_str()));
		//hourmin.Format("%d",destine.come_time.substr(pos+1,destine.come_time.length()).c_str());
		m_min = static_cast<int>(atoi(destine.come_time.substr(pos+1,2).c_str()));
		m_subscription = destine.subscription;
		m_remark = destine.remark.c_str();
		m_phone = destine.guest_phone.c_str();
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
