/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		ϵͳ����logo
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once


// CFlashDialog �Ի���

class CFlashDialog : public CDialog
{
	DECLARE_DYNAMIC(CFlashDialog)

public:
	CFlashDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlashDialog();

// �Ի�������
	enum { IDD = IDD_FLASH_DIALOG };

protected:
	CBitmap m_bitmap;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	int m_cx,m_cy;
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
