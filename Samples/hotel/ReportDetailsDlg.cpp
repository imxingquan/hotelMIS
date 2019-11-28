//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  ReprotDetailsDlg.cpp
// 
// Desc:  经营明细报表
//
// Author:  xq
// 
// Modified: 2005年6月14日 5:09
//-----------------------------------------------------------------------
#include "stdafx.h"
#include "ReportDetailsDlg.h"
#include "HReportDtailsCtrl.h"
#include "HFoodKindCtrl.h"
#include ".\reportdetailsdlg.h"
#include "ReportDetailsPrint.h"

#include "HAdminBdy.H"
#include "HSetHotelPrintMsg.h"
#include "PreParent.h"

// CReportDetailsDlg 对话框
CString CReportDetailsDlg::m_exp;
CString CReportDetailsDlg::m_hotelname;

IMPLEMENT_DYNAMIC(CReportDetailsDlg, CDialog)
CReportDetailsDlg::CReportDetailsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportDetailsDlg::IDD, pParent)
	, m_dateStart(COleDateTime::GetCurrentTime())
	//, m_timeStart(COleDateTime::GetCurrentTime())
	, m_dateEnd(COleDateTime::GetCurrentTime())
	
{
	m_timeEnd.ParseDateTime(_T("23:59:59"));
}

CReportDetailsDlg::~CReportDetailsDlg()
{
}

void CReportDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_dateStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_timeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_dateEnd);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_timeEnd);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_GuiButtonSearch);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiButtonPrint);
	DDX_Control(pDX, IDC_LIST_DETAILS, m_list);
	DDX_Control(pDX, IDC_BUTTON_PREVIEW, m_GuiButtonPreView);
	DDX_Control(pDX, IDCANCEL, m_GuiBtnCancel);
}


BEGIN_MESSAGE_MAP(CReportDetailsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, OnBnClickedButtonPreview)
END_MESSAGE_MAP()


// CReportDetailsDlg 消息处理程序
//=----------------------------------------------------------------------------------------------------
void CReportDetailsDlg::InitIdle()
{
	int i = 0;
	m_list.InsertColumn(i++,_T("编号"),LVCFMT_CENTER,50);
	m_list.InsertColumn(i++,_T("名称"),LVCFMT_LEFT,200);
	m_list.InsertColumn(i++,_T("数量"),LVCFMT_RIGHT,50);
	m_list.InsertColumn(i++,_T("单位"),LVCFMT_LEFT,60);
	//m_list.InsertColumn(i++,_T("售价"),LVCFMT_LEFT,60);
	m_list.InsertColumn(i++,_T("总价"),LVCFMT_RIGHT,200);
	ListView_SetExtendedListViewStyleEx(m_list.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
}

void CReportDetailsDlg::OnBnClickedButtonSearch()
{
	// 查询
	Refresh();
	m_GuiButtonPrint.EnableWindow(TRUE);
	m_GuiButtonPreView.EnableWindow(TRUE);

}

//-----------------------------------------------------------------------------------------------------------------------
void CReportDetailsDlg::OnBnClickedButtonPrint()
{
PrintView();
	//TRY{
	//	// 打印
	//	CString t;
	//	string datetimeStart,datetimeEnd;
	//	t = m_dateStart.Format("%Y-%m-%d");
	//	t += m_timeStart.Format(" %H:%M:%S");
	//	datetimeStart = t.GetBuffer();
	//	t = m_dateEnd.Format("%Y-%m-%d");
	//	t += m_timeEnd.Format(" %H:%M:%S");
	//	datetimeEnd = t.GetBuffer();

	//	ReportDetailsPrint rdp(datetimeStart,datetimeEnd);
	//	if ( rdp.CreateExcel() ){
	//		rdp.LoadTemplate("\\tmpl\\reportdetails");
	//		rdp.SendExcel();
	//		rdp.SaveAs(_T("经营详细报表"));
	//		rdp.Print();

	//	}
	//}CATCH(CException,e)
	//{
	//	e->ReportError();
	//}
	//END_CATCH
}

//------------------------------------------------------------------------------------------------------------------------
void CReportDetailsDlg::OnBnClickedButtonPreview()
{
	//打印预览
	TRY{
		CString t;
		string datetimeStart,datetimeEnd;
		t = m_dateStart.Format("%Y-%m-%d");
		t += m_timeStart.Format(" %H:%M:%S");
		datetimeStart = t.GetBuffer();
		t = m_dateEnd.Format("%Y-%m-%d");
		t += m_timeEnd.Format(" %H:%M:%S");
		datetimeEnd = t.GetBuffer();

		ReportDetailsPrint rdp(datetimeStart,datetimeEnd);
		if ( rdp.CreateExcel() ){
			rdp.LoadTemplate("\\tmpl\\reportdetails");
			rdp.SendExcel();
			rdp.SaveAs(_T("经营详细报表"));
			rdp.PrintPreview();

		}
	}CATCH(CException,e)
	{
		e->ReportError();
	}
	END_CATCH
}

BOOL CReportDetailsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_GuiButtonPrint.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonPreView.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiButtonSearch.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiBtnCancel.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiButtonPrint.ShowText();
	m_GuiButtonPreView.ShowText();
	m_GuiButtonSearch.ShowText();
	m_GuiBtnCancel.ShowText();

	InitIdle();	

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReportDetailsDlg::Refresh()
{
	UpdateData();
	CString t;
	string datetimeStart,datetimeEnd;
	t = m_dateStart.Format("%Y-%m-%d");
	t += m_timeStart.Format(" %H:%M:%S");
	datetimeStart = t.GetBuffer();
	t = m_dateEnd.Format("%Y-%m-%d");
	t += m_timeEnd.Format(" %H:%M:%S");
	datetimeEnd = t.GetBuffer();
	
	m_list.DeleteAllItems();
	
	hotelMIS::HReportDetailsCtrl repDetailsCtrl(m_con.get_con());
	
	hotelMIS::HFoodKindCtrl kindCtrl(m_con.get_con());
	
	hotelMIS::HFoodKindVec kindVec = kindCtrl.getAllKind();
	hotelMIS::HFoodKindVec::iterator it ;
	
	hotelMIS::HReportDetailsVec::iterator it2;
	hotelMIS::HReportDetailsVec vec;

	int nRow = 0;
	int j = 0;
	
	float uSum = 0.0f;
	float aSum = 0.0f;

	for ( it = kindVec.begin(); it != kindVec.end(); it++)
	{
		if ( it->kind_id == hotelMIS::HFoodKind::HOUCHU_FLAG){
			continue;
		}
		
		vec = repDetailsCtrl.reportDetails(datetimeStart,datetimeEnd,it->kind_id);
		if ( !vec.empty() )
		{
			m_list.InsertItem(nRow,_T("类名"));
			m_list.SetItemText(nRow++,1,it->kind_name.c_str());
			uSum = 0.0f;
			for ( it2 = vec.begin(); it2 != vec.end(); it2++)
			{
				j = 1;

				t.Format("%d",it2->food_id);
				m_list.InsertItem(nRow,t);

				m_list.SetItemText(nRow,j++,it2->food_name.c_str());

				t.Format("%.2f",it2->sum_num);
				m_list.SetItemText(nRow,j++,t);
				
				m_list.SetItemText(nRow,j++,it2->food_unit.c_str());

				t.Format("%.2f",it2->sum_price);
				m_list.SetItemText(nRow,j++,t);
				
				uSum += it2->sum_price;

				nRow++;
			}
						
			if ( uSum != 0){
				t.Format("%.2f",uSum);
				m_list.InsertItem(nRow,_T("合计:"));
				m_list.SetItemText(nRow,4,t);
				nRow++;
			}
			m_list.InsertItem(nRow++,_T("")); //空行

			aSum += uSum;
		}
	}	
	
	if ( aSum != 0){
		t.Format("%.2f",aSum);
		m_list.InsertItem(nRow,_T("总合计:"));
		m_list.SetItemText(nRow,4,t);
	}
	
	m_exp.Format("统计日期:%s至%s",datetimeStart.c_str(),datetimeEnd.c_str());
}


void CReportDetailsDlg::PrintView()
{
	
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_list.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_list.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(Draw, PrnInfo);
	DlgPreView.DoModal();
}

void CReportDetailsDlg::Draw(CDC &memDC, PRNINFO PrnInfo)
{
	//打印回调
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
	wsprintf(szTitle,TEXT("%s 经营详细报表"),m_hotelname.GetBuffer());
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8,rt9;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, PFont,*oldfont;
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
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 70*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);
		

		memDC.DrawText("编号", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("名称", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("数量", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("单位", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("总价", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
		
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

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0},szDD[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 70*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right, rt1.bottom);
		
		//rt5.SetRect(rt4.right, rt1.top, rc.right, rt1.bottom);	

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
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			
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
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 70*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right , rt1.bottom);
		

		memDC.DrawText("编号", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("名称", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("数量", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("单位", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("总价", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
		
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

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0},szDD[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 70*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 30*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 18*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rc.right, rt1.bottom);
		
		//rt5.SetRect(rt4.right, rt1.top, rc.right, rt1.bottom);	

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
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
			
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