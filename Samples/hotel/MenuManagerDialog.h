/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		�˵�����
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
#include "HFoodKindCtrl.h"

#include <map>
using namespace std;
// CMenuManagerDialog �Ի���

class CMenuManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(CMenuManagerDialog)

public:
	CMenuManagerDialog(BOOL bRep = FALSE,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMenuManagerDialog();

// �Ի�������
	enum { IDD = IDD_MENU_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;
	//CGuiGroupBox m_GuiGroupBoxL;
	
	CGuiComboBoxExt m_GuiComboKind;
	
	CGuiComboBoxExt m_GuiComboUnit;
	CGuiComboBoxExt m_GuiComboCook;
	
	CListCtrl m_GuiListCtrl;
	
	CGuiEdit m_GuiEditName;
	CGuiEdit m_GuiEditPrice;
	CGuiEdit m_GuiEditKind;
	
	CButton m_GuiCheckRepertory; //checkbox
	CButton m_GuiCheckBoxRepNoCalc;

	CGuiButton m_GuiButtonAdd;
	CGuiButton m_GuiCheckAllAdd;
	CGuiButton m_GuiDelButton;
	CGuiEdit m_GuiPYEdit;
	CComboBox m_GuiComboFilter;
	CGuiButton m_GuiPrintMenuBtn;

	//bind var
	CString m_addKind;	//
	BOOL m_bAllAdd;	

	BOOL m_bSpecial;
	BOOL m_bRepNoCalc;
	
	BOOL m_bRepOpen;	//ע����� ���ڿ��ƿ��
	BOOL m_bRep;
	
	int m_kindPos;
	CString m_foodName;	//����
	float m_price;		//�۸�
	CString m_unit;		//��λ
	CString m_cook;		//��ʦ��
	BOOL m_repertory;	//�Ƿ����
	CString m_py;
		
	CFont m_font;
	hotelMIS::HFoodKindVec m_foodVec;

	map<int,pair<int,int> > m_menuMap;	//map<pos,pair<food_id,kind_id> >
	map<int,pair<int,string> > m_kindMap; //map<pos,pair<kind_id,kind_name> >
	hotelMIS::KDBCon m_con;
	int m_nIndex; //����pos
	BOOL m_isModify; //��ǰ�Ƿ���޸�


	//��ӡ
	static CString m_exp;
	static CString m_hotelname;
	
	void 	PrintView();
	static void DrawView(CDC &memDC, PRNINFO PrnInfo);  //��ӡ�ص�


public:
	void Init();
	void Refresh();
	
	afx_msg void OnBnClickedButtonAdd();
	//afx_msg void OnBnClickedButtonAddKind();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboKind();
	afx_msg void OnPopupModifymenu();
	afx_msg void OnPopupDelmenu();
	afx_msg void OnNMRclickListMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListMenu(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedDelButton();
	afx_msg void OnNMClickListMenu(NMHDR *pNMHDR, LRESULT *pResult);
		
	afx_msg void OnBnClickedCheckRepertory();
	afx_msg void OnBnClickedCheckRepertoryNocalc();
	

	afx_msg void OnCbnSelchangeComboFilter();
	afx_msg void OnBnClickedPrintMenuButton();
	
	// ͳ�Ʒ���
	CComboBox m_totalCombo;
	int m_totalfl;
};
