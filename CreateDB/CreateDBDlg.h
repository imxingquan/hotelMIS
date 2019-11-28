// CreateDBDlg.h : ͷ�ļ�
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		����ϵͳ���ݿ� ���� demo.db �� starand.db �ļ��е�Sqlִ��
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ	08/28/05	v1.3 �汾

--*/

#pragma once
#include "afxwin.h"

#include "config.h"
#include "KDBCon.h"


// CCreateDBDlg �Ի���
class CCreateDBDlg : public CDialog
{
// ����
public:
	CCreateDBDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CREATEDB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetdbButton();
	LRESULT OnDetails(WPARAM wParam ,LPARAM lParam);
	
	CEdit m_hostEdit;
	CEdit m_portEdit;
	CEdit m_nameEdit;
	CEdit m_passwordEdit;
	CEdit m_detailsEdit;
	CString m_host;
	CString m_port;
	CString m_name;
	CString m_password;

	hotelMIS::KDBCon con;
	CButton m_setDBBtn;
	CString m_details;
	afx_msg void OnBnClickedSetdemodbBtn();
private:
	void SetDB(string dbfile);
public:
	CButton m_setDemoDBBtn;
};
