/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		�˵�
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "KDBCon.h"
#include <map>
#include <string>
using namespace std;
// CRepertoryDialog �Ի���

class CRepertoryDialog : public CDialog
{
	DECLARE_DYNAMIC(CRepertoryDialog)

public:
	CRepertoryDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepertoryDialog();

// �Ի�������
	enum { IDD = IDD_REPERTORY_DLG };

protected:
	//CString ReplaceChar(CString &str)
	//{
	//	//�滻�ַ��е� "'" �Լ�
	//	CString strReturn("");
	//	TRY
	//	{
	//		if(str.GetLength()>0)
	//		{
	//			strReturn=str;
	//			strReturn.TrimLeft();
	//			strReturn.TrimRight();

	//			strReturn.Replace(_T("'"),_T("''"));
	//			strReturn.Replace(_T("\\"),_T(""));
	//		}
	//	}
	//	CATCH(CException,e){
	//		e->ReportError();
	//	}
	//	END_CATCH
	//		return strReturn;
	//}
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiComboBoxExt m_GuiComboReId;
	CGuiComboBoxExt m_GuiComboOpType;
	CGuiComboBoxExt m_GuiComboReUnit;
	CGuiEdit m_GuiEditReNum;
	CGuiEdit m_GuiEditRePrice;
	
	CGuiButton m_GuiOkBtn;
	CGuiButton m_GuiCancelBtn;
	
	CDateTimeCtrl m_GuiDateTimeCtrl;
	int m_reId;
	int m_reNum;
	float m_rePrice;
	CString m_reUnit;
	COleDateTime m_dateTime;
	
	int m_opType;

	hotelMIS::KDBCon m_con;
	map<int,pair<int,string> > m_maprep; //map<pos,pair<food_id,unit>>
	//op
	void Init();

	afx_msg void OnCbnSelchangeComboReId();
	afx_msg void OnCbnSelchangeComboReUnit();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	
};
