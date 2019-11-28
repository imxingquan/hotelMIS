// ReportDayDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ReportDayDialog.h"
#include "PreParent.h"		//��ӡԤ��������
#include "HSetHotelPrintMsg.h"
#include "HAdminBdy.h"
#include "PrintReportDay.h"
#include "XFDetailsDlg.h"
#include <math.h>
// CReportDayDialog �Ի���
CString CReportDayDialog::m_hotelname;
CString CReportDayDialog::m_exp;

IMPLEMENT_DYNAMIC(CReportDayDialog, CDialog)
CReportDayDialog::CReportDayDialog(CWnd* pParent /*=NULL*/)
: CDialog(CReportDayDialog::IDD, pParent)
, m_dStart(COleDateTime::GetCurrentTime())
, m_dEnd(COleDateTime::GetCurrentTime())


, m_jsfsPos(0)
{
	m_tEnd.ParseDateTime(_T("23:59:59"));
}

CReportDayDialog::~CReportDayDialog()
{
}

void CReportDayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXT, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);

	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_GuiButtonSearch);
	DDX_Control(pDX, IDC_LIST_REPORT_DAY, m_GuiListCtrlReporyDay);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_GuiDTCtrl);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiButtonPrint);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dStart);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_tStart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_dEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_tEnd);

	DDX_Control(pDX, IDC_COMBO1, m_jzfsCombo);
	DDX_CBIndex(pDX, IDC_COMBO1, m_jsfsPos);
}


BEGIN_MESSAGE_MAP(CReportDayDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)

	ON_COMMAND(ID_PRINT_PREVIEW, OnPrintPreview)
	ON_COMMAND(ID_POPUP_PRINT, OnPopupPrint)
	ON_COMMAND(ID_EXACT_EXCEL, OnExactExcel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT_DAY, OnNMDblclkListReportDay)
END_MESSAGE_MAP()


// CReportDayDialog ��Ϣ�������

void CReportDayDialog::OnBnClickedButtonSearch()
{
	// TODO: 
	UpdateData();
	
	totalByDay();
	
}

void CReportDayDialog::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CReportDayDialog::totalByDay()
{
	m_GuiListCtrlReporyDay.DeleteAllItems();

	UpdateData(true);

	CString t;
	string start_dtime,end_dtime;
	t = m_dStart.Format("%Y-%m-%d");
	t += m_tStart.Format(" %H:%M:%S");
	start_dtime = t.GetBuffer();
	t = m_dEnd.Format("%Y-%m-%d");
	t += m_tEnd.Format(" %H:%M:%S");
	end_dtime = t.GetBuffer();

	//ͳ������ //��ӡʹ��
	m_exp.Format("%s �� %s",start_dtime.c_str(),end_dtime.c_str());

	m_accvec = m_reportBdy.totalByDateTime(start_dtime,end_dtime,m_jsfsPos);
	hotelMIS::HAccountVec::iterator it ;

	int i = 0;
	int j=0;
	float sum_sscost = 0.0f;
	float sum_ys =0.0f;
	float sum_subscription = 0.0f;
	float sum_mcard = 0.0f,sum_xj = 0.0f,sum_xycard=0.0f,sum_zp=0.0f,sum_daiji=0.0f;
m_accMap.clear();
	m_GuiListCtrlReporyDay.DeleteAllItems();
	for ( it = m_accvec.begin(); it != m_accvec.end(); it++)
	{
		j = 1;
		m_accMap.insert(make_pair(i,it->account_id)); //�ʵ���
		m_GuiListCtrlReporyDay.InsertItem(i,it->account_id.c_str()); //�ʵ���
		t.Format("%.2f",it->yscost);m_GuiListCtrlReporyDay.SetItemText(i,j++,t); //Ӧ���˿�
		t.Format("%.2f",it->zhekou);m_GuiListCtrlReporyDay.SetItemText(i,j++,t);//�ۿ�
		t.Format("%.2f",it->erase_zero);m_GuiListCtrlReporyDay.SetItemText(i,j++,t); //Ĩ��
		float ss = it->sscost+it->erase_zero+it->subscription+it->daijin;
		if ( it->sswr == 1) ss = myRound(ss);
		t.Format("%.2f",ss);m_GuiListCtrlReporyDay.SetItemText(i,j++,t); //ʵ���˿�
		
		t.Format("%.2f",it->subscription);m_GuiListCtrlReporyDay.SetItemText(i,j++,t); //����
		t.Format("%.2f",(it->sswr==1 ? myRound(it->sj-it->zy):it->sj-it->zy) );m_GuiListCtrlReporyDay.SetItemText(i,j++,t); //�ֽ�
		t.Format("%.2f",it->daijin);m_GuiListCtrlReporyDay.SetItemText(i,j++,t); //����
				
		if ( it->paystatus== hotelMIS::HAccount::JSFS::mcard) //��Ա��
		{	
			sum_mcard += it->zfprice;
			t.Format("%.2f",it->zfprice);
			m_GuiListCtrlReporyDay.SetItemText(i,j++,t);
		}
		else
			m_GuiListCtrlReporyDay.SetItemText(i,j++,_T("0.0"));

		if ( it->paystatus== hotelMIS::HAccount::JSFS::xycard) //���ÿ�
		{	
			sum_xycard += it->zfprice;
			t.Format("%.2f",it->zfprice);
			m_GuiListCtrlReporyDay.SetItemText(i,j++,t);
		}
		else
			m_GuiListCtrlReporyDay.SetItemText(i,j++,_T("0.0"));

		if ( it->paystatus== hotelMIS::HAccount::JSFS::zp) //֧Ʊ
		{	
			sum_zp += it->zfprice;
			t.Format("%.2f",it->zfprice);
			m_GuiListCtrlReporyDay.SetItemText(i,j++,t);
		}
		else
			m_GuiListCtrlReporyDay.SetItemText(i,j++,_T("0.0"));

		m_GuiListCtrlReporyDay.SetItemText(i,j++,it->bz.c_str()); //��ע

		
		sum_sscost += it->sscost+it->erase_zero+it->subscription+it->daijin;
		sum_ys += it->yscost;
		sum_daiji += it->daijin;
		sum_xj += it->sj-it->zy;
		sum_subscription += it->subscription;
		i++;
	}

	
	m_GuiListCtrlReporyDay.InsertItem(i,_T("�ϼ�"));
	
	//Ӧ���˿�
	t.Format("%.2f",sum_ys);
	m_GuiListCtrlReporyDay.SetItemText(i,1,t);

	//�ϼ�
	t.Format("%.2f",sum_sscost);
	m_GuiListCtrlReporyDay.SetItemText(i,4,t);

	//����
	t.Format("%.2f",sum_subscription);
	m_GuiListCtrlReporyDay.SetItemText(i,5,t);

	//�ֽ�
	t.Format("%.2f",sum_xj);
	m_GuiListCtrlReporyDay.SetItemText(i,6,t);

	//����ϼ�
	t.Format("%.2f",sum_daiji);
	m_GuiListCtrlReporyDay.SetItemText(i,7,t);
		
	
	//��Ա��
	t.Format("%.2f",sum_mcard);
	m_GuiListCtrlReporyDay.SetItemText(i,8,t);

	//���ÿ�
	t.Format("%.2f",sum_xycard);
	m_GuiListCtrlReporyDay.SetItemText(i,9,t);

	//֧Ʊ
	t.Format("%.2f",sum_zp);
	m_GuiListCtrlReporyDay.SetItemText(i,10,t);
	
	
	

}

void CReportDayDialog::Init()
{
	int i=0;
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("�˵���"),LVCFMT_LEFT,110);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("Ӧ���˿�"),LVCFMT_RIGHT,100);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("�ۿ�"),LVCFMT_RIGHT,40);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("Ĩ��"),LVCFMT_RIGHT,40);
	
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("�ϼ�"),LVCFMT_RIGHT,90);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("����"),LVCFMT_RIGHT,80);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("�ֽ�"),LVCFMT_RIGHT,100);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("����ȯ"),LVCFMT_RIGHT,80);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("��Ա��"),LVCFMT_RIGHT,60);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("���ÿ�"),LVCFMT_RIGHT,60);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("֧Ʊ"),LVCFMT_RIGHT,60);
	m_GuiListCtrlReporyDay.InsertColumn(i++,_T("��ע"),LVCFMT_LEFT,150);
	
	
	ListView_SetExtendedListViewStyleEx(m_GuiListCtrlReporyDay.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

totalByDay();
}

BOOL CReportDayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonSearch.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonSearch.ShowText();
	m_GuiButtonPrint.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonPrint.ShowText();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//
	Init();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	m_jzfsCombo.AddString(_T("����"));
	m_jzfsCombo.AddString(_T("�ų��ҽ�"));
	m_jzfsCombo.AddString(_T("�ҽ�"));
	m_jzfsCombo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CReportDayDialog::OnBnClickedButtonPrint()
{
		
	//PrintViewByDay();
	
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));

	CMenu m_popupMenu;
	m_popupMenu.LoadMenu(IDR_PRINT_MENU);
	m_popupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

}

void CReportDayDialog::PrintViewByDay()
{
	/*PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListCtrlReporyDay.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListCtrlReporyDay.GetItemCount();

	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawByDay, PrnInfo);
	DlgPreView.DoModal();*/
	//UpdateData();
	CString jsfsMsg="";
	if(m_jsfsPos == 1)
		jsfsMsg ="���������˽�������";
	else if(m_jsfsPos==2)
		jsfsMsg="���˽�������";

	PrintReportDay print(m_accvec,m_exp.GetBuffer(),m_hotelname.GetBuffer(),jsfsMsg.GetBuffer());
	if ( print.CreateExcel() == true){
		print.LoadTemplate("\\tmpl\\ReportDay.xlt");
		print.SendExcel();
		
		print.PrintPreview();
	}

}

void CReportDayDialog::OnPrintPreview()
{
	CString jsfsMsg="";
	if(m_jsfsPos == 1)
		jsfsMsg ="���������˽�������";
	else if(m_jsfsPos==2)
		jsfsMsg="���˽�������";

	PrintReportDay print(m_accvec,m_exp.GetBuffer(),m_hotelname.GetBuffer(),jsfsMsg.GetBuffer());
	if ( print.CreateExcel() == true){
		print.LoadTemplate("\\tmpl\\ReportDay.xlt");
		print.SendExcel();
		
		print.PrintPreview();
		print.Close();
	}
}

void CReportDayDialog::OnPopupPrint()
{
	CString jsfsMsg="";
	if(m_jsfsPos == 1)
		jsfsMsg ="���������˽�������";
	else if(m_jsfsPos==2)
		jsfsMsg="���˽�������";

	PrintReportDay print(m_accvec,m_exp.GetBuffer(),m_hotelname.GetBuffer(),jsfsMsg.GetBuffer());
	if ( print.CreateExcel() == true){
		print.SetExcelVisible(false);
		print.LoadTemplate("\\tmpl\\ReportDay.xlt");
		print.SendExcel();
		
		print.Print();
		print.Close();
	}
}

//-----------------------------------------------------------------------------------------------

void CReportDayDialog::OnExactExcel()
{
	CString jsfsMsg="";
	if(m_jsfsPos == 1)
		jsfsMsg ="���������˽�������";
	else if(m_jsfsPos==2)
		jsfsMsg="���˽�������";

	PrintReportDay print(m_accvec,m_exp.GetBuffer(),m_hotelname.GetBuffer(),jsfsMsg.GetBuffer());
	if ( print.CreateExcel() == true){
		print.SetExcelVisible(false);
		print.LoadTemplate("\\tmpl\\ReportDay.xlt");
		print.SendExcel();
		TCHAR szFilters[]=_T("Excel File(*.xls)|*.xls");
		CFileDialog dlg(FALSE,_T("xls"),_T("��������"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilters);
		if ( dlg.DoModal() == IDOK)
		{
			print.SaveAs(dlg.GetPathName());
		}
		print.Close();
	}
}

void CReportDayDialog::OnNMDblclkListReportDay(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nPos = -1;
	if ( (nPos = m_GuiListCtrlReporyDay.GetSelectionMark()) != -1  )
	{
		string accid = m_accMap[nPos];
		CXFDetailsDlg dlg(this,accid.c_str());
		dlg.DoModal();
	}
}

float CReportDayDialog::myRound(float x)
{
	if((int)x*10+5 > (int)(x*10))
		return floor(x);
	else
		return ceil(x);
}