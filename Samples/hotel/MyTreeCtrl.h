#pragma once


// CMyTreeCtrl

class CMyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyTreeCtrl)

public:
	CMyTreeCtrl();
	virtual ~CMyTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


