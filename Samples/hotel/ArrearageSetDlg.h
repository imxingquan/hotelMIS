/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		�����ʻ�����
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CArrearageSetDlg �Ի���

class CArrearageSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CArrearageSetDlg)

public:
	CArrearageSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CArrearageSetDlg();

// �Ի�������
	enum { IDD = IDD_ARREARAGE_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_GuiGroupBoxT;
	CStatic m_GuiGroupBoxB;
	CListCtrl m_GuiListCtrlArr;
	CButton m_GuiButtonAdd;
	CButton m_GuiButtonModify;
	CButton m_GuiButtonDel;
	CButton m_GuiButtonOk;

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDel();
};
