// MemModifyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemModifyDlg.h"
#include ".\memmodifydlg.h"

#include "HMemberCtrl.h"

// CMemModifyDlg �Ի���

IMPLEMENT_DYNAMIC(CMemModifyDlg, CDialog)
CMemModifyDlg::CMemModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemModifyDlg::IDD, pParent)
	, m_bh(_T(""))
	, m_mname(_T(""))
	, m_sex(_T(""))
	, m_birth(COleDateTime::GetCurrentTime())
	, m_telphone(_T(""))
	, m_mdjname(_T(""))
	, m_zhekou(0)
	, m_czmoney(0)
	, m_remark(_T(""))
{
}

CMemModifyDlg::~CMemModifyDlg()
{
}

void CMemModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BH_EDIT, m_GuiBhEdit);
	DDX_Control(pDX, IDC_MNAME_EDIT, m_GuiMnameEdit);
	DDX_Control(pDX, IDC_SEXCOMBO, m_GuiSexCombo);
	DDX_Control(pDX, IDC_BIRTH_EDIT, m_GuiBirthEdit);
	DDX_Control(pDX, IDC_TEL_EDIT, m_GuiTelEdit);
	DDX_Control(pDX, IDC_MDJ_COMBO, m_GuiMDJCombo);
	DDX_Control(pDX, IDC_ZK_EDIT, m_GuiZKEdit);
	DDX_Control(pDX, IDC_CZMONEY_EDIT, m_GuiCzMoneyEdit);
	DDX_Control(pDX, IDC_REMARK_EDIT, m_GuiRemarkEdit);
	DDX_Text(pDX, IDC_BH_EDIT, m_bh);
	DDV_MaxChars(pDX, m_bh, 20);
	DDX_Text(pDX, IDC_MNAME_EDIT, m_mname);
	DDV_MaxChars(pDX, m_mname, 20);
	DDX_CBString(pDX, IDC_SEXCOMBO, m_sex);
	DDX_DateTimeCtrl(pDX, IDC_BIRTH_EDIT, m_birth);
	//DDX_Text(pDX, IDC_BIRTH_EDIT, m_birth);
	DDX_Text(pDX, IDC_TEL_EDIT, m_telphone);
	DDX_CBString(pDX, IDC_MDJ_COMBO, m_mdjname);
	DDX_Text(pDX, IDC_ZK_EDIT, m_zhekou);
	DDX_Text(pDX, IDC_CZMONEY_EDIT, m_czmoney);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_remark);
}


BEGIN_MESSAGE_MAP(CMemModifyDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_MDJ_COMBO, OnCbnSelchangeMdjCombo)
END_MESSAGE_MAP()


// CMemModifyDlg ��Ϣ�������

void CMemModifyDlg::OnBnClickedOk()
{
	UpdateData();

	//������

	hotelMIS::HMemberCtrl hMemberCtrl(m_con.get_con());
	
	////��֤��Ա���
	//if ( m_bh.Trim().IsEmpty())
	//{
	//	MessageBox(_T("�������Ա���!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
	//	m_GuiBhEdit.SetFocus();
	//	return;
	//}

		
	//��֤��Ա����
	if ( m_mname.Trim().IsEmpty())
	{
		MessageBox(_T("�������Ա����!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_GuiMnameEdit.SetFocus();
		return;
	}
	
	int r = MessageBox(_T("ȷ��Ҫ�޸Ĵ˻�Ա����Ϣ��?"),_T("��ʾ"),MB_ICONINFORMATION|MB_YESNO);
	if ( r != IDYES){
		return ;
	}

	hotelMIS::HMember hMember;
	hMember.bh = m_bh.Trim().GetBuffer();
	CString t;
	t.Format("%d-%d-%d",m_birth.GetYear(),m_birth.GetMonth(),m_birth.GetDay());
	hMember.mbirth = t.GetBuffer();

	int nPos =m_GuiMDJCombo.GetCurSel();
	hMember.mdjid = m_map[nPos].first;
	hMember.mdjname = m_mdjname.Trim().GetBuffer();
	hMember.zhekou = m_map[nPos].second;
	hMember.mname = m_mname.Trim().GetBuffer();
	
	hMember.remark = m_remark.Trim().GetBuffer();
	hMember.telphone = m_telphone.Trim().GetBuffer();
	hMember.sex = m_sex.Trim().GetBuffer();

	hMemberCtrl.update(hMember);

	OnOK();
}

BOOL CMemModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ��ʼ��

	m_GuiSexCombo.AddString(_T("��"));
	m_GuiSexCombo.AddString(_T("Ů"));
	
	//�����ݿ������λ
	//m_GuiSexCombo.SetCurSel(0);

	hotelMIS::HMdjCtrl hMdjCtrl(m_con.get_con());
	hotelMIS::HMdjVec vec = hMdjCtrl.getAllMdj();
	hotelMIS::HMdjVec::iterator it;

	int nPos = -1;
	m_map.clear();

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		nPos = m_GuiMDJCombo.AddString(it->djname.c_str());
		m_map.insert(make_pair(nPos,make_pair(it->id,it->zhekou)));
	}
		//�����ݿ������λ
	//m_GuiMDJCombo.SetCurSel(0);

	//m_zhekou = m_map[0].second;
	
	
	hotelMIS::HMemberCtrl hMemberCtrl(m_con.get_con());
	
	hotelMIS::HMember hMember = hMemberCtrl.getMember(m_bh.Trim().GetBuffer());
	m_bh= hMember.bh.c_str();
	m_mname = hMember.mname.c_str();
	m_sex = hMember.sex.c_str();
	m_birth.ParseDateTime(hMember.mbirth.c_str());
	m_telphone = hMember.telphone.c_str();
	m_mdjname = hMember.mdjname.c_str();
	m_zhekou = hMember.zhekou;
	m_czmoney = hMember.czmoney;
	m_remark = hMember.remark.c_str();

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMemModifyDlg::OnCbnSelchangeMdjCombo()
{
	UpdateData(TRUE);

	int nPos = m_GuiMDJCombo.GetCurSel();
	
	m_zhekou = m_map[nPos].second;
	
	UpdateData(FALSE);
}
