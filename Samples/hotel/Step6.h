#pragma once
#include "afxwin.h"
#include "resource.h"
#include <map>
#include <string>
using namespace std;

/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:27278617 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		打印机设置,添加可以分厨打印的功能
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉	06-04-05	新添加的功能

--*/
// CStep6 对话框
//打印机设置
class CStep6 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep6)

public:
	CStep6();   // 标准构造函数
	virtual ~CStep6();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	void GetPrint(); //获得打印机
	void Init();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_GuiComboBefore;
	CComboBox m_GuiComboBehind;
	CButton m_GuiCheckFenChu;
	CComboBox m_GuiComboMiandian;
	CComboBox m_GuiComboLiangCai;
	CComboBox m_GuiComboRerCai;
	
	CString m_sPrintBefore;
	CString m_sPrintBehind;
	CString m_sPrintMianDian;
	CString m_sPrintLiangCai;
	CString m_sPrintReCai;
	CButton m_GuiCheckMianDian;
	CButton m_GuiCheckLiangCai;
	CButton m_GuiCheckReCai;
	
	BOOL m_bFenchu;
	map<string,int> m_map;
	void CheckBehind();

	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnInitDialog();
		
	
	afx_msg void OnBnClickedCheckMiandian();
	afx_msg void OnBnClickedCheckLiangcai();
	afx_msg void OnBnClickedCheckRecai();
	BOOL m_bMianDian;
	BOOL m_bLiangCai;
	BOOL m_bReCai;
	virtual BOOL OnApply();
	afx_msg void OnCbnSelchangeComboBefore();

};
