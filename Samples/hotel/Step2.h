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

// CStep2 �Ի���

class CStep2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep2)

public:
	CStep2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStep2();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_2 };

protected:
	//	CString ReplaceChar(CString &str)
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
	//op
	void Init();
	void Refresh();
public:
	
	CGuiEdit m_GuiEditCanTinName;
	CGuiEdit m_GuiEditNum;
	CGuiEdit m_GuiRoomNoEdit;
	
	CGuiButton m_GuiButtonDelCanTin;
	CGuiButton m_GuiButtonAddCanTin;
	CListCtrl m_GuiListCanTin;

	CString m_canTinName;
	int m_tableNum;	
	int m_roomNo;
	hotelMIS::KDBCon m_con;
	map<int,int> m_roomMap; //map<pos,room_id>
	BOOL m_isModify;
public:
	//msg
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddCantin();
	afx_msg void OnDeleteRoom();
	afx_msg void OnNMClickListCantin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMDblclkListCantin(NMHDR *pNMHDR, LRESULT *pResult);
};
