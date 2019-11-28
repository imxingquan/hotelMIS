/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统启动logo
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once


// CFlashDialog 对话框

class CFlashDialog : public CDialog
{
	DECLARE_DYNAMIC(CFlashDialog)

public:
	CFlashDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFlashDialog();

// 对话框数据
	enum { IDD = IDD_FLASH_DIALOG };

protected:
	CBitmap m_bitmap;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int m_cx,m_cy;
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
