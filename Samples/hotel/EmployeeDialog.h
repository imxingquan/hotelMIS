/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		添加员工
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "HEmployeeBdy.h"

// CEmployeeDialog 对话框

class CEmployeeDialog : public CDialog
{
	DECLARE_DYNAMIC(CEmployeeDialog)

public:
	CEmployeeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEmployeeDialog();

// 对话框数据
	enum { IDD = IDD_EMPLOYEE_ADD_DLG };

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
	//Control var
	CGuiGroupBox m_GuiGroupBox;
	CGuiEdit m_GuiEditEmpId;
	CGuiEdit m_GuiEditEmpName;
	CGuiComboBoxExt m_GuiComboSex;
	CGuiEdit m_GuiEditEmpBir;
	CGuiEdit m_GuiEditAddress;
	CGuiEdit m_GuiEditPhone;
	CGuiEdit m_GuiEditRemark;
	CGuiEdit m_GuiEditPhotoUrl;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	CGuiComboBoxExt m_GuiComboBoxJobSet;
//bind var
	CString m_empId;
	CString m_empName;
	CString m_empSex;
	CString m_empBir;
	CString m_empAddress;
	CString m_empPhone;
	CString m_empRemark;
	CString m_photoUrl;
	CString m_empJob;
//bdy
	hotelMIS::HEmployeeBdy m_empBdy;
	map<int,int> m_jobMap; //map<pos,job_id>
	int m_pos;
	afx_msg void OnBnClickedOk();

	
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelectChgJob();
};
