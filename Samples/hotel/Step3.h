/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"

// CStep3 �Ի���

class CStep3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep3)

public:
	CStep3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStep3();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
