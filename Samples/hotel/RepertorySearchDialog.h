/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		库存查询
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "atlcomtime.h"

#include "KDBCon.h"
#include <map>
using namespace std;

// CRepertorySearchDialog 对话框

class CRepertorySearchDialog : public CDialog
{
	DECLARE_DYNAMIC(CRepertorySearchDialog)

public:
	CRepertorySearchDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRepertorySearchDialog();

// 对话框数据
	enum { IDD = IDD_REPERTORY_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	static void Draw(CDC &memDC, PRNINFO PrnInfo);  //打印回调

public:
	

	void Init();
	
	void RestRepRefresh(); //剩余库存列表

	afx_msg void OnRestRepSearch();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedPrintButton();

	afx_msg void OnEnChangeBhEdit();
	afx_msg void OnEnChangeNamePyEdit();
	
	afx_msg void OnBnClickedRepModifyBtn();
};
