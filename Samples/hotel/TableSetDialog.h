/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��������
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include "resource.h"
#include "afxwin.h"

#include "KDBCon.h"
// CTableSetDialog �Ի���

class CTableSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CTableSetDialog)

public:
	CTableSetDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CTableSetDialog(CWnd* pParent ,int tableId,int roomId);   // ��׼���캯��
	virtual ~CTableSetDialog();

// �Ի�������
	enum { IDD = IDD_TABLE_SET_DIALOG };

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

	int m_tableId;
	int m_roomId;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void Init();
	hotelMIS::KDBCon m_con;
	std::map<int,int> m_map_tableStatus,m_map_tableStatus2; //pos,state

	CString m_curTableMsg;
	CGuiEdit m_GuiTableNameEdit;
	CGuiComboBoxExt m_GuiComboTableStatus;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	CGuiGroupBox m_GuiGroupBox;
	CString m_tableName;
	afx_msg void OnBnClickedOk();
};
