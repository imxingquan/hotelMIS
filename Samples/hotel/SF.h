#pragma once
#include "resource.h"

// SF �Ի���

class SF : public CDialog
{
	DECLARE_DYNAMIC(SF)

public:
	SF(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SF();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
