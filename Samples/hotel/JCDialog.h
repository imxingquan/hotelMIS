/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		�ͲͲ���
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HMenuInfo.h"
#include "KDBCon.h"
#include "HRepDetails.h"

#include "HMenuInfoCtrl.h"

#include <vector>
#include <map>
using namespace std;
using namespace hotelMIS;

// CJCDialog �Ի���

class CJCDialog : public CDialog
{
	DECLARE_DYNAMIC(CJCDialog)

public:
	CJCDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CJCDialog(int tableId,int roomId,float subscription = 0.0f,CWnd* pParent = NULL);
	virtual ~CJCDialog();
	
// �Ի�������
	enum { IDD = IDD_JC_DLG };
	enum FOOD_COOK{ ALL = -1,LIANGCAI=0,MIANDIAN = 1,RECAI=2 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	BOOL PrintBehind(); //��ӡ�����
	BOOL PrintLiangCai(); //��ӡ����
	BOOL PrintMianDian();//��ӡ���
	BOOL PrintReCai(); //��ӡ�Ȳ�
	void FillTreeMenu();
	void FillListMenu();
	void Print(vector<HRepDetails> &vec,HDC hdc,CString pName,FOOD_COOK food_cook);
	void PrintSelectToCook(vector<int> &vecItem);

	void Print(CString pName,HDC hdc,FOOD_COOK food_cook); //��ӡ��������
	DECLARE_MESSAGE_MAP()
public:
	//Control Variable
	CGuiGroupBox m_GuiGroupBoxLeft;
	CGuiGroupBox m_GuiGroupBoxRight;
	CListCtrl m_GuiList;
	CTreeCtrl m_GiuiTree;
	CGuiEdit m_GuiEditNum;
	CSpinButtonCtrl m_GuiSpinNum;
	CGuiButton m_GuiButtonAdd;
	CGuiButton m_GuiButtonDel;
	CGuiButton m_GuiBtnExpand;

	CGuiButton m_GuiButtonPrintBehind;
	CGuiButton m_GuiButtonOk;
	CGuiEdit m_GuiEditPy;
	
	CListCtrl m_GuiMenuList;
	CButton m_GuiBtnTree;
	CButton m_GuiBtnList;

	//Binding Variable
    int m_num;	
	hotelMIS::KDBCon m_con;
	int m_roomId,m_tableId;
	CPoint m_point;
	CFont font;
	map<int,pair<string,int> > m_repMap; //map<pos,pair<account_id,food_id> >
	map<int,int> m_repPosMap; //map<pos,repId>

	map<int,int> m_menuListMap; // ���˵��б�
	
	hotelMIS::HMenuInfoVec m_menuVec; 

	bool m_bIsTree;		
	CToolTipCtrl m_tip;

	CString m_py;
	int m_leftPos;

	float m_subscription;
    //HACCEL  m_hAccelTable;
	//op
	void InitIdle();
	void Refresh();
	void FengChuPrintAll(); //�ֳ���ӡ
	
	afx_msg void OnBnClickedButtonAdd();
	
	afx_msg void OnNMDblclkTreeRight(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickTreeRight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOkButton();
	afx_msg void OnBnClickedButtonPrintbehind();
	afx_msg void OnPrintjctocook();
	afx_msg void OnNMRclickListLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPrintLiangcai();
	afx_msg void OnUpdatePrintLiangcai(CCmdUI *pCmdUI);
	afx_msg void OnPrintMiandian();
	afx_msg void OnUpdatePrintMiandian(CCmdUI *pCmdUI);
	afx_msg void OnPrintRecai();
	afx_msg void OnUpdatePrintRecai(CCmdUI *pCmdUI);
	afx_msg void OnPrintAllmenu();
	afx_msg void OnCancelmenu();
	afx_msg void OnBnClickedButtonExpand();
	afx_msg void OnDeletemenu();
	afx_msg void OnAwardmenu();
	afx_msg void OnBnClickedButtonTree();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnNMClickMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMenuList(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnEnChangeEditPy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_dwCombo;
	afx_msg void OnClose();
};
