/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		Ԥ��
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
#include "DiningRoomTab.h"
#include <map>
using namespace std;
// CYDDialog �Ի���

class CYDDialog : public CDialog
{
	DECLARE_DYNAMIC(CYDDialog)

public:
	CYDDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYDDialog();

// �Ի�������
	enum { IDD = IDD_YD_DLG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//Control Variable
	CGuiGroupBox m_GuiGroupBox;
	CListCtrl m_GuiListYd;
	
	CGuiButton m_GuiButtonAdd;
	CGuiButton m_GuiButtonDel;
	CGuiButton m_GuiButtonCancel;

	CDiningRoomTab * m_ListCtrl;
	hotelMIS::KDBCon m_con;
	int m_nPos;
	map<int,int> m_accountMap; //map<pos,id>
	pair<int,int> m_tableIdAndRoomId;
	void Init();
	void Refresh();
	void InitRoomNoAndTalbeId();
	afx_msg void OnBnClickedButtonDisplay();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListYd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListYd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	CComboBox m_GuiRoomNoComBo;
	map<int,int> m_roomMap;
	CComboBox m_GuiTableIDComBo;
	map<int,int> m_mapTable;
	CButton m_GuiRepastBtn;
	afx_msg void OnCbnSelchangeRoomnoCombo();
	afx_msg void OnBnClickedRepastButton();
	void ChangeTableState(int tableId,int roomId); //�ı�ͼ��״̬
};
