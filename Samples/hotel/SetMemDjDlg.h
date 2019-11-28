#pragma once
#include "afxcmn.h"
#include "resource.h"

#include "KDBCon.h"

#include <map>
#include <string>
#include "afxwin.h"
using namespace std;

// CSetMemDjDlg �Ի���

class CSetMemDjDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetMemDjDlg)

public:
	CSetMemDjDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetMemDjDlg();

// �Ի�������
	enum { IDD = IDD_SETMEMDJ_DIALOG };
//-------------------------------------------
private:
	hotelMIS::KDBCon m_con;
	map<int,int> m_map;
	bool m_isDel;
	int m_nPos;
protected:
	void Init();
	void Refresh();

//--------------------------------------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_djname;
	float m_zhekou;
	afx_msg void OnBnClickedAdddjButton();
	afx_msg void OnBnClickedMdButton();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_GuiAddBtn;
	CButton m_GuiMDBtn;
};
