#pragma once

#include "resource.h"
#include "afxwin.h"

#include "KDBCon.h"
#include <map>
using namespace std;

// CAddMemberDlg 对话框

class CAddMemberDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddMemberDlg)

public:
	CAddMemberDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddMemberDlg();

// 对话框数据
	enum { IDD = IDD_MEMADD_DLG };

//================================================

private:
	hotelMIS::KDBCon m_con;
	map<int,pair<int,float> > m_map;			//map<nPos,pair<id,zhekou> >记录 选中的id 和会员等级id 的对应
	
//================================================

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_GuiBhEdit;
	CEdit m_GuiMnameEdit;
	CComboBox m_GuiSexCombo;
	CEdit m_GuiBirthEdit;
	CEdit m_GuiTelEdit;
	CComboBox m_GuiMDJCombo;
	CEdit m_GuiZKEdit;
	CEdit m_GuiCzMoneyEdit;
	CEdit m_GuiRemarkEdit;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_bh;
	CString m_mname;
	CString m_sex;
	CString m_birth;
	CString m_telphone;
	CString m_mdjname;
	float m_zhekou;
	float m_czmoney;
	CString m_remark;
	afx_msg void OnCbnSelchangeMdjCombo();
};
