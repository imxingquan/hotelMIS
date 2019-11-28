// InOutRepSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "InOutRepSearchDlg.h"
#include ".\inoutrepsearchdlg.h"
#include "HInOutRepCtrl.h"
#include "HAdminBdy.h"
#include "PreParent.h"
#include "HSetHotelPrintMsg.h"

// CInOutRepSearchDlg �Ի���
 CString CInOutRepSearchDlg::m_exp;
 CString CInOutRepSearchDlg::m_hotelname;
 CString CInOutRepSearchDlg::m_inout;

IMPLEMENT_DYNAMIC(CInOutRepSearchDlg, CDialog)
CInOutRepSearchDlg::CInOutRepSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInOutRepSearchDlg::IDD, pParent)
	, m_d1(COleDateTime::GetCurrentTime())
	, m_d2(COleDateTime::GetCurrentTime())
	, m_inOutFlag(0)
{
}

CInOutRepSearchDlg::~CInOutRepSearchDlg()
{
}

void CInOutRepSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REP_STATUS, m_GuiRepStatusCombo);
	DDX_Control(pDX, IDC_SEARCH_BUTTON, m_CGuiSearchBtn);
	DDX_Control(pDX, IDC_PRINT_BUTTON, m_GuiPrintBtn);
	DDX_Control(pDX, IDCANCEL, m_GuiExitBtn);
	DDX_Control(pDX, IDC_REP_LIST, m_GuiRepList);
	DDX_Control(pDX, IDC_REP_DETAILS_LIST, m_GuiRepDetailsList);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_d1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_d2);
	DDX_CBIndex(pDX, IDC_REP_STATUS, m_inOutFlag);
}


BEGIN_MESSAGE_MAP(CInOutRepSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, OnBnClickedSearchButton)
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnBnClickedPrintButton)
	ON_NOTIFY(NM_CLICK, IDC_REP_LIST, OnNMClickRepList)
	ON_NOTIFY(NM_DBLCLK, IDC_REP_LIST, OnNMDblclkRepList)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REP_LIST, OnLvnItemchangedRepList)
END_MESSAGE_MAP()


// CInOutRepSearchDlg ��Ϣ�������

void CInOutRepSearchDlg::OnBnClickedSearchButton()
{
	RefreshRep();
}

void CInOutRepSearchDlg::OnBnClickedPrintButton()
{
	PrintView();
}

void CInOutRepSearchDlg::OnNMClickRepList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int nPos = m_GuiRepList.GetSelectionMark();
	if ( nPos != -1)
	{
		string zdh = m_zdmap[nPos].first;
		RefreshDetails(zdh);
		if ( zdh.substr(0,2) == "CK"){
			m_exp.Format("�˵���:%s  ��������:%s",zdh.c_str(),m_zdmap[nPos].second.c_str());
			m_inout = "���ⵥ";
		}
		else if ( zdh.substr(0,2) == "RK"){
			m_exp.Format("�˵���:%s  �������:%s",zdh.c_str(),m_zdmap[nPos].second.c_str());
			m_inout = "��ⵥ";
		}
	}
}

void CInOutRepSearchDlg::OnNMDblclkRepList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int nPos = m_GuiRepList.GetSelectionMark();
	if ( nPos != -1)
	{
		string zdh = m_zdmap[nPos].first;
		RefreshDetails(zdh);
		if ( zdh.substr(0,2) == "CK"){
			m_exp.Format("�˵���:%s  ��������:%s",zdh.c_str(),m_zdmap[nPos].second.c_str());
			m_inout = "���ⵥ";
		}
		else if ( zdh.substr(0,2) == "RK"){
			m_exp.Format("�˵���:%s  �������:%s",zdh.c_str(),m_zdmap[nPos].second.c_str());
			m_inout = "��ⵥ";
		}
	}
}

//---------------------------------------------------------------------------------------------------
void  CInOutRepSearchDlg::InitIdle()
{
	//��ʼ�������б����
	 
	int i = 0;
	m_GuiRepList.InsertColumn(i++,_T("�˵���"),LVCFMT_LEFT,120);
	m_GuiRepList.InsertColumn(i++,_T("����"),LVCFMT_LEFT,150);
    ListView_SetExtendedListViewStyleEx(m_GuiRepList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	
	i=0;
	m_GuiRepDetailsList.InsertColumn(i,_T("���"),LVCFMT_LEFT,40);
	m_GuiRepDetailsList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,160);
	m_GuiRepDetailsList.InsertColumn(++i,_T("��λ"),LVCFMT_LEFT,40);
	m_GuiRepDetailsList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,40);
	m_GuiRepDetailsList.InsertColumn(++i,_T("����"),LVCFMT_RIGHT,70);
	m_GuiRepDetailsList.InsertColumn(++i,_T("���"),LVCFMT_RIGHT,60);

	ListView_SetExtendedListViewStyleEx(m_GuiRepDetailsList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);


}

//----------------------------------------------------------------------------------------------------
void  CInOutRepSearchDlg::RefreshRep()
{
	UpdateData();
	CString d1,d2;
	d1 = m_d1.Format("%Y-%m-%d");
	d2 = m_d2.Format("%Y-%m-%d");

	hotelMIS::HInOutRepCtrl inOutRepCtrl(m_con.get_con());
	hotelMIS::HInOutRepVec vec;
	if ( m_inOutFlag == 0 ) //ȫ�� 
	{
		vec = inOutRepCtrl.search(d1.GetBuffer(),d2.GetBuffer());
	}
	else if ( m_inOutFlag == 1) // ����
	{
		vec = inOutRepCtrl.search(d1.GetBuffer(),d2.GetBuffer(),hotelMIS::HInOutRep::OUT_REP);
	}
	else if ( m_inOutFlag == 2) //���
	{
		vec = inOutRepCtrl.search(d1.GetBuffer(),d2.GetBuffer(),hotelMIS::HInOutRep::IN_REP);
	}
	

	int i =0;
	int j =0;
	m_zdmap.clear();
	m_GuiRepList.DeleteAllItems();
	hotelMIS::HInOutRepVec::iterator it ;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		m_zdmap.insert(make_pair(i,make_pair(it->inout_dh,it->opdate)));
		m_GuiRepList.InsertItem(i,it->inout_dh.c_str());
		m_GuiRepList.SetItemText(i,j++,it->opdate.c_str());
		
		i++;

	}	

}

//----------------------------------------------------------------------------------------------------
void  CInOutRepSearchDlg::RefreshDetails(string inout_dh)
{
	m_GuiRepDetailsList.DeleteAllItems();

	int i = 0,j = 0;
	hotelMIS::HInOutRepCtrl inOutRepCtrl(m_con.get_con());
	hotelMIS::HInOutRepVec vec = inOutRepCtrl.search(inout_dh);

	hotelMIS::HInOutRepVec::iterator it ;
	CString t;
	float fSum = 0.0f;

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		t.Format("%d",it->food_id);
		m_GuiRepDetailsList.InsertItem(i,t);
		m_GuiRepDetailsList.SetItemText(i,j++,it->food_name.c_str());
		m_GuiRepDetailsList.SetItemText(i,j++,it->food_unit.c_str());

		t.Format("%.2f",it->food_num);
		m_GuiRepDetailsList.SetItemText(i,j++,t);

		t.Format("%.2f",it->food_price);
		m_GuiRepDetailsList.SetItemText(i,j++,t);
		
		t.Format("%.2f",it->food_num * it->food_price);
		m_GuiRepDetailsList.SetItemText(i,j++,t);
		fSum += it->food_price * it->food_num;
		i++;
	}
	//�ϼ�
	m_GuiRepDetailsList.InsertItem(i,_T("�ϼ�:"));
	t.Format("%.2f",fSum);m_GuiRepDetailsList.SetItemText(i,5,t);
	
}

//----------------------------------------------------------------------------------------------------
BOOL CInOutRepSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_GuiRepStatusCombo.AddString(_T("ȫ���˵�"));
	m_GuiRepStatusCombo.AddString(_T("�����˵�")); //0
	m_GuiRepStatusCombo.AddString(_T("����˵�")); //1

	m_GuiRepStatusCombo.SetCurSel(0);

	m_CGuiSearchBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiExitBtn.SetStyleBorder(CGuiButton::STYLEXP);

	m_CGuiSearchBtn.ShowText();
	m_GuiPrintBtn.ShowText();
	m_GuiExitBtn.ShowText();

	InitIdle();

	RefreshRep();
	
	m_font.CreatePointFont(150,_T("����"));

	
	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CInOutRepSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if ( pWnd->GetDlgCtrlID() == IDC_STATIC_T)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CInOutRepSearchDlg::OnLvnItemchangedRepList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;

	int nPos = m_GuiRepList.GetSelectionMark();
	if ( nPos != -1)
	{
		RefreshDetails(m_zdmap[nPos].first);
	}
}

void CInOutRepSearchDlg::PrintView()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiRepDetailsList.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiRepDetailsList.GetItemCount();

	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawDC, PrnInfo);
	DlgPreView.DoModal();
}

void CInOutRepSearchDlg::DrawDC(CDC &memDC, PRNINFO PrnInfo)  //��ӡ�ص�
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
	wsprintf(szTitle,TEXT("%s %s"),m_hotelname.GetBuffer(),m_inout.GetBuffer());

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

					rt1.SetRect(nLeft, nTop, nLeft+20*xPix, nTop+fAdd);					
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
					rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
					rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
					/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
					rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
					//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

					memDC.DrawText("���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("��λ", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("����", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("����", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("���", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					/*memDC.DrawText("����ȯ", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("ʵ���˿�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
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
					/*memDC.MoveTo(rt7.right, rt1.top);
					memDC.LineTo(rt7.right, rt1.bottom);*/
					memDC.MoveTo(rc.left, rt1.bottom);
					memDC.LineTo(rc.right, rt1.bottom);

					TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
					rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
					rt1.SetRect(nLeft, nTop+fAdd, nLeft+20*xPix, nTop+2*fAdd);					
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
					rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);	
					rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
					/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
					rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
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
						/*ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
						ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);*/

						memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						/*memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/

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
						/*memDC.MoveTo(rt7.right, rt1.top);
						memDC.LineTo(rt7.right, rt1.bottom);*/
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
						/*rt7.top = rt1.top;
						rt7.bottom = rt1.bottom;
						rt8.top = rt1.top;
						rt8.bottom = rt1.bottom;*/

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

		rt1.SetRect(nLeft, nTop, nLeft+20*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��λ", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		/*memDC.DrawText("����ȯ", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("ʵ���˿�", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
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
		/*memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);*/
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+20*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 65*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);	
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
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
			/*ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
			ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);*/

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			/*memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/

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
			/*memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);*/
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
			/*rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;*/

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