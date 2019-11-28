// SearchAccountDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "HAdminBdy.h"
#include "SearchAccountDlg.h"
#include "PreParent.h"		//打印预览父窗口


// CSearchAccountDlg 对话框
CString CSearchAccountDlg::m_hotelname;
CString CSearchAccountDlg::m_exp;
CString CSearchAccountDlg::m_exp2;
IMPLEMENT_DYNAMIC(CSearchAccountDlg, CDialog)
CSearchAccountDlg::CSearchAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchAccountDlg::IDD, pParent)
	, m_date1(COleDateTime::GetCurrentTime())
	, m_date2(COleDateTime::GetCurrentTime())
	, m_accid(_T(""))
{
}

CSearchAccountDlg::~CSearchAccountDlg()
{
}
void CSearchAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUPBOXUL, m_GuiGroupBoxUL);
	DDX_Control(pDX, IDC_GROUPBOXUR, m_GuiGroupBoxUR);
	DDX_Control(pDX, IDC_GROUPBOXB, m_GuiGroupBoxB);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_GuiDateTime1Ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_GuiDateTime2Ctrl);
	DDX_Control(pDX, IDC_ACCSTATUS_COMBO, m_GuiAccStatusCombo);
	DDX_Control(pDX, IDC_SRH_BYDATEBTN, m_GuiSrhByDateBtn);
	DDX_Control(pDX, IDC_ACCID_EDIT, m_GuiAccidEdit);
	DDX_Control(pDX, IDC_SEARCH_BYACCIDBTN, m_GuiSrhByAccidBtn);
	DDX_Control(pDX, IDC_ACCOUNT_LIST, m_GuiAccListCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_ACCID_EDIT, m_accid);
	DDX_Control(pDX, IDC_ACC_DETAIL_LIST, m_GuiDetailsListCtrl);
	DDX_Control(pDX, IDC_OPENDOWN, m_GuiOpenDownBtn);
	DDX_Control(pDX, IDC_BUTTON_REPRINT, m_GuiRePrintBtn);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_GuiPrintBtn);
}


BEGIN_MESSAGE_MAP(CSearchAccountDlg, CDialog)
	ON_BN_CLICKED(IDC_SRH_BYDATEBTN, OnSearchByDate)
	ON_BN_CLICKED(IDC_SEARCH_BYACCIDBTN, OnSearchByAccid)
	ON_NOTIFY(NM_CLICK, IDC_ACCOUNT_LIST, OnNMClickAccountList)
	ON_BN_CLICKED(IDC_BUTTON_REPRINT, OnBnClickedButtonReprint)
	ON_NOTIFY(HDN_ITEMCHANGED, 0, OnHdnItemchangedAccountList)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CSearchAccountDlg 消息处理程序

void CSearchAccountDlg::OnSearchByDate()
{
	// TODO: 在此添加控件通知处理程序代码
	Refresh();
}

void CSearchAccountDlg::OnSearchByAccid()
{
	// TODO: 在此添加控件通知处理程序代码
	Refresh2();
}

void CSearchAccountDlg::Init()
{
	m_GuiAccStatusCombo.AddString(_T("已结账"));
	m_GuiAccStatusCombo.AddString(_T("挂  账"));
	m_GuiAccStatusCombo.AddString(_T("挂账结账"));
	m_GuiAccStatusCombo.AddString(_T("退  单"));
	m_GuiAccStatusCombo.SetCurSel(0);

	int i = 0;
	m_GuiAccListCtrl.InsertColumn(i++,_T("账单号"),LVCFMT_LEFT,100);
	m_GuiAccListCtrl.InsertColumn(i++,_T("餐厅"),LVCFMT_LEFT,100);
	m_GuiAccListCtrl.InsertColumn(i++,_T("消费日期"),LVCFMT_LEFT,130);
	m_GuiAccListCtrl.InsertColumn(i++,_T("订金"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("应收账款"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("抹零"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("折扣"),LVCFMT_LEFT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("代金券"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("实收账款"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("实收现金"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("找余金额"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("会员卡"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("信用卡"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("支票"),LVCFMT_RIGHT,70);
	
	m_GuiAccListCtrl.InsertColumn(i++,_T("备注"),LVCFMT_LEFT,100);
	//m_GuiAccListCtrl.InsertColumn(i++,_T("发票"),LVCFMT_LEFT,50);
	//m_GuiAccListCtrl.InsertColumn(i++,_T("状态"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiAccListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	i = 0;
	m_GuiDetailsListCtrl.InsertColumn(i,_T("编号"),LVCFMT_LEFT,50);
	m_GuiDetailsListCtrl.InsertColumn(++i,_T("名称"),LVCFMT_LEFT,150);
	m_GuiDetailsListCtrl.InsertColumn(++i,_T("价格"),LVCFMT_RIGHT,70);
	m_GuiDetailsListCtrl.InsertColumn(++i,_T("数量"),LVCFMT_LEFT,40);
	m_GuiDetailsListCtrl.InsertColumn(++i,_T("单位"),LVCFMT_LEFT,40);
	m_GuiDetailsListCtrl.InsertColumn(++i,_T("打折"),LVCFMT_LEFT,40);
	m_GuiDetailsListCtrl.InsertColumn(++i,_T("折后价"),LVCFMT_RIGHT,50);

	m_GuiDetailsListCtrl .InsertColumn(++i,_T("厨师"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiDetailsListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

}

void CSearchAccountDlg::Refresh()
{
	//刷新账单列表
	UpdateData(true);
	int pos = m_GuiAccStatusCombo.GetCurSel();
	CString status;
	hotelMIS::HAccountVec vec;
	if ( 0 == pos ){	//已结账
		vec = m_accSearchBdy.search(m_date1.Format("%Y-%m-%d 00:00:00").GetBuffer(),
			m_date2.Format("%Y-%m-%d 23:59:59").GetBuffer(),hotelMIS::HAccount::havedAcc);
		m_exp2 = "已结账";

	}else if ( 1 == pos){ //挂账
		vec = m_accSearchBdy.search(m_date1.Format("%Y-%m-%d 00:00:00").GetBuffer(),
			m_date2.Format("%Y-%m-%d 23:59:59").GetBuffer(),hotelMIS::HAccount::gzAcc);
		m_exp2 = "挂账";
	}
	else if ( 2 == pos ){ //挂账结账
		vec = m_accSearchBdy.search(m_date1.Format("%Y-%m-%d 00:00:00").GetBuffer(),
			m_date2.Format("%Y-%m-%d 23:59:59").GetBuffer(),hotelMIS::HAccount::gzhavedAcc);
		m_exp2 ="挂账结账";
	}
	else if ( 3 == pos ){ //取消
		vec = m_accSearchBdy.search(m_date1.Format("%Y-%m-%d 00:00:00").GetBuffer(),
			m_date2.Format("%Y-%m-%d 23:59:59").GetBuffer(),hotelMIS::HAccount::cancelAcc);
		m_exp2 ="退单";
	}
	
	//统计条件打印使用
	m_exp.Format("统计日期: %s 至 %s",m_date1.Format("%Y-%m-%d").GetBuffer(),m_date2.Format("%Y-%m-%d").GetBuffer());

	int i = 0,j;
	float sscost = 0.0f,ys=0.0f;
	float xj_total = 0.0f;
	float dj_total = 0.0f;
	float mc_total = 0.0f;
	float xyk_total = 0.0f;
	float zp_total = 0.0f;


	CString t;
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	hotelMIS::HAccountVec::iterator it;
	m_GuiAccListCtrl.DeleteAllItems();
	m_accMap.clear();
	for ( it = vec.begin(); it != vec.end(); it++)
	{	
		j = 1;
		m_accMap.insert(make_pair(i,it->account_id));
		m_GuiAccListCtrl.InsertItem(i,it->account_id.c_str());
		
		t.Format("%s-%d号",roomCtrl.getRoomName(it->room_id).c_str(),it->table_id);
		m_GuiAccListCtrl.SetItemText(i,j++,t);

		m_GuiAccListCtrl.SetItemText(i,j++,it->cust_date.c_str());
		
		t.Format("%.2f",it->subscription); m_GuiAccListCtrl.SetItemText(i,j++,t);
		t.Format("%.2f",it->yscost); m_GuiAccListCtrl.SetItemText(i,j++,t);
		t.Format("%.2f",it->erase_zero); m_GuiAccListCtrl.SetItemText(i,j++,t);
		t.Format("%.2f",it->zhekou);m_GuiAccListCtrl.SetItemText(i,j++,t);
		t.Format("%.2f",it->daijin);m_GuiAccListCtrl.SetItemText(i,j++,t);
		dj_total += it->daijin;

		t.Format("%.2f",it->sscost);m_GuiAccListCtrl.SetItemText(i,j++,t);
		t.Format("%.2f",it->sj);m_GuiAccListCtrl.SetItemText(i,j++,t);
		t.Format("%.2f",it->zy);m_GuiAccListCtrl.SetItemText(i,j++,t);

		if ( it->paystatus== hotelMIS::HAccount::JSFS::mcard) //会员卡
		{	
			mc_total += it->zfprice;
			t.Format("%.2f",it->zfprice);
			m_GuiAccListCtrl.SetItemText(i,j++,t);
		}
		else
			m_GuiAccListCtrl.SetItemText(i,j++,_T("0.0"));

		if ( it->paystatus== hotelMIS::HAccount::JSFS::xycard) //信用卡
		{	
			xyk_total += it->zfprice;
			t.Format("%.2f",it->zfprice);
			m_GuiAccListCtrl.SetItemText(i,j++,t);
		}
		else
			m_GuiAccListCtrl.SetItemText(i,j++,_T("0.0"));

		if ( it->paystatus== hotelMIS::HAccount::JSFS::zp) //支票
		{	
			zp_total += it->zfprice;
			t.Format("%.2f",it->zfprice);
			m_GuiAccListCtrl.SetItemText(i,j++,t);
		}
		else
			m_GuiAccListCtrl.SetItemText(i,j++,_T("0.0"));

		m_GuiAccListCtrl.SetItemText(i,j++,it->bz.c_str()); //备注

		sscost += it->sscost;
		ys += it->yscost;

		i++;
	}

	m_GuiAccListCtrl.InsertItem(i,_T("合计"));
	
	//应收账款
	t.Format("%.2f",ys);
	m_GuiAccListCtrl.SetItemText(i,4,t);

	//代金合计
	t.Format("%.2f",dj_total);
	m_GuiAccListCtrl.SetItemText(i,7,t);

	//实收账款
	t.Format("%.2f",sscost);
	m_GuiAccListCtrl.SetItemText(i,8,t);
	
	t.Format("%.2f",mc_total);
	m_GuiAccListCtrl.SetItemText(i,11,t);
	t.Format("%.2f",xyk_total);
	m_GuiAccListCtrl.SetItemText(i,12,t);
	t.Format("%.2f",zp_total);
	m_GuiAccListCtrl.SetItemText(i,13,t);

}

void CSearchAccountDlg::Refresh2()
{	
	//刷新账单列表(按账单号查询)
	UpdateData(true);
	
	hotelMIS::HAccount acc = m_accSearchBdy.search(hotelMIS::ReplaceChar(m_accid).GetBuffer());
	m_GuiAccListCtrl.DeleteAllItems();
	int i = 0,j = 1;
	CString t;
	m_accMap.clear();
	m_accMap.insert(make_pair(i,acc.account_id));
	m_GuiAccListCtrl.InsertItem(i,acc.account_id.c_str());
	m_GuiAccListCtrl.SetItemText(i,j++,acc.cust_date.c_str());
	m_GuiAccListCtrl.SetItemText(i,j++,acc.cust_time.c_str());
	t.Format("%.2f",acc.subscription); m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.yscost); m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.erase_zero); m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.zhekou);m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.daijin);m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.sscost);m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.sj);m_GuiAccListCtrl.SetItemText(i,j++,t);
	t.Format("%.2f",acc.zy);m_GuiAccListCtrl.SetItemText(i,j++,t);

	if ( acc.paystatus== hotelMIS::HAccount::JSFS::mcard) //会员卡
		{	
			
			t.Format("%.2f",acc.zfprice);
			m_GuiAccListCtrl.SetItemText(i,j++,t);
		}
		else
			m_GuiAccListCtrl.SetItemText(i,j++,_T("0.0"));

		if ( acc.paystatus== hotelMIS::HAccount::JSFS::xycard) //信用卡
		{	
			
			t.Format("%.2f",acc.zfprice);
			m_GuiAccListCtrl.SetItemText(i,j++,t);
		}
		else
			m_GuiAccListCtrl.SetItemText(i,j++,_T("0.0"));

		if ( acc.paystatus== hotelMIS::HAccount::JSFS::zp) //支票
		{	
			
			t.Format("%.2f",acc.zfprice);
			m_GuiAccListCtrl.SetItemText(i,j++,t);
		}
		else
			m_GuiAccListCtrl.SetItemText(i,j++,_T("0.0"));
	
		t.Format("%s",acc.bz.c_str());m_GuiAccListCtrl.SetItemText(i,j++,t);
	//t.Format("%s", acc.reckoning == 1 ? _T("需要") : _T("") );m_GuiAccListCtrl.SetItemText(i,j++,t);
	
}

void CSearchAccountDlg::Refresh3()
{
	int nPos = -1;
	if ( (nPos = m_GuiAccListCtrl.GetSelectionMark()) != -1  )
	{
		string accid = m_accMap[nPos];
		hotelMIS::HAccDetailsVec vec = m_accSearchBdy.searchDetails(accid);
		hotelMIS::HAccDetailsVec::iterator it ;
		int i = 0,j;
		float p=0.0f,zkprice=0.0f;
		CString t;
		m_GuiDetailsListCtrl.DeleteAllItems();
		for ( it = vec.begin(); it != vec.end(); it++)
		{
			j = 1;
			t.Format("%d",i+1);m_GuiDetailsListCtrl.InsertItem(i,t);
			m_GuiDetailsListCtrl.SetItemText(i,j++,it->food_name.c_str());
			t.Format("%.2f",it->food_price);m_GuiDetailsListCtrl.SetItemText(i,j++,t);
			t.Format("%d",it->food_num);m_GuiDetailsListCtrl.SetItemText(i,j++,t);
			m_GuiDetailsListCtrl.SetItemText(i,j++,it->food_unit.c_str());

			t.Format("%.2f",it->zk_num);
			m_GuiDetailsListCtrl.SetItemText(i,j++,t); //打折
			zkprice += it->food_price * it->food_num * it->zk_num;
			t.Format("%.2f", it->food_price * it->food_num * it->zk_num);
			m_GuiDetailsListCtrl.SetItemText(i,j++,t); //折后价

			m_GuiDetailsListCtrl.SetItemText(i,j++,it->ck_name.c_str());
			i++;
			p = p+(it->food_price*it->food_num);
		}
		m_GuiDetailsListCtrl.InsertItem(i,_T("合计:"));
		//float ys = repDetailsCtrl.getAllPrice(accid);
		t.Format("%.2f",p);
		m_GuiDetailsListCtrl.SetItemText(i,2,t);
		t.Format("%.2f",zkprice);
		m_GuiDetailsListCtrl.SetItemText(i,6,t);
	}
}

void CSearchAccountDlg::OnNMClickAccountList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//显示详细
	/*DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiListCtrl.ScreenToClient(&point);
	int nPos ;
	if (( nPos= m_GuiListCtrl.HitTest(point)) != -1 ) {
		
	}*/
	Refresh3();

}

BOOL CSearchAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiSrhByDateBtn.SetStyleBorder(CGuiButton::STYLEXP);	
	m_GuiSrhByAccidBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiOpenDownBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiRePrintBtn.SetStyleBorder(CGuiButton::STYLEXP);
	m_GuiPrintBtn.SetStyleBorder(CGuiButton::STYLEXP);

	m_GuiSrhByDateBtn.ShowText();	
	m_GuiSrhByAccidBtn.ShowText();
	m_GuiOpenDownBtn.ShowText();
	m_GuiRePrintBtn.ShowText();
	m_GuiPrintBtn.ShowText();

	// TODO:  在此添加额外的初始化
	Init();

hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSearchAccountDlg::OnBnClickedButtonReprint()
{
	// TODO: 重新打印小票
	int nPos = -1;
	if ( (nPos = m_GuiAccListCtrl.GetSelectionMark()) != -1  )
	{
		string accid = m_accMap[nPos];

		int r = MessageBox(_T("确定要开始打印?"),_T("警告"),MB_ICONWARNING|MB_YESNO);
		if ( r != IDYES)
			return;

		CWinApp* pApp = AfxGetApp();
		CString sPrint = pApp->GetProfileString("Print","PrintBefore");
		HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //创建打印句柄
		if ( hdc != NULL){
			CDC dc;
			dc.Attach(hdc);
			DOCINFO di;
			::ZeroMemory(&di,sizeof(DOCINFO));
			di.cbSize = sizeof(DOCINFO);
			di.lpszDocName= _T("消费账单");

			dc.StartDoc(&di);
			dc.StartPage();
			PrintReport(&dc,accid);
			dc.EndPage();
			dc.EndDoc();
		}
		else{
			MessageBox(_T("打印机连接失败!"));
		}
	}
}

void CSearchAccountDlg::PrintReport(CDC *dc,string accountId)
{
		
	hotelMIS::HAccDetailsVec vec = m_accSearchBdy.searchDetails(accountId);
	hotelMIS::HAccDetailsVec::iterator it ;
	
	hotelMIS::HAccountCtrl accountCtrl(m_con.get_con());
	hotelMIS::HAccount account = accountCtrl.getAccount(accountId);

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg hotelMsg = s.getHotelMsg();

	dc->SetMapMode(MM_LOMETRIC); //设置为厘米单位
	dc->SetTextAlign(TA_LEFT);
	
	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("宋体"));
	dc->SetTextColor(RGB(0,0,0));
	pOldFont = dc->SelectObject(&font);

	int xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",30);
	int yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	yPos = -yPos;
	int col_2_w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	int col_3_w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	int col_4_w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	int lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	int restline = pApp->GetProfileInt("Settings","PrintRestLine",6);

	CString acc;
	CTime t1=CTime::GetCurrentTime();
	
	TEXTMETRIC lpMetrics;
	
	dc->GetTextMetrics(&lpMetrics);
	int fHeight = lpMetrics.tmHeight + lineHeight;
	int n = 2;
	acc.Format("%s",hotelMsg.hotelname.c_str());
	dc->TextOut(xPos,yPos,acc);
	dc->TextOut(xPos,yPos-fHeight,_T("--------------消费小票----------------"));

	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	acc.Format("%s-%d号",roomCtrl.getRoomName(account.room_id).c_str(),account.table_id);
	dc->TextOut(xPos,yPos-fHeight*n++,acc);

	acc.Format("账单号: %s ",accountId.c_str());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	acc.Format("日期: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	dc->TextOut(xPos,yPos-fHeight*5,_T("菜名"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*n,_T("单价"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*n,_T("数量"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*n++,_T("总价"));
		
	CString cnt;
	int len = 0;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//菜名
		
		cnt.Format("%.2f",it->food_price);
		
		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;

		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//单价
		cnt.Format("%d",it->food_num);
		//dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//数量
		cnt.Format("%.2f",it->food_price*it->food_num);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //总价
		
        n++;
	}
	
	cnt.Format("%.2f",account.yscost);	//应收账款
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("合计:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	n++;	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));
	

	if ( account.zhekou > 0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("折    扣:"));
		cnt.Format("%.1f ",account.zhekou*10);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	if ( account.subscription > 0)
	{
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("押    金:"));
		cnt.Format("%.2f",account.subscription);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	if ( account.daijin > 0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos-fHeight*n,_T("  代金券:"));
		dc->SetTextAlign(TA_RIGHT);
		cnt.Format("%.2f",account.daijin);
		dc->TextOut(xPos+lpMetrics.tmAveCharWidth*col_4_w,yPos - fHeight*n,cnt);
	}

	if ( account.erase_zero >0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos-fHeight*n,_T("摸零金额:"));
		dc->SetTextAlign(TA_RIGHT);
		cnt.Format("%.2f",account.erase_zero);
		dc->TextOut(xPos+lpMetrics.tmAveCharWidth*col_4_w,yPos - fHeight*n,cnt);
	}
	
	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("结算金额:"));
	cnt.Format("%.2f",account.sscost);
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	
	dc->SetTextAlign(TA_LEFT);
	if(account.sj > 0)
	{
		n++;
		dc->TextOut(xPos,yPos - fHeight*n,_T("现金支付:"));
		cnt.Format("%.2f",account.sj);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}
	
	dc->SetTextAlign(TA_LEFT);
	if(account.zfprice >0)
	{
		n++;
		if ( account.paystatus == hotelMIS::HAccount::JSFS::mcard)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("会员卡支付:"));
			cnt.Format("%.2f",account.zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
		else if(account.paystatus == hotelMIS::HAccount::JSFS::xycard)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("信用卡支付:"));
			cnt.Format("%.2f",account.zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
		else if(account.paystatus == hotelMIS::HAccount::JSFS::zp)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("支票支付:"));
			cnt.Format("%.2f",account.zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
	}
		
	
	if ( account.zy >=0){
	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("找    余:"));
	cnt.Format("%.2f",account.zy);
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}
	
	if (!account.bz.empty())
	{
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("备注: "));
		
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth+90,yPos -fHeight*n,account.bz.c_str());
		
	}

	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));

	if ( ! hotelMsg.hoteltel.empty() ){
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("订餐电话:"));
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel.c_str());
	}
	if ( ! hotelMsg.hoteltel2.empty() && ! hotelMsg.hoteltel.empty()){
	n++;
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel2.c_str());
	}
	if ( !hotelMsg.hotelhttp.empty()){
	n++;
	dc->TextOut(xPos,yPos - fHeight*n,_T("餐厅网址:"));
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hotelhttp.c_str());
	}
	
	//print space line
	n = n+restline;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);
}

void CSearchAccountDlg::OnHdnItemchangedAccountList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	
	*pResult = 0;
Refresh3();

}

void CSearchAccountDlg::OnBnClickedButtonPrint()
{
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_GuiAccListCtrl.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_GuiAccListCtrl.GetItemCount();
	PrnInfo.nTag = m_GuiAccStatusCombo.GetCurSel();
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawReport, PrnInfo);
	DlgPreView.DoModal();
}

void CSearchAccountDlg::DrawReport(CDC &memDC, PRNINFO PrnInfo)
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
	
	wsprintf(szTitle,TEXT("%s 【%s】账单报表"),m_hotelname.GetBuffer(),m_exp2.GetBuffer());
    
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

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);		//账单号			
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 22*xPix, rt1.bottom);	//消费日期
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 20*xPix, rt1.bottom);	//消费时间
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 24*xPix, rt1.bottom);	//应收账款
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 24*xPix, rt1.bottom);   //实收账款
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 24*xPix, rt1.bottom);   //代金

		rt7.SetRect(rt6.right, rt1.top, rc.right , rt1.bottom);				//备注
		/*rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);
		*///rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("账单号", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("消费日期", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("消费时间", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("应收账款", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		;
		if ( PrnInfo.nTag ==1 )
			memDC.DrawText("挂账账款", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		else
			memDC.DrawText("实收账款", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.DrawText("代金券", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("备注", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		/*memDC.DrawText("抹零", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("代金券", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("实收账款", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
		//memDC.DrawText("合计", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
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
		/*memDC.MoveTo(rt6.right, rt1.top);
    	memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);*/

		TCHAR szID[32]={0}, szDate[32]={0}, szTime[32]={0}, szYs[32]={0}, szSs[32]={0},szDj[32]={0}, szBz[255]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 22*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 20*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 24*xPix, rt1.bottom);
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 24*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 24*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top,  rc.right , rt1.bottom);	
		/*rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32); //账单号
			ListView_GetItemText(hList, i+iStart, 2, szDate, 32);//消费日期
			ListView_GetItemText(hList, i+iStart, 3, szTime, 32);//消费时间
			ListView_GetItemText(hList, i+iStart, 5, szYs, 32);//应收账款
			ListView_GetItemText(hList, i+iStart, 8, szDj, 32);//代金券
			ListView_GetItemText(hList, i+iStart, 9, szSs, 32);//实收账款
			
			ListView_GetItemText(hList, i+iStart, 15, szBz, 255);//备注

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szDate, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szTime, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szYs, &rt4, DT_CENTER | DT_VCENTER| DT_SINGLELINE);
			memDC.DrawText(szSs, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szDj, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBz, &rt7, DT_VCENTER | DT_LEFT| DT_SINGLELINE);

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
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			/*memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);*/
			
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
			/*rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;*/

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

		rt1.SetRect(nLeft, nTop, nLeft+30*xPix, nTop+fAdd);		//账单号			
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 22*xPix, rt1.bottom);	//消费日期
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 20*xPix, rt1.bottom);	//消费时间
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 24*xPix, rt1.bottom);	//应收账款
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 24*xPix, rt1.bottom);   //实收账款
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 24*xPix, rt1.bottom);   //代金

		rt7.SetRect(rt6.right, rt1.top, rc.right , rt1.bottom);				//备注
		/*rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);
		*///rt8.SetRect(rt7.right, rt1.top, rc.right, rt1.bottom);	

		memDC.DrawText("账单号", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("消费日期", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("消费时间", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("应收账款", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		;
		if ( PrnInfo.nTag ==1 )
			memDC.DrawText("挂账账款", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		else
			memDC.DrawText("实收账款", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.DrawText("代金券", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("备注", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		/*memDC.DrawText("抹零", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("代金券", &rt7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("实收账款", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
		//memDC.DrawText("合计", &rt8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
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
		/*memDC.MoveTo(rt6.right, rt1.top);
    	memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rt7.right, rt1.top);
		memDC.LineTo(rt7.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);*/

		TCHAR szID[32]={0}, szDate[32]={0}, szTime[32]={0}, szYs[32]={0}, szSs[32]={0},szDj[32]={0}, szBz[255]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft, nTop+fAdd, nLeft+30*xPix, nTop+2*fAdd);					
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 22*xPix, rt1.bottom);	
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 20*xPix, rt1.bottom);	
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 24*xPix, rt1.bottom);
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 24*xPix, rt1.bottom);
		rt6.SetRect(rt5.right, rt1.top, rt5.right + 24*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top,  rc.right , rt1.bottom);	
		/*rt6.SetRect(rt5.right, rt1.top, rt5.right + 18*xPix, rt1.bottom);
		rt7.SetRect(rt6.right, rt1.top, rt6.right + 25*xPix, rt1.bottom);
		rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);*/
		//rt8.SetRect(rt7.right, rt1.top, rc.right , rt1.bottom);	

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32); //账单号
			ListView_GetItemText(hList, i+iStart, 2, szDate, 32);//消费日期
			ListView_GetItemText(hList, i+iStart, 3, szTime, 32);//消费时间
			ListView_GetItemText(hList, i+iStart, 5, szYs, 32);//应收账款
			ListView_GetItemText(hList, i+iStart, 8, szDj, 32);//代金券
			ListView_GetItemText(hList, i+iStart, 9, szSs, 32);//实收账款
			
			ListView_GetItemText(hList, i+iStart, 15, szBz, 255);//备注

			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szDate, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szTime, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szYs, &rt4, DT_CENTER | DT_VCENTER| DT_SINGLELINE);
			memDC.DrawText(szSs, &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szDj, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBz, &rt7, DT_VCENTER | DT_LEFT| DT_SINGLELINE);

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
			memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			/*memDC.MoveTo(rt6.right, rt1.top);
			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rt7.right, rt1.top);
			memDC.LineTo(rt7.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);*/
			
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
			/*rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			rt7.top = rt1.top;
			rt7.bottom = rt1.bottom;
			rt8.top = rt1.top;
			rt8.bottom = rt1.bottom;*/

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
