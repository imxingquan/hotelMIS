#pragma once

#include "resource.h"
#include "TabPageSSL.h"
// CTabPageTree �Ի���

class CTabPageTree : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTabPageTree)

public:
	CTabPageTree(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabPageTree();

// �Ի�������
	enum { IDD = IDD_TABPAGE_TREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
