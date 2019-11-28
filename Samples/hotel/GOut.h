// GOut.h: interface for the CGOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOUT_H__234E6903_71D2_4F19_B70D_216CA6097D32__INCLUDED_)
#define AFX_GOUT_H__234E6903_71D2_4F19_B70D_216CA6097D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiOutLookView.h"
#include "GuiOutLookEx.h"
class CGOut : public CGuiOutLookView  
{
public:
	CGOut();
	DECLARE_DYNCREATE(CGOut)
	virtual ~CGOut();
public:
	enum TSIZE{tsize=9};
	LRESULT  OnDelMenu(WPARAM wParam,LPARAM lParam);
	
	CBitmap m_bitmap;
	CGuiOutLookEx m_tab[CGOut::tsize];
	CTreeCtrl tc;
protected:
	int InitPurview();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnRepast();
	afx_msg void OnSysparaSet();
	afx_msg void OnKindSet();
	afx_msg void OnMenuModify();
	afx_msg void OnEmpSetjob();
	afx_msg void OnFeatureManage();
	afx_msg void OnReInput();
	afx_msg void OnReOutput();
	afx_msg void OnDestine();
	afx_msg void OnDestineManage();
	afx_msg void OnAccount();
	afx_msg void OnChangetable();
	afx_msg void OnEmpAdd();
	afx_msg void OnEmpManage();
	afx_msg void OnDayReport();
	afx_msg void OnSysuserSet();
	afx_msg void OnReSearch();
	afx_msg void OnSearchAccounts();
	afx_msg void OnOtherCalc();
	afx_msg void OnOtherNotepad();
	afx_msg void OnOtherPaint();
	afx_msg void OnLesson();
	afx_msg void OnArrearageGzjz();
	afx_msg void OnCancelMenuSearch();
	afx_msg void OnMemberManage();
	afx_msg void OnMemberBirth();
	afx_msg void OnMemberCastsearch();
	afx_msg void OnMemberCz();
	afx_msg void OnMemberZz();
//	afx_msg void OnAppExit();
//	afx_msg void OnAppAbout();
};

#endif // !defined(AFX_GOUT_H__234E6903_71D2_4F19_B70D_216CA6097D32__INCLUDED_)
