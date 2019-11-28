// SyyReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SyyReportDlg.h"
#include "HRepDetailsCtrl.h"
#include "PrintReportSyy.h"
#include "HArrerageCtrl.h"
#include "XFDetailsDlg.h"
#include <math.h>

// CSyyReportDlg 对话框

IMPLEMENT_DYNAMIC(CSyyReportDlg, CDialog)
CSyyReportDlg::CSyyReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSyyReportDlg::IDD, pParent)
	, m_date1(COleDateTime::GetCurrentTime())
	, m_date2(COleDateTime::GetCurrentTime())
	
	,m_acc_status(_T(""))
	,m_exp(_T(""))
	, m_cwCheck(FALSE)
	, m_jsfs(0)
{
	m_time2.ParseDateTime(_T("23:59:59"));
}

CSyyReportDlg::~CSyyReportDlg()
{
}

void CSyyReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Control(pDX, IDC_ACCSTATUS_COMBO, m_GuiAccStatusCombo);
	DDX_Control(pDX, IDC_ACCOUNT_LIST, m_GuiAccListCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER5, m_time1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_time2);
	DDX_Control(pDX, IDC_DW_COMBO, m_dwCombo);
	DDX_Check(pDX, IDC_CHECK1, m_cwCheck);
	DDX_Control(pDX, IDC_COMBO1, m_GuiJsfsCombo);
	DDX_CBIndex(pDX, IDC_COMBO1, m_jsfs);
}


BEGIN_MESSAGE_MAP(CSyyReportDlg, CDialog)
	ON_BN_CLICKED(IDC_SRH_BYDATEBTN, OnBnClickedSrhBydatebtn)
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnBnClickedPrintButton)
	ON_COMMAND(ID_EXACT_EXCEL, OnExactExcel)
	ON_COMMAND(ID_PRINT_PREVIEW, OnPrintPreview)
	ON_COMMAND(ID_POPUP_PRINT, OnPopupPrint)
	ON_NOTIFY(NM_DBLCLK, IDC_ACCOUNT_LIST, OnNMDblclkAccountList)

	ON_CBN_SELCHANGE(IDC_ACCSTATUS_COMBO, OnCbnSelchangeAccstatusCombo)
	ON_CBN_SELCHANGE(IDC_DW_COMBO, OnCbnSelchangeDwCombo)
END_MESSAGE_MAP()


// CSyyReportDlg 消息处理程序


BOOL CSyyReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

		
	m_GuiAccStatusCombo.AddString(_T("已结账"));
	m_GuiAccStatusCombo.AddString(_T("挂  账"));
	m_GuiAccStatusCombo.AddString(_T("挂账结账"));
	m_GuiAccStatusCombo.AddString(_T("退  单"));
	m_GuiAccStatusCombo.SetCurSel(0);

	m_GuiJsfsCombo.AddString(_T("  无  "));
	m_GuiJsfsCombo.AddString(_T("现  金"));
	m_GuiJsfsCombo.AddString(_T("会员卡"));	
	m_GuiJsfsCombo.AddString(_T("信用卡"));
	m_GuiJsfsCombo.AddString(_T("支  票"));
	m_GuiJsfsCombo.AddString(_T("代金券"));
	m_GuiJsfsCombo.SetCurSel(0);

	int i = 0;
	m_GuiAccListCtrl.InsertColumn(i++,_T("账单号"),LVCFMT_LEFT,100);
	m_GuiAccListCtrl.InsertColumn(i++,_T("台号"),LVCFMT_LEFT,100);
	m_GuiAccListCtrl.InsertColumn(i++,_T("应收账款"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("食物"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("饮料"),LVCFMT_RIGHT,60);	
	m_GuiAccListCtrl.InsertColumn(i++,_T("酒类"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("香烟"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T(" 茶 "),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("杂项"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("服务费"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("实收总计"),LVCFMT_RIGHT,70);
	m_GuiAccListCtrl.InsertColumn(i++,_T("优惠金额"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("现金"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("代金券"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("会员卡"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("信用卡"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("支票"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("抹零"),LVCFMT_RIGHT,60);
	m_GuiAccListCtrl.InsertColumn(i++,_T("备注"),LVCFMT_LEFT,100);
	//m_GuiAccListCtrl.InsertColumn(i++,_T("发票"),LVCFMT_LEFT,50);
	//m_GuiAccListCtrl.InsertColumn(i++,_T("状态"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_GuiAccListCtrl.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//初始化挂账单位
	hotelMIS::HArrerageZHCtrl hArrZHCtrl(m_con.get_con());
	hotelMIS::HArrerageZHVec zhVec = hArrZHCtrl.getAll();
	hotelMIS::HArrerageZHVec::iterator it;
	int pos =m_dwCombo.AddString(_T("无"));
	m_dwCombo.SetItemData(pos,0);
	for(it = zhVec.begin(); it!= zhVec.end(); it++)
	{
		pos = m_dwCombo.AddString(it->guest_name.c_str());
		m_dwCombo.SetItemData(pos,it->arid);
	}
	m_dwCombo.SetCurSel(0);
	return TRUE;
}

void CSyyReportDlg::OnBnClickedSrhBydatebtn()
{
	//刷新账单列表
	UpdateData(true);
	int pos = m_GuiAccStatusCombo.GetCurSel();
	CString status;
	
	CString dt1,dt2;
	dt1= m_date1.Format("%Y-%m-%d ") + m_time1.Format("%H:%M:%S");
	dt2 = m_date2.Format("%Y-%m-%d ") + m_time2.Format("%H:%M:%S");
	int arid= m_dwCombo.GetItemData(m_dwCombo.GetCurSel());
	if ( 0 == pos ){	//已结账
		m_vec = m_accSearchBdy.search(dt1.GetBuffer(),
			dt2.GetBuffer(),hotelMIS::HAccount::havedAcc,arid,m_cwCheck,m_jsfs);
		m_acc_status = "已结账";

	}else if ( 1 == pos){ //挂账
		m_vec = m_accSearchBdy.search(dt1.GetBuffer(),
			dt2.GetBuffer(),hotelMIS::HAccount::gzAcc,arid,m_cwCheck,m_jsfs);
		m_acc_status = "挂账";
	}else if ( 2 == pos ){ //挂账结账
		m_vec = m_accSearchBdy.search(dt1.GetBuffer(),
			dt2.GetBuffer(),hotelMIS::HAccount::gzhavedAcc,arid,m_cwCheck,m_jsfs);
		m_acc_status ="挂账结账";
	}
	else if ( 3 == pos ){ //取消
		m_vec = m_accSearchBdy.search(dt1.GetBuffer(),
			dt2.GetBuffer(),hotelMIS::HAccount::cancelAcc,arid,m_cwCheck,m_jsfs);
		m_acc_status ="退单";
	}
	
	m_exp.Format("%s 至 %s",dt1,dt2);
	//统计条件打印使用
	//m_exp.Format("统计日期: %s 至 %s",m_date1.Format("%Y-%m-%d").GetBuffer(),m_date2.Format("%Y-%m-%d").GetBuffer());

	int i = 0,j=0;

	CString t;
	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	hotelMIS::HAccDetailsCtrl accDetailsCtrl(m_con.get_con());
	hotelMIS::HAccDetailsVec detailsVec;
	hotelMIS::HAccDetailsVec::iterator detailsIt;

	hotelMIS::HAccountVec::iterator it;
	m_GuiAccListCtrl.DeleteAllItems();
	m_accMap.clear();
	float shiwu_total=0.0f;			//食物合计
	float yingliao_total=0.0f;		//饮料合计
	float jiulei_total=0.0f;		//酒类合计     
	float xiangyan_total=0.0f;		//香烟合计
	float tea_total = 0.0f;			//茶合计
	float zaxiang_total=0.0f;		//杂项合计
	float fuwufei_total=0.0f;		//服务费合计
	float zongji_total=0.0f;		//总计

	float xj_total = 0.0f;			//现金合计
	float dj_total = 0.0f;			//定金合计
	float mc_total = 0.0f;			//会员卡合计
	float xyk_total = 0.0f;			//信用卡合计
	float zp_total = 0.0f;			//支票合计
	float ml_total = 0.0f;			//抹零合计
	float yscost_total=0.0f;		//应收总计
	float yh_total =0.0f;			//优惠总计

	for ( it = m_vec.begin(); it != m_vec.end(); it++)
	{	
		j = 1;
		
		float shiwu=0.0f;			//食物
		float yingliao=0.0f;		//饮料
		float jiulei=0.0f;			//酒类
		float xiangyan=0.0f;		//香烟
		float tea=0.0f;				//茶
		float zaxiang=0.0f;			//杂项
		float fuwufei=0.0f;			//服务费
		float zongji=0.0f;			//总计
		
		m_accMap.insert(make_pair(i,it->account_id)); //帐单号
		m_GuiAccListCtrl.InsertItem(i,it->account_id.c_str());
		
		t.Format("%s-%d号",roomCtrl.getRoomName(it->room_id).c_str(),it->table_id);
		m_GuiAccListCtrl.SetItemText(i,j++,t); //桌号

		t.Format("%.2f",it->yscost);
		m_GuiAccListCtrl.SetItemText(i,j++,t); //应收账款

		yscost_total += it->yscost; //应收账款合计


		detailsVec = accDetailsCtrl.getAccDetails(it->account_id);
		for(detailsIt = detailsVec.begin(); detailsIt != detailsVec.end(); detailsIt++)
		{			
			
			if (detailsIt->total_fl== 1)
			{
				
				shiwu+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
				
			}
			else if(detailsIt->total_fl==  2)
			{
				yingliao+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
			}
			else if(detailsIt->total_fl== 3)
			{
				jiulei+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
			}
			else if(detailsIt->total_fl == 4)
			{
				xiangyan+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
			}
			else if(detailsIt->total_fl== 5)
			{
				zaxiang+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
			}
			else if(detailsIt->total_fl== 6)
			{
				fuwufei+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
			}
			else if(detailsIt->total_fl== 7)
			{
				tea+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;
				
			}
			
		
		}
		if(it->sswr==1)
		{
			shiwu = myRound(shiwu);
			yingliao = myRound(yingliao);
			jiulei = myRound(jiulei);
			xiangyan = myRound(xiangyan);
			tea = myRound(tea);
			zaxiang = myRound(zaxiang);
			fuwufei = myRound(fuwufei);

		}
		zongji += shiwu+yingliao+jiulei+xiangyan+tea+zaxiang+fuwufei;
		shiwu_total += shiwu;
		yingliao_total += yingliao;
		jiulei_total+= jiulei;
		xiangyan_total+= xiangyan;
		tea_total += tea;
		zaxiang_total+=zaxiang;
		fuwufei_total+= fuwufei;
		zongji_total += zongji;

		t.Format("%.2f",shiwu);m_GuiAccListCtrl.SetItemText(i,j++,t); //食物
		t.Format("%.2f",yingliao);m_GuiAccListCtrl.SetItemText(i,j++,t);//饮料
		t.Format("%.2f",jiulei);m_GuiAccListCtrl.SetItemText(i,j++,t);//酒类
		t.Format("%.2f",xiangyan);m_GuiAccListCtrl.SetItemText(i,j++,t);//香烟
		t.Format("%.2f",tea);m_GuiAccListCtrl.SetItemText(i,j++,t);//茶
		t.Format("%.2f",zaxiang);m_GuiAccListCtrl.SetItemText(i,j++,t);//杂项
		t.Format("%.2f",fuwufei);m_GuiAccListCtrl.SetItemText(i,j++,t);//服务费
		t.Format("%.2f",zongji);m_GuiAccListCtrl.SetItemText(i,j++,t);//总计
		t.Format("%.2f",it->yscost-zongji);m_GuiAccListCtrl.SetItemText(i,j++,t);//优惠金额
		yh_total += it->yscost-zongji; //优惠总计
		//
		float xj = it->sj - it->zy;
		if ( it->sswr == 1) xj = myRound(xj);
		xj_total += xj;
		t.Format("%.2f",xj);m_GuiAccListCtrl.SetItemText(i,j++,t);//现金=现金支付-找余
		dj_total += it->daijin;
		t.Format("%.2f",it->daijin);m_GuiAccListCtrl.SetItemText(i,j++,t); //代金券


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

		ml_total += it->erase_zero;
		t.Format("%.2f",it->erase_zero);
		m_GuiAccListCtrl.SetItemText(i,j++,t);
		m_GuiAccListCtrl.SetItemText(i,j++,it->bz.c_str()); //备注
		i++;
	}


	j=2;
	m_GuiAccListCtrl.InsertItem(i,_T("合计"));
	t.Format("%.2f",yscost_total);m_GuiAccListCtrl.SetItemText(i,j++,t); //应收账款合计
	t.Format("%.2f",shiwu_total);m_GuiAccListCtrl.SetItemText(i,j++,t); //食物合计
	t.Format("%.2f",yingliao_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//饮料合计
	t.Format("%.2f",jiulei_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//酒类合计
	t.Format("%.2f",xiangyan_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//香烟合计
	t.Format("%.2f",tea_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//茶合计
	t.Format("%.2f",zaxiang_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//杂项合计
	t.Format("%.2f",fuwufei_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//服务费合计
	t.Format("%.2f",zongji_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//实收总计
	t.Format("%.2f",yh_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//优惠总计

	t.Format("%.2f",xj_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//现金合计
	t.Format("%.2f",dj_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//代金券合计
	t.Format("%.2f",mc_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//会员卡合计
	t.Format("%.2f",xyk_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//信用卡合计
	t.Format("%.2f",zp_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//支票合计
	t.Format("%.2f",ml_total);m_GuiAccListCtrl.SetItemText(i,j++,t);//抹零合计

}
void CSyyReportDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	//m_GuiAccListCtrl.SetWindowPos(this,-1,-1,pRect->right,pRect->bottom,1);
}

void CSyyReportDlg::OnBnClickedPrintButton()
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));

	CMenu m_popupMenu;
	m_popupMenu.LoadMenu(IDR_PRINT_MENU);
	m_popupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

}

void CSyyReportDlg::OnExactExcel()
{
		hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	CString dwmc="";
	m_dwCombo.GetLBText(m_dwCombo.GetCurSel(),dwmc);
	PrintReportSyy print(m_vec,m_acc_status.GetBuffer(),m_exp.GetBuffer(),msg.hotelname,dwmc.GetBuffer(),m_jsfs);
	if ( print.CreateExcel() == true){
		print.SetExcelVisible(false);
		print.LoadTemplate("\\tmpl\\ReportSsy.xlt");
		print.SendExcel();
		
		TCHAR szFilters[]=_T("Excel File(*.xls)|*.xls");
		CFileDialog dlg(FALSE,_T("xls"),_T("收银分类报表"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilters);
		if ( dlg.DoModal() == IDOK)
		{
			print.SaveAs(dlg.GetPathName());
		}
		print.Close();
	}

}

void CSyyReportDlg::OnPrintPreview()
{
	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();

	CString dwmc="";
	m_dwCombo.GetLBText(m_dwCombo.GetCurSel(),dwmc);
	PrintReportSyy print(m_vec,m_acc_status.GetBuffer(),m_exp.GetBuffer(),msg.hotelname,dwmc.GetBuffer(),m_jsfs);
	if ( print.CreateExcel() == true){
		print.LoadTemplate("\\tmpl\\ReportSsy.xlt");
		print.SendExcel();
		
		//print.SetExcelVisible(true);
		print.PrintPreview();
		print.Close();
	}
}

void CSyyReportDlg::OnPopupPrint()
{

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();

	CString dwmc="";
	m_dwCombo.GetLBText(m_dwCombo.GetCurSel(),dwmc);
	PrintReportSyy print(m_vec,m_acc_status.GetBuffer(),m_exp.GetBuffer(),msg.hotelname,dwmc.GetBuffer(),m_jsfs);
	if ( print.CreateExcel() == true){
		print.LoadTemplate("\\tmpl\\ReportSsy.xlt");
		print.SendExcel();
		
		//print.SetExcelVisible(true);
		print.Print();
		print.Close();
	}
}

void CSyyReportDlg::OnNMDblclkAccountList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;

	int nPos = -1;
	if ( (nPos = m_GuiAccListCtrl.GetSelectionMark()) != -1  )
	{
		string accid = m_accMap[nPos];
		CXFDetailsDlg dlg(this,accid.c_str());
		dlg.DoModal();
	}
}



void CSyyReportDlg::OnCbnSelchangeAccstatusCombo()
{
	m_GuiJsfsCombo.EnableWindow(m_GuiAccStatusCombo.GetCurSel() == 0);

}

void CSyyReportDlg::OnCbnSelchangeDwCombo()
{
	GetDlgItem(IDC_CHECK1)->EnableWindow(m_dwCombo.GetCurSel() == 0);
}

float CSyyReportDlg::myRound(float x)
{
	if((int)x*10+5 > (int)(x*10))
		return floor(x);
	else
		return ceil(x);
}