#pragma once


// CSetDBDevDlg �Ի���

class CSetDBDevDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDBDevDlg)

public:
	CSetDBDevDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDBDevDlg();

// �Ի�������
	enum { IDD = IDD_SET_DBENV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
