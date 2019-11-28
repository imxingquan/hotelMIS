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

// CStep2 对话框

class CStep2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep2)

public:
	CStep2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStep2();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_2 };

protected:
	//	CString ReplaceChar(CString &str)
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
	//op
	void Init();
	void Refresh();
public:
	
	CGuiEdit m_GuiEditCanTinName;
	CGuiEdit m_GuiEditNum;
	CGuiEdit m_GuiRoomNoEdit;
	
	CGuiButton m_GuiButtonDelCanTin;
	CGuiButton m_GuiButtonAddCanTin;
	CListCtrl m_GuiListCanTin;

	CString m_canTinName;
	int m_tableNum;	
	int m_roomNo;
	hotelMIS::KDBCon m_con;
	map<int,int> m_roomMap; //map<pos,room_id>
	BOOL m_isModify;
public:
	//msg
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddCantin();
	afx_msg void OnDeleteRoom();
	afx_msg void OnNMClickListCantin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMDblclkListCantin(NMHDR *pNMHDR, LRESULT *pResult);
};
