// CreateDB.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CCreateDBApp:
// �йش����ʵ�֣������ CreateDB.cpp
//
#include <string>
using namespace std;



class CCreateDBApp : public CWinApp
{
public:
	CCreateDBApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��
	string globaStr;
	DECLARE_MESSAGE_MAP()
};

extern CCreateDBApp theApp;
