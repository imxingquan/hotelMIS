// Step5.cpp : 实现文件
//

#include "stdafx.h"
#include "Step5.h"
#include "HSetHotelPrintMsg.h"
#include ".\step5.h"


// CStep5 对话框

IMPLEMENT_DYNAMIC(CStep5, CPropertyPage)
CStep5::CStep5()
	: CPropertyPage(CStep5::IDD)
	, m_hotelname(_T(""))
	, m_hoteltel(_T(""))
	, m_hotelhttp(_T(""))
	, m_hoteltel2(_T(""))
	, m_xPos(0)
	, m_yPos(0)
	, m_lineHeight(0)
	, m_col2w(0)
	, m_col3w(0)
	, m_col4w(0)
	, m_fontSize(0)
	, m_restLine(6)
{
}

CStep5::~CStep5()
{
}

void CStep5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOTELNAME_EDIT, m_hotelname);
	DDX_Text(pDX, IDC_HOTELTEL_EDIT, m_hoteltel);
	DDX_Text(pDX, IDC_HOTELHTTP_EDIT, m_hotelhttp);
	DDX_Control(pDX, IDC_HOTELTEL2_EDIT, m_GuiHotelTel2Edit);
	DDX_Text(pDX, IDC_HOTELTEL2_EDIT, m_hoteltel2);
	DDX_Control(pDX, IDC_HOTELNAME_EDIT, m_GuiHotelNameEdit);
	DDX_Control(pDX, IDC_HOTELTEL_EDIT, m_GuiHotelTelEdit);
	DDX_Control(pDX, IDC_HOTELHTTP_EDIT, m_GuiHotelHttpEdit);
	DDX_Text(pDX, IDC_XPOS_EDIT, m_xPos);
	DDX_Text(pDX, IDC_YPOS_EDIT, m_yPos);
	DDX_Text(pDX, IDC_LINEHEIGHT_EDIT, m_lineHeight);
	DDX_Text(pDX, IDC_COL2W_EDIT, m_col2w);
	DDX_Text(pDX, IDC_COL3W_EDIT, m_col3w);
	DDX_Text(pDX, IDC_COL4W_EDIT, m_col4w);
	DDX_Control(pDX, IDC_XPOS_SPIN, m_GuiXPosSpin);
	DDX_Control(pDX, IDC_YPOS_SPIN, m_GuiYPosSpin);
	DDX_Control(pDX, IDC_LINEHEIGHT_SPIN, m_GuiLineHeightSpin);
	DDX_Control(pDX, IDC_COL2W_SPIN, m_GuiCol2wSpin);
	DDX_Control(pDX, IDC_COL3W_SPIN, m_GuiCol3wSpin);
	DDX_Control(pDX, IDC_COL4W_SPIN, m_GuiCol4wSpin);
	DDX_Text(pDX, IDC_FONTSIZE_EDIT, m_fontSize);
	DDX_Control(pDX, IDC_FONTSIZE_SPIN, m_GuiFontSizeSpin);
	DDX_Text(pDX, IDC_RESTLINE_EDIT, m_restLine);
}


BEGIN_MESSAGE_MAP(CStep5, CPropertyPage)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_DEFAULTVAL_BUTTON, OnBnClickedDefaultvalButton)
	ON_BN_CLICKED(IDC_DEFAULTVAL_BUTTON2, OnBnClickedDefaultvalButton2)
	ON_EN_CHANGE(IDC_HOTELNAME_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_HOTELTEL_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_HOTELTEL2_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_HOTELHTTP_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_XPOS_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_YPOS_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_LINEHEIGHT_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_FONTSIZE_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_COL2W_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_COL3W_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_COL4W_EDIT, OnEnChangeEdit)
ON_EN_CHANGE(IDC_RESTLINE_EDIT, OnEnChangeEdit)


END_MESSAGE_MAP()


// CStep5 消息处理程序

void CStep5::OnBnClickedSaveButton()
{
	// TODO: 保存设置
	/*UpdateData(true);
	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	s.Update(m_hotelname.GetBuffer(),m_hoteltel.GetBuffer(),m_hoteltel2.GetBuffer(),m_hotelhttp.GetBuffer());
	AfxMessageBox(_T("保存成功!"));*/

}

BOOL CStep5::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg msg = s.getHotelMsg();
	m_hotelname = msg.hotelname.c_str();
	m_hoteltel = msg.hoteltel.c_str();
	m_hoteltel2= msg.hoteltel2.c_str();
	m_hotelhttp = msg.hotelhttp.c_str();
	
	m_GuiXPosSpin.SetRange(1,100);
	m_GuiYPosSpin.SetRange(1,100);
	m_GuiLineHeightSpin.SetRange(0,100);
	m_GuiCol2wSpin.SetRange(0,100);
	m_GuiCol3wSpin.SetRange(0,100);
	m_GuiCol4wSpin.SetRange(0,100);
	m_GuiFontSizeSpin.SetRange(1,100);

	CWinApp* pApp = AfxGetApp();
	m_xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",30);
	m_yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	m_col2w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	m_col3w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	m_col4w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	m_lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	m_fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	m_restLine = pApp->GetProfileInt("Settings", "PrintRestLine",6);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CStep5::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
//CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
//pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK); 
	return CPropertyPage::OnSetActive();
}

//BOOL CStep5::OnWizardFinish()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	
//	return CPropertyPage::OnWizardFinish();
//}

void CStep5::OnBnClickedDefaultvalButton()
{
	// TODO: 
	m_xPos = 30;
	m_yPos = 15;
	m_col2w = 19;
	m_col3w = 25;
	m_col4w = 32;
	m_lineHeight = 8;
	m_fontSize = 26;
	UpdateData(false);

}

void CStep5::OnBnClickedDefaultvalButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_xPos = 5;
	m_yPos = 15;
	m_col2w = 16;
	m_col3w = 21;
	m_col4w = 26;
	m_lineHeight = 8;
	m_fontSize = 26;
	UpdateData(false);
}

LRESULT CStep5::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
UpdateData(true);

	/*if ( m_xPos > 50 || m_xPos < 0){
		MessageBox(_T("左上角X超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_XPOS_EDIT)->SetFocus();
		return false;
	}
	if ( m_yPos > 50 || m_yPos < 0){
		MessageBox(_T("左上角Y超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_YPOS_EDIT)->SetFocus();
		return false;
	}
	if ( m_col2w > 50 || m_col2w < 0){
		MessageBox(_T("第2列间距超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_COL2W_EDIT)->SetFocus();
		return false;
	}
	if ( m_col3w > 50 || m_col3w < 0){
		MessageBox(_T("第3列间距超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_COL3W_EDIT)->SetFocus();
		return false;
	}
	if ( m_col4w > 50 || m_col4w < 0 ){
		MessageBox(_T("第4列间距超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_COL4W_EDIT)->SetFocus();
		return false;
	}
	if ( m_lineHeight > 50 || m_lineHeight < 0){
		MessageBox(_T("行间距超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_LINEHEIGHT_EDIT)->SetFocus();
		return false;
	}
	if ( m_fontSize > 50 || m_fontSize < 1){
		MessageBox(_T("行间距超出有效范围,请重新输入"),_T("系统提示"),MB_ICONINFORMATION|MB_OK);
		GetDlgItem(IDC_FONTSIZE_EDIT)->SetFocus();
		return false;
	}*/

	
	return CPropertyPage::OnWizardNext();
}

BOOL CStep5::OnApply()
{
	// TODO: 在此添加专用代码和/或调用基类

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	s.Update(hotelMIS::ReplaceChar(m_hotelname).GetBuffer(),
		hotelMIS::ReplaceChar(m_hoteltel).GetBuffer(),
		hotelMIS::ReplaceChar(m_hoteltel2).GetBuffer(),
		hotelMIS::ReplaceChar(m_hotelhttp).GetBuffer());
	
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "PrintLeftxPos",m_xPos);
	pApp->WriteProfileInt("Settings", "PrintLeftyPos",m_yPos);
	pApp->WriteProfileInt("Settings", "PrintCol2w",m_col2w);
	pApp->WriteProfileInt("Settings", "PrintCol3w",m_col3w);
	pApp->WriteProfileInt("Settings", "PrintCol4w",m_col4w);
	pApp->WriteProfileInt("Settings", "PrintLineHeight",m_lineHeight);
	pApp->WriteProfileInt("Settings", "PrintFontSize",m_fontSize);
	pApp->WriteProfileInt("Settings", "PrintRestLine",m_restLine);
	
	SetModified(FALSE);
	
	return CPropertyPage::OnApply();
}

void CStep5::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified(TRUE);
}
