#pragma once
#include "afxwin.h"


// CCancelFoodDlg �Ի���

class CCancelFoodDlg : public CDialog
{
	DECLARE_DYNAMIC(CCancelFoodDlg)

public:
	CCancelFoodDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCancelFoodDlg();

// �Ի�������
	enum { IDD = IDD_CANCELFOOD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_GuiEditCancelNum;
	CEdit m_GuiEditCancelMsg;
	
	CString m_cancelSnum; //����ȡ��������
	int m_cancelNum;
	int m_nNum;
	CString m_cancelMsg; //ȡ��ԭ��
	afx_msg void OnBnClickedOk();
};
