/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		挂账帐户管理
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CArrearageSetDlg 对话框

class CArrearageSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CArrearageSetDlg)

public:
	CArrearageSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CArrearageSetDlg();

// 对话框数据
	enum { IDD = IDD_ARREARAGE_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_GuiGroupBoxT;
	CStatic m_GuiGroupBoxB;
	CListCtrl m_GuiListCtrlArr;
	CButton m_GuiButtonAdd;
	CButton m_GuiButtonModify;
	CButton m_GuiButtonDel;
	CButton m_GuiButtonOk;

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDel();
};
