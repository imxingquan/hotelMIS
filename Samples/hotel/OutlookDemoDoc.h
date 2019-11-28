// OutlookDemoDoc.h : interface of the COutlookDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
class COutlookDemoDoc : public CDocument
{
protected: // create from serialization only
	COutlookDemoDoc();
	DECLARE_DYNCREATE(COutlookDemoDoc)

// Attributes
public:

// Operations
public:


public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
// Implementation
public:
	virtual ~COutlookDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	BOOL RoteCmdToAllViews(CView* pView,UINT nID,int nCode,void * pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
	DECLARE_MESSAGE_MAP()
};
