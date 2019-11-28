// MemberInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "MemberInfoDlg.h"

#include "HMemberCtrl.h"

#include ".\memberinfodlg.h"

#include "AddMemberDlg.h"
#include "MczDlg.h"
#include "MemModifyDlg.h"
#include "MemZZDlg.h"

#include "HAdminBdy.H"
#include "HSetHotelPrintMsg.h"
#include "PreParent.h"

// CMemberInfoDlg �Ի���

CString CMemberInfoDlg::m_exp;
CString CMemberInfoDlg::m_hotelname;

IMPLEMENT_DYNAMIC(CMemberInfoDlg, CDialog)
CMemberInfoDlg::CMemberInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemberInfoDlg::IDD, pParent),
	m_nPos(-1)
{
}

CMemberInfoDlg::~CMemberInfoDlg()
{
}

void CMemberInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MEMINFO_LIST, m_GuiMemInfoList);
	DDX_Control(pDX, IDC_ADDMEM_BUTTON, m_GuiAddBtn);
	DDX_Control(pDX, IDC_MODIFYMEM_BUTTON, m_GuiModifyBtn);
	DDX_Control(pDX, IDC_DELMEM_BUTTON, m_GuiDelBtn);
	DDX_Control(pDX, IDC_ZZMEM_BUTTON, m_GuiZZBtn);
	DDX_Control(pDX, IDC_CZMEM_BUTTON, m_GuiCZBtn);
	DDX_Control(pDX, IDC_PMEM_BUTTON, m_GuiPrintBtn);
	DDX_Control(pDX, IDCANCEL, m_GuiBtnCancel);
}


BEGIN_MESSAGE_MAP(CMemberInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_ADDMEM_BUTTON, OnBnClickedAddmemButton)
	ON_BN_CLICKED(IDC_MODIFYMEM_BUTTON, OnBnClickedModifymemButton)
	ON_BN_CLICKED(IDC_DELMEM_BUTTON, OnBnClickedDelmemButton)
	ON_BN_CLICKED(IDC_ZZMEM_BUTTON, OnBnClickedZzmemButton)
	ON_BN_CLICKED(IDC_CZMEM_BUTTON, OnBnClickedCzmemButton)
	ON_BN_CLICKED(IDC_PMEM_BUTTON, OnBnClickedPmemButton)
	ON_NOTIFY(NM_CLICK, IDC_MEMINFO_LIST, OnNMClickMeminfoList)
	ON_NOTIFY(NM_DBLCLK, IDC_MEMINFO_LIST, OnNMDblclkMeminfoList)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CMemberInfoDlg ��Ϣ�������

BOOL CMemberInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	Init();
	Refresh();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BEGIN_EVENTSINK_MAP(CMemberInfoDlg, CDialog)
	
END_EVENTSINK_MAP()

//
// ��ʼ��
//
void CMemberInfoDlg::Init()
{
	m_GuiAddBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiModifyBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiDelBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiZZBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiCZBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnCancel.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiAddBtn.ShowText();
	m_GuiModifyBtn.ShowText();
	m_GuiDelBtn.ShowText();
	m_GuiZZBtn.ShowText();
	m_GuiCZBtn.ShowText();
	m_GuiPrintBtn.ShowText();
	m_GuiBtnCancel.ShowText();

	//��ʼ���б�
	int i=0;
	m_GuiMemInfoList.InsertColumn(i++,_T("��Ա��"),LVCFMT_LEFT,50);
	m_GuiMemInfoList.InsertColumn(i++,_T("����"),LVCFMT_LEFT,80);
	m_GuiMemInfoList.InsertColumn(i++,_T("�Ա�"),LVCFMT_LEFT,40);
	m_GuiMemInfoList.InsertColumn(i++,_T("��������"),LVCFMT_LEFT,100);
	m_GuiMemInfoList.InsertColumn(i++,_T("�ȼ�"),LVCFMT_LEFT,100);
	m_GuiMemInfoList.InsertColumn(i++,_T("�ۿ�ֵ"),LVCFMT_LEFT,70);
	m_GuiMemInfoList.InsertColumn(i++,_T("��ϵ�绰"),LVCFMT_LEFT,120);
	m_GuiMemInfoList.InsertColumn(i++,_T("��ֵ���"),LVCFMT_RIGHT,70);
	m_GuiMemInfoList.InsertColumn(i++,_T("�������"),LVCFMT_LEFT,120);

	ListView_SetExtendedListViewStyleEx(m_GuiMemInfoList.m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}

//
// ˢ���б�
//
void CMemberInfoDlg::Refresh()
{
	m_GuiMemInfoList.DeleteAllItems();
	
	hotelMIS::HMemberCtrl hMemberCtrl(m_con.get_con());
	hotelMIS::HMemberVec vec = hMemberCtrl.getAllMember();
	
	hotelMIS::HMemberVec::iterator it;

	int i=0,j;
	CString t;
	m_map.clear();
	
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		m_map.insert(make_pair(i,it->bh));

		m_GuiMemInfoList.InsertItem(i,it->bh.c_str());				//��Ա���
		m_GuiMemInfoList.SetItemText(i,j++,it->mname.c_str());		//����
		m_GuiMemInfoList.SetItemText(i,j++,it->sex.c_str());		//�Ա�
		m_GuiMemInfoList.SetItemText(i,j++,it->mbirth.c_str());		//��������
		m_GuiMemInfoList.SetItemText(i,j++,it->mdjname.c_str());	//�ȼ�����
		t.Format("%.2f",it->zhekou);
		m_GuiMemInfoList.SetItemText(i,j++,t);						//�ۿ�ֵ
		m_GuiMemInfoList.SetItemText(i,j++,it->telphone.c_str());	//��ϵ�绰
		t.Format("%.2f",it->czmoney);
		m_GuiMemInfoList.SetItemText(i,j++,t);						//��ֵ���
		m_GuiMemInfoList.SetItemText(i,j++,it->rhdate.c_str());		//�������

		i++;
	}
}
void CMemberInfoDlg::OnBnClickedAddmemButton()
{
	// TODO: ��ӻ�Ա
	CAddMemberDlg dlg;
	dlg.DoModal();

	Refresh();
}

void CMemberInfoDlg::OnBnClickedModifymemButton()
{
	// TODO: �޸Ļ�Ա����
	if ( m_nPos != -1){
		CString bh = m_GuiMemInfoList.GetItemText(m_nPos,0);
		CMemModifyDlg dlg;
		dlg.m_bh = bh;
		dlg.DoModal();

		Refresh();
	}
}

void CMemberInfoDlg::OnBnClickedDelmemButton()
{
	// TODO: ɾ����Ա����
	if ( m_nPos != -1){
		
		CString bh = m_GuiMemInfoList.GetItemText(m_nPos,0);
		CString name = m_GuiMemInfoList.GetItemText(m_nPos,1);

		CString t;
		t.Format(_T("ȷ��Ҫɾ�� %s - %s �Ļ�Ա������?"),bh,name);
		int r = MessageBox(t,_T("��ʾ"),MB_ICONINFORMATION|MB_YESNO);
		if ( r == IDYES){
			hotelMIS::HMemberCtrl hMemberCtrl(m_con.get_con());
			hotelMIS::HMczCtrl hMczCtrl(m_con.get_con());

			hMemberCtrl.Delete(bh.Trim().GetBuffer());
			hMczCtrl.Delete(bh.Trim().GetBuffer());

			m_nPos = -1;
			m_GuiDelBtn.EnableWindow(FALSE);
			Refresh();
		}
	}
}

void CMemberInfoDlg::OnBnClickedZzmemButton()
{
	//  ת��
	if ( m_nPos != -1)
	{
		CString bh = m_GuiMemInfoList.GetItemText(m_nPos,0);
		CString name = m_GuiMemInfoList.GetItemText(m_nPos,1);
		CString money = m_GuiMemInfoList.GetItemText(m_nPos,7);
		CMemZZDlg dlg(NULL,bh,name,atof(money));
		dlg.DoModal();
		Refresh();
	}
}

void CMemberInfoDlg::OnBnClickedCzmemButton()
{
	// TODO: ��ֵ
	if ( m_nPos != -1){
		CString bh = m_GuiMemInfoList.GetItemText(m_nPos,0);
		CString name = m_GuiMemInfoList.GetItemText(m_nPos,1);
		
		CMczDlg dlg(NULL,bh,name);
		dlg.DoModal();
		Refresh();
	}
}

void CMemberInfoDlg::OnNMClickMeminfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �����б�
	*pResult = 0;
	m_nPos = m_GuiMemInfoList.GetSelectionMark();
	if ( m_nPos != -1 ){
		m_GuiModifyBtn.EnableWindow(TRUE);
		m_GuiDelBtn.EnableWindow(TRUE);
		m_GuiCZBtn.EnableWindow(TRUE);
		m_GuiZZBtn.EnableWindow(TRUE);
	}
	else{
		m_GuiModifyBtn.EnableWindow(FALSE);
		m_GuiDelBtn.EnableWindow(FALSE);
		m_GuiCZBtn.EnableWindow(FALSE);
		m_GuiZZBtn.EnableWindow(FALSE);
	}
}

void CMemberInfoDlg::OnNMDblclkMeminfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ˫���б� �޸�
	*pResult = 0;
	m_nPos = m_GuiMemInfoList.GetSelectionMark();
	OnBnClickedModifymemButton();
}


void CMemberInfoDlg::OnBnClickedPmemButton()
{
	// TODO: ��ӡ
	PrintView();
}

void CMemberInfoDlg::PrintView()
{
	
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiMemInfoList.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiMemInfoList.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(Draw, PrnInfo);
	DlgPreView.DoModal();
}

void CMemberInfoDlg::Draw(CDC &memDC, PRNINFO PrnInfo)
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
	wsprintf(szTitle,TEXT("%s ��Ա��Ϣ����"),m_hotelname.GetBuffer());
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8,rt9;
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
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+15*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 15*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 20*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + 30*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("��Ա��", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�Ա�", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��������", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ȼ�", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ۿ�ֵ", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    memDC.DrawText("��ϵ�绰", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ֵ���", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�������", &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
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
		memDC.MoveTo(rt8.right, rt1.top);
		memDC.LineTo(rt8.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0},szDD[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+15*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 15*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 20*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);	
		rt8.SetRect(rt7.right, rt1.top, rt7.right + 30*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rc.right , rt1.bottom);	
		//rt5.SetRect(rt4.right, rt1.top, rc.right, rt1.bottom);	

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
			ListView_GetItemText(hList, i+iStart, 8, szDD, 32);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szDD, &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
			memDC.MoveTo(rt8.right, rt1.top);
			memDC.LineTo(rt8.right, rt1.bottom);
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
			rt9.top = rt1.top;
			rt9.bottom = rt1.bottom;

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

		rt1.SetRect(nLeft, nTop, nLeft+15*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 15*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 20*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rt7.right + 30*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("��Ա��", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("����", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�Ա�", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��������", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ȼ�", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�ۿ�ֵ", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    memDC.DrawText("��ϵ�绰", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ֵ���", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�������", &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
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
		memDC.MoveTo(rt8.right, rt1.top);
		memDC.LineTo(rt8.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0},szDD[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+15*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 15*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 15*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 20*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 20*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);	
		rt8.SetRect(rt7.right, rt1.top, rt7.right + 30*xPix, rt1.bottom);
		rt9.SetRect(rt8.right, rt1.top, rc.right , rt1.bottom);	
		//rt5.SetRect(rt4.right, rt1.top, rc.right, rt1.bottom);	

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
			ListView_GetItemText(hList, i+iStart, 8, szDD, 32);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szDD, &rt9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
			memDC.MoveTo(rt8.right, rt1.top);
			memDC.LineTo(rt8.right, rt1.bottom);
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
			rt9.top = rt1.top;
			rt9.bottom = rt1.bottom;

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
void CMemberInfoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
