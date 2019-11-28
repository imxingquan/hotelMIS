// Step4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "Step4.h"
#include ".\step4.h"
#include "KProfile.h"
#include "KDBCon.h"
#include "HAccountCtrl.h"
#include "HAccDetailsCtrl.h"
#include "HArrerageCtrl.h"
#include "HDestineCtrl.h"
#include "HFoodKindCtrl.h"
#include "HMenuInfoCtrl.h"
#include "HOutStoreCtrl.h"
#include "HRepastCtrl.h"
#include "HRepDetailsCtrl.h"
#include "HRepertoryCtrl.h"
#include "SetMemDjDlg.h"
#include "HBeforeRepCtrl.h"
#include "KDBCon.h"
#include "HPwdCtrl.h"
#include "HMemberCtrl.h"
#include "HBehindRepCtrl.h"
#include "HInOutRepCtrl.h"
#include "HEmployeeCtrl.h"

// CStep4 �Ի���

IMPLEMENT_DYNAMIC(CStep4, CPropertyPage)
CStep4::CStep4(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CStep4::IDD)
	, m_autoRefresh(FALSE)
	, m_printWarning(FALSE)
	, m_jzAndPrint(FALSE)
	, m_bNeedPwd(FALSE)
	, m_awardPwd1(_T(""))
	, m_awardPwd2(_T(""))
	, m_bRepNumWarning(FALSE)
	, m_bRepOpen(FALSE)
{
}

CStep4::~CStep4()
{
}

void CStep4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AUTOREFRESH_CHECK, m_autoRefresh);
	DDX_Check(pDX, IDC_PRINT_WARNING, m_printWarning);
	DDX_Control(pDX, IDC_AUTOREFRESH_CHECK, m_GuiAutoRefreshCheck);
	DDX_Control(pDX, IDC_PRINT_WARNING, m_GuiPrintWarningCheck);
	DDX_Control(pDX, IDC_JZANDPRINT_CHECK, m_GuiJZAndPrintCheck);
	DDX_Check(pDX, IDC_JZANDPRINT_CHECK, m_jzAndPrint);
	DDX_Control(pDX, IDC_NEEDPWD_CHECK, m_GuiNeedPwdCheck);
	DDX_Control(pDX, IDC_AWARDPWD1_EDIT, m_GuiAwardPwd1Edit);
	DDX_Control(pDX, IDC_AWARDPWD2_EDIT, m_GuiAwardPwd2Edit);
	DDX_Check(pDX, IDC_NEEDPWD_CHECK, m_bNeedPwd);
	DDX_Text(pDX, IDC_AWARDPWD1_EDIT, m_awardPwd1);
	DDX_Text(pDX, IDC_AWARDPWD2_EDIT, m_awardPwd2);
	DDX_Control(pDX, IDC_SETPWD_BTN, m_GuiSetPwdBtn);
	DDV_MaxChars(pDX, m_awardPwd1, 10);
	DDV_MaxChars(pDX, m_awardPwd2, 10);
	DDX_Check(pDX, IDC_REPWARNING_CHECK, m_bRepNumWarning);
	DDX_Control(pDX, IDC_REPWARNING_CHECK, m_GuiRepWarningCheck);
	DDX_Check(pDX, IDC_CHECK_REP_C, m_bRepOpen);
	DDX_Control(pDX, IDC_CHECK_REP_C, m_GuiRepOpenCheck);
}


BEGIN_MESSAGE_MAP(CStep4, CPropertyPage)
	ON_WM_CLOSE()
	
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_CLEARALL, OnBnClickedButtonClearall)
	ON_BN_CLICKED(IDC_SETMEMDJ_BUTTON, OnBnClickedSetmemdjButton)
	ON_BN_CLICKED(IDC_SETPWD_BTN, OnBnClickedSetpwdBtn)
	ON_BN_CLICKED(IDC_NEEDPWD_CHECK, OnBnClickedNeedpwdCheck)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_MEMCZ, OnBnClickedButtonClearMemcz)
	ON_BN_CLICKED(IDC_AUTOREFRESH_CHECK, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_PRINT_WARNING, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_JZANDPRINT_CHECK, OnBnClickedCheck)
END_MESSAGE_MAP()


// CStep4 ��Ϣ�������

BOOL CStep4::OnSetActive()
{
	// TODO: �ڴ˴������Ϣ����������
	/*CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
	pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); */
	

	return CPropertyPage::OnSetActive();
}

BOOL CStep4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CWinApp* pApp = AfxGetApp();
	m_autoRefresh = pApp->GetProfileInt("Settings", "AutoRefresh",1);
	m_printWarning = pApp->GetProfileInt("Settings", "PrintWarning",1);
	m_jzAndPrint = pApp->GetProfileInt("Settings", "JzAndPrint",1);
	

	//������Ҫ����
	m_bNeedPwd = pApp->GetProfileInt("Settings","bNeedAwardPwd",1); 
	//�����ʾ
	m_bRepNumWarning = pApp->GetProfileInt("Settings", "repNumWarning",0);

	//ǰ��̨������

	m_bRepOpen = pApp->GetProfileInt("Settings", "repOpen",0);

	//�������� �������������
	m_GuiAwardPwd1Edit.EnableWindow(m_bNeedPwd);
	m_GuiAwardPwd2Edit.EnableWindow(m_bNeedPwd);
	m_GuiSetPwdBtn.EnableWindow(m_bNeedPwd);
	
	//�����ݿ��н�����ȡ��
	hotelMIS::KDBCon con;
	hotelMIS::HPwdCtrl hPwdCtrl(con.get_con());
	m_awardPwd1 = hPwdCtrl.getAwardPwd().c_str();
	m_awardPwd2 = m_awardPwd1;
	
	

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



LRESULT CStep4::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	return CPropertyPage::OnWizardNext();
}

void CStep4::OnBnClickedButtonClear()
{
	// TODO: �������Ӫҵ����
	int r = MessageBox(_T("���������,�����ܱ��ָ�,���Ҫ�����?"),_T("��ʾ"),MB_ICONWARNING|MB_YESNO);
	if ( r != IDYES)
		return ;

	hotelMIS::KDBCon con;
	hotelMIS::HAccountCtrl accountCtrl(con.get_con());
	accountCtrl.DeleteAll();
	hotelMIS::HAccDetailsCtrl accDetailsCtrl(con.get_con());
	accDetailsCtrl.DeleteAll();
	hotelMIS::HArrerageCtrl arrCtrl(con.get_con());
	arrCtrl.DeleteAll();
	hotelMIS::HArrerageZHCtrl arrZhCtrl(con.get_con());
	arrZhCtrl.DeleteAll();
	hotelMIS::HDestineCtrl destineCtrl(con.get_con());
	destineCtrl.DeleteAll();
	hotelMIS::HRepastCtrl repastCtrl(con.get_con());
	repastCtrl.DeleteAll();
	hotelMIS::HRepDetailsCtrl repDetailsCtrl(con.get_con());
	repDetailsCtrl.DeleteAll();
	/*hotelMIS::HRepertoryCtrl repertoryCtrl(con.get_con());
	repertoryCtrl.DeleteAll();*/
	hotelMIS::HBeforeRepCtrl beforeRepCtrl(con.get_con());
	beforeRepCtrl.DeleteAll();
	hotelMIS::HBehindRepCtrl behindRepCtrl(con.get_con());
	behindRepCtrl.DeleteAll();
	hotelMIS::HInOutRepCtrl inOutRepCtrl(con.get_con());
	inOutRepCtrl.DeleteAll();
	hotelMIS::HMemberCtrl memberCtrl(con.get_con());
	memberCtrl.DeleteAll();
	hotelMIS::HMczCtrl mczCtrl(con.get_con());
	mczCtrl.DeleteAll();
	hotelMIS::HMdjCtrl mdjCtrl(con.get_con());
	mdjCtrl.DeleteAll();

	MessageBox(_T("����ɹ�!"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
}

void CStep4::OnBnClickedButtonClearall()
{
	// TODO: �����������
	int r = MessageBox(_T("���������,�����ܱ��ָ�,���Ҫ�����?"),_T("��ʾ"),MB_ICONWARNING|MB_YESNO);
	if ( r != IDYES)
		return ;

	hotelMIS::KDBCon con;
	hotelMIS::HAccountCtrl accountCtrl(con.get_con());
	accountCtrl.DeleteAll();
	hotelMIS::HAccDetailsCtrl accDetailsCtrl(con.get_con());
	accDetailsCtrl.DeleteAll();
	hotelMIS::HArrerageCtrl arrCtrl(con.get_con());
	arrCtrl.DeleteAll();
	hotelMIS::HArrerageZHCtrl arrZhCtrl(con.get_con());
	arrZhCtrl.DeleteAll();
	hotelMIS::HDestineCtrl destineCtrl(con.get_con());
	destineCtrl.DeleteAll();
	hotelMIS::HFoodKindCtrl foodKindCtrl(con.get_con());
	foodKindCtrl.DeleteAll();
	hotelMIS::HMenuInfoCtrl menuInfoCtrl(con.get_con());
	menuInfoCtrl.DeleteAll();
	hotelMIS::HRepastCtrl repastCtrl(con.get_con());
	repastCtrl.DeleteAll();
	hotelMIS::HRepDetailsCtrl repDetailsCtrl(con.get_con());
	repDetailsCtrl.DeleteAll();
	/*hotelMIS::HRepertoryCtrl repertoryCtrl(con.get_con());
	repertoryCtrl.DeleteAll();*/
	hotelMIS::HEmployeeCtrl employeeCtrl(con.get_con());
	employeeCtrl.getAllEmployee();
	hotelMIS::HBeforeRepCtrl beforeRepCtrl(con.get_con());
	beforeRepCtrl.DeleteAll();
	hotelMIS::HBehindRepCtrl behindRepCtrl(con.get_con());
	behindRepCtrl.DeleteAll();
	hotelMIS::HInOutRepCtrl inOutRepCtrl(con.get_con());
	inOutRepCtrl.DeleteAll();
	hotelMIS::HMemberCtrl memberCtrl(con.get_con());
	memberCtrl.DeleteAll();
	hotelMIS::HMczCtrl mczCtrl(con.get_con());
	mczCtrl.DeleteAll();
	hotelMIS::HMdjCtrl mdjCtrl(con.get_con());
	mdjCtrl.DeleteAll();
	hotelMIS::HMzzCtrl mzzCtrl(con.get_con());
	mzzCtrl.DeleteAll();

	MessageBox(_T("����ɹ�!"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
}

void CStep4::OnBnClickedButtonClearMemcz()
{
	// TODO: ������Ա��ֵ����
	int r = MessageBox(_T("���������,�����ܱ��ָ�,���Ҫ�����?"),_T("��ʾ"),MB_ICONWARNING|MB_YESNO);
	if ( r != IDYES)
		return ;

	hotelMIS::KDBCon con;
	hotelMIS::HMczCtrl hMczCtrl(con.get_con());
	hMczCtrl.DeleteAll();
	MessageBox(_T("����ɹ�!"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
}

void CStep4::OnBnClickedSetmemdjButton()
{
	// TODO: ���û�Ա�ȼ�
	CSetMemDjDlg dlg;
	dlg.DoModal();
}

void CStep4::OnBnClickedSetpwdBtn()
{
	// TODO: ������������
	UpdateData();
	if ( m_awardPwd1.IsEmpty() && m_awardPwd2.IsEmpty())
	{
		MessageBox(_T("���벻��Ϊ��!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_GuiAwardPwd1Edit.SetFocus();
		return;
	}

	if ( m_awardPwd1 != m_awardPwd2 ){
		MessageBox(_T("������������벻һ��,����������!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_GuiAwardPwd2Edit.SetFocus();
		return;
	}

	hotelMIS::KDBCon con;
	hotelMIS::HPwdCtrl hPwdCtrl(con.get_con());
	hPwdCtrl.setAwardPwd(m_awardPwd1.GetBuffer());
	MessageBox(_T("�������óɹ�!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);

}

void CStep4::OnBnClickedNeedpwdCheck()
{
	// TODO: 
	UpdateData();
	//�������� �������������
	m_GuiAwardPwd1Edit.EnableWindow(m_bNeedPwd);
	m_GuiAwardPwd2Edit.EnableWindow(m_bNeedPwd);
	m_GuiSetPwdBtn.EnableWindow(m_bNeedPwd);
}



BOOL CStep4::OnApply()
{
	// TODO: �ڴ����ר�ô����/����û���

	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "AutoRefresh", m_GuiAutoRefreshCheck.GetCheck());
	pApp->WriteProfileInt("Settings", "PrintWarning", m_GuiPrintWarningCheck.GetCheck());
	pApp->WriteProfileInt("Settings", "JzAndPrint", m_GuiJZAndPrintCheck.GetCheck());
	pApp->WriteProfileInt("Settings", "bNeedAwardPwd", m_GuiNeedPwdCheck.GetCheck()); //д����������
	pApp->WriteProfileInt("Settings", "repNumWarning", m_GuiRepWarningCheck.GetCheck());
	pApp->WriteProfileInt("Settings", "repOpen", m_GuiRepOpenCheck.GetCheck());
	
	SetModified(FALSE);

	return CPropertyPage::OnApply();
}

void CStep4::OnBnClickedCheck()
{
	SetModified(TRUE);
}
