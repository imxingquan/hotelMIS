/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��ӡ����
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"

#include "resource.h"

// CPrintWarningDialog �Ի���

class CPrintWarningDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrintWarningDialog)

public:
	CPrintWarningDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrintWarningDialog();

// �Ի�������
	enum { IDD = IDD_PRINTWARNING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_printWarningCheck;
	afx_msg void OnBnClickedOk();
	CButton m_GuiPrintWarningCheck;
	CButton m_GuiJZAndPrintCheck;
	BOOL m_jzAndPrint;
	virtual BOOL OnInitDialog();
};
