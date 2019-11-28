#pragma once



// CWinzid
#include "step1.h"
#include "step2.h"
#include "step3.h"

class CWinzid : public CPropertySheet
{
	DECLARE_DYNAMIC(CWinzid)

public:
	CWinzid(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWinzid(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CWinzid();
public:
	CStep1 m_step1;
	CStep2 m_step2;
	CStep3 m_step3;

protected:
	DECLARE_MESSAGE_MAP()
};


