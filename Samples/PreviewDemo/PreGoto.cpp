// PreGoto.cpp : implementation file
//

#include "stdafx.h"
#include "PreGoto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreGoto dialog


CPreGoto::CPreGoto(CWnd* pParent /*=NULL*/)
	: CDialog(CPreGoto::IDD, pParent)
{
	nMax = 1;
	nGoto = 1;
	nCurPage = 1;
	//{{AFX_DATA_INIT(CPreGoto)
	vGoto = 0;
	//}}AFX_DATA_INIT
}


void CPreGoto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreGoto)
	DDX_Control(pDX, SPIN_GOTO, CSpinGoto);
	DDX_Control(pDX, EDT_GOTO, CEdtGoto);
	DDX_Text(pDX, EDT_GOTO, vGoto);
	DDV_MinMaxInt(pDX, vGoto, 1, 999999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreGoto, CDialog)
	//{{AFX_MSG_MAP(CPreGoto)
	ON_BN_CLICKED(BTN_OK, OnOk)
	ON_EN_KILLFOCUS(EDT_GOTO, OnKillfocusGoto)
	ON_BN_CLICKED(BTN_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreGoto message handlers

BOOL CPreGoto::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int nID = LOWORD(wParam);
	switch(nID)
	{
	case IDOK:
		return FALSE;
	case IDCANCEL:
		return FALSE;
	}
	return CDialog::OnCommand(wParam, lParam);
}

BOOL CPreGoto::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CSpinGoto.SetRange(1, nMax);
	CSpinGoto.SetPos(nCurPage);
	vGoto = nCurPage;
	UpdateData(FALSE);
	return TRUE ; 
}

void CPreGoto::OnOk() 
{
	UpdateData();
	UpdateData();
	if(vGoto>nMax)
		vGoto = nMax;
	if(vGoto<=0)
		vGoto = 1;

	nGoto = vGoto;
	EndDialog(TRUE);
}

void CPreGoto::OnCancel() 
{
	EndDialog(FALSE);	
}

void CPreGoto::OnKillfocusGoto() 
{
	UpdateData();
	if(vGoto>nMax)
		vGoto = nMax;
	if(vGoto<=0)
		vGoto = 1;
	UpdateData(FALSE);
}
