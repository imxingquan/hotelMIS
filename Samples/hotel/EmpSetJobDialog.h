/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		����Ա��ְ��
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
// CEmpSetJobDialog �Ի���
#include <map>
using namespace std;
class CEmpSetJobDialog : public CDialog
{
	DECLARE_DYNAMIC(CEmpSetJobDialog)

public:
	CEmpSetJobDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmpSetJobDialog();

// �Ի�������
	enum { IDD = IDD_SET_JOB_DLG };

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
	CGuiGroupBox m_GuiGroupBox;
	CGuiEdit m_GuiJobEdit;
	CGuiButton m_GuiAddJobButton;
	CGuiButton m_GuiDelJobButton;
	CListCtrl m_GuiJobListCtrl;
	CString m_jobName;
	hotelMIS::KDBCon m_con;
	map<int,int> m_jobSetmap;	//���ؼ�������jobId��
	bool m_modifyFlag;
	int m_nIndex;
public:
	void Init();
	void Refresh();
	afx_msg void OnBnClickedAddJobButton();
	afx_msg void OnBnClickedDelJobButton();
	afx_msg void OnNMClickJobList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeJobEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkJobList(NMHDR *pNMHDR, LRESULT *pResult);
};
