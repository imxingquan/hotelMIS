//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  RepNumWarning.h
// 
// Desc: 库存量警告对话框
//
// Author:  邢泉
//
// Modified: 2006年 6月 14日
//--------------------------------------------------------------------------------------

#pragma once

#include "resource.h"
// CRepNumWarning 对话框

class CRepNumWarning : public CDialog
{
	DECLARE_DYNAMIC(CRepNumWarning)

public:
	CRepNumWarning(int food_id,BOOL tc = FALSE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRepNumWarning();

// 对话框数据
	enum { IDD = IDD_REPWARNING_DLG };
protected:
	int	m_food_id;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL m_bRepNumWarning;
	CString m_warning_msg;
	virtual BOOL OnInitDialog();
};
