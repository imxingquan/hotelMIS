// OutlookDemoDoc.cpp : implementation of the COutlookDemoDoc class
//

#include "stdafx.h"
#include "OutlookDemo.h"

#include "OutlookDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoDoc

IMPLEMENT_DYNCREATE(COutlookDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(COutlookDemoDoc, CDocument)
	//{{AFX_MSG_MAP(COutlookDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoDoc construction/destruction

COutlookDemoDoc::COutlookDemoDoc()
{
	// TODO: add one-time construction code here

}

COutlookDemoDoc::~COutlookDemoDoc()
{
}

BOOL COutlookDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutlookDemoDoc serialization

void COutlookDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoDoc diagnostics

#ifdef _DEBUG
void COutlookDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutlookDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoDoc commands
BOOL  COutlookDemoDoc::RoteCmdToAllViews(CView* pView,UINT nID,int nCode,void * pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	POSITION pos = GetFirstViewPosition();
	while ( pos != NULL){
		CView* pNextView = GetNextView(pos);
		if ( pNextView != pView){
			if ( pNextView->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
				return TRUE;
		}
	}
	return FALSE;
}