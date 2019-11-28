// RepertoryDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "RepertoryDialog.h"
//#include ".\repertorydialog.h"
#include "HMenuInfoCtrl.h"
#include "HUnitCtrl.h"
#include "HRepertoryCtrl.h"
#include "HAdminBdy.h"
// CRepertoryDialog 对话框

IMPLEMENT_DYNAMIC(CRepertoryDialog, CDialog)
CRepertoryDialog::CRepertoryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRepertoryDialog::IDD, pParent)
	, m_reId(0)
	, m_reNum(0)
	, m_rePrice(0)
	, m_reUnit(_T(""))
	, m_dateTime(COleDateTime::GetCurrentTime())
	, m_opType(0)
{
}

CRepertoryDialog::~CRepertoryDialog()
{
}

void CRepertoryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RE_ID, m_GuiComboReId);
	DDX_Control(pDX, IDC_EDIT_RE_NUM, m_GuiEditReNum);
	DDX_Control(pDX, IDC_EDIT_RE_PRICE, m_GuiEditRePrice);
	DDX_Control(pDX, IDC_COMBO_RE_UNIT, m_GuiComboReUnit);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_GuiDateTimeCtrl);
	DDX_CBIndex(pDX, IDC_COMBO_RE_ID, m_reId);
	DDX_Text(pDX, IDC_EDIT_RE_NUM, m_reNum);
	DDX_Text(pDX, IDC_EDIT_RE_PRICE, m_rePrice);
	DDX_CBString(pDX, IDC_COMBO_RE_UNIT, m_reUnit);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dateTime);
	DDX_Control(pDX, IDC_COMBO_OPTYPE, m_GuiComboOpType);
	DDX_CBIndex(pDX, IDC_COMBO_OPTYPE, m_opType);
	DDX_Control(pDX, IDOK, m_GuiOkBtn);
	DDX_Control(pDX, IDCANCEL, m_GuiCancelBtn);
}


BEGIN_MESSAGE_MAP(CRepertoryDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_RE_ID, OnCbnSelchangeComboReId)
	ON_CBN_SELCHANGE(IDC_COMBO_RE_UNIT, OnCbnSelchangeComboReUnit)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRepertoryDialog 消息处理程序

void CRepertoryDialog::OnCbnSelchangeComboReId()
{
	// TODO: 选择时改变到对照单位
	TRACE("UNIT= %s\n",m_maprep[m_GuiComboReId.GetCurSel()].second.c_str());
	//m_GuiComboReUnit.SetWindowText(m_maprep[m_GuiComboReId.GetCurSel()].second.c_str());
	m_reUnit = m_maprep[m_GuiComboReId.GetCurSel()].second.c_str();
	m_reId = m_GuiComboReId.GetCurSel();
	UpdateData(FALSE);

}

void CRepertoryDialog::OnCbnSelchangeComboReUnit()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRepertoryDialog::OnBnClickedOk()
{
	// TODO: 入库操作
	UpdateData(TRUE);
	//错误处理

	if ( m_reNum <=0 ){
		AfxMessageBox(_T("数量不能小于等于零!"));
		return;
	}
	if ( m_rePrice <=0 ){
		AfxMessageBox(_T("价格不能小于等于零!"));
		return;
	}
	

	CString date,tmp;
	hotelMIS::HRepertoryCtrl repCtrl(m_con.get_con());
	hotelMIS::HRepertory rep;
	rep.food_id = m_maprep[m_GuiComboReId.GetCurSel()].first;
	m_GuiComboReId.GetWindowText(tmp);
	rep.food_name = hotelMIS::ReplaceChar(tmp).GetBuffer();
	rep.rep_num = m_reNum;
	rep.rep_price = m_rePrice;
	rep.unit = hotelMIS::ReplaceChar(m_reUnit).GetBuffer();
	
	date.Format("%d-%d-%d",m_dateTime.GetYear(),m_dateTime.GetMonth(),m_dateTime.GetDay());
	rep.rep_date = date.GetBuffer();
	rep.ad_name = hotelMIS::HAdminBdy::_log_name;
	if ( 0 == m_opType ){ //入库操作
		rep.rep_flag = m_opType;
		tmp.Format("入库产品:%s\n数量:%d\n单价:%.2f\n确实正确单击[确定]按钮入库!",rep.food_name.c_str(),rep.rep_num,rep.rep_price);
		int result = AfxMessageBox(tmp,MB_YESNO);
		if ( IDYES == result ){
			repCtrl.insert(rep,0);
			AfxMessageBox(_T("入库成功!"));
		}
	}else{	//入库调整
		rep.rep_flag = m_opType;
		tmp.Format("调整入库::%s\n数量:%d\n单价:%.2f\n确实需要减少该产品的库存\n单击[确定]按钮调整入库!",rep.food_name.c_str(),rep.rep_num,rep.rep_price);
		int result = AfxMessageBox(tmp,MB_YESNO);
		if ( IDYES == result ){
			repCtrl.insert(rep,1);
			AfxMessageBox(_T("调整成功!"));
		}
	}
	//OnOK();
	m_reNum = 0;
	m_rePrice =0.0f;
	UpdateData(FALSE);
}



BOOL CRepertoryDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiOkBtn.ShowText();
	m_GuiCancelBtn.ShowText();
	
	// TODO:  在此添加额外的初始化

	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//op
void CRepertoryDialog::Init()
{
	//初始化界面,填充入库产品
	hotelMIS::HMenuInfoCtrl menuInfoCtrl( m_con.get_con());
	hotelMIS::HMenuInfoVec vec = menuInfoCtrl.getAllMenuInfoRep();
	hotelMIS::HMenuInfoVec::iterator it;
	int pos = 0;
	for ( it = vec.begin(); it!= vec.end(); it++)
	{
		m_GuiComboReId.AddString(it->food_name.c_str());
		m_maprep.insert(make_pair(pos,make_pair(it->food_id,it->food_unit)));
		TRACE("pos = %d,food_id = %d,food_unit=%s\n",pos,it->food_id,it->food_unit.c_str());
		pos++;
	}
	m_GuiComboReId.SetCurSel(0);
	
	//初始化单位
	hotelMIS::HUnitCtrl unitCtrl(m_con.get_con());
	hotelMIS::HUnitVec uVec = unitCtrl.getAllUnit();
	hotelMIS::HUnitVec::iterator uIt;
	for ( uIt = uVec.begin(); uIt != uVec.end(); uIt++)
	{
		m_GuiComboReUnit.AddString(uIt->getUnit_name().c_str());
	}
	m_reUnit = m_maprep[0].second.c_str();
	UpdateData(FALSE);
	//m_GuiComboReUnit.SetWindowText(m_maprep[0].second.c_str());
	m_GuiComboReUnit.EnableWindow(FALSE);

	m_GuiComboOpType.AddString(_T("入库"));
	m_GuiComboOpType.AddString(_T("入库调整"));
	m_GuiComboOpType.SetCurSel(0);
}