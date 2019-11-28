/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		菜类和单位设置
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"

#include <map>
using namespace std;
// CKindUnitSetDialog 对话框
#include "KDBCon.h"
#include "afxcmn.h"
class CKindUnitSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CKindUnitSetDialog)

public:
	CKindUnitSetDialog(BOOL IsBehindKc = FALSE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKindUnitSetDialog();

// 对话框数据
	enum { IDD = IDD_KINDADD_DLG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxR;	
	CGuiGroupBox m_GuiGroupBoxL;
	CGuiEdit m_GuiEditUnit;
	CGuiEdit m_GuiKindEdit;
	
	CListCtrl m_GuiUnitListCtrl;
	CListCtrl m_GuiKindListCtrl;
	
	CGuiButton m_GuiButtonAddUnit;
	CGuiButton m_GuiButtonDelUnit;
	CGuiButton m_GuiAddKindButton;
	CGuiButton m_GuiDelKindButton;
	
	CButton m_GuiAllAddCheck;
	CButton m_GuiTsCheck;
	
	CString m_unit;
	CString m_kindName;
	BOOL m_allAdd;
	BOOL m_ts;
	BOOL m_bKcKind;
	
	hotelMIS::KDBCon m_con;
	map<int,int> m_unitMap;
	map<int,int> m_kindMap;
	int m_nIndex,m_nIndex2;
	bool m_modifyFlag;
	
	BOOL m_isBehindKc;
	BOOL m_kindZK;
	BOOL m_zdyCheck;
public:
	void Init2();
	void Refresh2();
	void Init();
	void Refresh();
	afx_msg void OnBnClickedButtonUnitAdd();
	afx_msg void OnBnClickedButtonUnitDel();

	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickUnitList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditUnit();
	afx_msg void OnBnClickedAddkindButton();
	afx_msg void OnBnClickedDelkindButton();
	afx_msg void OnEnChangeKindEdit();
	afx_msg void OnNMClickKindList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkKindList(NMHDR *pNMHDR, LRESULT *pResult);
	
	
};
