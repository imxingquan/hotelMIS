// ConfigServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CConfigServerApp:
// �йش����ʵ�֣������ ConfigServer.cpp
//

class CConfigServerApp : public CWinApp
{
public:
	CConfigServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CConfigServerApp theApp;
