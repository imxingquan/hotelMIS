/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统用户管理
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"
#include "HAdmin.h"

#include <map>
#include <string>
using namespace std;

// CSysUserManagerDlg 对话框

class CSysUserManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CSysUserManagerDlg)

public:
	CSysUserManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysUserManagerDlg();

// 对话框数据
	enum { IDD = IDD_SYSUSER_DIALOG };

protected:
	//CString ReplaceChar(CString &str)
	//{
	//	//替换字符中的 "'" 以及
	//	CString strReturn("");
	//	TRY
	//	{
	//		if(str.GetLength()>0)
	//		{
	//			strReturn=str;
	//			strReturn.TrimLeft();
	//			strReturn.TrimRight();

	//			strReturn.Replace(_T("'"),_T("''"));
	//			strReturn.Replace(_T("\\"),_T(""));
	//		}
	//	}
	//	CATCH(CException,e){
	//		e->ReportError();
	//	}
	//	END_CATCH
	//		return strReturn;
	//}
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxLT;
	CGuiGroupBox m_GuiGroupBoxLB;
	CGuiGroupBox m_GuiGroupBoxR;
	CGuiEdit m_GuiLogNameEdit;
	CGuiEdit m_GuiLogPwdEdit;
	CGuiEdit m_GuiNameEdit;
	CGuiEdit m_GuiRemarkEdit;
	CGuiEdit m_GuiPurviewEdit;
	
	CGuiButton m_GuiAddSysButton;
	CGuiButton m_GuiDelSysButton;
	CGuiButton m_GuiAddOpTypeButton;
	CGuiButton m_GuiDelOpTypeButton;
	CGuiButton m_GuiToolButton;
	CGuiButton m_GuiSetPurviewButton;
	
	CListBox m_GuiPurviewList;
	CListCtrl m_GuiSysListCtrl;
	
	CGuiComboBoxExt m_GuiPurviewCombo;


	/*CGuiCheckBox m_GuiM0Check;
	CGuiCheckBox m_GuiM1Check;
	CGuiCheckBox m_GuiM2Check;
	CGuiCheckBox m_GuiM3Check;
	CGuiCheckBox m_GuiM4Check;
	CGuiCheckBox m_GuiM5Check;
	CGuiCheckBox m_GuiM6Check;
	CGuiCheckBox m_GuiM7Check;*/	
	CButton m_GuiM0Check;
	CButton m_GuiM1Check;
	CButton m_GuiM2Check;
	CButton m_GuiM3Check;
	CButton m_GuiM4Check;
	CButton m_GuiM5Check;
	CButton m_GuiM6Check;
	CButton m_GuiM7Check;
	
	//bind
	CString m_logName;
	CString m_password;
	CString m_purview;
	CString m_fname;
	CString m_remark;
	CString m_purviewr;
	CString m_purviewlist;

	BOOL m_bM0;
	BOOL m_bM1;
	BOOL m_bM2;
	BOOL m_bM3;
	BOOL m_bM4;
	BOOL m_bM5;
	BOOL m_bM6;
	BOOL m_bM7;
	BOOL m_bM8;

	int m_nPos;
	hotelMIS::KDBCon m_con;
	map<string,int> m_purviewCombo;
	map<int,hotelMIS::HAdmin> m_sysMap;
	bool m_isModify ;
	void InitSys();
	void RefreshSys();
	void InitPurview();
	void ResetComboBox();

	afx_msg void OnAddAndEditSys();
	afx_msg void OnDelSys();
	afx_msg void OnAddPurview();
	afx_msg void OnDelPurview();
	afx_msg void OnSetPurview();

	afx_msg void OnDispAndHide();

	afx_msg void OnNMDblclkSysList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickSysList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnCbnEditchangeOptypeCombo();
	

	afx_msg void OnLbnSelchangePurviewList();
};
