#pragma once


// CMemberCastSearchDlg �Ի���
#include "resource.h"


class CMemberCastSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemberCastSearchDlg)

public:
	CMemberCastSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMemberCastSearchDlg();

// �Ի�������
	enum { IDD = IDD_MEMBERCASTSEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
