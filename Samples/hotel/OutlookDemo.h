// OutlookDemo.h : main header file for the OUTLOOKDEMO application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoApp:
// See OutlookDemo.cpp for the implementation of this class
//
#include "flashDialog.h"

class COutlookDemoApp : public CWinApp
{
public:
	COutlookDemoApp();

public:
	bool InitDbConnect();
	void CloseDbConnect();

	bool UserLogin();
	//UINT ThreadProc(LPVOID pParam);
	CFlashDialog m_flashDlg;
	CWinThread  *pThread;
public:
	
	CString ReplaceChar(CString &str)
	{
		//替换字符中的 "'" 以及
		CString strReturn("");
		TRY
		{
			if(str.GetLength()>0)
			{
				/*for ( int i = 0; i < str.GetLength(); i++)
				{
					if ( str.GetAt(i) != "'")
					strReturn+=str.GetAt(i);

				}*/
				strReturn=str;
				strReturn.TrimLeft();
				strReturn.TrimRight();

				strReturn.Replace(_T("'"),_T("''"));
				strReturn.Replace(_T("\\"),_T(""));
				TRACE(". = %d\n","'");
			}
		}
		CATCH(CException,e){
			e->ReportError();
		}
		END_CATCH
			return strReturn;
	}

	bool m_isLogin;

	virtual BOOL InitInstance();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	virtual int ExitInstance();
//	virtual BOOL InitApplication();
};
