#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "MyTreeCtrl.h"
#include "KDBCon.h"
#include "HMenuInfoCtrl.h"

#include "HInOutRep.h"

#include <string>
#include <map>
#include <list>
using namespace std;

// COutRegDlg �Ի���

class COutRegDlg : public CDialog
{
	DECLARE_DYNAMIC(COutRegDlg)

public:
	COutRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COutRegDlg();

// �Ի�������
	enum { IDD = IDD_OUTREP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiEdit m_GuiEditPy;
	CGuiButton m_GuiBtnExt;
	CButton m_GuiBtnTree;
	CButton m_GuiBtnList;
	CGuiButton m_GuiBtnAdd;
	CGuiButton m_GuiBtnDel;
	CGuiButton m_GuiBtnInRep;
	CGuiButton m_GuiBtnCancel;
	CGuiButton m_GuiBtnPrint;
	CGuiButton m_GuiBtnPerView;

	CMyTreeCtrl m_GuiMenuTree;
	CListCtrl m_GuiMenuList;
	CListCtrl m_GuiListRep;
	CStatic m_GuiStaticTitle;
	CButton m_GuiCheckSendBefore;
	
	BOOL m_bSendBefore;
	CString m_py;
	CString m_title;
private:
	hotelMIS::KDBCon m_con;
	hotelMIS::HMenuInfoVec m_menuVec; 
	bool m_bIsTree;	
	
	CPoint m_point;
	map<int,int> m_menuListMap; // ���˵��б�
	list<hotelMIS::HInOutRep> m_listInOutRep;
	map<int,int> m_repListMap; //�Ҳ��б�

	CFont m_font;

	CString m_inout_dh;		//���β������˵���
	
	BOOL	m_bRepOpen;		//ֻ���ڿ��汾
	bool isOut;

//for print
	static CString m_exp;
	static CString m_hotelname;

	void PrintView();
	static void DrawDC(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�

public:
	//��ʼ�������б�
	void Init();
	
	void Refresh();

	afx_msg void OnEnChangeEditPy();
	afx_msg void OnBnClickedButtonExt();
	afx_msg void OnBnClickedButtonTree();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnBnClickedButtonMoveRight();
	afx_msg void OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListInrep(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonMoveLeft();
	afx_msg void OnBnClickedButtonInrep();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonPerview();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
