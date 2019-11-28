/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		����ѯ
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "atlcomtime.h"

#include "KDBCon.h"
#include <map>
using namespace std;

// CRepertorySearchDialog �Ի���

class CRepertorySearchDialog : public CDialog
{
	DECLARE_DYNAMIC(CRepertorySearchDialog)

public:
	CRepertorySearchDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepertorySearchDialog();

// �Ի�������
	enum { IDD = IDD_REPERTORY_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxU;
	CGuiGroupBox m_GuiGroupBoxB;
	
	CListCtrl m_GuiRepList;
	CGuiEdit m_GuiNamePyEdit;
	CGuiEdit m_GuiBhEdit;
	CGuiButton m_GuiPrintBtn;
	CGuiButton m_GuiRepModifyBtn;

	CString m_bh;
	CString m_namepy;
	
	map<int,int> m_repmap; //<nPos,food_id>
	hotelMIS::KDBCon m_con;

public:
	// for print
	static CString m_exp;
	static CString m_hotelname;
	void PrintView();
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�

public:
	

	void Init();
	
	void RestRepRefresh(); //ʣ�����б�

	afx_msg void OnRestRepSearch();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedPrintButton();

	afx_msg void OnEnChangeBhEdit();
	afx_msg void OnEnChangeNamePyEdit();
	
	afx_msg void OnBnClickedRepModifyBtn();
};
