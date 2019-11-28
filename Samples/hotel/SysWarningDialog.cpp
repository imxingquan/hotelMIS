// SysWarningDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SysWarningDialog.h"
#include ".\syswarningdialog.h"
#include "mmsystem.h"

// CSysWarningDialog �Ի���

IMPLEMENT_DYNAMIC(CSysWarningDialog, CDialog)
CSysWarningDialog::CSysWarningDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSysWarningDialog::IDD, pParent)
	, m_warning_msg(_T(""))
	, m_auto_close_msg(_T(""))
	, m_second(30)
{
}

CSysWarningDialog::~CSysWarningDialog()
{
}

void CSysWarningDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WARNING_MSG, m_warning_msg);
	DDX_Text(pDX, IDC_AUTO_CLOSE_MSG, m_auto_close_msg);
	DDX_Control(pDX, IDOK, m_GuiOkBtn);
	DDX_Control(pDX, IDC_WARNING_MSG, m_GuiWarningMsg);
}


BEGIN_MESSAGE_MAP(CSysWarningDialog, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysWarningDialog ��Ϣ�������

void CSysWarningDialog::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_auto_close_msg.Format("��Ϣ����%d����Զ��ر�!",m_second--);
	UpdateData(false);
	if ( m_second <= 0){
		KillTimer(1);
		GetParent()->SendMessage(WM_DELSELF);
		OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CSysWarningDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��	
	m_GuiOkBtn.ShowText();
	
	/*CDC * pDc = m_GuiWarningMsg.GetDC();
	pDc->SetTextColor(RGB(255,0,0));*/

	//->SetTextColor(RGB(255,0,0));
	
	CRect rt,taskBarRt;
	CWnd* taskBar;
	
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

    taskBar=FindWindow("Shell_TrayWnd",NULL); //������������ڵ�ָ��

    taskBar->GetWindowRect(&taskBarRt);

	GetWindowRect(&rt);
	int x = cx - rt.Width();
	int y = cy - rt.Height()-taskBarRt.Height();
	SetWindowPos(&CWnd::wndTopMost,x,y,0,0,SWP_NOSIZE);
	SetTimer(1,1000,NULL);
	
	char dir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH,dir);
	strcat(dir,"/sound/msg.wav");
	PlaySound(dir,::AfxGetInstanceHandle(),SND_ASYNC);
	
	AnimateWindow(1000,AW_BLEND);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSysWarningDialog::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//AnimateWindow(1000,AW_HIDE|AW_BLEND);
	CDialog::OnClose();

	
}

HBRUSH CSysWarningDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if( pWnd->GetDlgCtrlID() == IDC_WARNING_MSG)
		pDC->SetTextColor(RGB(0,0,200));
	if ( pWnd->GetDlgCtrlID() == IDC_AUTO_CLOSE_MSG){
		pDC->SetTextColor(RGB(255,0,0));
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
