// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__98E93E6D_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_MAINFRM_H__98E93E6D_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiCapOutBar.h"
#include "GuiToolBarWnd.h"
#include "GuiDocbarExten.h"
#include "MenuBar.h"
#include "CoolMenu.h"
#include "GuiSplitterWnd.h"
#include "GuiStatusBar.h"
#include "GuiMiniSplitter.h"
#include "GuiMiniTool.h"
#include "GuiFrameWnd.h"
#include "GuiComboBoxExt.h"
#include "SysWarningDialog.h"
#include <vector>
using namespace std;

class CMainFrame : public CGuiFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CBitmap m_bitmap;
	CImageList m_ImageList;
// Operations
public:
	LRESULT OnDelMenu(WPARAM wParam,LPARAM lParam);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CGuiMiniTool  m_guiMiniToolLeft;
	CGuiMiniTool  m_guiMiniToolRight;
	CGuiMiniSplitter m_MiniSplitter;
	GuiCapOutBar m_CapOutBar;
	CGuiDocBarExten m_dockbar;
	CGuiComboBoxExt   m_cb;
	//CSplitterWnd m_wndSplitter;
	CSysWarningDialog *m_warningdlg;
	vector<CSysWarningDialog*> m_pWarningVec;
	CGuiSplitterWnd m_wndSplitter;
	CGuiSplitterWnd m_wndSplitter2;

	CFont m_cfont;
	bool m_b2003;
	bool m_bXp;
	void OnBack();
	void OnToday();
	void OnCalendario();
	void OnContacto();
	void OnTareas();
	void OnNotas();
	void OnEliminar();
	
	void SetMenuQX();
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void On2003();
	afx_msg void OnXP();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	const CGuiSplitterWnd& GetSplitterWnd()
	{
		return this->m_wndSplitter;
	}
	const CGuiSplitterWnd& GetSplitterWnd2()
	{
		return this->m_wndSplitter2;
	}
	int InitMenu(UINT uIDMenu);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnUpdate2003(CCmdUI *pCmdUI);
	afx_msg void OnUpdateXp(CCmdUI *pCmdUI);
	afx_msg void OnViewToolbar();
	afx_msg void OnUpdateViewToolbar(CCmdUI *pCmdUI);
	afx_msg void OnRefresh();
	void WarningDestine();
	afx_msg void OnTimer(UINT nIDEvent);
		
	afx_msg void OnClose();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__98E93E6D_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
