// Winzid2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CWinzid2App:
// �йش����ʵ�֣������ Winzid2.cpp
//

class CWinzid2App : public CWinApp
{
public:
	CWinzid2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWinzid2App theApp;
