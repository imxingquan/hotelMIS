/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		���
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <HArrerageBdy.h>
#include <map>
using namespace std;

// CAddArrearageDialog �Ի���

class CAddArrearageDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddArrearageDialog)

public:
	CAddArrearageDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddArrearageDialog();

// �Ի�������
	enum { IDD = IDD_ADD_ARREARAGE_DLG };
	
protected:
	//CString ReplaceChar(CString &str)
	//{
	//	//�滻�ַ��е� "'" �Լ�
	//	CString strReturn("");
	//	TRY
	//	{
	//		if(str.GetLength()>0)
	//		{
	//			/*for ( int i = 0; i < str.GetLength(); i++)
	//			{
	//				if ( str.GetAt(i) != "'")
	//				strReturn+=str.GetAt(i);

	//			}*/
	//			strReturn=str;
	//			strReturn.TrimLeft();
	//			strReturn.TrimRight();

	//			strReturn.Replace(_T("'"),_T("''"));
	//			strReturn.Replace(_T("\\"),_T(""));
	//			TRACE(". = %d\n","'");
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
	//Control var
	CGuiGroupBox m_GuiGroupBox;
	CGuiButton m_GuiButtonCancel;
	CGuiButton m_GuiBtnAddArr;
	CGuiButton m_GuiDelZHBtn;
	//binding var
	virtual BOOL OnInitDialog();
	CGuiEdit m_GuiGZName;
	CGuiEdit m_GuiGZPhone;
	CGuiEdit m_GuiGZDept;
	CGuiEdit m_GuiGZDemo;

	CString m_gzName;
	CString m_gzPhone;
	CString m_gzDept;
	CString m_gzDemo;

	bool m_isModify ;
	int m_nPos; //Ҫ�޸ĵ� arid ��Ӧ�� nPos;
	hotelMIS::HArrerageBdy m_arrBdy;
	map<int,int> m_arrZHMap; //map<pos,arid>
	
	void Init();
	void Refresh();
	
	CListCtrl m_GuiArrZHListCtrl;
	afx_msg void OnBnClickedAddGzzh();
	
	afx_msg void OnBnClickedCancel();
	
	afx_msg void OnBnClickedDelzhBtn();
	afx_msg void OnEnChangeGzName();
	afx_msg void OnNMClickGzList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkGzList(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL m_cwCheck;
};
