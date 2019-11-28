// PayDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "PayDialog.h"
#include "HRepDetailsCtrl.h"
#include "HSetHotelPrintMsg.h"
#include "PrintWarningDialog.h"
#include "HRoomCtrl.h"
#include "HTableStatusCtrl.h"
#include "hMemberCtrl.h"
#include "MyCdKey.h"
#include "HArrerageBdy.h"
#include "ArrearageDialog.h"
#include <math.h>

using namespace std;

// CPayDialog �Ի���

IMPLEMENT_DYNAMIC(CPayDialog, CDialog)
CPayDialog::CPayDialog(CWnd* pParent /*=NULL*/,int tableId, int roomId)
	: CDialog(CPayDialog::IDD, pParent)
	, m_ml(0)
	, m_ys(0)
	, m_ss(0)
	, m_zk(0)
	, m_sj(0)
	, m_zy(0)
	, m_invoice(FALSE)
	, m_subscription(0)
	, m_tableId(tableId)
	, m_roomId(roomId)
	, m_daijin(0)
	, m_bCheckDaiJin(FALSE)
	, m_accountId(_T(""))
	, m_bh(_T(""))
	, m_mname(_T(""))
	, m_czmoney(0)
	//, m_gzCheck(FALSE)
	, m_sswrCheck(TRUE)
	, m_bz(_T(""))
	, m_zfprice(0)
{
	m_payBdy = NULL;
	m_payBdy = new hotelMIS::HPayBdy(m_tableId,m_roomId,m_con.get_con());
}

CPayDialog::~CPayDialog()
{
	if ( m_payBdy){
		delete m_payBdy;
		m_payBdy = NULL;
	}

}

void CPayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXL, m_GuiGroupBoxL);
	DDX_Control(pDX, IDC_GROUPBOXRT, m_GuiGroupBoxRT);
	DDX_Control(pDX, IDC_GROUPBOXRB, m_GuiGroupBoxRB);
	DDX_Control(pDX, IDC_LIST_RECKONING, m_GuiListCtrlReckoning);
	DDX_Control(pDX, IDC_EDIT_ML, m_GuiEditML);
	DDX_Control(pDX, IDC_EDIT_YS, m_GuiEditYS);
	DDX_Control(pDX, IDC_EDIT_SS, m_GuiEditSS);
	DDX_Control(pDX, IDC_EDIT_ZK, m_GuiEditZK);
	DDX_Control(pDX, IDC_EDIT_SJ, m_GuiEditSJ);
	DDX_Control(pDX, IDC_EDIT_ZY, m_GuiEditZY);
	DDX_Control(pDX, IDC_CHECK_INVOICE, m_GuiButtonInvoice);
	DDX_Control(pDX, IDC_BUTTON_JZ, m_GuiButtonJZ);
	DDX_Control(pDX, IDC_BUTTON_GZ, m_GuiButtonGZ);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiButtonPrint);
	DDX_Control(pDX, IDCANCEL, m_GuiButtonOk);
	DDX_Text(pDX, IDC_EDIT_ML, m_ml);
	DDX_Text(pDX, IDC_EDIT_YS, m_ys);
	DDX_Text(pDX, IDC_EDIT_SS, m_ss);
	DDX_Text(pDX, IDC_EDIT_ZK, m_zk);
	DDX_Text(pDX, IDC_EDIT_SJ, m_sj);
	DDX_Text(pDX, IDC_EDIT_ZY, m_zy);
	DDX_Text(pDX, IDC_EDIT_DAIJIN, m_daijin);

	DDX_Check(pDX, IDC_CHECK_INVOICE, m_invoice);
	DDX_Control(pDX, IDC_EDIT_DJ, m_GuiEditDj);
	DDX_Text(pDX, IDC_EDIT_DJ, m_subscription);
	DDX_Control(pDX, IDC_CHECK_DAIJIN, m_GuiCheckDaiJin);
	DDX_Control(pDX, IDC_EDIT_DAIJIN, m_GuiEditDaiJin);
	DDX_Check(pDX, IDC_CHECK_DAIJIN, m_bCheckDaiJin);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_GuiButtonCancel);
	DDX_Text(pDX, IDC_STATIC_ACCID, m_accountId);
	DDX_Control(pDX, IDC_JZFS_COMBO, m_GuiJzfsCombo);
	DDX_Control(pDX, IDC_MBH_EDIT, m_GuiMbhEdit);
	DDX_Control(pDX, IDC_MXM_EDIT, m_GuiMxmEdit);
	DDX_Control(pDX, IDC_GETMEM_BUTTON, m_GuiGetMemBtn);
	DDX_Control(pDX, IDC_CZ_EDIT, m_GuiCzEdit);
	DDX_Text(pDX, IDC_MBH_EDIT, m_bh);
	DDX_Text(pDX, IDC_MXM_EDIT, m_mname);
	DDX_Text(pDX, IDC_CZ_EDIT, m_czmoney);
	DDX_Control(pDX, IDC_SPIN1, m_GuiSpinML);
	//DDX_Check(pDX, IDC_GZ_CHECK, m_gzCheck);
	DDX_Check(pDX, IDC_SSWR_CHECK, m_sswrCheck);
	DDX_Text(pDX, IDC_BZ_EDIT, m_bz);
	DDX_Text(pDX, IDC_ZFPRICE_EDIT, m_zfprice);
	DDX_Control(pDX, IDC_ZFPRICE_EDIT, m_GuiZfPriceEdit);
	
}


BEGIN_MESSAGE_MAP(CPayDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT_SJ, OnEnChangeEditSj)
	ON_EN_CHANGE(IDC_EDIT_ZK, OnEnChangeEditSj)
	ON_EN_CHANGE(IDC_EDIT_ML, OnEnChangeEditSj)
	ON_EN_CHANGE(IDC_ZFPRICE_EDIT,OnEnChangeEditSj)
	ON_BN_CLICKED(IDC_BUTTON_JZ, OnBnClickedButtonJz)
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_GZ, OnBnClickedButtonGz)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_CHECK_DAIJIN, OnBnClickedCheckDaijin)
	ON_EN_CHANGE(IDC_EDIT_DAIJIN, OnEnChangeEditDaijin)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_CBN_SELCHANGE(IDC_JZFS_COMBO, OnCbnSelchangeJzfsCombo)
	ON_EN_CHANGE(IDC_MBH_EDIT, OnEnChangeMbhEdit)
	
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SSWR_CHECK, OnBnClickedSswrCheck)
END_MESSAGE_MAP()


// CPayDialog ��Ϣ��������

void CPayDialog::OnEnChangeEditSj()
{
	
	OnBnClickedSswrCheck();
	Refresh();
}

BOOL CPayDialog::TestDigit(CString &s,CEdit *pEdit)
{
	for ( int i = 0; i < s.GetLength(); i++){
		TCHAR Char =s.GetAt(i);
		if( !isdigit( Char ) && Char != 46){
			AfxMessageBox(_T("����������!"));
			pEdit->SetFocus();
			return FALSE;
		}
	}
	return TRUE;
}

void CPayDialog::OnBnClickedButtonJz()
{
	// TODO: ����
	//�����˿� = ʵ���տ�-(Ӧ���˿�*�ۿ۱���)-�����˿�
	//ʵ���˿� = Ӧ���˿�*�ۿ۱���-�����˿�

	/*CTime time=CTime::GetCurrentTime();
	if ( time.GetYear() >= 2009 && time.GetMonth() >= 5 && time.GetDay() >= 1)
	{
		::MessageBox(NULL,_T("�������Թ�!���볧����ϵ,\n�绰:0411-84799689!"),_T("��ʾ"),MB_OK);
		return ;
	}*/
	
	int paystatus = m_GuiJzfsCombo.GetCurSel();
	/*if ( paystatus == 0) {
		MessageBox(_T("����ѡ����˷�ʽ!"),_T("��ʾ"),MB_ICONINFORMATION|MB_OK);
		m_GuiJzfsCombo.SetFocus();
		return;
	}*/

	UpdateData(TRUE);

	if ( m_ml <0 || m_ml >100 )
	{
		MessageBox(_T("Ĩ������0-100֮��,����������!"),_T("����"),MB_ICONSTOP|MB_OK);
		m_GuiEditML.SetFocus();
		return;
	}

	if (paystatus== JSFS::XYCARD || paystatus == JSFS::ZP||paystatus == JSFS::MCARD)
	{
		if ( m_zfprice <=0  ){
			MessageBox(_T("��������!"));
			m_GuiZfPriceEdit.SetFocus();
			return;
		}
		else if ( m_zfprice > m_ss){
			MessageBox(_T("֧�����ӦС�ڻ���ڽ����"));
			m_GuiZfPriceEdit.SetFocus();
			return;
		}
	}
	/*if ( paystatus == JSFS::XJ || paystatus== JSFS::XYCARD || paystatus == JSFS::ZP)
	{
		if ( atof(m_sj) < m_ss && m_zy < 0 ){
			MessageBox(_T("������Ŀ������,����������!"),_T("����"),MB_ICONSTOP|MB_OK);
			m_GuiEditSJ.SetFocus();
			return;
		}
	}*/
	//else
	//if (paystatus == JSFS::MCARD &&  m_czmoney < atof(m_sj) )
	//{	
	//	// ������õĻ�Ա��,��Ҫ�жϻ�Ա�Ĵ����ǲ��ǹ�����
	//	MessageBox(_T("���Ĵ������Ѳ������,���ȳ�ֵ������ֽ�ʽ����!"),_T("����"),MB_ICONSTOP|MB_OK);
	//	return;
	//}

	
	bool result = WarningPrint();
	if ( true == result){
		
	/*	if ( !TestDigit(m_sj,&m_GuiEditSJ) ||
			!TestDigit(m_ml,&m_GuiEditML) || 
			!TestDigit(m_daijin,&m_GuiEditDaiJin)
			
			)
			return ;
	*/
		
		if (  m_zy >= 0){
			
			
			m_payBdy->jz(m_invoice,paystatus,m_zfprice,m_bz.GetBuffer(),m_sswrCheck);
		
			m_payBdy->memberJz(paystatus,m_zfprice,m_bh.Trim().GetBuffer());
			
				

			OnOK();
		}else{
			AfxMessageBox(_T("������Ŀ������,����������!"));
			m_GuiEditSJ.SetFocus();
			return;
		}
		////�Ƿ��ӡСƱ
		//CWinApp* pApp = AfxGetApp();
		//int bPrintWarning = pApp->GetProfileInt("Settings", "PrintWarning",1);
		//if ( 1 == bPrintWarning){
		//	//��ʾ����Ի���
		//	CPrintWarningDialog dlg;
		//	if ( dlg.DoModal() == IDOK){
		//		OnBnClickedButtonPrint();
		//	}
		//}else{
		//	OnBnClickedButtonPrint();
		//}
	}

}

bool CPayDialog::WarningPrint()
{
	//�Ƿ��ӡСƱ
		CWinApp* pApp = AfxGetApp();
		int PrintWarning = pApp->GetProfileInt("Settings", "PrintWarning",1);
		int JzAndPrint= pApp->GetProfileInt("Settings", "JzAndPrint",1);
		if ( 1 == PrintWarning){
			//��ʾ����Ի���
			CPrintWarningDialog dlg;
			if ( dlg.DoModal() == IDOK){
				int JzAndPrint= pApp->GetProfileInt("Settings", "JzAndPrint",1);
				if ( 1== JzAndPrint ){
					TRY{
					OnBnClickedButtonPrint();
					}CATCH(CException,e){
						e->ReportError();
					}END_CATCH
				}
			}
			else{
				return false;
			}
		}else{
			int JzAndPrint= pApp->GetProfileInt("Settings", "JzAndPrint",1);
				if ( 1== JzAndPrint ){
					TRY{
					OnBnClickedButtonPrint();
					}CATCH(CException,e){
						e->ReportError();
					}END_CATCH
				}
		}
		return true;
}

void CPayDialog::Init()
{
	//����
	/*m_GuiEditYS.EnableWindow(FALSE);
	m_GuiEditDj.EnableWindow(FALSE);
	m_GuiEditSS.EnableWindow(FALSE);
	m_GuiEditZY.EnableWindow(FALSE);*/
	//��������
		
	int i = 0;
	m_GuiListCtrlReckoning.InsertColumn(i,_T("���"),LVCFMT_LEFT,35);
	m_GuiListCtrlReckoning.InsertColumn(++i,_T("����"),LVCFMT_LEFT,130);
	m_GuiListCtrlReckoning.InsertColumn(++i,_T("�۸�"),LVCFMT_RIGHT,70);
	m_GuiListCtrlReckoning.InsertColumn(++i,_T("����"),LVCFMT_LEFT,35);
	m_GuiListCtrlReckoning.InsertColumn(++i,_T("��λ"),LVCFMT_LEFT,40);
	m_GuiListCtrlReckoning.InsertColumn(++i,_T("����"),LVCFMT_LEFT,40);
	m_GuiListCtrlReckoning.InsertColumn(++i,_T("�ۺ��"),LVCFMT_RIGHT,50);

	m_GuiListCtrlReckoning.InsertColumn(++i,_T("��ʦ"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlReckoning.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	m_account_Id =accountId;
	m_accountId.Format("�˵���: %s",accountId.c_str());
	hotelMIS::HRepDetailsVec vec = repDetailsCtrl.getAllDetails(accountId);
	hotelMIS::HRepDetailsVec::iterator it;
	i = 0;
	CString cnt;
	float zkprice=0.0f;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		cnt.Format("%d",i+1);
		m_GuiListCtrlReckoning.InsertItem(i,cnt);
		m_GuiListCtrlReckoning.SetItemText(i,1,it->food_name.c_str());
		cnt.Format("%.2f",it->food_price);
		m_GuiListCtrlReckoning.SetItemText(i,2,cnt);
		cnt.Format("%d",it->food_num);
		m_GuiListCtrlReckoning.SetItemText(i,3,cnt);
		m_GuiListCtrlReckoning.SetItemText(i,4,it->food_unit.c_str()); //��λ
		cnt.Format("%.2f",it->zk_num);
		m_GuiListCtrlReckoning.SetItemText(i,5,cnt); //����
		zkprice += it->food_price * it->food_num * it->zk_num;
		cnt.Format("%.2f", it->food_price * it->food_num * it->zk_num);
		m_GuiListCtrlReckoning.SetItemText(i,6,cnt); //�ۺ��

		m_GuiListCtrlReckoning.SetItemText(i,7,it->ck_name.c_str());
		i++;
	}
	m_GuiListCtrlReckoning.InsertItem(i,_T("�ϼ�:"));
	HTotalPair t = repDetailsCtrl.getAllPrice(accountId);
	float ys = t.first + t.second;
	cnt.Format("%.2f",ys);
	m_GuiListCtrlReckoning.SetItemText(i,2,cnt);
	cnt.Format("%.2f",zkprice);
	m_GuiListCtrlReckoning.SetItemText(i,6,cnt);

	//��ʼ���˿�
	hotelMIS::HAccountCtrl accountCtrl(m_con.get_con());
	m_ys = ys;
	m_subscription = accountCtrl.getSubscription(accountId);
	//if ( m_subscription >= m_ys ){ //���������ڵ���Ӧ�� ���ö��𸳿�
	//	m_sj.Format("%.2f",m_subscription);
	//}else{
	//	m_sj.Empty();
	//}

	UpdateData(FALSE);
	OnEnChangeEditSj();

	//�����˷�ʽ
	m_GuiJzfsCombo.AddString(_T("��ѡ��..."));
	m_GuiJzfsCombo.AddString(_T("��  ��"));
	m_GuiJzfsCombo.AddString(_T("��Ա��"));	
	m_GuiJzfsCombo.AddString(_T("���ÿ�"));
	m_GuiJzfsCombo.AddString(_T("֧  Ʊ"));
	m_GuiJzfsCombo.SetCurSel(1);

	m_GuiSpinML.SetRange(0,100);
}

void CPayDialog::Refresh()
{
	m_GuiListCtrlReckoning.DeleteAllItems();

	hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	m_accountId.Format("�˵���: %s",accountId.c_str());
	hotelMIS::HRepDetailsVec vec = repDetailsCtrl.getAllDetails(accountId);
	hotelMIS::HRepDetailsVec::iterator it;
	int i = 0;
	CString cnt;
	float price=0.0f;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		cnt.Format("%d",i+1);
		m_GuiListCtrlReckoning.InsertItem(i,cnt);
		m_GuiListCtrlReckoning.SetItemText(i,1,it->food_name.c_str());
		cnt.Format("%.2f",it->food_price);
		m_GuiListCtrlReckoning.SetItemText(i,2,cnt);
		cnt.Format("%d",it->food_num);
		m_GuiListCtrlReckoning.SetItemText(i,3,cnt);
		m_GuiListCtrlReckoning.SetItemText(i,4,it->food_unit.c_str()); //��λ
		cnt.Format("%.2f",it->zk_num);
		m_GuiListCtrlReckoning.SetItemText(i,5,cnt); //�ۿ�
		price += it->food_price * it->food_num;
		cnt.Format("%.2f", it->food_price * it->food_num * it->zk_num);
		m_GuiListCtrlReckoning.SetItemText(i,6,cnt); //�ۺ��

		m_GuiListCtrlReckoning.SetItemText(i,7,it->ck_name.c_str());
		i++;
	}
	m_GuiListCtrlReckoning.InsertItem(i,_T("�ϼ�:"));
	HTotalPair t = repDetailsCtrl.getAllPrice(accountId);
	float zkprice = t.first + t.second;
	cnt.Format("%.2f",price);
	m_GuiListCtrlReckoning.SetItemText(i,2,cnt);
	cnt.Format("%.2f",zkprice);
	m_GuiListCtrlReckoning.SetItemText(i,6,cnt);	
}
BOOL CPayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_GuiButtonJZ.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonJZ.ShowText();
	m_GuiButtonGZ.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonGZ.ShowText();
	m_GuiButtonPrint.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonPrint.ShowText();
	m_GuiButtonOk.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonOk.ShowText();
	m_GuiButtonCancel.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonCancel.ShowText();

	//m_GuiEditML.SetMask(_T("#.##"),_T("0.00"));
	
	m_GuiEditZK.SetMask(_T("#.#"),_T("0.0"));

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	Init();
	m_font.CreatePointFont(190,_T("Arial"));
	GetDlgItem(IDC_EDIT_ML)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_YS)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_ZK)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_DJ)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_SS)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_SJ)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_ZY)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT_DAIJIN)->SetFont(&m_font);
	//m_GuiEditSS.GetDC()->SetTextColor(RGB(0,0,255));
	
	HRoomCtrl roomCtrl(m_con.get_con());
	CString t;
	t.Format(" %s-%d����",roomCtrl.getRoomName(m_roomId).c_str(),m_tableId);
	m_GuiGroupBoxL.SetCaption(t);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPayDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if ( nSBCode == SB_ENDSCROLL){
		return;
	}
	if ( pScrollBar->GetDlgCtrlID() == IDC_SPIN1){
		CString strValue;
		strValue.Format("%.2f",(float)nPos/10.0);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strValue);
	}else
	if ( pScrollBar->GetDlgCtrlID() == IDC_SPIN2){
		CString strValue;
		strValue.Format("%.2f",(float)nPos/10.0);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strValue);
	
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

HBRUSH CPayDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	TRACE("EDIT=%d\n", pWnd->GetDlgCtrlID());
	//pDC->SelectObject(&m_font);

	//if ( pWnd->GetDlgCtrlID() == IDC_EDIT_SJ ){
	//	pDC->SetTextColor(RGB(0,0,255));
	//	//pDC->SelectObject(&m_font);
	//}
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	

	if (   pWnd->GetDlgCtrlID() == IDC_EDIT_SS ){
		pDC->SetTextColor(RGB(0,0,255));
		//pDC->SelectObject(&m_font);
		//pDC->SetBkColor(RGB(255,255,255));
	}

	//���ñ���
	/*if (pWnd->GetDlgCtrlID() == IDC_EDIT_ML
		|| pWnd->GetDlgCtrlID() == IDC_EDIT_YS
		|| pWnd->GetDlgCtrlID() == IDC_EDIT_ZK
		|| pWnd->GetDlgCtrlID() == IDC_EDIT_DJ
		|| pWnd->GetDlgCtrlID() == IDC_EDIT_SS
		)
	{
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(RGB(0,255,0));
		pDC->SetBkColor(RGB(0,0,0));
		
	}*/
	
	if(nCtlColor== CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(RGB(255,0,0));
	}
	
	return hbr;
}


void CPayDialog::OnBnClickedButtonGz()
{
	UpdateData(TRUE);

	if ( m_ml <0 || m_ml >100 )
	{
		MessageBox(_T("Ĩ������0-100֮��,����������!"),_T("����"),MB_ICONSTOP|MB_OK);
		m_GuiEditML.SetFocus();
		return;
	}

	if ( m_bz.IsEmpty())
	{
		MessageBox(_T("��д��ע"),_T("����"),MB_ICONSTOP|MB_OK);
		GetDlgItem(IDC_BZ_EDIT)->SetFocus();
		return;
	}

	/*if ( !TestDigit(m_sj,&m_GuiEditSJ) || !TestDigit(m_ml,&m_GuiEditML) || !TestDigit(m_daijin,&m_GuiEditDaiJin))
			return ;*/

	bool result = WarningPrint();
	
		CArrearageDialog dlg;
		dlg.m_arrMoney = m_ss;
		dlg.m_accountId = m_account_Id;
			if ( dlg.DoModal() == IDOK){ //����
				m_payBdy->gz(m_invoice,m_bz.GetBuffer(),m_sswrCheck);

					//4) �������˺ź��˵���д��������ݿ�
				hotelMIS::HArrerageBdy arrBdy;
				arrBdy.gz(dlg.m_callback_arid,m_account_Id);
				//arrBdy.writeArrIdtoAccount(m_callback_arid,m_account_Id);
			}
	

	OnOK();
}

void CPayDialog::PrintReport(CDC *dc)
{
	

	hotelMIS::HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	hotelMIS::HRepastCtrl repastCtrl(m_con.get_con());
	string accountId = repastCtrl.getAccountId(m_tableId,m_roomId);
	hotelMIS::HRepDetailsVec vec = repDetailsCtrl.getAllDetails(accountId);
	hotelMIS::HRepDetailsVec::iterator it;
	
	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg hotelMsg = s.getHotelMsg();

	dc->SetMapMode(MM_LOMETRIC); //����Ϊ���׵�λ
	dc->SetTextAlign(TA_LEFT);
	
	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("����"));
	dc->SetTextColor(RGB(0,0,0));
	pOldFont = dc->SelectObject(&font);

	int xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",30);
	int yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	yPos = -yPos;
	int col_2_w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	int col_3_w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	int col_4_w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	int lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	int restline = pApp->GetProfileInt("Settings","PrintRestLine",6);

	CString acc;
	CTime t1=CTime::GetCurrentTime();
	
	TEXTMETRIC lpMetrics;
	
	dc->GetTextMetrics(&lpMetrics);
	int fHeight = lpMetrics.tmHeight + lineHeight;
	int n = 2;
	acc.Format("%s",hotelMsg.hotelname.c_str());
	dc->TextOut(xPos,yPos,acc);
	dc->TextOut(xPos,yPos-fHeight,_T("--------------����СƱ----------------"));

	HRoomCtrl roomCtrl(m_con.get_con());
	
	hotelMIS::HTableStatusCtrl tableStatusCtrl(m_con.get_con());
	string tableName = tableStatusCtrl.getTableName(m_tableId,m_roomId);

	if( !tableName.empty())
		acc.Format("%s-%d����[%s]",roomCtrl.getRoomName(m_roomId).c_str(),m_tableId,tableName.c_str());
	else
		acc.Format("%s-%d����",roomCtrl.getRoomName(m_roomId).c_str(),m_tableId);
		
	
	dc->TextOut(xPos,yPos-fHeight*n++,acc);

	acc.Format("�˵���: %s ",accountId.c_str());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	acc.Format("����: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	dc->TextOut(xPos,yPos-fHeight*5,_T("����"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*n,_T("����"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*n,_T("����"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*n++,_T("�ܼ�"));
		
	CString cnt;
	int len = 0;

	//float sum_price=0.0f;

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//����
		
		cnt.Format("%.2f",it->food_price);
		
		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;

		
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//����
		cnt.Format("%d",it->food_num);
		//dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//����
		cnt.Format("%.2f",it->food_price*it->food_num);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //�ܼ�
		
        n++;
	}
	
	/*HTotalPair t =  repDetailsCtrl.getAllPrice(accountId);
	float ys = t.first + t.second;*/
	cnt.Format("%.2f",m_ys);	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("�ϼ�:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	n++;	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));
	
	if ( m_zk > 0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("��    ��:"));
		cnt.Format("%.1f ",m_zk);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	if ( m_subscription > 0)
	{
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("Ѻ    ��:"));
		cnt.Format("%.2f",m_subscription);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	
	if ( m_bCheckDaiJin){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos-fHeight*n,_T("  ����ȯ:"));
		dc->SetTextAlign(TA_RIGHT);
		cnt.Format("%.2f",m_daijin);
		dc->TextOut(xPos+lpMetrics.tmAveCharWidth*col_4_w,yPos - fHeight*n,cnt);
	}
	if ( m_ml >0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos-fHeight*n,_T("������:"));
		dc->SetTextAlign(TA_RIGHT);
		cnt.Format("%.2f",m_ml);
		dc->TextOut(xPos+lpMetrics.tmAveCharWidth*col_4_w,yPos - fHeight*n,cnt);
	}

	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("������:"));
	//UpdateData(false);
	cnt.Format("%.2f",m_ss);
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		
	
	dc->SetTextAlign(TA_LEFT);
	if(m_sj > 0)
	{
		n++;
		dc->TextOut(xPos,yPos - fHeight*n,_T("�ֽ�֧��:"));
		cnt.Format("%.2f",m_sj);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}
	
	dc->SetTextAlign(TA_LEFT);
	if(m_zfprice >0)
	{
		n++;
		int nPos = m_GuiJzfsCombo.GetCurSel();
		if ( nPos == JSFS::MCARD)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("��Ա��֧��:"));
			cnt.Format("%.2f",m_zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
		else if(nPos == JSFS::XYCARD)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("���ÿ�֧��:"));
			cnt.Format("%.2f",m_zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
		else if(nPos == JSFS::ZP)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("֧Ʊ֧��:"));
			cnt.Format("%.2f",m_zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
	}
	
	if ( m_zy >=0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("��    ��:"));
		cnt.Format("%.2f",m_zy);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}
	
	if (!m_bz.IsEmpty())
	{
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("��ע: "));
		
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth+90,yPos -fHeight*n,m_bz);
		
	}

	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));

	if ( ! hotelMsg.hoteltel.empty() ){
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("���͵绰:"));
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel.c_str());
	}
	if ( ! hotelMsg.hoteltel2.empty() && ! hotelMsg.hoteltel.empty()){
	n++;
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel2.c_str());
	}
	if ( !hotelMsg.hotelhttp.empty()){
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("������ַ:"));
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hotelhttp.c_str());
	}

	MyCdKey cdkey;
	if ( !cdkey.RegisterCdKey()){
	n++;
	dc->TextOut(xPos,yPos -fHeight*n,_T("---------------------------------------"));
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("����֧��: ��������"));
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("http://www.digitwest.com"));
	}
	//print space line
	n = n+restline;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);
}

void CPayDialog::OnBnClickedButtonPrint()
{
	UpdateData(TRUE);

	int r = MessageBox(_T("ȷ��Ҫ��ʼ��ӡ?"),_T("����"),MB_ICONWARNING|MB_YESNO);
	if ( r != IDYES)
		return;

	CWinApp* pApp = AfxGetApp();
	CString sPrint = pApp->GetProfileString("Print","PrintBefore");
	HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //������ӡ���
	if ( hdc != NULL){
		CDC dc;
		dc.Attach(hdc);
		DOCINFO di;
		::ZeroMemory(&di,sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName= _T("�����˵�");

		dc.StartDoc(&di);
		dc.StartPage();
			PrintReport(&dc);
		dc.EndPage();
		dc.EndDoc();
	}
	else{
		MessageBox(_T("��ӡ������ʧ��!"));
	}
	//AfxMessageBox(_T("��ʾ�汾û�д˹���!�빺����������!\n�����ܲ�:0411-84799689\n���ɴ���:0471-6350482"),MB_ICONINFORMATION|MB_OK);
}

void CPayDialog::OnBnClickedCheckDaijin()
{
	// TODO: �Ƿ����ô����
	UpdateData(true);
	if ( m_bCheckDaiJin )
		m_GuiEditDaiJin.EnableWindow(true);
	else
		m_GuiEditDaiJin.EnableWindow(false);
	m_daijin = 0.0f;
	OnEnChangeEditDaijin();
}

void CPayDialog::OnEnChangeEditDaijin()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������

	UpdateData(TRUE);
    	
	//CString zy;
	//zy.Format("%.2f",m_payBdy->calc(
	//				static_cast<float>(atof(m_ml)),
	//				static_cast<float>(atof(m_zk)/10),
	//				static_cast<float>(atof(m_sj)),
	//				m_bCheckDaiJin,
	//				static_cast<float>(atof(m_daijin))
	//				)
	//			);
	//m_zy= static_cast<float>(atof(zy));
	//m_ss = m_payBdy->getSsPrice();
	//m_ys = m_payBdy->getYsPrice();

	//// ������㷽ʽ�ǻ�Ա��,��ʵ���ֽ� = ʵ���˿�
	//int paystatus = m_GuiJzfsCombo.GetCurSel();
	//if (paystatus == JSFS::MCARD )
	//	m_sj.Format("%.2f",m_ss);

	m_zy=m_payBdy->calc2(m_ml,m_zk/10,m_sj,m_zfprice,m_bCheckDaiJin,m_daijin);
		m_ss = m_payBdy->getSsPrice();
		m_ys=m_payBdy->getYsPrice();
		if(m_nCurrJSFS== JSFS::MCARD)
			m_zfprice=m_ss;

	UpdateData(FALSE);
}

void CPayDialog::OnBnClickedButtonCancel()
{
	//�˵�����
	int r = MessageBox(_T("ȷ��Ҫ�˵���?"),_T("����"),MB_YESNO|MB_ICONINFORMATION);
	if ( r == IDYES){
		UpdateData(TRUE);
		if ( m_bz.IsEmpty())
		{
			MessageBox(_T("��д��ע"),_T("����"),MB_ICONSTOP|MB_OK);
			GetDlgItem(IDC_BZ_EDIT)->SetFocus();
			return;
		}

		UpdateData(TRUE);
		m_payBdy->cancelMenu(m_invoice,m_bz.GetBuffer());
		OnOK();
	}
}
void CPayDialog::InitJz()
{
	m_sj=0.0f;
	m_zk = 0.0;
	m_bh.Empty();
	m_mname.Empty();
	m_czmoney = 0.0f;
	m_ml = 0.0f;
	m_zy = 0.0f;
	m_ss = m_ys;
	m_zfprice=0.0f;
	UpdateData(FALSE);
}
void CPayDialog::OnCbnSelchangeJzfsCombo()
{
	// TODO: ѡ����˷�ʽ
	
	//ÿ��ѡ�����
	InitJz();

	int nPos = m_GuiJzfsCombo.GetCurSel();
	if ( nPos == JSFS::XJ){  //�ֽ����
		m_nCurrJSFS =JSFS::XJ;
		//���� ��Ա����
		m_GuiMbhEdit.ShowWindow(SW_HIDE);
		m_GuiMxmEdit.ShowWindow(SW_HIDE);
		//m_GuiGetMemBtn.ShowWindow(SW_HIDE);
		m_GuiCzEdit.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MBH_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MNAME_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CZ_STATIC)->ShowWindow(SW_HIDE);

		//����֧������
		GetDlgItem(IDC_ZFPRICE_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ZFPRICE_EDIT)->ShowWindow(SW_HIDE);


	}
	else if ( nPos == JSFS::MCARD){ //��Ա��
		m_nCurrJSFS = JSFS::MCARD;
		// ��ʾ ��Ա���,��Ա����,��Ա��ֵ
		m_GuiMbhEdit.ShowWindow(SW_SHOW);
		m_GuiMxmEdit.ShowWindow(SW_SHOW);
		//m_GuiGetMemBtn.ShowWindow(SW_SHOW);
		m_GuiCzEdit.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MBH_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MNAME_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CZ_STATIC)->ShowWindow(SW_SHOW);
	
			
		//֧������
		GetDlgItem(IDC_ZFPRICE_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ZFPRICE_EDIT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_ZFPRICE_STATIC)->SetWindowText(_T("��Ա��֧��"));
		
	}
	else if ( nPos == JSFS::XYCARD || nPos == JSFS::ZP){ //���ÿ�
		m_nCurrJSFS = (JSFS)nPos;
		//���� ��Ա����
		m_GuiMbhEdit.ShowWindow(SW_HIDE);
		m_GuiMxmEdit.ShowWindow(SW_HIDE);
		//m_GuiGetMemBtn.ShowWindow(SW_HIDE);
		m_GuiCzEdit.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MBH_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MNAME_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CZ_STATIC)->ShowWindow(SW_HIDE);
		
		//֧������
		GetDlgItem(IDC_ZFPRICE_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ZFPRICE_EDIT)->ShowWindow(SW_SHOW);

		if ( nPos == JSFS::XYCARD)
			GetDlgItem(IDC_ZFPRICE_STATIC)->SetWindowText(_T("���ÿ�֧��"));
		else if ( nPos == JSFS::ZP)
			GetDlgItem(IDC_ZFPRICE_STATIC)->SetWindowText(_T("֧Ʊ֧��"));
	}
	
	OnEnChangeEditSj();
}

void CPayDialog::OnEnChangeMbhEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO: �����Ա�ź� ������Ա��Ϣ
	// ��� ��Ա����,��Ա��ֵ���
	
	UpdateData();
	hotelMIS::HMemberCtrl hMemberCtrl(m_con.get_con());
	HMember hMember = hMemberCtrl.getMember(m_bh.Trim().GetBuffer());
	if ( hMember.bh.empty() )
		return;

	m_mname = hMember.mname.c_str();
	m_czmoney = hMember.czmoney; //��Ա���



	//�������Ա���ۿ۱�����д ���ۿ���
	m_zk=hMember.zhekou;

	//��Ա��֧��
	if ( m_czmoney >= m_ss)
		m_zfprice = m_ss;
	else
		m_zfprice = m_czmoney;
	
	UpdateData(false);

		//���¼���ʵ���˿�
	OnEnChangeEditSj();
	
}



void CPayDialog::OnBnClickedCancel()
{
	HRepDetailsCtrl repDetailsCtrl(m_con.get_con());
	repDetailsCtrl.update(m_account_Id,1);

	OnCancel();
}

//��������࣬Ӧ�գ�ʵ��
void CPayDialog::OnBnClickedSswrCheck()
{
	
	// ��������
	UpdateData(TRUE);
	
	if ( m_zfprice > m_ss)
	{
		m_zfprice = m_ss;
	}
	
	if ( m_sswrCheck )
	{
		
		
		/*CString zy;
		zy.Format("%.2f",m_payBdy->calc2(
			static_cast<float>(atof(m_ml)),
			static_cast<float>(atof(m_zk)/10),
			static_cast<float>(atof(m_sj)),
			m_bCheckDaiJin,
			static_cast<float>(atof(m_daijin))
			)
			);
		m_zy= static_cast<float>(atof(zy));
		m_ss = m_payBdy->getSsPrice();
		m_ys = m_payBdy->getYsPrice();
		if (m_nCurrJSFS == JSFS::MCARD )
			m_sj.Format("%.2f",m_ss);*/
		
		m_zy=m_payBdy->calc2(m_ml,m_zk/10,m_sj,m_zfprice,m_bCheckDaiJin,m_daijin);
		m_ss = m_payBdy->getSsPrice();
		m_ys=m_payBdy->getYsPrice();
		

		
	}
	else{

		
	/*CString zy;
	zy.Format("%.2f",m_payBdy->calc(
					static_cast<float>(atof(m_ml)),
					static_cast<float>(atof(m_zk)/10),
					static_cast<float>(atof(m_sj)),
					m_bCheckDaiJin,
					static_cast<float>(atof(m_daijin))
					)
				);
	m_zy= static_cast<float>(atof(zy));
	m_ss = m_payBdy->getSsPrice();
	m_ys = m_payBdy->getYsPrice();
	if (m_nCurrJSFS == JSFS::MCARD )
		m_sj.Format("%.2f",m_ss);*/
	m_zy=m_payBdy->calc(m_ml,m_zk/10,m_sj,m_zfprice,m_bCheckDaiJin,m_daijin);
		m_ss = m_payBdy->getSsPrice();
		m_ys=m_payBdy->getYsPrice();
		
	
	}
	UpdateData(FALSE);
}

float CPayDialog::myRound(float x)
{
	if((int)x*10+5 > (int)(x*10))
		return floor(x);
	else
		return ceil(x);
}