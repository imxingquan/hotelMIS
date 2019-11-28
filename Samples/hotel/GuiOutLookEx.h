#pragma once

#include "GuiOutLook.h"

class CGuiOutLookEx : public CGuiOutLook
{
public:
	CGuiOutLookEx();
	DECLARE_DYNCREATE(CGuiOutLookEx)
	virtual ~CGuiOutLookEx();
	
public:
	void  SetImageList(CBitmap *pBmp, CImageList *pImageList,int cx, int nGrow, COLORREF crMask);

};
