// Step6.cpp : 实现文件
//

#include "stdafx.h"
#include "Step6.h"
#include <winspool.h>
#include ".\step6.h"
// CStep6 对话框

IMPLEMENT_DYNAMIC(CStep6, CPropertyPage)
CStep6::CStep6()
: CPropertyPage(CStep6::IDD)
, m_sPrintBefore(_T(""))
, m_sPrintBehind(_T(""))
, m_sPrintMianDian(_T(""))
, m_sPrintLiangCai(_T(""))
, m_sPrintReCai(_T(""))
, m_bMianDian(FALSE)
, m_bLiangCai(FALSE)
, m_bReCai(FALSE)
, m_bFenchu(FALSE)
{
}

CStep6::~CStep6()
{
}

void CStep6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BEFORE, m_GuiComboBefore);
	DDX_Control(pDX, IDC_COMBO_BEHIND, m_GuiComboBehind);
	DDX_Control(pDX, IDC_COMBO_BIANDIAN, m_GuiComboMiandian);
	DDX_Control(pDX, IDC_COMBO_LIANGCAI, m_GuiComboLiangCai);
	DDX_Control(pDX, IDC_COMBO_RECAI, m_GuiComboRerCai);
	DDX_CBString(pDX, IDC_COMBO_BEFORE, m_sPrintBefore);
	DDX_CBString(pDX, IDC_COMBO_BEHIND, m_sPrintBehind);
	DDX_CBString(pDX, IDC_COMBO_BIANDIAN, m_sPrintMianDian);
	DDX_CBString(pDX, IDC_COMBO_LIANGCAI, m_sPrintLiangCai);
	DDX_CBString(pDX, IDC_COMBO_RECAI, m_sPrintReCai);
	DDX_Control(pDX, IDC_CHECK_MIANDIAN, m_GuiCheckMianDian);
	DDX_Control(pDX, IDC_CHECK_LIANGCAI, m_GuiCheckLiangCai);
	DDX_Control(pDX, IDC_CHECK_RECAI, m_GuiCheckReCai);
	DDX_Check(pDX, IDC_CHECK_MIANDIAN, m_bMianDian);
	DDX_Check(pDX, IDC_CHECK_LIANGCAI, m_bLiangCai);
	DDX_Check(pDX, IDC_CHECK_RECAI, m_bReCai);
}


BEGIN_MESSAGE_MAP(CStep6, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_MIANDIAN, OnBnClickedCheckMiandian)
	ON_BN_CLICKED(IDC_CHECK_LIANGCAI, OnBnClickedCheckLiangcai)
	ON_BN_CLICKED(IDC_CHECK_RECAI, OnBnClickedCheckRecai)
	ON_CBN_SELCHANGE(IDC_COMBO_BEFORE, OnCbnSelchangeComboBefore)
	ON_CBN_SELCHANGE(IDC_COMBO_BEHIND, OnCbnSelchangeComboBefore)
	ON_CBN_SELCHANGE(IDC_COMBO_BIANDIAN, OnCbnSelchangeComboBefore)
	ON_CBN_SELCHANGE(IDC_COMBO_LIANGCAI, OnCbnSelchangeComboBefore)
	ON_CBN_SELCHANGE(IDC_COMBO_RECAI, OnCbnSelchangeComboBefore)	
END_MESSAGE_MAP()


// CStep6 消息处理程序
void CStep6::GetPrint()
{
	TRY{

	DWORD  dwNeeded, dwReturned ;

	HDC    hdc ;

	PRINTER_INFO_4 * pinfo4 ;

	PRINTER_INFO_5 * pinfo5 ;
	
	int i=0;

	if (GetVersion () & 0x80000000)      // Windows 98
	{

		EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 5, NULL,

			0, &dwNeeded, &dwReturned) ;

		pinfo5 =(PRINTER_INFO_5 *) malloc (dwNeeded) ;

		EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 5, (PBYTE) pinfo5,

			dwNeeded, &dwNeeded, &dwReturned) ;
		m_map.clear();
		int pos = 0;
		for (i = 0 ; i < dwReturned ; i++)
		{
			
			pos = m_GuiComboBefore.AddString(pinfo5[i].pPrinterName);
			m_GuiComboBehind.AddString(pinfo5[i].pPrinterName);
			m_GuiComboMiandian.AddString(pinfo5[i].pPrinterName);
			m_GuiComboLiangCai.AddString(pinfo5[i].pPrinterName);
			m_GuiComboRerCai.AddString(pinfo5[i].pPrinterName);
			m_map.insert(make_pair(pinfo5[i].pPrinterName,pos));
			pos++;
		}

		free (pinfo5) ;


	}
	else  //Windows NT	
	{

		
		EnumPrinters (PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL, 4, NULL,
			0, &dwNeeded, &dwReturned) ;

		pinfo4 = (PRINTER_INFO_4 *)malloc (dwNeeded) ;
		 EnumPrinters (PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL, 4, (PBYTE) pinfo4,
			dwNeeded, &dwNeeded, &dwReturned) ;
		
		int pos = 0;
		m_map.clear();
		for (i = 0 ; i < dwReturned ; i++)
		{

			pos = m_GuiComboBefore.AddString(pinfo4[i].pPrinterName);
			m_GuiComboBehind.AddString(pinfo4[i].pPrinterName);
			m_GuiComboMiandian.AddString(pinfo4[i].pPrinterName);
			m_GuiComboLiangCai.AddString(pinfo4[i].pPrinterName);
			m_GuiComboRerCai.AddString(pinfo4[i].pPrinterName);
			m_map.insert(make_pair(pinfo4[i].pPrinterName,pos));
			pos++;

		}

		free (pinfo4) ;
		

	}


	}CATCH(CException,e)
	{
		e->ReportError();
	}
	END_CATCH

	
	

}
BOOL CStep6::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
//CPropertySheet* pParent=(CPropertySheet*)GetParent(); 
//pParent->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK); 


	return CPropertyPage::OnSetActive();
}

BOOL CStep6::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CStep6::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  填充打印机


	GetPrint();	
	
	Init();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CStep6::Init()
{
	CWinApp* pApp = AfxGetApp();
	CString print;
	print = pApp->GetProfileString("Print","PrintBefore");
	m_GuiComboBefore.SetCurSel(m_map[print.GetBuffer()]);
	
	print =pApp->GetProfileString("Print","PrintBehind");
	m_GuiComboBehind.SetCurSel(m_map[print.GetBuffer()]);
	BOOL bFenchu= pApp->GetProfileInt("Print","bFenchu",0);
	m_GuiComboBehind.EnableWindow(!bFenchu);
	if ( bFenchu)
	{
		print =pApp->GetProfileString("Print","PrintLiangCai");
		m_GuiComboLiangCai.SetCurSel(m_map[print.GetBuffer()]);
		m_bLiangCai = pApp->GetProfileInt("Print","bLiangCai",0);
		m_GuiComboLiangCai.EnableWindow(m_bLiangCai);


		print =pApp->GetProfileString("Print","PrintMianDian");
		m_GuiComboMiandian.SetCurSel(m_map[print.GetBuffer()]);
		m_bMianDian = pApp->GetProfileInt("Print","bMianDian",0);
		m_GuiComboMiandian.EnableWindow(m_bMianDian);

		print =pApp->GetProfileString("Print","PrintReCai");
		m_GuiComboRerCai.SetCurSel(m_map[print.GetBuffer()]);
		m_bReCai = pApp->GetProfileInt("Print","bReCai",0);
		m_GuiComboRerCai.EnableWindow(m_bReCai);
	}
	else{
		m_GuiComboLiangCai.EnableWindow(false);
		m_GuiComboMiandian.EnableWindow(false);
		m_GuiComboRerCai.EnableWindow(false);
	}
	

	UpdateData(false);
}

void CStep6::CheckBehind()
{
	UpdateData(true);
	if ( m_bLiangCai || m_bMianDian || m_bReCai )
	{
		m_GuiComboBehind.EnableWindow(false);
		m_bFenchu = TRUE;
	}
	else
	{
		m_GuiComboBehind.EnableWindow(true);
		m_bFenchu = FALSE;
	}

}

void CStep6::OnBnClickedCheckMiandian()
{
	// TODO: 启用关闭面点打印
	CheckBehind();
	
	m_GuiComboMiandian.EnableWindow(m_bMianDian);

}

void CStep6::OnBnClickedCheckLiangcai()
{
	// TODO: 启用关闭凉菜打印
	CheckBehind();

	m_GuiComboLiangCai.EnableWindow(m_bLiangCai);
}

void CStep6::OnBnClickedCheckRecai()
{
	// TODO: 启用关闭热菜打印
	CheckBehind();

	m_GuiComboRerCai.EnableWindow(m_bReCai);

}

BOOL CStep6::OnApply()
{
	UpdateData(true);

	
	if (m_sPrintBefore.Trim().GetLength() <=0 )
	{
		MessageBox("请设置前台打印机!");
		m_GuiComboBefore.GetFocus();
		return false;
	}
	
	if ( !m_bFenchu &&  m_sPrintBehind.Trim().GetLength() <= 0)
	{
		MessageBox("请设置后厨打印机!");
		m_GuiComboBehind.GetFocus();
		return false;
	}
	
	if ( m_bMianDian && m_sPrintMianDian.Trim().GetLength() <=0)
	{
		MessageBox("请设置面点厨房打印机!");
		m_GuiComboMiandian.GetFocus();
		return false;
	}

	if ( m_bLiangCai && m_sPrintLiangCai.Trim().GetLength() <=0)
	{
		MessageBox("请设置凉菜厨房打印机!");
		m_GuiComboLiangCai.GetFocus();
		return false;
	}

	if ( m_bReCai && m_sPrintReCai.Trim().GetLength() <=0)
	{
		MessageBox("请设置执菜厨房打印机!");
		m_GuiComboRerCai.GetFocus();
		return false;
	}

	//写入注册表
    CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString("Print","PrintBefore",m_sPrintBefore.Trim());
	pApp->WriteProfileString("Print","PrintBehind",m_sPrintBehind.Trim());
	pApp->WriteProfileInt("Print","bFenchu",m_bFenchu);
	pApp->WriteProfileInt("Print","bMianDian",m_bMianDian);
	pApp->WriteProfileString("Print","PrintMianDian",m_sPrintMianDian.Trim());
	pApp->WriteProfileInt("Print","bLiangCai",m_bLiangCai);
	pApp->WriteProfileString("Print","PrintLiangCai",m_sPrintLiangCai.Trim());
	pApp->WriteProfileInt("Print","bReCai",m_bReCai);
	pApp->WriteProfileString("Print","PrintReCai",m_sPrintReCai.Trim());

	SetModified(FALSE);
	return CPropertyPage::OnApply();
}

void CStep6::OnCbnSelchangeComboBefore()
{
		SetModified(TRUE);
}

