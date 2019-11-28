/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		挂账
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <HArrerageBdy.h>
#include <map>
using namespace std;

// CArrearageDialog 对话框

class CArrearageDialog : public CDialog
{
	DECLARE_DYNAMIC(CArrearageDialog)

public:
	CArrearageDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CArrearageDialog();

// 对话框数据
	enum { IDD = IDD_ARREARAGE_DLG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	CString m_arrDept;	//挂账单位
	float m_arrMoney;	//挂账金额
	
	int m_callback_arid ;
	string m_accountId;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnNMDblclkListArr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedArrGz();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
