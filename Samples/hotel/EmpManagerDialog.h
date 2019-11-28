/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		Ա������
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HEmployeeBdy.h"

// CEmpManagerDialog �Ի���

class CEmpManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(CEmpManagerDialog)

public:
	CEmpManagerDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmpManagerDialog();

// �Ի�������
	enum { IDD = IDD_EMPLOYEE_MANAGER };

protected:
CString ReplaceChar(CString &str)
	{
		//�滻�ַ��е� "'" �Լ�
		CString strReturn("");
		TRY
		{
			if(str.GetLength()>0)
			{
				strReturn=str;
				strReturn.TrimLeft();
				strReturn.TrimRight();

				strReturn.Replace(_T("'"),_T("''"));
				strReturn.Replace(_T("\\"),_T(""));
			}
		}
		CATCH(CException,e){
			e->ReportError();
		}
		END_CATCH
			return strReturn;
	}
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//control var
	CGuiGroupBox m_GuiGroupBoxT;
	CGuiGroupBox m_GuiGroupBoxB;
	CListCtrl m_GuiListCtrlEmployee;
	CGuiEdit m_GuiEditKey;
	CGuiButton m_GuiButtonSearch;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	CGuiButton m_GuiEditAndDelBtn;
	//bind var
	CString m_editKey;
	
	map<int,string> m_empMap; //map<pos,emp_id>
	hotelMIS::HEmployeeBdy m_empBdy;
	void Init();
	void Refresh();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnNMClickListEmployee(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

	afx_msg void OnEditAndDel();
	
};
