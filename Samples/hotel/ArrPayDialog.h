/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		���˽���
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <HArrerageBdy.h>
#include <map>
using namespace std;
// CArrPayDialog �Ի���

class CArrPayDialog : public CDialog
{
	DECLARE_DYNAMIC(CArrPayDialog)

public:
	CArrPayDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CArrPayDialog();

// �Ի�������
	enum { IDD = IDD_ARREARAGE_PAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//control var
	CStatic m_GuiGroupBoxLT;
	CStatic m_GuiGroupBoxLB;
	CStatic m_GuiGroupBoxR;
	CListCtrl m_GuiListCtrlArr;
	CListCtrl m_GuiListCtrlArrXX;
	CEdit m_GuiEditSS;
	CEdit m_GuiEditYS;
	CEdit m_GuiEditZY;
	CButton m_GuiButtonFP;
	CButton m_GuiButtonJZ;
	CButton m_GuiButtonPrint;
	CButton m_GuiButtonOk;
	//bind var
	float m_ss;			//ʵ���˿�
	float m_ys;			//Ӧ���˿�
	float m_zy;			//����
	float m_jz_rest;
	BOOL m_fp;			//��Ҫ��Ʊ
	int m_arid;			//���˵�λid
	hotelMIS::HArrerageBdy m_arrBdy;
	hotelMIS::HArrerageVec m_gzList; //���˵���ϸ�˵�

	int m_onlyJzPos;

	map<int,int> m_arrZHMap; //map<pos,arid>
	map<int,string> m_gzMap;
	//map<int,string> m_gzJzMap;

	float m_total;	// ���˺ϼ�

	afx_msg void OnEnChangeEditSs();
	afx_msg void OnNMClickListArr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonJz();
	afx_msg void OnBnClickedButtonPrint();
	void Init();
	void Refresh();
	void Refresh2();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListArrxx(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMRclickListArrxx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOnlyJz();
};
