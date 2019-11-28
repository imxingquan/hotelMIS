// RepertorySearchDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include ".\repertorysearchdialog.h"
#include "HBehindRepCtrl.h"
#include "HMenuInfoCtrl.h"
#include "HSetHotelPrintMsg.h"
#include "HAdminBdy.h"
#include "PreParent.h"
#include "RepModifyDlg.h"
// CRepertorySearchDialog 对话框
CString CRepertorySearchDialog::m_hotelname;
CString CRepertorySearchDialog::m_exp;

IMPLEMENT_DYNAMIC(CRepertorySearchDialog, CDialog)
CRepertorySearchDialog::CRepertorySearchDialog(CWnd* pParent /*=NULL*/)
: CDialog(CRepertorySearchDialog::IDD, pParent)
, m_bh(_T(""))
, m_namepy(_T(""))
{
}

CRepertorySearchDialog::~CRepertorySearchDialog()
{
}

void CRepertorySearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXU, m_GuiGroupBoxU);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);

	DDX_Control(pDX, IDC_REPLIST, m_GuiRepList);

	DDX_Control(pDX, IDC_BH_EDIT, m_GuiBhEdit);
	DDX_Text(pDX, IDC_BH_EDIT, m_bh);
	DDX_Control(pDX, IDC_NAME_PY_EDIT, m_GuiNamePyEdit);
	DDX_Text(pDX, IDC_NAME_PY_EDIT, m_namepy);
	DDX_Control(pDX, IDC_PRINT_BUTTON, m_GuiPrintBtn);
	DDX_Control(pDX,IDC_REP_MODIFY_BTN ,m_GuiRepModifyBtn);
}


BEGIN_MESSAGE_MAP(CRepertorySearchDialog, CDialog)
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnBnClickedPrintButton)
	ON_EN_CHANGE(IDC_BH_EDIT, OnEnChangeBhEdit)
	ON_EN_CHANGE(IDC_NAME_PY_EDIT, OnEnChangeNamePyEdit)
	ON_BN_CLICKED(IDC_REP_MODIFY_BTN, OnBnClickedRepModifyBtn)
END_MESSAGE_MAP()


// CRepertorySearchDialog 消息处理程序




void CRepertorySearchDialog::Init()
{

	m_GuiRepList.InsertColumn(0,_T("编号"),LVCFMT_LEFT,80);
	m_GuiRepList.InsertColumn(1,_T("名称"),LVCFMT_LEFT,200);
	m_GuiRepList.InsertColumn(2,_T("库存数量"),LVCFMT_LEFT,100);
	m_GuiRepList.InsertColumn(3,_T("单位"),LVCFMT_LEFT,50);
	m_GuiRepList.InsertColumn(4,_T("出库单价"),LVCFMT_RIGHT,100);
	m_GuiRepList.InsertColumn(5,_T("总金额"),LVCFMT_RIGHT,100);
	ListView_SetExtendedListViewStyleEx(m_GuiRepList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

}


void CRepertorySearchDialog::RestRepRefresh() //剩余库存列表
{	
	UpdateData();
	CTime dt = CTime::GetCurrentTime();
	m_exp.Format("统计日期:%s",dt.Format("%y-%m-%d %H:%M:%S"));

	m_GuiRepList.DeleteAllItems();
	m_repmap.clear();

	hotelMIS::HBehindRepCtrl bhRepCtrl(m_con.get_con());
	hotelMIS::HBehindRepVec vec;
	if ( !m_namepy.Trim().IsEmpty())
		vec= bhRepCtrl.search(m_namepy.GetBuffer());
	else if ( !m_bh.Trim().IsEmpty())
		vec = bhRepCtrl.search(atoi(m_bh));
	else
		vec = bhRepCtrl.getAll();

	hotelMIS::HBehindRepVec::iterator it ;
	int i = 0;
	CString t;

	hotelMIS::HMenuInfoCtrl menuCtrl(m_con.get_con());
	hotelMIS::HMenuInfo m;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		m_repmap.insert(make_pair(i,it->food_id));
		m = menuCtrl.getMenuInfo(it->food_id);
		t.Format("%d",it->food_id); m_GuiRepList.InsertItem(i,t);
		m_GuiRepList.SetItemText(i,1,m.food_name.c_str());
		t.Format("%.2f",it->rep_num); m_GuiRepList.SetItemText(i,2,t);
		m_GuiRepList.SetItemText(i,3,m.food_unit.c_str());
		t.Format("%.2f",it->food_price);m_GuiRepList.SetItemText(i,4,t); //出库单价
		t.Format("%.2f",it->total_price);m_GuiRepList.SetItemText(i,5,t);//总金额
		i++;
	}


}

void CRepertorySearchDialog::OnBnClickedRepModifyBtn()
{
	// 调整库存量
	int nPos = m_GuiRepList.GetSelectionMark();
	if ( nPos != -1)
	{
		int food_id = m_repmap[nPos];
		CRepModifyDlg dlg;
		dlg.m_bh = food_id;
		if ( dlg.DoModal() == IDOK){
			RestRepRefresh();
		}
	}
}


BOOL CRepertorySearchDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiRepModifyBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.ShowText();
	m_GuiRepModifyBtn.ShowText();

	// TODO:  在此添加额外的初始化
	Init();

	RestRepRefresh();

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRepertorySearchDialog::OnBnClickedPrintButton()
{
	//打印
PrintView();	
}

void CRepertorySearchDialog::OnEnChangeBhEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_namepy.Empty();
	RestRepRefresh();
}

void CRepertorySearchDialog::OnEnChangeNamePyEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_bh.Empty();
	RestRepRefresh();
}

void CRepertorySearchDialog::PrintView()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiRepList.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiRepList.GetItemCount();

	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(Draw, PrnInfo);
	DlgPreView.DoModal();
}

void CRepertorySearchDialog::Draw(CDC &memDC, PRNINFO PrnInfo)
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
	wsprintf(szTitle,TEXT("%s 库存量报表"),m_hotelname.GetBuffer());

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

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 80*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt2.top, rt2.right + 50*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right,rt3.top,rc.right,rt1.bottom);


		memDC.DrawText("商品编号", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("商品名称", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("库存量", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("单位", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 80*xPix, rt1.bottom);
		rt3.SetRect(rt2.right, rt2.top, rt2.right + 50*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt3.top, rc.right, rt1.bottom);	

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

			//下横线
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
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

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 80*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt2.top, rt2.right + 50*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right,rt3.top,rc.right,rt1.bottom);


		memDC.DrawText("商品编号", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("商品名称", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("库存量", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("单位", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 80*xPix, rt1.bottom);
		rt3.SetRect(rt2.right, rt2.top, rt2.right + 50*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt3.top, rc.right, rt1.bottom);	

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

			//下横线
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
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
