#include "stdafx.h"
#include ".\mycdkey.h"

MyCdKey::MyCdKey(void)
{
}

MyCdKey::~MyCdKey(void)
{
}

BOOL MyCdKey::RegisterCdKey()
{
	CString strCdKey,strCdKey2;
	strCdKey = getKey();
	CWinApp* pWinApp = AfxGetApp();
	strCdKey2 =pWinApp->GetProfileString("Settings", "cdkey");
	if ( strCdKey == strCdKey2)
		return TRUE;
	else
		return FALSE;
	
}