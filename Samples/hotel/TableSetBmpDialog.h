/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��������ͼ��
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
//#include "afxwin.h"

// CTableSetBmpDialog �Ի���

class CTableSetBmpDialog : public CDialog
{
	DECLARE_DYNAMIC(CTableSetBmpDialog)

public:
	CTableSetBmpDialog(CWnd* pParent = NULL);   // ��׼���캯��
	
	virtual ~CTableSetBmpDialog();

// �Ի�������
	enum { IDD = IDD_TABLE_SETBMP_DLG };
	int m_nPos;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	CImageList m_ImageList;
	CBitmap m_bitmap;
	
	DECLARE_MESSAGE_MAP()
public:
	int m_nState;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	
	void Init();
	CListCtrl m_GuiTableImageList;
	afx_msg void OnNMClickEmptyTableList(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_GuiOkButton;
};