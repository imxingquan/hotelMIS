#pragma once

#include "resource.h"
#include "atlcomtime.h"
#include "afxcmn.h"
#include "KDBCon.h"
// CMemCZListDlg �Ի���

class CMemCZListDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemCZListDlg)

public:
	CMemCZListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMemCZListDlg();

// �Ի�������
	enum { IDD = IDD_MEM_CZLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_d1;
	COleDateTime m_d2;
	CString m_bh;
	CListCtrl m_GuiListCz;

	hotelMIS::KDBCon m_con;
public:
	void InitIdle();
	void Refresh();
public:
	//for print
	static CString m_exp;
	static CString m_hotelname;
	void PrintView();
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnEnChangeEditBh();
	afx_msg void OnBnClickedButtonPrint();
};
