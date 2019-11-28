// ReportYearDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "ReportYearDialog.h"
#include ".\reportyeardialog.h"
#include "HAdminBdy.h"

#include "PreParent.h"		//��ӡԤ��������
#include "HSetHotelPrintMsg.h"


// CReportYearDialog �Ի���
CString CReportYearDialog::m_hotelname;
CString CReportYearDialog::m_exp;

IMPLEMENT_DYNAMIC(CReportYearDialog, CDialog)
CReportYearDialog::CReportYearDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CReportYearDialog::IDD, pParent)
	, m_year(_T(""))
	,m_byColNum(0)
	, m_byCook(FALSE)
	, m_bPayStatus(FALSE)
{
}

CReportYearDialog::~CReportYearDialog()
{
}

void CReportYearDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXT, m_GuiGroupBoxT);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);
	DDX_Control(pDX, IDC_COMBO_YEAR, m_GuiComboYear);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiButtonPrint);
	DDX_Control(pDX, IDOK, m_GuiButtonOk);
	DDX_CBString(pDX, IDC_COMBO_YEAR, m_year);
	DDX_Control(pDX, IDC_COOKCHECK, m_GuiCookCheck);
	DDX_Check(pDX, IDC_COOKCHECK, m_byCook);
	DDX_Control(pDX, IDC_LIST_REPORT_YEAR, m_GuiListReportYear);
	DDX_Control(pDX, IDC_TOTALYEARBUTTON, m_GuiTotalYearBtn);
	DDX_Check(pDX, IDC_CHECK_PAYSTATUS, m_bPayStatus);
}


BEGIN_MESSAGE_MAP(CReportYearDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_TOTALYEARBUTTON, OnTotalByYear)
	ON_COMMAND(ID_DEL_ACCOUNT, OnDelAccount)
	ON_COMMAND(ID_DELALL_ACCOUNT, OnDelallAccount)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REPORT_YEAR, OnNMRclickListReportYear)
END_MESSAGE_MAP()


// CReportYearDialog ��Ϣ�������

void CReportYearDialog::OnBnClickedButtonPrint()
{
	// TODO: ��ӡ
	UpdateData(true);
	if ( m_byCook ){
		PrintViewByCook();
	}else if ( m_bPayStatus){
		PrintViewByPayStatus();
	}
	else{
		PrintViewByYear();
	}
}

void CReportYearDialog::OnTotalByYear()
{
	// TODO: 
	UpdateData();
	if ( m_byCook ){
		totalByYearCook();
	}else if ( m_bPayStatus){
		totalByPayStatus();
	}else{
		totalByYear();
	}
}

void CReportYearDialog::totalByYear()
{
		//��ʼListCtrl�ؼ�
	int i = 0;
	for ( int k =m_byColNum ; k >=0 ; k--)
		m_GuiListReportYear.DeleteColumn(k);

	m_GuiListReportYear.InsertColumn(i++,_T("�˵���"),LVCFMT_LEFT,110);
	m_GuiListReportYear.InsertColumn(i++,_T("Ӧ���˿�"),LVCFMT_RIGHT,100);
	m_GuiListReportYear.InsertColumn(i++,_T("���㷽ʽ"),LVCFMT_CENTER,80);
	m_GuiListReportYear.InsertColumn(i++,_T("����"),LVCFMT_RIGHT,80);
	m_GuiListReportYear.InsertColumn(i++,_T("�ۿ�"),LVCFMT_RIGHT,80);
	m_GuiListReportYear.InsertColumn(i++,_T("Ĩ��"),LVCFMT_RIGHT,80);
	m_GuiListReportYear.InsertColumn(i++,_T("����ȯ"),LVCFMT_RIGHT,80);
	m_GuiListReportYear.InsertColumn(i++,_T("ʵ���˿�"),LVCFMT_RIGHT,100);
	//m_GuiListReportYear.InsertColumn(i++,_T("��"),LVCFMT_RIGHT,100);
	m_byColNum = i-1 ;

	    ListView_SetExtendedListViewStyleEx(m_GuiListReportYear.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);


	Refresh();
}

void CReportYearDialog::Refresh()
{
	UpdateData(true);
	
	m_exp.Format("ͳ������:%s",m_year);

	hotelMIS::HAccountVec vec = m_reportBdy.totalByYear(m_year.GetBuffer());
	hotelMIS::HAccountVec::iterator it ;

	int j;
	float sscost = 0.0f,subscription=0.0f;
	float sum_mcard = 0.0f,sum_xj = 0.0f,sum_xycard=0.0f,sum_zp=0.0f;

	CString t;
	int i = 0;
	m_GuiListReportYear.DeleteAllItems();
	m_map.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_map.insert(make_pair(i,it->account_id.c_str()));
		j = 1;
		m_GuiListReportYear.InsertItem(i,it->account_id.c_str());
		t.Format("%.2f",it->yscost);m_GuiListReportYear.SetItemText(i,j++,t);
		if ( it->paystatus == hotelMIS::HAccount::JSFS::mcard )
		{
			m_GuiListReportYear.SetItemText(i,j++,_T("��Ա��"));
			sum_mcard += it->sscost;
		}
		else if ( it->paystatus == hotelMIS::HAccount::JSFS::xj )
		{
			m_GuiListReportYear.SetItemText(i,j++,_T("�ֽ�"));
			sum_xj += it->sscost;
		}
		else if ( it->paystatus == hotelMIS::HAccount::JSFS::xycard)
		{
			m_GuiListReportYear.SetItemText(i,j++,_T("���ÿ�"));
			sum_xycard += it->sscost;

		}
		else if ( it->paystatus == hotelMIS::HAccount::JSFS::zp)
		{
			m_GuiListReportYear.SetItemText(i,j++,_T("֧Ʊ"));
			sum_zp += it->sscost;
		}else 
		{
			m_GuiListReportYear.SetItemText(i,j++,_T("�ֽ�"));
			sum_xj += it->sscost;
		}
		//t.Format("%.2f",it->yscost);m_GuiListReportYear.SetItemText(i,j++,t);
		t.Format("%.2f",it->subscription);m_GuiListReportYear.SetItemText(i,j++,t);
		t.Format("%.2f",it->zhekou);m_GuiListReportYear.SetItemText(i,j++,t);
		t.Format("%.2f",it->erase_zero);m_GuiListReportYear.SetItemText(i,j++,t);
		t.Format("%.2f",it->daijin);m_GuiListReportYear.SetItemText(i,j++,t);
		t.Format("%.2f",it->sscost);m_GuiListReportYear.SetItemText(i,j,t);
		sscost += it->sscost;
		subscription += it->subscription;
		i++;
	}
	m_GuiListReportYear.InsertItem(i,_T(""));
	m_GuiListReportYear.SetItemText(i,1,_T("���㷽ʽͳ��"));

	i++;
	//����ϼ�:
	m_GuiListReportYear.InsertItem(i,_T("��Ա���ϼ�:"));
	t.Format("%.2f",sum_mcard);
	m_GuiListReportYear.SetItemText(i,1,t);

	i++;
	m_GuiListReportYear.InsertItem(i,_T("�ֽ�ϼ�:"));
	t.Format("%.2f",sum_xj);
	m_GuiListReportYear.SetItemText(i,1,t);

	i++;
	m_GuiListReportYear.InsertItem(i,_T("���ÿ��ϼ�:"));
	t.Format("%.2f",sum_xycard);
	m_GuiListReportYear.SetItemText(i,1,t);

	i++;
	m_GuiListReportYear.InsertItem(i,_T("֧Ʊ�ϼ�:"));
	t.Format("%.2f",sum_zp);
	m_GuiListReportYear.SetItemText(i,1,t);

	i++;
	m_GuiListReportYear.InsertItem(i,_T("�ܺϼ�:"));
	t.Format("%.2f",sum_mcard+sum_xj+sum_xycard+sum_zp);
	m_GuiListReportYear.SetItemText(i,1,t);
}

void CReportYearDialog::totalByYearCook()
{
	//��ʼListCtrl�ؼ�
	int i = 0;
	for ( int k =m_byColNum ; k >=0 ; k--)
			m_GuiListReportYear.DeleteColumn(k);
	m_map.clear();
	m_GuiListReportYear.InsertColumn(i++,_T("����"),LVCFMT_LEFT,160);
	m_GuiListReportYear.InsertColumn(i++,_T("������"),LVCFMT_LEFT,80);
	m_GuiListReportYear.InsertColumn(i++,_T("�ܼ۸�"),LVCFMT_RIGHT,80);
	m_GuiListReportYear.InsertColumn(i++,_T("��ʦ"),LVCFMT_LEFT,80);
	m_byColNum = i-1 ;
	    ListView_SetExtendedListViewStyleEx(m_GuiListReportYear.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	UpdateData(true);
	int j;
	i  = 0;
	CString t;
	
	m_exp = m_year;

	hotelMIS::HTotalByCookVec vec = m_reportBdy.totalByCookYear(m_year.GetBuffer());
	hotelMIS::HTotalByCookVec::iterator it;
	m_GuiListReportYear.DeleteAllItems();
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		m_GuiListReportYear.InsertItem(i,it->food_name.c_str());
		t.Format("%d",it->total_food_num);m_GuiListReportYear.SetItemText(i,j++,t);
		t.Format("%.2f",it->total_food_price);m_GuiListReportYear.SetItemText(i,j++,t);
		m_GuiListReportYear.SetItemText(i,j++,it->ck_name.c_str());
		i++;
	}
	CTime t1=CTime::GetCurrentTime();
	m_GuiListReportYear.InsertItem(i,_T("ͳ������:"));
	m_GuiListReportYear.SetItemText(i,1,t1.Format("%Y/%m/%d"));
	m_GuiListReportYear.SetItemText(i,2,t1.Format("%H:%M:%S"));
}

BOOL CReportYearDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiButtonPrint.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonPrint.ShowText();
	m_GuiButtonOk.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonOk.ShowText();
	m_GuiTotalYearBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiTotalYearBtn.ShowText();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString t;
	for ( int i = 2005; i< 2022; i ++ )
	{
		t.Format("%d",i);
		m_GuiComboYear.AddString(t);
	}
	CTime t1=CTime::GetCurrentTime();
	m_GuiComboYear.SetCurSel(t1.GetYear()-2005);

	totalByYear();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CReportYearDialog::OnDelAccount()
{
	// TODO: ɾ��ѡ�����˺�
	if ( m_nIndex != -1 )
	{
		int r = MessageBox(_T("ȷ��Ҫɾ��?"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_YESNO);
		if ( r == IDYES){
			//ɾ���˵���
			m_reportBdy.DeleteByAccountId(m_map[m_nIndex]);
			totalByYear();
		}
	}
}

void CReportYearDialog::OnDelallAccount()
{
	// TODO: ȫ�����
	int r = MessageBox(_T("ȷ��Ҫɾ��?"),_T("ϵͳ��ʾ"),MB_ICONINFORMATION|MB_YESNO);
	if ( r == IDYES){
		//ɾ�������˵���
		m_reportBdy.DeleteAll();
		totalByYear();
	}
}

void CReportYearDialog::OnNMRclickListReportYear(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( hotelMIS::HAdminBdy::_log_name == "idcwest"){
		DWORD dwPos = ::GetMessagePos();
		CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
		m_GuiListReportYear.ScreenToClient(&point);
		m_nIndex = m_GuiListReportYear.HitTest(point);
		m_GuiListReportYear.ClientToScreen(&point);
		CMenu m_popupMenu;
		m_popupMenu.LoadMenu(IDR_DEL_ACCOUNT_MENU);
		m_popupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
		TRACE("�һ�����%d \n",m_nIndex);
	}
	*pResult = 0;
}

void CReportYearDialog::PrintViewByYear()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListReportYear.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListReportYear.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawByYear, PrnInfo);
	DlgPreView.DoModal();
}

void CReportYearDialog::PrintViewByCook()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListReportYear.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListReportYear.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawByCook, PrnInfo);
	DlgPreView.DoModal();
}

void CReportYearDialog::DrawByYear(CDC &memDC, PRNINFO PrnInfo)
{
if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//��ǰҳ
	BOOL IsPrint = PrnInfo.IsPrint;		//�Ƿ��ӡ
	int nMaxPage = PrnInfo.nCountPage;	//���ҳ��
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");
	csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);

	
	TCHAR szTitle[255];
	wsprintf(szTitle,TEXT("%s %s��Ӫ�걨��"),m_hotelname.GetBuffer(),m_exp);
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, PFont,*oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//����������
	PFont.CreateFont(-MulDiv(11,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//ϸ������
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//�ֱ�
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

 	int xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	int yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

	DOUBLE xPix = (DOUBLE)xP*10/254;	//ÿ mm ��ȵ�����
	DOUBLE yPix = (DOUBLE)yP*10/254;	//ÿ mm �߶ȵ�����
	DOUBLE fAdd = 7*yPix;		//ÿ�������
	DOUBLE nTop = 32*yPix;		//��һҳ������
	int	  iStart = 0;			//�ӵڼ��п�ʼ��ȡ
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 15*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-15);	//������



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//������ӡ����
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//��ʼ�ĵ���ӡ
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "���ӵ���ӡ������!", "����", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 30*yPix;		//��һҳ������
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//��ʼҳ
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("��ӡʧ��!"), "����", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//��ӡ
	//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,nRight,yPix*40);
			memDC.DrawText(m_exp,&rc,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			CString t;
			t.Format("�Ʊ���:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
 		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 18*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("�˵���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("Ӧ���˿�", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���㷽ʽ", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ۿ�", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("Ĩ��", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����ȯ", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("ʵ���˿�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//memDC.DrawText("�ϼ�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		memDC.MoveTo(rt4.right, rt1.top);
		memDC.LineTo(rt4.right, rt1.bottom);
		memDC.MoveTo(rt5.right, rt1.top);
		memDC.LineTo(rt5.right, rt1.bottom);
		memDC.MoveTo(rt6.right, rt1.top);
    	memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 18*xPix, rt1.bottom);	
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
			ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
			ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
			ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;

			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β
					memDC.MoveTo(rc.left, nTop);
					memDC.LineTo(rc.left, rc.top);
					memDC.MoveTo(rc.right, nTop);
					memDC.LineTo(rc.right, rc.top);
					memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
					memDC.EndPage();
					memDC.SelectObject(oldfont);
				}
			}
			memDC.EndDoc();
		}
	}
	else
	{
		//��ӡԤ��
		
		//�߿���
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	
		
		//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,nRight,yPix*40);
			memDC.DrawText(m_exp,&rc,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			CString t;
			t.Format("�Ʊ���:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
 		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 18*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("�˵���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("Ӧ���˿�", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���㷽ʽ", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ۿ�", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("Ĩ��", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����ȯ", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("ʵ���˿�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//memDC.DrawText("�ϼ�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		memDC.MoveTo(rt4.right, rt1.top);
		memDC.LineTo(rt4.right, rt1.bottom);
		memDC.MoveTo(rt5.right, rt1.top);
		memDC.LineTo(rt5.right, rt1.bottom);
		memDC.MoveTo(rt6.right, rt1.top);
    	memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 18*xPix, rt1.bottom);	
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
			ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
			ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
			ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;

			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β

		memDC.MoveTo(rc.left, nTop);
		memDC.LineTo(rc.left, rc.top);
		memDC.MoveTo(rc.right, nTop);
		memDC.LineTo(rc.right, rc.top);
		memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);

		memDC.SelectObject(oldfont);
		memDC.SelectObject(hPenOld);
	}
	TitleFont.DeleteObject();
	DetailFont.DeleteObject();
	cPen.DeleteObject();
}

//
// ��ӡ��ʦ������
//
void CReportYearDialog::DrawByCook(CDC &memDC, PRNINFO PrnInfo)
{
if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//��ǰҳ
	BOOL IsPrint = PrnInfo.IsPrint;		//�Ƿ��ӡ
	int nMaxPage = PrnInfo.nCountPage;	//���ҳ��
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");
	csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);

	
	TCHAR szTitle[255];
	wsprintf(szTitle,TEXT("%s %s��ʦ�깤����ͳ�Ʊ���"),m_hotelname.GetBuffer(),m_exp);
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, *oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//ϸ������
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//�ֱ�
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

 	int xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	int yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

	DOUBLE xPix = (DOUBLE)xP*10/254;	//ÿ mm ��ȵ�����
	DOUBLE yPix = (DOUBLE)yP*10/254;	//ÿ mm �߶ȵ�����
	DOUBLE fAdd = 7*yPix;		//ÿ�������
	DOUBLE nTop = 25*yPix;		//��һҳ������
	int	  iStart = 0;			//�ӵڼ��п�ʼ��ȡ
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 15*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-15);	//������



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//������ӡ����
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//��ʼ�ĵ���ӡ
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "���ӵ���ӡ������!", "����", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 25*yPix;		//��һҳ������
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//��ʼҳ
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("��ӡʧ��!"), "����", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//��ӡ
			//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+60*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rc.right, rt1.bottom);	
		

		memDC.DrawText("������", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��������", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ܼ۸�", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ʦ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		        
		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+60*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rc.right, rt1.bottom);	
		

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			
			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			
			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β
					memDC.MoveTo(rc.left, nTop);
					memDC.LineTo(rc.left, rc.top);
					memDC.MoveTo(rc.right, nTop);
					memDC.LineTo(rc.right, rc.top);
					memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
					memDC.EndPage();
					memDC.SelectObject(oldfont);
				}
			}
			memDC.EndDoc();
		}
	}
	else
	{
		//��ӡԤ��
		
		//�߿���
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	
		
		//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+60*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rc.right, rt1.bottom);	
		

		memDC.DrawText("������", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��������", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ܼ۸�", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ʦ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		        
		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+60*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rc.right, rt1.bottom);	
		

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			
			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			
			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β

		memDC.MoveTo(rc.left, nTop);
		memDC.LineTo(rc.left, rc.top);
		memDC.MoveTo(rc.right, nTop);
		memDC.LineTo(rc.right, rc.top);
		memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);

		memDC.SelectObject(oldfont);
		memDC.SelectObject(hPenOld);
	}
	TitleFont.DeleteObject();
	DetailFont.DeleteObject();
	cPen.DeleteObject();
}

//-------------------------------------------------------------------------------------------------------------------------------
void CReportYearDialog::totalByPayStatus()
{
	int i = 0;
	for ( int k = m_byColNum; k>= 0; k--)
		m_GuiListReportYear.DeleteColumn(k);

	m_GuiListReportYear.InsertColumn(i++,_T("���㷽ʽ"),LVCFMT_LEFT,110);
	m_GuiListReportYear.InsertColumn(i++,_T("���"),LVCFMT_RIGHT,250);

	m_byColNum = i-1 ;
	ListView_SetExtendedListViewStyleEx(m_GuiListReportYear.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	UpdateData(true);

	CString t;
	
	//ͳ��������ӡʹ��
	m_exp.Format("ͳ������: %s",m_year);

	hotelMIS::HTotalAccountVec vec = m_reportBdy.totalByPayStatus(m_year.GetBuffer());
	hotelMIS::HTotalAccountVec::iterator it;
	i = 0;
	m_GuiListReportYear.DeleteAllItems();
	float s = 0.0f;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		if ( it->pay_status == hotelMIS::HAccount::JSFS::mcard )
			m_GuiListReportYear.InsertItem(i,_T("��Ա������ϼ�"));
		else if ( it->pay_status == hotelMIS::HAccount::JSFS::xj)
			m_GuiListReportYear.InsertItem(i,_T("�ֽ����ϼ�"));
		else if ( it->pay_status == hotelMIS::HAccount::JSFS::xycard)
			m_GuiListReportYear.InsertItem(i,_T("���ÿ�����ϼ�"));
		else if ( it->pay_status == hotelMIS::HAccount::JSFS::zp)
			m_GuiListReportYear.InsertItem(i,_T("֧Ʊ����ϼ�"));
		s += it->sum_sscost;
		t.Format("%.2f",it->sum_sscost);
		m_GuiListReportYear.SetItemText(i,1,t);
		i++;
	}

	m_GuiListReportYear.InsertItem(i,_T("�ܺϼ�:"));
	t.Format("%.2f",s);
	m_GuiListReportYear.SetItemText(i,1,t);

	i++;
	m_GuiListReportYear.InsertItem(i,_T(""));
	i++;
	m_GuiListReportYear.InsertItem(i,_T("��ӡ����:"));
	CTime dt = CTime::GetCurrentTime();
	m_GuiListReportYear.SetItemText(i,1,dt.Format("%Y-%m-%d %H:%M:%S"));
}
void CReportYearDialog::PrintViewByPayStatus()
{
PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListReportYear.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListReportYear.GetItemCount();

	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawByPayStatus, PrnInfo);
	DlgPreView.DoModal();
}

void CReportYearDialog::DrawByPayStatus(CDC &memDC, PRNINFO PrnInfo)
{
	if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//��ǰҳ
	BOOL IsPrint = PrnInfo.IsPrint;		//�Ƿ��ӡ
	int nMaxPage = PrnInfo.nCountPage;	//���ҳ��
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	/*CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("��ӡ����:%Y-%m-%d %H:%M:%S");*/
	csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);


	TCHAR szTitle[255];
	wsprintf(szTitle,TEXT("%s ��Ӫ����ͳ�Ʊ���"),m_hotelname.GetBuffer());

	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, PFont,*oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//����������
	PFont.CreateFont(-MulDiv(11,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//ϸ������
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//�ֱ�
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	DOUBLE xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	DOUBLE yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

	DOUBLE xPix = xP*10/254;	//ÿ mm ��ȵ�����
	DOUBLE yPix = yP*10/254;	//ÿ mm �߶ȵ�����
	DOUBLE fAdd = 7*yPix;		//ÿ�������
	DOUBLE nTop = 32*yPix;		//��һҳ������
	int	  iStart = 0;			//�ӵڼ��п�ʼ��ȡ
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 15*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-15);	//������



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//������ӡ����
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//��ʼ�ĵ���ӡ
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "���ӵ���ӡ������!", "����", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 32*yPix;		//��һҳ������
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);
				CTime time;
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("�Ʊ�����:%Y-%m-%d");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//��ʼҳ
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("��ӡʧ��!"), "����", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//��ӡ
					//-------------------------------------------------------------------------------------------
				//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,nRight,yPix*40);
			memDC.DrawText(m_exp,&rc,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			CString t;
			t.Format("�Ʊ���:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+60*xPix, nTop+fAdd);	
		rt2.SetRect(rt1.right, rt1.top, rc.right , rt1.bottom);
		//rt2.SetRect(rt1.right, rt1.top, rt1.right + 90*xPix, rt1.bottom);	
		//rt3.SetRect(rt2.right,rt1.top,rc.right,rt1.bottom);

		memDC.DrawText("���㷽ʽ", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[50]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+60*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rc.right,rt1.bottom);		


		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 50);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);

			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);

			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;

			if((i+iStart+1)>=nCountItem)
				break;
		}
		//��β
					memDC.MoveTo(rc.left, nTop);
					memDC.LineTo(rc.left, rc.top);
					memDC.MoveTo(rc.right, nTop);
					memDC.LineTo(rc.right, rc.top);
					memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
					memDC.EndPage();
					memDC.SelectObject(oldfont);
				}
			}
			memDC.EndDoc();
		}
	}
	else
	{
		//��ӡԤ��

		//�߿���
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	

		//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			memDC.SelectObject(&PFont);
			rc.SetRect(nLeft,yPix*15,nRight,yPix*40);
			memDC.DrawText(m_exp,&rc,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			CString t;
			t.Format("�Ʊ���:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+60*xPix, nTop+fAdd);	
		rt2.SetRect(rt1.right, rt1.top, rc.right , rt1.bottom);
		//rt2.SetRect(rt1.right, rt1.top, rt1.right + 90*xPix, rt1.bottom);	
		//rt3.SetRect(rt2.right,rt1.top,rc.right,rt1.bottom);

		memDC.DrawText("���㷽ʽ", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[50]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+60*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rc.right,rt1.bottom);	


		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 50);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);

			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);

			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;

			if((i+iStart+1)>=nCountItem)
				break;
		}
		//��β

		memDC.MoveTo(rc.left, nTop);
		memDC.LineTo(rc.left, rc.top);
		memDC.MoveTo(rc.right, nTop);
		memDC.LineTo(rc.right, rc.top);
		memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
		memDC.EndPage();
		memDC.SelectObject(oldfont);

		
		memDC.SelectObject(hPenOld);
	}
	TitleFont.DeleteObject();
	DetailFont.DeleteObject();
	cPen.DeleteObject();
}