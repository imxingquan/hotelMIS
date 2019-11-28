#pragma once



// CSheet
#include "page1.h"
#include "page2.h"
#include "page3.h"

class CSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheet)

public:
	CSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSheet();
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;

protected:
	DECLARE_MESSAGE_MAP()
};


