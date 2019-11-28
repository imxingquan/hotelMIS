/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		系统配置
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once



// CSetpConfigDialog
#include "./TreePropSheet/TreePropSheet.h"
#include "Step1.h"
#include "Step2.h"
//#include "Step3.h"
#include "Step4.h"
#include "Step5.h"
#include "Step6.h"

class CSetpConfigDialog : public TreePropSheet::CTreePropSheet
{
	DECLARE_DYNAMIC(CSetpConfigDialog)

public:
	CSetpConfigDialog();
	CSetpConfigDialog(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSetpConfigDialog(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSetpConfigDialog();
public:
	CStep1 m_step1;
	CStep2 m_step2;
	//CStep3 m_step3;
	CStep4 m_step4;
	CStep5 m_step5;
	CStep6 m_step6;

protected:
	bool m_isModify;
	void Init();
	LRESULT OnModified(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
};


