/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统设置
			启用鼠标自动选定与提醒功能
			结账时显示提示对话框
			结账时打印小票
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CStep4 对话框

class CStep4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep4)

public:
	CStep4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStep4();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();

	
	CButton m_GuiAutoRefreshCheck;
	CButton m_GuiPrintWarningCheck;
	CButton m_GuiJZAndPrintCheck;
	CButton m_GuiNeedPwdCheck;
	CButton m_GuiRepWarningCheck;
	CButton m_GuiRepOpenCheck;

	CEdit m_GuiAwardPwd1Edit;
	CEdit m_GuiAwardPwd2Edit;

	BOOL m_bNeedPwd;
	CString m_awardPwd1;
	CString m_awardPwd2;
	BOOL m_autoRefresh;
	BOOL m_printWarning;
	BOOL m_jzAndPrint;
	BOOL m_bRepNumWarning;

	virtual LRESULT OnWizardNext();
	
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonClearall();
	afx_msg void OnBnClickedSetmemdjButton();

	CButton m_GuiSetPwdBtn;
	afx_msg void OnBnClickedSetpwdBtn();
	afx_msg void OnBnClickedNeedpwdCheck();
	afx_msg void OnBnClickedButtonClearMemcz();
	
	
	BOOL m_bRepOpen;
	
	virtual BOOL OnApply();
	afx_msg void OnBnClickedCheck();
};
