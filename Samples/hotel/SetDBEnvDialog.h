/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		���ݿ⻷������
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "resource.h"


// CSetDBEnvDialog �Ի���
//#define IDD_SET_DBENV_DIALOG 202
class CSetDBEnvDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetDBEnvDialog)

public:
	CSetDBEnvDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDBEnvDialog();

// �Ի�������
	enum { IDD = IDD_SET_DBENV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_host;
	CString m_user;
	CString m_pwd;
	CString m_port;
};
