// MemZZListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemZZListDlg.h"
#include ".\memzzlistdlg.h"
#include "HMemberCtrl.h"

#include "HAdminBdy.H"
#include "HSetHotelPrintMsg.h"
#include "PreParent.h"

CString CMemZZListDlg::m_exp;
CString CMemZZListDlg::m_hotelname;

IMPLEMENT_DYNAMIC(CMemZZListDlg, CDialog)
CMemZZListDlg::CMemZZListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemZZListDlg::IDD, pParent)
	, m_d1(COleDateTime::GetCurrentTime())
	, m_bh(_T(""))
{
	CTime t = CTime::GetCurrentTime();
	m_d2.SetDate(t.GetYear(),t.GetMonth(),t.GetDay()+1);
}

CMemZZListDlg::~CMemZZListDlg()
{
}

void CMemZZListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_d1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_d2);
	DDX_Text(pDX, IDC_EDIT1, m_bh);
	DDX_Control(pDX, IDC_LIST_ZZ, m_GuiZZList);
}


BEGIN_MESSAGE_MAP(CMemZZListDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CMemZZListDlg 消息处理程序

BOOL CMemZZListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitIdle();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMemZZListDlg::Refresh()
{
	UpdateData();
	
	CString t;
	string d1,d2,bh;
	t = m_d1.Format("%Y-%m-%d");
	d1 = t.GetBuffer();
	t = m_d2.Format("%Y-%m-%d");
	d2 = t;
	bh = m_bh.GetBuffer();

	hotelMIS::HMzzCtrl mzzCtrl(m_con.get_con());
	hotelMIS::HMemberCtrl memCtrl(m_con.get_con());

	hotelMIS::HMzzVec mzzVec = mzzCtrl.getMzz(d1,d2,bh);

	hotelMIS::HMzzVec::iterator it ;
	
	int i = 0;
	int j = 0;
	m_GuiZZList.DeleteAllItems();
	for ( it = mzzVec.begin(); it != mzzVec.end(); it++)
	{
		j = 1;
		m_GuiZZList.InsertItem(i,it->sbh.c_str());
		hotelMIS::HMember m = memCtrl.getMember(it->sbh);
		m_GuiZZList.SetItemText(i,j++,m.mname.c_str());
		m_GuiZZList.SetItemText(i,j++,it->dbh.c_str());
		m = memCtrl.getMember(it->dbh);
		m_GuiZZList.SetItemText(i,j++,m.mname.c_str());
		t.Format("%.2f",it->zzmoney);	
		m_GuiZZList.SetItemText(i,j++,t);
		m_GuiZZList.SetItemText(i,j++,it->zzdate.c_str());
		m_GuiZZList.SetItemText(i,j++,it->remark.c_str());
        i++;
	}

	m_exp.Format("统计日期:%s 至 %s",d1.c_str(),d2.c_str());

}

void CMemZZListDlg::InitIdle()
{
	int i = 0;
	m_GuiZZList.InsertColumn(i++,_T("转出账户"),LVCFMT_LEFT,60);
	m_GuiZZList.InsertColumn(i++,_T("会员姓名"),LVCFMT_LEFT,70);
	m_GuiZZList.InsertColumn(i++,_T("转入账户"),LVCFMT_LEFT,60);
	m_GuiZZList.InsertColumn(i++,_T("会员姓名"),LVCFMT_LEFT,70);
	m_GuiZZList.InsertColumn(i++,_T("转账金额"),LVCFMT_RIGHT,80);
	m_GuiZZList.InsertColumn(i++,_T("转账日期"),LVCFMT_LEFT,110);
	m_GuiZZList.InsertColumn(i++,_T("备注"),LVCFMT_LEFT,120);
	
	ListView_SetExtendedListViewStyleEx(m_GuiZZList.m_hWnd, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	Refresh();
    
}
void CMemZZListDlg::OnBnClickedButtonSearch()
{
	Refresh();
	m_bh.Empty();
	UpdateData(false);
}

void CMemZZListDlg::OnBnClickedButtonPrint()
{
	//打印
	PrintView();
}

void CMemZZListDlg::PrintView()
{
	
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiZZList.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiZZList.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(Draw, PrnInfo);
	DlgPreView.DoModal();
}

void CMemZZListDlg::Draw(CDC &memDC, PRNINFO PrnInfo)
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
	wsprintf(szTitle,TEXT("%s 会员转账报表"),m_hotelname.GetBuffer());
    
	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6,rt7,rt8;
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

		rt1.SetRect(nLeft, nTop, nLeft+25*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 25*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 25*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 37*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("转出账户", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("会员姓名", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("转入账户", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("会员姓名", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("转账金额", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    memDC.DrawText("转账日期", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
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
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+25*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 25*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 25*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 37*xPix, rt1.bottom);	
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);	
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

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;

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
 		//细节
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//上横线
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+25*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 25*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 25*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 37*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);
		/*rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("转出账户", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("会员姓名", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("转入账户", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("会员姓名", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("转账金额", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    memDC.DrawText("转账日期", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
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
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[32]={0}, szSex[32]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0},szSS[32]={0},szHJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+25*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 25*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 25*xPix, rt1.bottom);	
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 37*xPix, rt1.bottom);	
		rt6.SetRect(rt5.right, rt1.top, rc.right , rt1.bottom);	
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

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;

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