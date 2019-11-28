#pragma once


// COutPutList

class COutPutList : public CListCtrl
{
	DECLARE_DYNAMIC(COutPutList)

public:
	COutPutList();
	virtual ~COutPutList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


