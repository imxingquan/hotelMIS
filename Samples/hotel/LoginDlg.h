/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		�û���¼
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "KDBCon.h"
#include "HAdmin.h"
#include "HAdminBdy.h"
// CLoginDlg �Ի���

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//Control Variable
	CGuiEdit m_GuiEditUserName;
	CGuiEdit m_GuiEditPassword;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	
	//Binding Variable
	CString m_userName;		// ��¼�û���
	CString m_password;		// ����
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_GuiStaticMsg;
	afx_msg void OnBnClickedOk();
	CComboBox m_userComboBox;
	CString m_uName;

	hotelMIS::KDBCon m_con;
};
