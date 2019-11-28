#include "stdafx.h"
#include "resource.h"
#include "GuiOutLookEx.h"

IMPLEMENT_DYNCREATE(CGuiOutLookEx,CGuiOutLook)

CGuiOutLookEx::CGuiOutLookEx()
{
}

CGuiOutLookEx::~CGuiOutLookEx()
{
}


void CGuiOutLookEx::SetImageList(CBitmap *pBmp, CImageList *pImageList,int cx, int nGrow, COLORREF crMask)
{
	BITMAP hbmp;
	//cbmp.LoadBitmap(nBitmapID);
	pBmp->GetBitmap(&hbmp);
	m_imageList.Create(pImageList);
	m_imageList.Add(pBmp,crMask);
	m_sizeImage=CSize(cx,hbmp.bmHeight);
}