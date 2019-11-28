// FlashDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "FlashDialog.h"
#include ".\flashdialog.h"
//#include ".\flashdialog.h"


// CFlashDialog 对话框

IMPLEMENT_DYNAMIC(CFlashDialog, CDialog)
CFlashDialog::CFlashDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashDialog::IDD, pParent)
{
	
}

CFlashDialog::~CFlashDialog()
{
}

void CFlashDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFlashDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFlashDialog 消息处理程序

void CFlashDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = dcmem.SelectObject(&m_bitmap);

	dc.BitBlt(0,0,m_cx,m_cy,&dcmem,0,0,SRCCOPY);
}

BOOL CFlashDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,"res/idcwest.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Attach(hbitmap);

	//AnimateWindow(2000,AW_BLEND);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFlashDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	m_cx = cx;
	m_cy = cy;
}



int CFlashDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	lpCreateStruct->cx = 400;
	lpCreateStruct->cy = 200;
	return 0;
}
