//-----------------------------------------------------------------------//
// This is a part of the GuiLib MFC Extention.							 //	
// Modified  :  Francisco Campos										 //
// (C) 2002 Francisco Campos <www.beyondata.com> All rights reserved     //
// This code is provided "as is", with absolutely no warranty expressed  //
// or implied. Any use is at your own risk.								 //		
// You must obtain the author's consent before you can include this code //
// in a software library.												 //
// If the source code in  this file is used in any application			 //
// then acknowledgement must be made to the author of this program		 //	
// fcampos@tutopia.com													 //
//-----------------------------------------------------------------------//

// Copyright (C) 1998 by Juraj Rojko jrojko@twist.cz
// All rights reserved
//
// VBScriptEditorView.h : interface of the CGuiEditView class
//

#if !defined(AFX_VBSCRIPTEDITORVIEW_H__EDDE6D51_C472_11D1_8635_00403395B157__INCLUDED_)
#define AFX_VBSCRIPTEDITORVIEW_H__EDDE6D51_C472_11D1_8635_00403395B157__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGuiEditView : public CRichEditView
{
protected: // create from serialization only
	CGuiEditView();
	DECLARE_DYNCREATE(CGuiEditView)
		
		void Initialize();
	
	// Attributes
public:
	CVBScriptEditorDoc* GetDocument();
	
	void SetCaseSensitive(BOOL bSensitive);
	void SetChangeCase(BOOL bChange);
	
	void SetSLComment(TCHAR chComment, TCHAR chComment2 = 0);
	void SetSLComment(LPCTSTR lpszComment);
	void SetStringQuotes(LPCTSTR lpszStrQ);
	
	void AddKeywords(LPCTSTR lpszKwd);
	void AddConstants(LPCTSTR lpszKwd);
	void ClearKeywords();
	void ClearConstants();
	
	void SetKeywordColor(COLORREF clr, BOOL bBold);
	void SetConstantColor(COLORREF clr, BOOL bBold);
	void SetCommentColor(COLORREF clr, BOOL bBold);
	void SetNumberColor(COLORREF clr, BOOL bBold);
	void SetStringColor(COLORREF clr, BOOL bBold);
	
	// Operations
public:
	void FormatAll();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiEditView)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CGuiEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
	BOOL IsStringQuote(TCHAR ch);
	int IsKeyword(LPCTSTR lpszSymbol);
	int IsConstant(LPCTSTR lpszSymbol);
	
	void SetFormatRange(int nStart, int nEnd, BOOL bBold, COLORREF clr);
	void FormatTextRange(int nStart, int nEnd);
	void FormatTextLines(int nStart, int nEnd);
	void ChangeCase(int nStart, int nEnd, LPCTSTR lpszStr);
	
	
	struct SymbolColor 
	{
		COLORREF clrColor;
		BOOL bBold;
	};
	enum ChangeType {ctUndo, ctUnknown, ctReplSel, ctDelete, ctBack, ctCut, ctPaste, ctMove};
	
	BOOL m_bCaseSensitive;
	BOOL m_bChangeCase;
	TCHAR m_chComment;
	TCHAR m_chComment2;
	CString m_strComment;
	CString m_strInitComment;
	CString m_strEndComment;
	CString m_strStringQuotes;
	CString m_strKeywords;
	CString m_strKeywordsLower;
	CString m_strConstants;
	CString m_strConstantsLower;
	
	SymbolColor m_icComment;
	SymbolColor m_icNumber;
	SymbolColor m_icString;
	SymbolColor m_icKeyword;
	SymbolColor m_icConstant;
	
	BOOL m_bInForcedChange;
	ChangeType m_changeType;
	CHARRANGE m_crOldSel;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiEditView)
	afx_msg void OnChange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnProtected(NMHDR*, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in VBScriptEditorView.cpp
inline CVBScriptEditorDoc* CGuiEditView::GetDocument()
{ return (CVBScriptEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VBSCRIPTEDITORVIEW_H__EDDE6D51_C472_11D1_8635_00403395B157__INCLUDED_)
