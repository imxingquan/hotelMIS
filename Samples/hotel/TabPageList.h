#pragma once

#include "resource.h"
#include "TabPageSSL.h"
// CTabPageList �Ի���

class CTabPageList : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTabPageList)

public:
	CTabPageList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabPageList();

// �Ի�������
	enum { IDD = IDD_TABPAGE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
