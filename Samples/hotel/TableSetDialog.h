/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		餐桌设置
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "resource.h"
#include "afxwin.h"

#include "KDBCon.h"
// CTableSetDialog 对话框

class CTableSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CTableSetDialog)

public:
	CTableSetDialog(CWnd* pParent = NULL);   // 标准构造函数
	CTableSetDialog(CWnd* pParent ,int tableId,int roomId);   // 标准构造函数
	virtual ~CTableSetDialog();

// 对话框数据
	enum { IDD = IDD_TABLE_SET_DIALOG };

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

	int m_tableId;
	int m_roomId;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void Init();
	hotelMIS::KDBCon m_con;
	std::map<int,int> m_map_tableStatus,m_map_tableStatus2; //pos,state

	CString m_curTableMsg;
	CGuiEdit m_GuiTableNameEdit;
	CGuiComboBoxExt m_GuiComboTableStatus;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	CGuiGroupBox m_GuiGroupBox;
	CString m_tableName;
	afx_msg void OnBnClickedOk();
};
