// Winzid.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CWinzidApp:
// �йش����ʵ�֣������ Winzid.cpp
//

class CWinzidApp : public CWinApp
{
public:
	CWinzidApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWinzidApp theApp;
