G// EmployeeDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "EmployeeDialog.h"
//#include ".\employeedialog.h"


// CEmployeeDialog �Ի���

IMPLEMENT_DYNAMIC(CEmployeeDialog, CDialog)
CEmployeeDialog::CEmployeeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployeeDialog::IDD, pParent)
	, m_empId(_T(""))
	, m_empName(_T(""))
	, m_empSex(_T(""))
	, m_empBir(_T(""))
	, m_empAddress(_T(""))
	, m_empPhone(_T(""))
	, m_empRemark(_T(""))
	, m_photoUrl(_T(""))
	, m_empJob(_T(""))
{
}

CEmployeeDialog::~CEmployeeDialog()
{
}

void CEmployeeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOX, m_GuiGroupBox);
	DDX_Control(pDX, IDC_EDIT_EMP_ID, m_GuiEditEmpId);
	DDX_Control(pDX, IDC_EDIT_EMP_NAME, m_GuiEditEmpName);
	DDX_Control(pDX, IDC_COMBO_EMP_SEX, m_GuiComboSex);
	DDX_Control(pDX, IDC_EDIT_EMP_BIR, m_GuiEditEmpBir);

	DDX_Control(pDX, IDC_EDIT_EMP_ADDRESS, m_GuiEditAddress);
	DDX_Control(pDX, IDC_EDIT_EMP_PHONE, m_GuiEditPhone);
	DDX_Control(pDX, IDC_EDIT_EMP_REMARK, m_GuiEditRemark);
	DDX_Control(pDX, IDC_EDIT_PHOTO_URL, m_GuiEditPhotoUrl);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonCancel);
	DDX_Text(pDX, IDC_EDIT_EMP_ID, m_empId);
	DDX_Text(pDX, IDC_EDIT_EMP_NAME, m_empName);
	DDX_CBString(pDX, IDC_COMBO_EMP_SEX, m_empSex);
	DDX_Text(pDX, IDC_EDIT_EMP_BIR, m_empBir);
	DDX_Text(pDX, IDC_EDIT_EMP_ADDRESS, m_empAddress);
	DDX_Text(pDX, IDC_EDIT_EMP_PHONE, m_empPhone);
	DDX_Text(pDX, IDC_EDIT_EMP_REMARK, m_empRemark);
	DDX_Text(pDX, IDC_EDIT_PHOTO_URL, m_photoUrl);
	DDX_Control(pDX, IDC_COMBO1, m_GuiComboBoxJobSet);
	DDX_CBString(pDX, IDC_COMBO1, m_empJob);
}


BEGIN_MESSAGE_MAP(CEmployeeDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelectChgJob)
END_MESSAGE_MAP()


// CEmployeeDialog ��Ϣ�������

void CEmployeeDialog::OnBnClickedOk()
{
	// TODO: �����Ա��
	UpdateData(true);
	
	if ( m_empId.IsEmpty() ){
		MessageBox(_T("������Ա����!"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_OK);
		return;
	}else if ( m_empName.IsEmpty() ){
		MessageBox(_T("������Ա������!"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	m_pos = m_GuiComboBoxJobSet.GetCurSel();

	int result = m_empBdy.AddEmp(
		hotelMIS::ReplaceChar(m_empId).GetBuffer(),
		hotelMIS::ReplaceChar(m_empName).GetBuffer(),
		hotelMIS::ReplaceChar(m_empSex).GetBuffer(),
		m_jobMap[m_pos],m_empJob.Trim().GetBuffer(),
		hotelMIS::ReplaceChar(m_empPhone).GetBuffer(),
		hotelMIS::ReplaceChar(m_empBir).GetBuffer(),
		hotelMIS::ReplaceChar(m_empAddress).GetBuffer(),
		hotelMIS::ReplaceChar(m_empRemark).GetBuffer(),
		hotelMIS::ReplaceChar(m_photoUrl).GetBuffer());
	if ( result != 0){
		MessageBox(_T("Ա������Ѿ�����,����������!"),_T("����"),MB_ICONWARNING|MB_OK);
		m_empId.Empty();
		m_GuiEditEmpId.SetFocus();
		
	}
	else{
		MessageBox(_T("һ����Ա����ӳɹ�!"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_empId.Empty();
		m_empName.Empty();
		//m_empJob.Empty();
		m_empPhone.Empty();
		m_empBir.Empty();
		m_empAddress.Empty();
		m_empRemark.Empty();
	}
	UpdateData(false);
}

BOOL CEmployeeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.ShowText();
	
	// TODO:  
	//��ʼ���Ա�/������
	m_GuiComboSex.AddString(_T("��"));
	m_GuiComboSex.AddString(_T("Ů"));
	m_GuiComboSex.SetCurSel(0);

	hotelMIS::HJobSetVec vec = m_empBdy.getAllJob();
	hotelMIS::HJobSetVec::iterator it;
	int i;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		i = m_GuiComboBoxJobSet.AddString(it->getJob_name().c_str());
		m_jobMap.insert(make_pair(i,it->getJob_id()));

	}
	m_GuiComboBoxJobSet.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CEmployeeDialog::OnCbnSelectChgJob()
{
	// TODO: 
	
}
