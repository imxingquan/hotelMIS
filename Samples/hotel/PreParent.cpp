// PrvParent.cpp : implementation file
//

#include "stdafx.h"
#include "PreParent.h"
#include "PreGoto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreParent dialog


CPreParent::CPreParent(CWnd* pParent /*=NULL*/)
	: CDialog(CPreParent::IDD, pParent)
{
	pPreView = NULL;
	m_OneCount = B5_ONELINE;
	m_NextCount = B5_OTHERLINE;
	m_nCount = 0;
	m_PosPage = 1;
	memset(&PrnInfo, 0, sizeof(PRNINFO));
	//{{AFX_DATA_INIT(CPreParent)
	//}}AFX_DATA_INIT
}


void CPreParent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreParent)
	DDX_Control(pDX, IDC_SDOWN, CSDown);
	DDX_Control(pDX, IDC_SUP, CSUP);
	DDX_Control(pDX, IDC_LIST1, CList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreParent, CDialog)
	//{{AFX_MSG_MAP(CPreParent)
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_COMMAND(TBTN_TOP, OnTop)
	ON_COMMAND(TBTN_PREVIOUS, OnPrevious)
	ON_COMMAND(TBTN_GOTO, OnGoto)
	ON_COMMAND(TBTN_NEXT, OnNext)
	ON_COMMAND(TBTN_LAST, OnLast)
	ON_COMMAND(TBTN_EXIT, OnExit)
	ON_COMMAND(TBTN_PRINT, OnPrint)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipText)
/////////////////////////////////////////////////////////////////////////////
// CPreParent message handlers

WNDPROC		CPreParent::wpListProc = NULL;
HWND		CPreParent::hPrvWnd = NULL;

LRESULT CALLBACK CPreParent::ListProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT	pt;
	RECT	rc;
	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		::GetCursorPos(&pt);	
		if(!IsWindow(hPrvWnd))
			break;
		::GetWindowRect(hPrvWnd, &rc);
		if(::PtInRect(&rc, pt))
		{
			::SendMessage(hPrvWnd, WM_MOUSEWHEEL, wParam, lParam);
			return 0;
		}
		break;
	}
	return CallWindowProc(wpListProc, hwnd, uMsg, wParam, lParam);
}


BOOL CPreParent::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int nID = LOWORD(wParam);
	switch(nID)
	{
	case IDOK:
		return FALSE;
	case IDCANCEL:
		return FALSE;
	}	
	return CDialog::OnCommand(wParam, lParam);
}

void CPreParent::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if(nID == SC_CLOSE)
		EndDialog(FALSE);
	CDialog::OnSysCommand(nID, lParam);
}

BOOL CPreParent::OnInitDialog() 
{

	if(m_nCount<=0)
	{
		EndDialog(FALSE);
		return FALSE;
	}
	CDialog::OnInitDialog();
	wpListProc = (WNDPROC)::SetWindowLong(CList.m_hWnd, GWL_WNDPROC, (LONG)ListProc);
	CList.MoveWindow(-1000, -1000, 10, 10, TRUE);

	m_hIcon = ::LoadIcon(AfxGetApp()->m_hInstance, (LPCTSTR)ICON_PREVIEW);
	::SetClassLong(this->m_hWnd, GCL_HICON, (LONG)m_hIcon);
	ShowWindow(SW_MAXIMIZE);

	//添加工具条
	if (!m_wndtoolbar.CreateEx(this,TBSTYLE_FLAT,  WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS ,
								CRect(4,4,0,0)) ||	!m_wndtoolbar.LoadToolBar(IDR_TOOLBAR))
	{
		MessageBox("创建工具栏失败!", "错误", MB_ICONSTOP);
		return FALSE;
	}


	m_wndtoolbar.ShowWindow(SW_SHOW);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);	
	m_wndtoolbar.GetWindowRect(&m_TbRect);
	GetWindowRect(&rcClient);

	
	SendMessage(WM_SIZE, 0, 0);

	pPreView = new CPreView;
	pPreView->Create(DLG_SYS_PREVIEW, this);
	pPreView->ShowWindow(SW_SHOW);
	CRect rcTemp;
	rcTemp.SetRect(rcClient.left, m_TbRect.Height()+2, rcClient.right, rcClient.bottom);
	pPreView->SetCallBackFun(pDrawInfo, PrnInfo);
	pPreView->MoveWindow(&rcTemp);
	hPrvWnd = pPreView->m_hWnd;

	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, FALSE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, FALSE); 
	if(m_nCount <= m_OneCount)
	{
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_GOTO, FALSE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, FALSE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, FALSE); 
	}
	else
	{
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_GOTO, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, TRUE); 
	}

	return TRUE;
}

void CPreParent::SetCallBackFun(PRINTPREVIEW pFun, PRNINFO sPrnInfo)
{
	memcpy(&PrnInfo, &sPrnInfo, sizeof(PRNINFO));
	pDrawInfo = pFun;
	m_nCount = PrnInfo.nMaxLine;

	m_nCountPage = 1;
	int m = m_nCount-m_OneCount;
	int n = m/m_NextCount;
	m_nCountPage += n;
	n = m%m_NextCount;
	if(n>0)
		m_nCountPage++;
	PrnInfo.nCountPage = m_nCountPage;
}
void CPreParent::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	GetClientRect(&rcClient);
	CRect rup;
	rup.left = 0;
	rup.top = 0;
	rup.bottom = 2;
	rup.right = rcClient.right;
	if(IsWindow(CSUP.m_hWnd))
		CSUP.MoveWindow(&rup);
	if(IsWindow(CSDown.m_hWnd))
	{
		rup.top = m_TbRect.Height();
		rup.bottom = rup.top+2;	
		CSDown.MoveWindow(&rup);
	}
	if(pPreView != NULL)
	{
		if(IsWindow(pPreView->m_hWnd))
		{
			CRect rcTemp;
			rcTemp.SetRect(rcClient.left, m_TbRect.Height()+2, rcClient.right, rcClient.bottom);
			pPreView->MoveWindow(&rcTemp);
		}
	}
}


BOOL CPreParent::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
	
	// UNICODE消息
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	//TCHAR szFullText[512];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom为工具条的HWND 
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	
	if (nID != 0) //不为分隔符
	{
		strTipText.LoadString(nID);
		strTipText = strTipText.Mid(strTipText.Find('\n',0)+1);
		
#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		}
		else
		{
			_mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			_wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
		}
		else
		{
			lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#endif
		
		*pResult = 0;
		
		// 使工具条提示窗口在最上面
		::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
					SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER); 
		return TRUE;
	}
	return TRUE;
}

void CPreParent::OnPaint() 
{
		CPaintDC dc(this); // device context for painting
		
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect; 
		GetClientRect(rect); 
		dc.FillSolidRect(rect, RGB(60,70,120)); 
		CDialog::OnPaint();
	}
}
//首页
void CPreParent::OnTop()
{
	m_PosPage = 1;
	pPreView->SetCurrentPage(m_nCountPage, m_PosPage);

	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, FALSE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, FALSE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, TRUE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, TRUE); 
	UpdatePreViewWnd();
}
//上一页
void CPreParent::OnPrevious() 
{
	m_PosPage--;
	pPreView->SetCurrentPage(m_nCountPage, m_PosPage);
	if(m_PosPage<=1)
	{
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, FALSE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, FALSE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, TRUE); 
	}
	else
	{
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, TRUE); 
	}	
	UpdatePreViewWnd();
}
//转到
void CPreParent::OnGoto() 
{
	int nPage = 1;
	int m = m_nCount-m_OneCount;
	int n = m/m_NextCount;
	nPage += n;
	n = m%m_NextCount;
	if(n>0)
		nPage++;
	CPreGoto cpg;
	cpg.nMax = nPage;
	cpg.nCurPage = m_PosPage;
	if(cpg.DoModal())
	{
		m_PosPage = cpg.nGoto;
		pPreView->SetCurrentPage(m_nCountPage, m_PosPage);
		if(m_PosPage > 1 && m_PosPage< m_nCountPage)
		{
			m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, TRUE); 
			m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, TRUE); 
			m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, TRUE); 
			m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, TRUE); 
		}
		if(m_PosPage == 1)
			OnTop();
		if(m_PosPage == m_nCountPage)
			OnLast();
	}

	UpdatePreViewWnd();
}
//下一页
void CPreParent::OnNext() 
{
	m_PosPage++;
	pPreView->SetCurrentPage(m_nCountPage, m_PosPage);

	int nSpare = 0;
	nSpare = m_nCount - m_PosPage*m_NextCount;
	if(m_PosPage <= 2)
		nSpare +=(m_NextCount - m_OneCount);

	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, TRUE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, TRUE); 

	if(nSpare>0)
	{
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, TRUE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, TRUE); 
	}
	else
	{
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, FALSE); 
		m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, FALSE); 
	}	
	UpdatePreViewWnd();
}
//尾页
void CPreParent::OnLast() 
{
	m_PosPage = m_nCountPage;
	pPreView->SetCurrentPage(m_nCountPage, m_PosPage);

	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_TOP, TRUE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_PREVIOUS, TRUE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_NEXT, FALSE); 
	m_wndtoolbar.SendMessage(TB_ENABLEBUTTON, TBTN_LAST, FALSE); 
	UpdatePreViewWnd();
}
//退出
void CPreParent::OnExit() 
{
	SendMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
}
//打印
void CPreParent::OnPrint() 
{
	pPreView->PrintDoc();
}

BOOL CPreParent::DestroyWindow() 
{
	if(IsWindow(m_wndtoolbar.m_hWnd))
		m_wndtoolbar.DestroyWindow();
	if(pPreView != NULL)
	{
		pPreView->DestroyWindow();
		delete	pPreView;
	}	

	return CDialog::DestroyWindow();
}

void CPreParent::UpdatePreViewWnd()
{
	pPreView->SendMessage(WM_PAINT, NULL, NULL);
}
