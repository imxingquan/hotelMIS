#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "KDBCon.h"
#include <map>
using namespace std;

// CMemModifyDlg �Ի���

class CMemModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemModifyDlg)

public:
	CMemModifyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMemModifyDlg();


// �Ի�������
	enum { IDD = IDD_MEMMODIFY_DLG };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

	hotelMIS::KDBCon m_con;
	map<int,pair<int,float> > m_map;			//map<nPos,pair<id,zhekou> >��¼ ѡ�е�id �ͻ�Ա�ȼ�id �Ķ�Ӧ
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic m_GuiBhEdit;
	CEdit m_GuiMnameEdit;
	CComboBox m_GuiSexCombo;
	CDateTimeCtrl m_GuiBirthEdit;
	CEdit m_GuiTelEdit;
	CComboBox m_GuiMDJCombo;
	/*CEdit m_GuiZKEdit;
	CEdit m_GuiCzMoneyEdit;*/
	CStatic m_GuiZKEdit;
	CStatic m_GuiCzMoneyEdit;
	CEdit m_GuiRemarkEdit;
	CString m_bh;
	CString m_mname;
	CString m_sex;
	COleDateTime  m_birth;
	CString m_telphone;
	CString m_mdjname;
	float m_zhekou;
	float m_czmoney;
	CString m_remark;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeMdjCombo();
};
