#pragma once
#include "resource.h"
//�Զ���۸�
// CZdyPriceDlg �Ի���

class CZdyPriceDlg : public CDialog
{
	DECLARE_DYNAMIC(CZdyPriceDlg)

public:
	CZdyPriceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZdyPriceDlg();

// �Ի�������
	enum { IDD = IDD_ZDY_PRICE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_zdyPrice;
	afx_msg void OnBnClickedOk();
};
