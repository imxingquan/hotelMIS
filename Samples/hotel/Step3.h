/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
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

// CStep3 对话框

class CStep3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep3)

public:
	CStep3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStep3();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxR;
	CGuiComboBoxExt m_GuiComboBoxCanTin;
	CGuiComboBoxExt m_GuiComboBoxTableStatus;
	CGuiButton m_GuiButtonSetTableStatus;
	CListCtrl m_GuiListTableFlag;
	hotelMIS::KDBCon m_con;
	std::map<std::string,int> m_map_room;
	std::map<std::string,int> m_map_tableSet;
	CString m_canTinName;
public:
	//op
	void Init();
	void Refresh();

public:
	//msg
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboCantin();
//	virtual void OnOK();
	afx_msg void OnSetTableStatus();
};
