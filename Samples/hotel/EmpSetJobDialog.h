/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		设置员工职务
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
// CEmpSetJobDialog 对话框
#include <map>
using namespace std;
class CEmpSetJobDialog : public CDialog
{
	DECLARE_DYNAMIC(CEmpSetJobDialog)

public:
	CEmpSetJobDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEmpSetJobDialog();

// 对话框数据
	enum { IDD = IDD_SET_JOB_DLG };

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
	CGuiEdit m_GuiJobEdit;
	CGuiButton m_GuiAddJobButton;
	CGuiButton m_GuiDelJobButton;
	CListCtrl m_GuiJobListCtrl;
	CString m_jobName;
	hotelMIS::KDBCon m_con;
	map<int,int> m_jobSetmap;	//将控件索引与jobId绑定
	bool m_modifyFlag;
	int m_nIndex;
public:
	void Init();
	void Refresh();
	afx_msg void OnBnClickedAddJobButton();
	afx_msg void OnBnClickedDelJobButton();
	afx_msg void OnNMClickJobList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeJobEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkJobList(NMHDR *pNMHDR, LRESULT *pResult);
};
