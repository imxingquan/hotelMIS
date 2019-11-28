/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		更换餐桌图标
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
//#include "afxwin.h"

// CTableSetBmpDialog 对话框

class CTableSetBmpDialog : public CDialog
{
	DECLARE_DYNAMIC(CTableSetBmpDialog)

public:
	CTableSetBmpDialog(CWnd* pParent = NULL);   // 标准构造函数
	
	virtual ~CTableSetBmpDialog();

// 对话框数据
	enum { IDD = IDD_TABLE_SETBMP_DLG };
	int m_nPos;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
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