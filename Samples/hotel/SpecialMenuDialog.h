/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��ɫ��
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "MyTreeCtrl.h"
#include "KDBCon.h"
#include "HMenuInfoCtrl.h"

#include <string>
#include <map>
using namespace std;
// CSpecialMenuDialog �Ի���

class CSpecialMenuDialog : public CDialog
{
	DECLARE_DYNAMIC(CSpecialMenuDialog)

public:
	CSpecialMenuDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpecialMenuDialog();

// �Ի�������
	enum { IDD = IDD_SPECIAL_MENU_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxL;
	CGuiGroupBox m_GuiGroupBoxR;
	CMyTreeCtrl m_GuiTreeCtrlMenu;
	CGuiComboBoxExt m_GuiComboSpecial;			//�ײͿؼ�
	CListCtrl m_GuiListCtrlSpecialMenu;
	CListCtrl m_GuiMenuList;
	
	CButton m_GuiBtnTree;
	CButton m_GuiBtnList;
	CGuiButton m_GuiBtnExt;
	CGuiButton m_GuiBtnExit;
	
	CGuiButton m_GuiButtonMoveR;
	CGuiButton m_GuiButtonMoveL;
	CGuiEdit m_GuiEditPy;
	CGuiEdit m_GuiEditNum;
	CString m_py;
	
	int m_kindSpPos;
	CPoint m_point,m_point2;
	hotelMIS::KDBCon m_con;
	map<int,int> m_taoCanKindMap; // map<pos,food_id>
	map<int,int> m_menuSpMap; // map<pos,food_id>
	map<int,int> m_menuListMap; // ���˵��б�
	
	hotelMIS::HMenuInfoVec m_menuVec; 

	bool m_bIsTree;		
	CToolTipCtrl m_tip;
	int m_num;

public: 
	//op
	void Init();
	void InitTaoCan();
	void Refresh();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMoveRight();
	afx_msg void OnBnClickedButtonMoveLeft();
	afx_msg void OnNMClickMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboSpecial();
	afx_msg void OnNMClickListSpecialMenu(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButtonTree();
	afx_msg void OnBnClickedButtonList();
	
	
	afx_msg void OnBnClickedButtonExt();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEditPy();
	
	
	afx_msg void OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult);
};
