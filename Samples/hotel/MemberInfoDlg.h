#pragma once


// CMemberInfoDlg �Ի���
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "KDBCon.h"

#include <map>
#include <string>
using namespace std;


class CMemberInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemberInfoDlg)

public:
	CMemberInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMemberInfoDlg();

// �Ի�������
	enum { IDD = IDD_MEMBERINFO_DIALOG };
private:
	hotelMIS::KDBCon m_con;		//��������
	
	map<int,string>  m_map;		//map<pos,bh>
	int m_nPos;

protected:
	void Init(); //��ʼ��
	void Refresh(); //ˢ���б�
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	
	CListCtrl m_GuiMemInfoList;
	CGuiButton m_GuiAddBtn;
	CGuiButton m_GuiModifyBtn;
	CGuiButton m_GuiDelBtn;
	CGuiButton m_GuiZZBtn;
	CGuiButton m_GuiCZBtn;
	CGuiButton m_GuiPrintBtn;	
	CGuiButton m_GuiBtnCancel;
public:
	static CString m_exp;
	static CString m_hotelname;
	void PrintView();
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�

	afx_msg void OnBnClickedAddmemButton();
	afx_msg void OnBnClickedModifymemButton();
	afx_msg void OnBnClickedDelmemButton();
	afx_msg void OnBnClickedZzmemButton();
	afx_msg void OnBnClickedCzmemButton();
	afx_msg void OnBnClickedPmemButton();
	afx_msg void OnNMClickMeminfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMeminfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();

};
