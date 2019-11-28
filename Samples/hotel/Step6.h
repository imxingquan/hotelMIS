#pragma once
#include "afxwin.h"
#include "resource.h"
#include <map>
#include <string>
using namespace std;

/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:27278617 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		��ӡ������,��ӿ��Էֳ���ӡ�Ĺ���
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ	06-04-05	����ӵĹ���

--*/
// CStep6 �Ի���
//��ӡ������
class CStep6 : public CPropertyPage
{
	DECLARE_DYNAMIC(CStep6)

public:
	CStep6();   // ��׼���캯��
	virtual ~CStep6();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	void GetPrint(); //��ô�ӡ��
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
