/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		出库
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "KDBCon.h"
#include <map>
using namespace std;

// COutStoreDialog 对话框

class COutStoreDialog : public CDialog
{
	DECLARE_DYNAMIC(COutStoreDialog)

public:
	COutStoreDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COutStoreDialog();

// 对话框数据
	enum { IDD = IDD_OUTSTORE_DLG };

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
	//			TRACE(". = %d\n","'");
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
	CGuiGroupBox m_GuiGroupBox;
	CGuiComboBoxExt m_GuiComboOutStoreId;
	CGuiEdit m_GuiEditNum;
	CGuiEdit m_GuiEditPrice;
	
	CDateTimeCtrl m_GuiDateTimeCtrl;
	CGuiComboBoxExt m_GuiComboOpType;
	CGuiComboBoxExt m_GuiComboBoxUnit;
	CGuiButton m_GuiOkBtn;
	CGuiButton m_GuiCancelBtn;
	
	int m_id;
	int m_num;
	float m_price;
	CString m_unit;
	COleDateTime m_dateTime;
	int m_opType;
	hotelMIS::KDBCon m_con;
	map<int,pair<int,string> > m_mapout; //map<pos,pair<food_id,unit>>
	//////////////////////////////////////////////////
	void Init();

	afx_msg void OnCbnSelchangeComboOsId();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	
};
