/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		打印设置
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "resource.h"
#include "KDBCon.h"
#include "afxwin.h"
#include "afxcmn.h"

// CStep5 对话框

class CStep5 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep5)

public:
	CStep5();
	virtual ~CStep5();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_5 };

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
	hotelMIS::KDBCon m_con;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedSaveButton();
	CGuiEdit m_GuiHotelTel2Edit;
	CGuiEdit m_GuiHotelNameEdit;
	CGuiEdit m_GuiHotelTelEdit;
	CGuiEdit m_GuiHotelHttpEdit;
	
	CString m_hotelname;
	CString m_hoteltel;
	CString m_hotelhttp;
	CString m_hoteltel2;

	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	
	
//	virtual BOOL OnWizardFinish();
	int m_xPos;
	int m_yPos;
	int m_lineHeight;
	int m_col2w;
	int m_col3w;
	int m_col4w;
	int m_fontSize;

	CSpinButtonCtrl m_GuiXPosSpin;
	CSpinButtonCtrl m_GuiYPosSpin;
	CSpinButtonCtrl m_GuiLineHeightSpin;
	CSpinButtonCtrl m_GuiCol2wSpin;
	CSpinButtonCtrl m_GuiCol3wSpin;
	CSpinButtonCtrl m_GuiCol4wSpin;
	CSpinButtonCtrl m_GuiFontSizeSpin;

	afx_msg void OnBnClickedDefaultvalButton();
	
	
	afx_msg void OnBnClickedDefaultvalButton2();
	virtual LRESULT OnWizardNext();
	int m_restLine;
	virtual BOOL OnApply();
	afx_msg void OnEnChangeEdit();
};
