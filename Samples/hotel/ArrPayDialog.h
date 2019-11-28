/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		挂账结账
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
// CArrPayDialog 对话框

class CArrPayDialog : public CDialog
{
	DECLARE_DYNAMIC(CArrPayDialog)

public:
	CArrPayDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CArrPayDialog();

// 对话框数据
	enum { IDD = IDD_ARREARAGE_PAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	float m_ss;			//实收账款
	float m_ys;			//应收账款
	float m_zy;			//找余
	float m_jz_rest;
	BOOL m_fp;			//需要发票
	int m_arid;			//挂账单位id
	hotelMIS::HArrerageBdy m_arrBdy;
	hotelMIS::HArrerageVec m_gzList; //挂账的详细账单

	int m_onlyJzPos;

	map<int,int> m_arrZHMap; //map<pos,arid>
	map<int,string> m_gzMap;
	//map<int,string> m_gzJzMap;

	float m_total;	// 挂账合计

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
