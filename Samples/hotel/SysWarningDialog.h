/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		ϵͳ���浯���Ի���
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once


// CSysWarningDialog �Ի���
#include "resource.h"
#include "afxwin.h"

class CSysWarningDialog : public CDialog
{
	DECLARE_DYNAMIC(CSysWarningDialog)

public:
	CSysWarningDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysWarningDialog();

// �Ի�������
	enum { IDD = IDD_SYS_WARNING_DLG };
	void SetWarningMsg(CString msg){ m_warning_msg = msg;}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	

	DECLARE_MESSAGE_MAP()
public:
	CString m_warning_msg;
	CString m_auto_close_msg;
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	int m_second;
	afx_msg void OnClose();
	CGuiButton m_GuiOkBtn;
	CStatic m_GuiWarningMsg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
