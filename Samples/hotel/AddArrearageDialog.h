/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		入库
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

// CAddArrearageDialog 对话框

class CAddArrearageDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddArrearageDialog)

public:
	CAddArrearageDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddArrearageDialog();

// 对话框数据
	enum { IDD = IDD_ADD_ARREARAGE_DLG };
	
protected:
	//CString ReplaceChar(CString &str)
	//{
	//	//替换字符中的 "'" 以及
	//	CString strReturn("");
	//	TRY
	//	{
	//		if(str.GetLength()>0)
	//		{
	//			/*for ( int i = 0; i < str.GetLength(); i++)
	//			{
	//				if ( str.GetAt(i) != "'")
	//				strReturn+=str.GetAt(i);

	//			}*/
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
	//Control var
	CGuiGroupBox m_GuiGroupBox;
	CGuiButton m_GuiButtonCancel;
	CGuiButton m_GuiBtnAddArr;
	CGuiButton m_GuiDelZHBtn;
	//binding var
	virtual BOOL OnInitDialog();
	CGuiEdit m_GuiGZName;
	CGuiEdit m_GuiGZPhone;
	CGuiEdit m_GuiGZDept;
	CGuiEdit m_GuiGZDemo;

	CString m_gzName;
	CString m_gzPhone;
	CString m_gzDept;
	CString m_gzDemo;

	bool m_isModify ;
	int m_nPos; //要修改的 arid 对应的 nPos;
	hotelMIS::HArrerageBdy m_arrBdy;
	map<int,int> m_arrZHMap; //map<pos,arid>
	
	void Init();
	void Refresh();
	
	CListCtrl m_GuiArrZHListCtrl;
	afx_msg void OnBnClickedAddGzzh();
	
	afx_msg void OnBnClickedCancel();
	
	afx_msg void OnBnClickedDelzhBtn();
	afx_msg void OnEnChangeGzName();
	afx_msg void OnNMClickGzList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkGzList(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL m_cwCheck;
};
