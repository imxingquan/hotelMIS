// FlashDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "FlashDialog.h"
#include ".\flashdialog.h"
//#include ".\flashdialog.h"


// CFlashDialog �Ի���

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


// CFlashDialog ��Ϣ�������

void CFlashDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	CBitmap *pOldBmp = dcmem.SelectObject(&m_bitmap);

	dc.BitBlt(0,0,m_cx,m_cy,&dcmem,0,0,SRCCOPY);
}

BOOL CFlashDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,"res/idcwest.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Attach(hbitmap);

	//AnimateWindow(2000,AW_BLEND);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFlashDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: �ڴ˴������Ϣ����������
	m_cx = cx;
	m_cy = cy;
}



int CFlashDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	lpCreateStruct->cx = 400;
	lpCreateStruct->cy = 200;
	return 0;
}
