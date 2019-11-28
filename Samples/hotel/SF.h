#pragma once
#include "resource.h"

// SF 对话框

class SF : public CDialog
{
	DECLARE_DYNAMIC(SF)

public:
	SF(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SF();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
