/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		预定管理及转入就餐
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "afxdtctl.h"
#include "HDestineBdy.h"
#include "KDBCon.h"
#include "afxcmn.h"

// CYDXXDialog 对话框

class CYDXXDialog : public CDialog
{
	DECLARE_DYNAMIC(CYDXXDialog)

public:
	CYDXXDialog(CWnd* pParent = NULL,int id = 0,bool bModify = false);   // 标准构造函数
	virtual ~CYDXXDialog();

// 对话框数据
	enum { IDD = IDD_YDXX_DLG };

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
	//Control Variable
	CGuiGroupBox m_GuiGroupBox;
	CDateTimeCtrl m_GuiDTCtrlYDDate;
	
	CGuiEdit m_GuiEditName;
	CGuiEdit m_GuiEditPersonNum;
	CGuiEdit m_GuiEditYDTime;
	CGuiEdit m_GuiEditSubScription;
	CGuiEdit m_GuiEditRemark;
	CGuiEdit m_GuiPhoneEdit;
	
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	
	CGuiComboBoxExt m_GuiComBoHallNo;
	CGuiComboBoxExt m_GuiComBoTableNo;
	
	int m_id;
	//Binding Variable
	CString m_name;
	int m_personNum;
	COleDateTime m_ydDate;
	int m_hour;
	float m_subscription;
	CString m_remark;
	CString m_phone;
	bool m_bModify;	
	
	hotelMIS::HDestineBdy m_pDestineBdy;
	hotelMIS::KDBCon m_con;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnEditchangeComboHallNo();
	
	virtual BOOL OnInitDialog();
			
	CSpinButtonCtrl m_hourSpinBtn;
	CSpinButtonCtrl m_minSpinBtn;
	int m_min;
	CEdit m_GuiMinEdit;
};
