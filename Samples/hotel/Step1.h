/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		餐桌餐厅配置
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
#include <map>
using namespace std;
// CStep1 对话框

class CStep1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep1)

public:
	CStep1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStep1();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_1 };

protected:
	//CString ReplaceChar(CString &str)
	//{
	//	//替换字符中的 "'" 以及
	//	CString strReturn("");
	//	TRY
	//	{
	//		if(str.GetLength()>0)
	//		{
	//			strReturn=str;
	//			strReturn.TrimLeft();
	//			strReturn.TrimRight();

	//			strReturn.Replace(_T("'"),_T("''"));
	//			strReturn.Replace(_T("\\"),_T(""));
	//		}
	//	}
	//	CATCH(CException,e){
	//		e->ReportError();
	//	}
	//	END_CATCH
	//		return strReturn;
	//}
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_GuiGroupBoxL;
	CGuiEdit m_GuiEditTableStatus;
	CGuiEdit m_GuiEditPersonNum;
	CGuiButton m_GuiButtonAddTableStatus;
	CGuiButton m_GuiButtonDelTableStatus;
	CGuiButton m_GuiSetTableBmpBtn;
	
	CListCtrl m_GuiListCtrlTableStatus;	
	CString m_tableStatus;
	int m_personNum;
	hotelMIS::KDBCon m_con;
	map<int,int> m_tableStatusMap; //map<pos,table_state>
	int m_nPos;
public:
	//op
	void Init();
	void Refresh();
public:
	//msg
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAddTableStatus();
	afx_msg void OnBnClickedButtonDelTableStatus();
	afx_msg void OnNMClickListTableStatus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTableStatus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSetTablebmpButton();
	
};
