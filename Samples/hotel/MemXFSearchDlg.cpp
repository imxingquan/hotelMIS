//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  MemXFSearchDlg.cpp
// 
// Desc: ��Ա������ϸ��ѯ
//
// Author:  ��Ȫ
//
// Modified: 2006�� 06 �� 21 ��
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "MemXFSearchDlg.h"
#include ".\memxfsearchdlg.h"
#include "HAccDetailsCtrl.h"
#include "HAccountCtrl.h"
#include "HMemberCtrl.h"
#include "HAdminBdy.h"
#include "PreParent.h"
#include "HSetHotelPrintMsg.h"

// CMemXFSearchDlg �Ի���
CString CMemXFSearchDlg::m_exp;
CString CMemXFSearchDlg::m_hotelname;

IMPLEMENT_DYNAMIC(CMemXFSearchDlg, CDialog)
CMemXFSearchDlg::CMemXFSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemXFSearchDlg::IDD, pParent)
	, m_bh(_T(""))
	, m_name(_T(""))
	, m_d1(COleDateTime::GetCurrentTime())
	, m_d2(COleDateTime::GetCurrentTime())
{
}

CMemXFSearchDlg::~CMemXFSearchDlg()
{
}

void CMemXFSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BH, m_bh);
	DDX_Text(pDX, IDC_EDIT_XM, m_name);
	DDX_Control(pDX, IDC_LIST_ZD, m_GuiListZd);
	DDX_Control(pDX, IDC_LIST_ZDMX, m_GuiListZdMx);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_d1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_d2);
	DDX_Control(pDX, IDC_COMBO_BH, m_GuiComboBh);
}


BEGIN_MESSAGE_MAP(CMemXFSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ZD, OnNMClickListZd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ZD, OnLvnItemchangedListZd)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CMemXFSearchDlg ��Ϣ�������

void CMemXFSearchDlg::OnBnClickedButtonSearch()
{
	//��ѯ
	RefreshZdList();
}

void CMemXFSearchDlg::InitIdle()
{//��ʼ��list
	int i = 0;
	m_GuiListZd.InsertColumn(i,_T("�˵���"),LVCFMT_LEFT,110);
	m_GuiListZd.InsertColumn(++i,_T("��������"),LVCFMT_LEFT,120);
	m_GuiListZd.InsertColumn(++i,_T("���"),LVCFMT_RIGHT,100);
	ListView_SetExtendedListViewStyleEx(m_GuiListZd.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	i = 0;
	m_GuiListZdMx.InsertColumn(i,_T("���"),LVCFMT_LEFT,50);
	m_GuiListZdMx.InsertColumn(++i,_T("����"),LVCFMT_LEFT,150);
	m_GuiListZdMx.InsertColumn(++i,_T("�۸�"),LVCFMT_RIGHT,70);
	m_GuiListZdMx.InsertColumn(++i,_T("����"),LVCFMT_LEFT,40);
	m_GuiListZdMx.InsertColumn(++i,_T("��λ"),LVCFMT_LEFT,40);
	m_GuiListZdMx .InsertColumn(++i,_T("��ʦ"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiListZdMx.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//��ʼ����Ա���
	hotelMIS::HMemberCtrl mCtrl(m_con.get_con());
	hotelMIS::HMemberVec vec = mCtrl.getAllMember();
	hotelMIS::HMemberVec::iterator it ;
	CString bh_name;
	int pos = -1;
	pos = m_GuiComboBh.AddString("��ѡ��");
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		bh_name.Format("%s %s",it->bh.c_str(),it->mname.c_str());
		pos = m_GuiComboBh.AddString(bh_name);
		m_mapcombo.insert(make_pair(pos,it->bh));
	}
	m_GuiComboBh.SetCurSel(0);

}
void CMemXFSearchDlg::RefreshZdList()
{
	//�������� ˢ���˵���
	UpdateData(TRUE);

	CString t;
	string d1,d2,bh,name;
	t = m_d1.Format("%Y-%m-%d");
	d1 = t;
	t = m_d2.Format("%Y-%m-%d");
	d2 = t;

	int nPos = m_GuiComboBh.GetCurSel();
	if ( nPos != 0)
	{
		bh = m_mapcombo[nPos];
	}
	else{
		MessageBox(_T("��ѡѡ���Ա����ٲ�ѯ"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
		m_GuiComboBh.SetFocus();
		return ;
	}
	
	hotelMIS::HAccountCtrl accCtrl(m_con.get_con());
	hotelMIS::HAccountVec vec;
	if ( bh.empty() && !m_name.Trim().IsEmpty() )
	{
		//�����û���ȡ�ر��
		name = m_name.GetBuffer();
		hotelMIS::HMemberCtrl mCtrl(m_con.get_con());
		hotelMIS::HMember m = mCtrl.getByName(name);
		vec = accCtrl.getAccount(d1,d2,m.bh);
		
		m_exp.Format("��Ա��:%s ��Ա���:%s",m.mname.c_str(),m.bh.c_str());

	}
	else if ( !bh.empty()){
		vec = accCtrl.getAccount(d1,d2,bh);
		hotelMIS::HMemberCtrl mCtrl(m_con.get_con());
		hotelMIS::HMember m = mCtrl.getMember(bh);
		m_exp.Format("��Ա��:%s ��Ա���:%s",m.mname.c_str(),m.bh.c_str());

	}
	
	int i =0, j =1;
	hotelMIS::HAccountVec::iterator it;
	m_GuiListZd.DeleteAllItems();
	m_mapzd.clear();
	float fSum = 0.0f;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		m_mapzd.insert(make_pair(i,it->account_id.c_str()));
		m_GuiListZd.InsertItem(i,it->account_id.c_str());
		m_GuiListZd.SetItemText(i,j++,it->pay_date.c_str());
		t.Format("%.2f",it->sscost);
		m_GuiListZd.SetItemText(i,j++,t);
		fSum += it->sscost;
		i++;
	}
	m_GuiListZd.InsertItem(i,_T("�ϼ�:"));
	t.Format("%.2f",fSum);
	m_GuiListZd.SetItemText(i,2,t);

	
}

void CMemXFSearchDlg::RefreshZdMxList()
{
	//�����˵���ˢ����ϸ
	int nPos = m_GuiListZd.GetSelectionMark();
	if ( nPos != -1)
	{
		hotelMIS::HAccDetailsCtrl accDetailsCtrl(m_con.get_con());
		string accountId = m_mapzd[nPos];

		hotelMIS::HAccDetailsVec vec = accDetailsCtrl.getAccDetails(accountId);
		hotelMIS::HAccDetailsVec::iterator it;
		int i = 0,j=1;
		CString t;
		float p=0.0f;
		m_GuiListZdMx.DeleteAllItems();
		for ( it = vec.begin(); it != vec.end(); it++)
		{
			j = 1;
			t.Format("%d",i+1);m_GuiListZdMx.InsertItem(i,t);
			m_GuiListZdMx.SetItemText(i,j++,it->food_name.c_str());
			t.Format("%.2f",it->food_price);m_GuiListZdMx.SetItemText(i,j++,t);
			t.Format("%d",it->food_num);m_GuiListZdMx.SetItemText(i,j++,t);
			m_GuiListZdMx.SetItemText(i,j++,it->food_unit.c_str());
			m_GuiListZdMx.SetItemText(i,j++,it->ck_name.c_str());
			i++;
			p = p+(it->food_price*it->food_num);
		}
		m_GuiListZdMx.InsertItem(i,_T("�ϼ�:"));
		//float ys = repDetailsCtrl.getAllPrice(accid);
		t.Format("%.2f",p);
		m_GuiListZdMx.SetItemText(i,2,t);
	}
}


BOOL CMemXFSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitIdle();
	
	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMemXFSearchDlg::OnNMClickListZd(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	RefreshZdMxList();
}

void CMemXFSearchDlg::OnLvnItemchangedListZd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	RefreshZdMxList();

}

void CMemXFSearchDlg::OnBnClickedButtonPrint()
{
	PrintView();
}

void CMemXFSearchDlg::PrintView()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiListZd.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiListZd.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(Draw, PrnInfo);
	DlgPreView.DoModal();
}

void CMemXFSearchDlg::Draw(CDC &memDC, PRNINFO PrnInfo)
{
	//��ӡ�ص�
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
	wsprintf(szTitle,TEXT("%s ��Ա���ѱ���"),m_hotelname.GetBuffer());
    
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

		rt1.SetRect(nLeft, nTop, nLeft+50*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 60*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 80*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rc.top, rc.right,rt1.bottom);	
		/*rt5.SetRect(rt4.right, rt1.top, rt4.right + 18*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("�˵���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��������", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	        
		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+50*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 60*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 80*xPix, rt1.bottom);	
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
			

			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			
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

		rt1.SetRect(nLeft, nTop, nLeft+50*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 60*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 80*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rc.top, rc.right,rt1.bottom);	
		/*rt5.SetRect(rt4.right, rt1.top, rt4.right + 18*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("�˵���", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��������", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("���", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	        
		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+50*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 60*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 80*xPix, rt1.bottom);	
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
			

			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			
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