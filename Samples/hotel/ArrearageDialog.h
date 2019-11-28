/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		����
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

// CArrearageDialog �Ի���

class CArrearageDialog : public CDialog
{
	DECLARE_DYNAMIC(CArrearageDialog)

public:
	CArrearageDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CArrearageDialog();

// �Ի�������
	enum { IDD = IDD_ARREARAGE_DLG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void Init();
	void Refresh();
	hotelMIS::HArrerageBdy m_arrBdy;
	map<int,int> m_arrZHMap; //map<pos,arid>

	//control var
	CGuiGroupBox m_GuiGroupBox;
	CListCtrl m_GuiListCtrlArr;
	CGuiEdit m_GuiEditArrDept;
	CGuiEdit m_GuiEditArrMoney;

	CGuiButton m_GuiArrGZ;
	CGuiButton m_GuiCancel;

	//binding var
	CString m_arrDept;	//���˵�λ
	float m_arrMoney;	//���˽��
	
	int m_callback_arid ;
	string m_accountId;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnNMDblclkListArr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedArrGz();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
