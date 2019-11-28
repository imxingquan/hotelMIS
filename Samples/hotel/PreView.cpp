// PreView.cpp : implementation file
//

#include "stdafx.h"
#include "PreView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreView dialog


CPreView::CPreView(CWnd* pParent /*=NULL*/)
	: CDialog(CPreView::IDD, pParent)
{
	m_CurPage = 1;
	pDrawInfo = NULL;
	//{{AFX_DATA_INIT(CPreView)
	//}}AFX_DATA_INIT
}


void CPreView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreView, CDialog)
	//{{AFX_MSG_MAP(CPreView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreView message handlers

BOOL CPreView::OnCommand(WPARAM wParam, LPARAM lParam) 
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

BOOL CPreView::OnInitDialog() 
{
	CDialog::OnInitDialog();
    ULONG	ulScrollLines;
	HDC	hdc;
	hdc = ::GetDC(::GetDesktopWindow());
	int xPix = ::GetDeviceCaps(hdc, LOGPIXELSX);
	int yPix = ::GetDeviceCaps(hdc, LOGPIXELSY);
	::ReleaseDC(::GetDesktopWindow(), hdc);

	nW = xPix*B5_W*10/254;
	nH = yPix*B5_H*10/254;
	xPt = 0;	yPt = 0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ulScrollLines, 0);
	if (ulScrollLines)
		iDeltaPerLine = WHEEL_DELTA/ulScrollLines ;
	else
		iDeltaPerLine = 0 ;
	iAccumDelta = 0;

	cBmp.LoadBitmap(BMP_BACK);
	m_brush.CreatePatternBrush(&cBmp);
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	si.cbSize = sizeof (si) ;
	si.fMask  = SIF_RANGE | SIF_PAGE ;
	si.nMin   = 0 ;
	si.nMax   = 0;
	si.nPage  = 0 ;
	xPt = 0; yPt =0;
	SetScrollInfo(SB_VERT, &si, TRUE) ;		
	SetScrollInfo(SB_HORZ, &si, TRUE) ;

	return TRUE;
}

BOOL CPreView::DestroyWindow() 
{
	m_brush.DeleteObject();
	cBmp.DeleteObject();
	cPen.DeleteObject();
	
	return CDialog::DestroyWindow();
}

void CPreView::OnPaint() 
{
	CPaintDC dc(this);

	CClientDC dlgDC(this);
 	SetWindowOrgEx(dlgDC.m_hDC, xPt, yPt, NULL);
	CDC	MemDc;
	MemDc.CreateCompatibleDC(NULL);
	CBitmap cBitmap;
 	int xP = dlgDC.GetDeviceCaps(LOGPIXELSX);
	int yP = dlgDC.GetDeviceCaps(LOGPIXELSY);

	DOUBLE xPix = (DOUBLE)xP*10/254;	//每 mm 宽度的像素
	DOUBLE yPix = (DOUBLE)yP*10/254;	//每 mm 高度的像素

	cBitmap.CreateCompatibleBitmap(&dlgDC, B5_W*xPix, B5_H*yPix);
	MemDc.SelectObject(&cBitmap);
	if(pDrawInfo!= NULL)
	{
		PrnInfo.IsPrint = FALSE;
		PrnInfo.nCurPage = m_CurPage;
		pDrawInfo(MemDc, PrnInfo);
	}
 	dlgDC.BitBlt(xP/2, yP/2, B5_W*xPix+xP/2, B5_H*yPix+yP/2, &MemDc, 0, 0, SRCCOPY);

	MemDc.DeleteDC();
	cBitmap.DeleteObject();
}

void CPreView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	GetClientRect(&WndRect);
	SetScrollbar(cx, cy);
	InvalidateRect(NULL);
	UpdateWindow();	
}

void CPreView::SetScrollbar(int cx, int cy)
{
	HDC	hdc;
	hdc = ::GetDC(::GetDesktopWindow());
	int xPix = ::GetDeviceCaps(hdc, LOGPIXELSX);
	int yPix = ::GetDeviceCaps(hdc, LOGPIXELSY);
	::ReleaseDC(::GetDesktopWindow(), hdc);

	xPt = 0;
	//设定滚动条垂直滚动范围及页面大小
	si.cbSize = sizeof (si) ;
	si.fMask  = SIF_RANGE | SIF_PAGE ;
	si.nMin   = 0;
	si.nMax   = nH+yPix;		//内容的高度
	si.nPage  = WndRect.Height();	//页面的高度
	SetScrollInfo(SB_VERT, &si, TRUE);
	si.fMask = SIF_POS;
	si.nPos   = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);

	
	//设定滚动条水平滚动范围及页面大小
	
	si.cbSize = sizeof (si);
	si.fMask  = SIF_RANGE | SIF_PAGE;
	si.nMin   = 0;
	si.nMax   = nW+xPix;			//内容的宽度
	si.nPage  = WndRect.Width();		//页面的宽度
	SetScrollInfo(SB_HORZ, &si, TRUE);
	si.fMask = SIF_POS;
	si.nPos   = 0;
	SetScrollInfo(SB_HORZ, &si, TRUE);
	xPt = yPt = 0;
}

void CPreView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	si.cbSize = sizeof (si) ;
	si.fMask  = SIF_ALL ;
	GetScrollInfo(SB_VERT, &si);

	int iVertPos = si.nPos ;
	switch(nSBCode)
	{
	case SB_TOP:
		si.nPos = si.nMin;	break;
	case SB_BOTTOM:
		si.nPos = si.nMax;	break;
	case SB_LINEUP:
		si.nPos -= 15;	break;
	case SB_LINEDOWN:
		si.nPos += 15;	break;
	case SB_PAGEUP:
		si.nPos -= si.nPage;	break;
	case SB_PAGEDOWN:
		si.nPos += si.nPage;	break;
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos; break;
	}

	si.fMask = SIF_POS ;
	SetScrollInfo(SB_VERT, &si, TRUE) ;
	GetScrollInfo(SB_VERT, &si) ;
	if(si.nPos != iVertPos)
	{
		yPt += si.nPos - iVertPos;
		ScrollWindow(0, iVertPos - si.nPos, NULL, NULL);
		UpdateWindow();
		::UpdateWindow(GetParent()->m_hWnd);
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPreView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	si.cbSize = sizeof(si);
	si.fMask  = SIF_ALL;

	GetScrollInfo(SB_HORZ, &si) ;
	int iHorzPos = si.nPos ;
	
	switch(nSBCode)
	{
	case SB_LINELEFT:
		si.nPos -= 15;			break;
	case SB_LINERIGHT:	
		si.nPos += 15;			break;
	case SB_PAGELEFT:
		si.nPos -= si.nPage;	break;
	case SB_PAGERIGHT:
		si.nPos += si.nPage;	break;
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;	break;
	}
	si.fMask = SIF_POS ;
	SetScrollInfo(SB_HORZ, &si, TRUE);
	GetScrollInfo(SB_HORZ, &si);
	
	if (si.nPos != iHorzPos)
	{
		xPt += si.nPos - iHorzPos;
		ScrollWindow(iHorzPos - si.nPos, 0, NULL, NULL);
 		UpdateWindow();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CPreView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(iDeltaPerLine != 0)
	{
		iAccumDelta += zDelta;
		while(iAccumDelta >= iDeltaPerLine)
		{               
			SendMessage(WM_VSCROLL, SB_LINEUP, 0);
			iAccumDelta -= iDeltaPerLine ;
		}
		
		while(iAccumDelta <= -iDeltaPerLine)
		{
			SendMessage(WM_VSCROLL, SB_LINEDOWN, 0) ;
			iAccumDelta += iDeltaPerLine;
		}
	}	
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

HBRUSH CPreView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brush.GetSafeHandle();
	
	return hbr;
}

void CPreView::SetCallBackFun(PRINTPREVIEW pFun, PRNINFO sPrnInfo)
{
	memcpy(&PrnInfo, &sPrnInfo, sizeof(PRNINFO));
	pDrawInfo = pFun;
	m_CountPage = PrnInfo.nCountPage;	//共多少页
	m_CurPage = PrnInfo.nCurPage;		//当前页
}

LPTSTR CPreView::GetRegistryString(HKEY hKeyClass, LPTSTR lpszSubKey, LPTSTR lpszValueName)
{
    // Local variables
    HKEY          hKey;                 // Registry key
    LPTSTR         lpszKeyValue;         // Buffer for key name
    DWORD         dwKeySize;            // Size of key value
    DWORD         dwKeyDataType;        // Type of data stored in key
    LONG          lRC;                  // Return code
	
    //  Initialize variables
    dwKeyDataType = 0;
    dwKeySize = 0;
    hKey = NULL;
	
    lRC = RegOpenKey(hKeyClass, lpszSubKey, &hKey);
    if (lRC != ERROR_SUCCESS)
    {
        return(NULL);
    }
	
    // Got key, get value.  First, get the size of the key.
    lRC = RegQueryValueEx(hKey, lpszValueName, NULL, NULL, NULL, &dwKeySize);
    if (lRC != ERROR_SUCCESS)
    {
        return(NULL);
    }
    if (dwKeySize <= 1)  // Registry will return "" if no printers installed
    {
        return(NULL);
    }
	
    lpszKeyValue = (LPTSTR)GlobalAlloc(GPTR, (++dwKeySize));
    if (lpszKeyValue == NULL)
    {
        return(NULL);
    }
	
    lRC = RegQueryValueEx(hKey, lpszValueName, NULL, &dwKeyDataType, (LPBYTE)lpszKeyValue, &dwKeySize);
    return(lpszKeyValue);
}   // End of function GetRegistryString

LPTSTR CPreView::CopyString(LPTSTR  lpszSrc)
{
    // Local variables
    LPTSTR    lpszDest;
    int       iStrLen;
	
    //  Initialize variables
    lpszDest = NULL;
	
    if (lpszSrc == NULL)
	{
        DebugMsg(__TEXT("ICMVIEW.C : CopyString : lpszSrc == NULL\r\n"));
        return(NULL);
	}
    iStrLen = ((int)(lstrlen(lpszSrc) +1) * sizeof(TCHAR));
    lpszDest = (LPTSTR)GlobalAlloc(GPTR, iStrLen);
    _tcscpy(lpszDest, lpszSrc);
    return(lpszDest);
}   // End of function CopyString

PDEVMODE CPreView::GetDefaultPrinterDevMode(LPTSTR lpszPrinterName)
{
    LONG        lDevModeSize;
    HANDLE      hDevMode;
    PDEVMODE    pDevMode = NULL;
	
	
    lDevModeSize = DocumentProperties(NULL, NULL, lpszPrinterName, NULL, NULL, 0);
    if (lDevModeSize > 0)
    {
        hDevMode = GlobalAlloc(GHND, lDevModeSize);
        pDevMode = (PDEVMODE) GlobalLock(hDevMode);
        DocumentProperties(NULL, NULL, lpszPrinterName, pDevMode, NULL, DM_OUT_BUFFER);
    }
    else
    {
        DebugMsg(__TEXT("GetDefaultPrinterDevMode:  Could not obtain printer's devmode.\r\n"));
    }
	
    return pDevMode;
}


void CPreView::DebugMsg (LPTSTR lpszMessage,...)
{
#ifdef _DEBUG
    va_list VAList;
    TCHAR   szMsgBuf[256];
	
    // Pass the variable parameters to wvsprintf to be formated.
    va_start(VAList, lpszMessage);
    wvsprintf(szMsgBuf, lpszMessage, VAList);
    va_end(VAList);
	
    ASSERT(lstrlen((LPTSTR)szMsgBuf) < MAX_DEBUG_STRING);
    OutputDebugString(szMsgBuf);
#endif
    lpszMessage = lpszMessage;  // Eliminates 'unused formal parameter' warning
}

void DebugMsgA (LPSTR lpszMessage,...)
{
#ifdef _DEBUG
    va_list VAList;
    char    szMsgBuf[256];
	
    // Pass the variable parameters to wvsprintf to be formated.
    va_start(VAList, lpszMessage);
    wvsprintfA(szMsgBuf, lpszMessage, VAList);
    va_end(VAList);
	
    ASSERT(strlen((LPSTR)szMsgBuf) < MAX_DEBUG_STRING);
    OutputDebugStringA(szMsgBuf);
#endif
    lpszMessage = lpszMessage;  // Eliminates 'unused formal parameter' warning
}


HDC CPreView::GetPrinterDC(LPTSTR lpszFriendlyName, PDEVMODE pDevMode)
{
    HDC     hDC;
    BOOL    bFreeDevMode = FALSE;


    //  Initialize variables
    hDC = NULL;

    if (lpszFriendlyName != NULL)
    {
        // Make sure that we have a devmode.
        if (NULL == pDevMode)
        {
            pDevMode = GetDefaultPrinterDevMode(lpszFriendlyName);
            bFreeDevMode = TRUE;
        }

        // Now get a DC for the printer
        hDC = CreateDC(NULL, lpszFriendlyName, NULL, pDevMode);

        // Free devmode if created in routine.
        if (bFreeDevMode)
        {
            GlobalFree((HANDLE)pDevMode);
        }
    }
    else
    {
        DebugMsg(__TEXT("GetPrinterDC:  lpszFriendlyName == NULL"));
    }

    return hDC;
}   // End of function GetPrinterDC

HDC CPreView::GetDefaultPrinterDC()
{
    HDC     hDC;
    LPTSTR  lpszPrinterName;


    //  Initialize variables
    hDC = NULL;

    lpszPrinterName = GetDefaultPrinterName();
    if (lpszPrinterName != NULL)
    {
        hDC = GetPrinterDC(lpszPrinterName, NULL);
        GlobalFree(lpszPrinterName);
    }
    else
    {
        DebugMsg(__TEXT("GetDefaultPrinterDC:  Could not obtain default printer name.\r\n"));
    }

    return hDC;
}   // End of function GetDefaultPrinterDC


LPTSTR CPreView::GetDefaultPrinterName(void)
{
    // Local variables
    LPTSTR     lpszDefaultPrinter = NULL;

    if(IS_WIN95)
    {

        lpszDefaultPrinter = GetRegistryString(HKEY_CURRENT_CONFIG,
                                               __TEXT("SYSTEM\\CurrentControlSet\\Control\\Print\\Printers"),
                                               __TEXT("Default"));
    }
    else if (IS_NT)
    {
        TCHAR szTemp[MAX_PATH];
        LPTSTR lpszTemp;

        // Get Default printer name.
        GetProfileString(__TEXT("windows"), __TEXT("device"), __TEXT(""),
                         szTemp, sizeof(szTemp));

        if (lstrlen(szTemp) == 0)
        {
            // INVARIANT:  no default printer.
            return(NULL);
        }

        // Terminate at first comma, just want printer name.
        lpszTemp = _tcschr(szTemp, ',');
        if (lpszTemp != NULL)
        {
            *lpszTemp = '\x0';
        }
        lpszDefaultPrinter = CopyString((LPTSTR)szTemp);
    }
    return(lpszDefaultPrinter);
}   // End of function GetDefaultPrinterName

void CPreView::PrintDoc()
{
	if(MessageBox("决定打印当前报表吗?", "打印提示", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) !=IDYES)
		return;
	HDC hdcPrint = GetDefaultPrinterDC();
	if(hdcPrint == NULL)
	{
		MessageBox("打印机初始化失败!", "错误", MB_ICONSTOP);
		return;
	}
	
	CDC MemDc;
	MemDc.Attach(hdcPrint);
	if(pDrawInfo!= NULL)
	{
		PrnInfo.IsPrint = TRUE;
		PrnInfo.nCurPage = m_CurPage;
		PrnInfo.nMaxLine = m_CountPage;
		pDrawInfo(MemDc, PrnInfo);
	}
	MemDc.DeleteDC();

//	PRINTDLG pd;  //该结构包含打印对话框中的所有信息
//	LPDEVMODE  lpDevMode; 
//	if(AfxGetApp()->GetPrinterDeviceDefaults(&pd)) //获得默认的打印机的信息
//	{
//	 lpDevMode=(LPDEVMODE)GlobalLock(pd.hDevMode); 
//	 if(lpDevMode)
//	 {   
//	  lpDevMode->dmPaperSize=DMPAPER_A4;    //将打印纸设置为A4
//	  lpDevMode->dmOrientation=DMORIENT_LANDSCAPE; //将打印机设置为横向打印。
//	  lpDevMode->dmPrintQuality=600   //打印分辨率为600dpi
//	 }
//	 GlobalUnlock(pd.hDevMode);
//	}

}

void CPreView::SetCurrentPage(int nCountPage, int nCurPage)
{
	m_CountPage = nCountPage;	//共多少页
	m_CurPage = nCurPage;		//当前页
}
