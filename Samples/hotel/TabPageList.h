#pragma once

#include "resource.h"
#include "TabPageSSL.h"
// CTabPageList 对话框

class CTabPageList : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTabPageList)

public:
	CTabPageList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabPageList();

// 对话框数据
	enum { IDD = IDD_TABPAGE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
