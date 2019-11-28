#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"
// CSysParamSetDialog 对话框

class CSysParamSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CSysParamSetDialog)

public:
	CSysParamSetDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysParamSetDialog();

// 对话框数据
	enum { IDD = IDD_SYS_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_GuiGroupBoxL;
	CStatic m_GuiGroupBoxR;
	CStatic m_GuiGroupBoxB;
	CEdit m_GuiEditTableStatus;
	CListBox m_GuiListBoxTableStatus;
	CButton m_GuiButtonAddTableStatus;
	CButton m_GuiButtonDelTableStatus;
	CEdit m_GuiEditCanTinName;
	CEdit m_GuiEditTableNum;
	CListCtrl m_GuiListCtrlCanTin;
	CListCtrl m_GuiListCtrlTableFlag;

	CButton m_GuiButtonAddCanTin;
	CButton m_GuiButtonDelCanTin;
	CComboBox m_GuiComboBoxCanTin;
	CComboBox m_GuiComboBoxTableStatus;
	CButton m_GuiButtonSetTableStatus;
	CString m_tableStatus;
	CString m_canTinName;
	int m_tableNum;
	int m_canTinBh;
public:
	hotelMIS::KDBCon m_con;
public:
	//op
	void InitShell();
	void RefreshRoomList();
	void RefreshTableComobBox();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddCantin();
	afx_msg void OnBnClickedButtonAddTableStatus();
	
};
