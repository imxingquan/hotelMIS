/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		������������
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "KDBCon.h"
#include <map>
using namespace std;
// CStep1 �Ի���

class CStep1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep1)

public:
	CStep1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStep1();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_1 };

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
	CGuiGroupBox m_GuiGroupBoxL;
	CGuiEdit m_GuiEditTableStatus;
	CGuiEdit m_GuiEditPersonNum;
	CGuiButton m_GuiButtonAddTableStatus;
	CGuiButton m_GuiButtonDelTableStatus;
	CGuiButton m_GuiSetTableBmpBtn;
	
	CListCtrl m_GuiListCtrlTableStatus;	
	CString m_tableStatus;
	int m_personNum;
	hotelMIS::KDBCon m_con;
	map<int,int> m_tableStatusMap; //map<pos,table_state>
	int m_nPos;
public:
	//op
	void Init();
	void Refresh();
public:
	//msg
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAddTableStatus();
	afx_msg void OnBnClickedButtonDelTableStatus();
	afx_msg void OnNMClickListTableStatus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTableStatus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSetTablebmpButton();
	
};