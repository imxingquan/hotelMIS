/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
// CEmpParticularDlg �Ի���

class CEmpParticularDlg : public CDialog
{
	DECLARE_DYNAMIC(CEmpParticularDlg)

public:
	CEmpParticularDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmpParticularDlg();

// �Ի�������
	enum { IDD = IDD_EMPLOYEE_PARTICULAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//control var
	CGuiGroupBox m_GuiGroupBox;
	CGuiEdit m_GuiEditEmpId;
	CGuiEdit m_GuiEditEmpName;
	CGuiComboBoxExt m_GuiComboSex;
	CGuiEdit m_GuiEditEmpBir;
	CGuiEdit m_GuiEditEmpAddress;
	CGuiEdit m_GuiEditEmpPhone;
	CGuiEdit m_GuiEditEmpRemark;
	CGuiButton m_GuiButtonModify;
	CGuiButton m_GuiButtonDel;
	//bind var
	CString m_empId;
	CString m_empName;
	CString m_empSex;
	CString m_empBir;
	CString m_empAddress;
	CString m_empPhone;
	CString m_empRemark;
	CString m_photoUrl;

	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDel();
	virtual BOOL OnInitDialog();
};
