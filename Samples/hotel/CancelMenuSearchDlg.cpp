// CancelMenuSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CancelMenuSearchDlg.h"
#include "HAccDetailsCtrl.h"
#include ".\cancelmenusearchdlg.h"
#include "HAdminBdy.h"
#include "PreParent.h"
#include "HSetHotelPrintMsg.h"

// CCancelMenuSearchDlg �Ի���
CString CCancelMenuSearchDlg::m_hotelname;
CString CCancelMenuSearchDlg::m_exp;

IMPLEMENT_DYNAMIC(CCancelMenuSearchDlg, CDialog)
CCancelMenuSearchDlg::CCancelMenuSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCancelMenuSearchDlg::IDD, pParent)
	, m_dTime1(COleDateTime::GetCurrentTime())
	, m_dTime2(COleDateTime::GetCurrentTime())
{
}

CCancelMenuSearchDlg::~CCancelMenuSearchDlg()
{
}

void CCancelMenuSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dTime1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dTime2);
	DDX_Control(pDX, IDC_BUTTON_CSEARCH, m_GuiButtonSearch);
	DDX_Control(pDX, IDC_LIST_CANCELMENU, m_GuiListCtrl);
	DDX_Control(pDX, IDC_PRINT_BUTTON, m_GuiPrintBtn);
}


BEGIN_MESSAGE_MAP(CCancelMenuSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CSEARCH, OnBnClickedButtonCsearch)
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnBnClickedPrintButton)
END_MESSAGE_MAP()


// CCancelMenuSearchDlg ��Ϣ�������

void CCancelMenuSearchDlg::OnBnClickedButtonCsearch()
{
	// TODO: �����ڲ�ѯ�˲���ϸ

	Refresh();
	
}

void CCancelMenuSearchDlg::Refresh()
{
	UpdateData(true);
	hotelMIS::HAccDetailsCtrl accDetailsCtrl(m_con.get_con());
	CString d1,d2;
	d1.Format("%d-%d-%d 00:00:00",m_dTime1.GetYear(),m_dTime1.GetMonth(),m_dTime1.GetDay());
	d2.Format("%d-%d-%d 23:59:59",m_dTime2.GetYear(),m_dTime2.GetMonth(),m_dTime2.GetDay());
	
	m_exp.Format("ͳ������:%s - %s ",d1,d2);

	hotelMIS::HAccDetailsVec vec = accDetailsCtrl.GetCancelMenuByDate(d1.GetBuffer(),d2.GetBuffer());
	hotelMIS::HAccDetailsVec::iterator it;

	m_GuiListCtrl.DeleteAllItems();
	int i =0;
	int j =0;
	CString t;
	int num = 0;
	float sum = 0.0f;

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_GuiListCtrl.InsertItem(i,it->food_name.c_str());
		j = 1;
		t.Format("%.2f",it->food_price);
		m_GuiListCtrl.SetItemText(i,j++,t);
		
		if ( it->food_num > 0){
			num = it->food_num;
			t.Format("%d",-it->food_num);
		}else{
			t.Format("%d",it->food_num);
			num = -it->food_num;
		}
		
		m_GuiListCtrl.SetItemText(i,j++,t);

		m_GuiListCtrl.SetItemText(i,j++,it->food_unit.c_str());
		m_GuiListCtrl.SetItemText(i,j++,it->food_cancel_msg.c_str());
		i++;
		
        sum += num * it->food_price;	
	}
	m_GuiListCtrl.InsertItem(i,_T("�ϼ�:"));
	t.Format("%.2f",sum);
	m_GuiListCtrl.SetItemText(i,1,t);

}

BOOL CCancelMenuSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_GuiButtonSearch.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiButtonSearch.ShowText();
	m_GuiPrintBtn.ShowText();
	
	Init();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCancelMenuSearchDlg::Init()
{
	int i = 0;
	m_GuiListCtrl.InsertColumn(i++,_T("�˲˲���"),LVCFMT_LEFT,160);
	m_GuiListCtrl.InsertColumn(i++,_T("�۸�"),LVCFMT_RIGHT,70);
	m_GuiListCtrl.InsertColumn(i++,_T("����"),LVCFMT_CENTER,50);
	m_GuiListCtrl.InsertColumn(i++,_T("��λ"),LVCFMT_CENTER,50);
	m_GuiListCtrl.InsertColumn(i++,_T("�˲�ԭ��"),LVCFMT_LEFT,150);
    ListView_SetExtendedListViewStyleEx(m_GuiListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

}
void CCancelMenuSearchDlg::OnBnClickedPrintButton()
{
	PrintView();
}

void  CCancelMenuSearchDlg::PrintView()
{
PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListCtrl.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListCtrl.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(Draw, PrnInfo);
	DlgPreView.DoModal();
}
	
void  CCancelMenuSearchDlg::Draw(CDC &memDC, PRNINFO PrnInfo)
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
	wsprintf(szTitle,TEXT("%s �˲���ϸ����"),m_hotelname.GetBuffer());
    
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

		rt1.SetRect(nLeft, nTop, nLeft+70*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);
		
		
		memDC.DrawText("�˵���Ʒ", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�۸�", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��λ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�˲�ԭ��", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
        
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

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+70*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
			
			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
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
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
		

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

		rt1.SetRect(nLeft, nTop, nLeft+70*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);
		
		
		memDC.DrawText("�˲���Ʒ", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�۸�", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��λ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�˲�ԭ��", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
        
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

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+70*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
			
			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
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
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
		

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
