#pragma once

#include "resource.h"
#include "TabPageSSL.h"
// CTabPageTree 对话框

class CTabPageTree : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTabPageTree)

public:
	CTabPageTree(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabPageTree();

// 对话框数据
	enum { IDD = IDD_TABPAGE_TREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
