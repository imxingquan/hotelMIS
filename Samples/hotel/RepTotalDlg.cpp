//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  ReptotalDlg.h
// 
// Desc: 库存汇总
//
// Author:  邢泉
// 
// Modified: 2006年6月16日 
//-----------------------------------------------------------------------


// RepTotalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepTotalDlg.h"
#include ".\reptotaldlg.h"
#include "HInOutRepCtrl.h"
#include "PreParent.h"		//打印预览父窗口

#include "HSetHotelPrintMsg.h"
#include "HAdminBdy.h"

// CRepTotalDlg 对话框
CString CRepTotalDlg::m_hotelname;
CString CRepTotalDlg::m_exp;

IMPLEMENT_DYNAMIC(CRepTotalDlg, CDialog)
CRepTotalDlg::CRepTotalDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRepTotalDlg::IDD, pParent)
, m_d1(COleDateTime::GetCurrentTime())
, m_d2(COleDateTime::GetCurrentTime())
{
}

CRepTotalDlg::~CRepTotalDlg()
{
}

void CRepTotalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_d1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_d2);
	DDX_Control(pDX, IDC_TOTAL_BUTTON, m_GuiTotalBtn);
	DDX_Control(pDX, IDC_TOTAL_LIST, m_GuiTotalList);
	DDX_Control(pDX, IDC_PRINT_BUTTON, m_GuiPrintBtn);
}


BEGIN_MESSAGE_MAP(CRepTotalDlg, CDialog)
	ON_BN_CLICKED(IDC_TOTAL_BUTTON, OnBnClickedTotalButton)
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnBnClickedPrintButton)
END_MESSAGE_MAP()


// CRepTotalDlg 消息处理程序

void CRepTotalDlg::OnBnClickedTotalButton()
{
	// 汇总
	UpdateData();

	CString d1,d2;
	d1 = m_d1.Format("%Y-%m-%d");
	d2 = m_d2.Format("%Y-%m-%d");
	m_exp.Format("统计日期:%s 至 %s",d1,d2);
	hotelMIS::HInOutRepCtrl inOutRepCtrl(m_con.get_con());
	hotelMIS::HTotalInOutRepVec vec = inOutRepCtrl.totalByDate(d1.GetBuffer(),d2.GetBuffer());
	hotelMIS::HTotalInOutRepVec::iterator it;

	m_GuiTotalList.DeleteAllItems();

	CString t;
	int i = 0;
	int j = 0;
	float upSum = 0.0f;
	float outSum=0.0f;
	float inSum=0.0f;
	

	for ( it = vec.begin(); it != vec.end(); it++)
	{
		j = 1;
		if ( it->rep_flag == hotelMIS::HInOutRep::IN_REP ){
			m_GuiTotalList.InsertItem(i,_T("入库"));
			upSum += it->sum_price;
			inSum += it->sum_price;
		}
		else if ( it->rep_flag == hotelMIS::HInOutRep::OUT_REP){
			j = 2;
			m_GuiTotalList.InsertItem(i,_T("出库"));
			upSum -= it->sum_price;
			outSum += it->sum_price; 
		}

		t.Format("%.2f",it->sum_price); m_GuiTotalList.SetItemText(i,j,t); //入出库
		j = 3;
		t.Format("%.2f",upSum);  m_GuiTotalList.SetItemText(i,j++,t);
		m_GuiTotalList.SetItemText(i,j,it->sdate.c_str());

		i++;
	}

	m_GuiTotalList.InsertItem(i,_T("合计"));
	t.Format("%.2f",inSum);
	m_GuiTotalList.SetItemText(i,1,t);
	t.Format("%.2f",outSum);
	m_GuiTotalList.SetItemText(i,2,t);
}

//--------------------------------------------------------------------------------------------------------------------------
void CRepTotalDlg::InitIdle()
{
	int nCol = 0;
	m_GuiTotalList.InsertColumn(nCol++,_T("摘要"),LVCFMT_LEFT,70);
	m_GuiTotalList.InsertColumn(nCol++,_T("入库"),LVCFMT_RIGHT,70);
	m_GuiTotalList.InsertColumn(nCol++,_T("出库"),LVCFMT_RIGHT,70);
	m_GuiTotalList.InsertColumn(nCol++,_T("结余"),LVCFMT_RIGHT,100);
	m_GuiTotalList.InsertColumn(nCol++,_T("日期"),LVCFMT_LEFT,100);


	ListView_SetExtendedListViewStyleEx(m_GuiTotalList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);



}

//--------------------------------------------------------------------------------------------------------------------------
BOOL CRepTotalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_GuiTotalBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiTotalBtn.ShowText();
	m_GuiPrintBtn.ShowText();

	InitIdle();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//--------------------------------------------------------------------------------------------------------------------------
void CRepTotalDlg::PrintTotal()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiTotalList.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiTotalList.GetItemCount();

	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawByTotal, PrnInfo);
	DlgPreView.DoModal();
}

//---------------------------------------------------------------------------------------------------------------------
void CRepTotalDlg::DrawByTotal(CDC &memDC, PRNINFO PrnInfo)
{
	if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//当前页
	BOOL IsPrint = PrnInfo.IsPrint;		//是否打印
	int nMaxPage = PrnInfo.nCountPage;	//最大页码
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("打印日期:%Y-%m-%d %H:%M:%S");
	csRFinality.Format("第 %i 页/共 %i 页", nCurPage, nMaxPage);


	TCHAR szTitle[255];
	wsprintf(szTitle,TEXT("%s 库存出入汇总报表"),m_hotelname);

	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont,PFont, *oldfont;
	//标题字体
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("黑体"));
	//副标题字体
	PFont.CreateFont(-MulDiv(11,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("黑体"));
	//细节字体
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("宋体"));
	//粗笔
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	int xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x方向每英寸像素点数
	int yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y方向每英寸像素点数

	DOUBLE xPix = (DOUBLE)xP*10/254;	//每 mm 宽度的像素
	DOUBLE yPix = (DOUBLE)yP*10/254;	//每 mm 高度的像素
	DOUBLE fAdd = 7*yPix;		//每格递增量
	DOUBLE nTop = 32*yPix;		//第一页最上线
	int	  iStart = 0;			//从第几行开始读取
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//非第一页最上线
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 15*xPix;			//最左线
	DOUBLE nRight = xPix*(B5_W-15);	//最右线



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//真正打印部分
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//开始文档打印
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "连接到打印机化败!", "错误", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 30*yPix;		//第一页最上线
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("第 %i 页/共 %i 页", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("打印日期:%Y-%m-%d %H:%M:%S");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//非第一页最上线
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//开始页
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("打印失败!"), "错误", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//打印
					//标题
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
						t.Format("制表人:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
						memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
					}
					//细节

					memDC.SelectObject(&DetailFont);
					rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
					//上横线
					memDC.MoveTo(rc.left, rc.top);
					memDC.LineTo(rc.right, rc.top);

					rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);					
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 50*xPix, rt1.bottom);	
					rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);


					memDC.DrawText("摘要", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("入库", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("出库", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("结余", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("日期", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


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

					memDC.MoveTo(rc.left, rt1.bottom);
					memDC.LineTo(rc.right, rt1.bottom);

					TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[50]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
					rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
					rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 50*xPix, rt1.bottom);	
					rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);	


					int nCountItem = ListView_GetItemCount(hList);
					for(int i=0;i<nItem; i++)
					{
						ListView_GetItemText(hList, i+iStart, 0, szID, 32);
						ListView_GetItemText(hList, i+iStart, 1, szName, 32);
						ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
						ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
						ListView_GetItemText(hList, i+iStart, 4, szNJ, 50);
						//ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
						//ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
						////ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);

						memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						//memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						//memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						////memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

						//下横线
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
						/*memDC.MoveTo(rt5.right, rt1.top);
						memDC.LineTo(rt5.right, rt1.bottom);
						memDC.MoveTo(rt6.right, rt1.top);
						memDC.LineTo(rt6.right, rt1.bottom);*/
						//memDC.MoveTo(rt7.right, rt1.top);
						//memDC.LineTo(rt7.right, rt1.bottom);
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
						/*rt6.top = rt1.top;
						rt6.bottom = rt1.bottom;
						rt7.top = rt1.top;
						rt7.bottom = rt1.bottom;*/

						if((i+iStart+1)>=nCountItem)
							break;
					}
					//结尾
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
		//打印预览

		//边框线
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	

		//标题
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
			t.Format("制表人:%s",hotelMIS::HAdminBdy::_ad_name.c_str());
			memDC.DrawText(t,&rc,DT_RIGHT |DT_VCENTER | DT_SINGLELINE);
		}
		//细节

		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//上横线
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 50*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);


		memDC.DrawText("摘要", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("入库", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("出库", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("结余", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("日期", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


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

		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[50]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 30*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 50*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);	


		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 32);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 32);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 50);
			//ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
			//ListView_GetItemText(hList, i+iStart, 6, szSS, 32);
			////ListView_GetItemText(hList, i+iStart, 7, szHJ, 32);

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//memDC.DrawText(szSS, &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			////memDC.DrawText(szHJ, &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//下横线
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
			/*memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);*/
			//memDC.MoveTo(rt7.right, rt1.top);
			//memDC.LineTo(rt7.right, rt1.bottom);
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
			/*rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;*/

			if((i+iStart+1)>=nCountItem)
				break;
		}
		//结尾

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

void CRepTotalDlg::OnBnClickedPrintButton()
{
	// 打印
	PrintTotal();
}
