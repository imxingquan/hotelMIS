//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  RepNumWarning.h
// 
// Desc: ���������Ի���
//
// Author:  ��Ȫ
//
// Modified: 2006�� 6�� 14��
//--------------------------------------------------------------------------------------

#pragma once

#include "resource.h"
// CRepNumWarning �Ի���

class CRepNumWarning : public CDialog
{
	DECLARE_DYNAMIC(CRepNumWarning)

public:
	CRepNumWarning(int food_id,BOOL tc = FALSE,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepNumWarning();

// �Ի�������
	enum { IDD = IDD_REPWARNING_DLG };
protected:
	int	m_food_id;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL m_bRepNumWarning;
	CString m_warning_msg;
	virtual BOOL OnInitDialog();
};
