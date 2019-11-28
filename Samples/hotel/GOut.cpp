// GOut.cpp: implementation of the CGOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutlookDemo.h"
#include "GOut.h"
#include "resource.h"

#include "hotelMIS/KDBCon.h"
#include "hotelMIS/HAdmin.h"
#include "hotelMIS/HAdminBdy.h"
#include "hotelMIS/HOpType.h"
#include "MainFrm.h"
#include "TabView.h"
#include "CancelMenuSearchDlg.h"
#include ".\gout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//#define IDO_OUTODAY	   5600
//#define IDO_CALENDARIO 5601
//#define IDO_CONTACTO   5602

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CGOut,CGuiOutLookView)

CGOut::CGOut()
{

}

CGOut::~CGOut()
{

}

BEGIN_MESSAGE_MAP(CGOut, CGuiOutLookView)
	ON_WM_CREATE()
	ON_COMMAND(ID_REPAST, OnRepast)
	ON_COMMAND(ID_SYSPARA_SET, OnSysparaSet)
	ON_COMMAND(ID_KIND_SET, OnKindSet)
	ON_COMMAND(ID_MENU_MODIFY, OnMenuModify)
	ON_COMMAND(ID_EMP_SETJOB, OnEmpSetjob)
	ON_COMMAND(ID_FEATURE_MANAGE, OnFeatureManage)
	ON_COMMAND(ID_RE_INPUT, OnReInput)
	ON_COMMAND(ID_RE_OUTPUT, OnReOutput)
	ON_COMMAND(ID_DESTINE, OnDestine)
	ON_COMMAND(ID_DESTINE_MANAGE, OnDestineManage)
	ON_COMMAND(ID_ACCOUNT, OnAccount)
	ON_COMMAND(ID_CHANGETABLE, OnChangetable)
	ON_COMMAND(ID_EMP_ADD, OnEmpAdd)
	ON_COMMAND(ID_EMP_MANAGE, OnEmpManage)
	ON_COMMAND(ID_DAY_REPORT, OnDayReport)
	ON_COMMAND(ID_SYSUSER_SET, OnSysuserSet)
	ON_COMMAND(ID_RE_SEARCH, OnReSearch)
	ON_COMMAND(ID_SEARCH_ACCOUNTS, OnSearchAccounts)
	ON_COMMAND(ID_OTHER_CALC, OnOtherCalc)
	ON_COMMAND(ID_OTHER_NOTEPAD, OnOtherNotepad)
	ON_COMMAND(ID_OTHER_PAINT, OnOtherPaint)
	ON_MESSAGE(WM_DELMENU,OnDelMenu)
	ON_COMMAND(ID_LESSON, OnLesson)
	ON_COMMAND(ID_ARREARAGE_GZJZ, OnArrearageGzjz)
	ON_COMMAND(ID_CANCEL_MENU_SEARCH, OnCancelMenuSearch)
	ON_COMMAND(ID_MEMBER_MANAGE, OnMemberManage)
	ON_COMMAND(ID_MEMBER_BIRTH, OnMemberBirth)
	ON_COMMAND(ID_MEMBER_CASTSEARCH, OnMemberCastsearch)
	ON_COMMAND(ID_MEMBER_CZ, OnMemberCz)
	ON_COMMAND(ID_MEMBER_ZZ, OnMemberZz)
//	ON_COMMAND(ID_APP_EXIT, OnAppExit)
//	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()


LRESULT  CGOut::OnDelMenu(WPARAM wParam,LPARAM lParam)
{
	/*m_NewMenu.DeleteMenu(0,MF_BYPOSITION);
	this->m_wndMenuBar.DrawMenuBar();
	::DrawMenuBar(m_hWnd);*/
	return 0;
}

int CGOut::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CGuiOutLookView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//Ȩ�޳�ʼ��
	return InitPurview();
}


int CGOut::InitPurview()
{
	hotelMIS::KDBCon con;
	hotelMIS::HAdminBdy bdy(con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),con.get_con());

	int i = 0;
	//��������
	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,"res/bitmap1.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Attach(hbitmap);
	
	CImageList m_ImageList; 
	m_ImageList.Create(32, 32, TRUE | ILC_COLOR32, 26, 0); 
	m_ImageList.Add(&m_bitmap,RGB(255,255,255));
	
	if ( op.getM0() )
	{
		if (!m_tab[0].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_0))
			return -1;
		//��������
		m_tab[0].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		//m_tab[0].SetImageList(IDB_BITMAP1, 32, 0, RGB(255,0,0));
		m_tab[0].AddItem(ID_REPAST,MAKEINTRESOURCE(ID_REPAST),i++,MAKEINTRESOURCE(ID_REPAST_TOOLTIPS));//�Ͳ�
		m_tab[0].AddItem(ID_DESTINE,MAKEINTRESOURCE(ID_DESTINE),i++,MAKEINTRESOURCE(ID_DESTINE_TOOLTIPS));//Ԥ��
		m_tab[0].AddItem(ID_DESTINE_MANAGE,MAKEINTRESOURCE(ID_DESTINE_MANAGE),i++,MAKEINTRESOURCE(ID_DESTINE_MANAGE_TOOLTIPS)); //Ԥ������
		m_tab[0].AddItem(ID_ACCOUNT,MAKEINTRESOURCE(ID_ACCOUNT),i++,MAKEINTRESOURCE(ID_ACCOUNT_TOOLTIPS));//����
		m_tab[0].AddItem(ID_CHANGETABLE,MAKEINTRESOURCE(ID_CHANGETABLE),i++,MAKEINTRESOURCE(ID_CHANGETABLE_TOOLTIPS));//����
		//m_tab[0].AddItem(ID_ARREARAGE,MAKEINTRESOURCE(ID_ARREARAGE),i++,MAKEINTRESOURCE(ID_ARREARAGE_TOOLTIPS));//����
		m_tab[0].AddItem(ID_ARREARAGE_MANAGE,MAKEINTRESOURCE(ID_ARREARAGE_MANAGE),i++,MAKEINTRESOURCE(ID_ARREARAGE_MANAGE_TOOLTIPS));//�����˻�����
		m_tab[0].AddItem(ID_ARREARAGE_GZJZ,MAKEINTRESOURCE(ID_ARREARAGE_GZJZ),i++,MAKEINTRESOURCE(ID_ARREARAGE_GZJZ_TOOLTIPS)); //���˽���

		if ( m_tab[0].m_hWnd ){ 
			m_tab[0].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[0],MAKEINTRESOURCE(ID_TAB_0));
		}
	}
	
	//������
	//if ( op.getM1() )
	//{
	//	if (!m_tab[1].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_1))
	//		return -1;
	//	m_tab[1].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
	//	m_tab[1].AddItem(ID_RE_INPUT,MAKEINTRESOURCE(ID_RE_INPUT),i++,MAKEINTRESOURCE(ID_RE_INPUT_TOOLTIPS));//���Ǽ�
	//	m_tab[1].AddItem(ID_RE_OUTPUT,MAKEINTRESOURCE(ID_RE_OUTPUT),i++,MAKEINTRESOURCE(ID_RE_OUTPUT_TOOLTIPS));//����Ǽ�
	//	m_tab[1].AddItem(ID_REP_DETAILS_SEARCH,MAKEINTRESOURCE(ID_REP_DETAILS_SEARCH),i++,MAKEINTRESOURCE(ID_REP_DETAILS_SEARCH)); //������ϸ
	//	m_tab[1].AddItem(ID_REP_TOTAL_SEARCH,MAKEINTRESOURCE(ID_REP_TOTAL_SEARCH),i++,MAKEINTRESOURCE(ID_REP_TOTAL_SEARCH)); //������ܲ�ѯ
	//	m_tab[1].AddItem(ID_INOUT_ZD_SEARCH,MAKEINTRESOURCE(ID_INOUT_ZD_SEARCH),i++,MAKEINTRESOURCE(ID_INOUT_ZD_SEARCH)); //�����˵���ѯ
	//	m_tab[1].AddItem(ID_RE_SEARCH,MAKEINTRESOURCE(ID_RE_SEARCH),i++,MAKEINTRESOURCE(ID_RE_SEARCH));//����ѯ

	//	if ( m_tab[1].m_hWnd ){ 
	//		m_tab[1].StyleDispl(GUISTYLE_2003);
	//		cf.AddFolder(&m_tab[1],MAKEINTRESOURCE(ID_TAB_1));
	//	}
	//}

	//�˵���ѯ
	if ( op.getM2() )
	{
		if (!m_tab[2].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_2))
			return -1;
		m_tab[2].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[2].AddItem(ID_SEARCH_ACCOUNTS,MAKEINTRESOURCE(ID_SEARCH_ACCOUNTS),i++,MAKEINTRESOURCE(ID_SEARCH_ACCOUNTS_TOOLTIPS));//�˵���ѯ
		m_tab[2].AddItem(ID_CANCEL_MENU_SEARCH,MAKEINTRESOURCE(ID_CANCEL_MENU_SEARCH),i++,MAKEINTRESOURCE(ID_CANCEL_SEARCH_TOOLTIPS));

		if ( m_tab[2].m_hWnd ){ 
			m_tab[2].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[2],MAKEINTRESOURCE(ID_TAB_2));
		}

	}
	//Ա������
	if ( op.getM3() )
	{
		if (!m_tab[3].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_3))
			return -1;
		m_tab[3].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[3].AddItem(ID_EMP_ADD,MAKEINTRESOURCE(ID_EMP_ADD),i++,MAKEINTRESOURCE(ID_EMP_ADD_TOOLTIPS));//���Ա��
		m_tab[3].AddItem(ID_EMP_MANAGE,MAKEINTRESOURCE(ID_EMP_MANAGE),i++,MAKEINTRESOURCE(ID_EMP_MANAGE_TOOLTIPS));//Ա������
		//m_tab[3].AddItem(ID_EMP_SEARCH,MAKEINTRESOURCE(ID_EMP_SEARCH),2,MAKEINTRESOURCE(ID_EMP_SEARCH_TOOLTIPS));//Ա����ѯ
		m_tab[3].AddItem(ID_EMP_SETJOB,MAKEINTRESOURCE(ID_EMP_SETJOB),i++,MAKEINTRESOURCE(ID_EMP_SETJOB_TOOLTIPS));//ְλ����

		if ( m_tab[3].m_hWnd ){ 
			m_tab[3].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[3],MAKEINTRESOURCE(ID_TAB_3));
		}

	}
	//���׹���
	if ( op.getM4() )
	{
		if (!m_tab[4].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_4))
			return -1;
		m_tab[4].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[4].AddItem(ID_MENU_MODIFY,MAKEINTRESOURCE(ID_MENU_MODIFY),i++,MAKEINTRESOURCE(ID_MENU_MODIFY_TOOLTIPS));//����ά��
		m_tab[4].AddItem(ID_FEATURE_MANAGE,MAKEINTRESOURCE(ID_FEATURE_MANAGE),i++,MAKEINTRESOURCE(ID_FEATURE_MANAGE_TOOLTIPS));//��ɫ�˹���
		m_tab[4].AddItem(ID_KIND_SET,MAKEINTRESOURCE(ID_KIND_SET),i++,MAKEINTRESOURCE(ID_KIND_SET_TOOLTIPS));//��λ������

		if ( m_tab[4].m_hWnd ){ 
			m_tab[4].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[4],MAKEINTRESOURCE(ID_TAB_4));
		}
	}
	//ͳ�Ʊ���
	if ( op.getM5() )
	{
		if (!m_tab[5].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_5))
			return -1;
		m_tab[5].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[5].AddItem(ID_DAY_REPORT,MAKEINTRESOURCE(ID_DAY_REPORT),i++,MAKEINTRESOURCE(ID_DAY_REPORT_TOOLTIPS));//��Ӫ�ձ���
		//m_tab[5].AddItem(ID_MONTH_REPORT,MAKEINTRESOURCE(ID_MONTH_REPORT),i++,MAKEINTRESOURCE(ID_MONTH_REPORT_TOOLTIPS));//��Ӫ�±���
		//m_tab[5].AddItem(ID_YEAR_REPORT,MAKEINTRESOURCE(ID_YEAR_REPORT),i++,MAKEINTRESOURCE(ID_YEAR_REPORT_TOOLTIPS));//��Ӫ�걨��
		m_tab[5].AddItem(ID_REPORT_DETAILS,MAKEINTRESOURCE(ID_REPORT_DETAILS),i++,MAKEINTRESOURCE(ID_REPORT_DETAILS));//��Ʒ������ϸ
		m_tab[5].AddItem(ID_SKY_MENU,MAKEINTRESOURCE(ID_SKY_MENU),i++,MAKEINTRESOURCE(ID_SKY_MENU_TOOLTIPS));//��Ӫ�걨��

		if ( m_tab[5].m_hWnd ){ 
			m_tab[5].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[5],MAKEINTRESOURCE(ID_TAB_5));
		}

	}
	
	//��Ա����
	if ( op.getM8())
	{
		if ( !m_tab[8].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_8))
			return -1;
		m_tab[8].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[8].AddItem(ID_MEMBER_MANAGE,MAKEINTRESOURCE(ID_MEMBER_MANAGE),i++,MAKEINTRESOURCE(ID_MEMBER_MANAGE)); //��Ա����
		m_tab[8].AddItem(ID_MEMBER_CASTSEARCH,MAKEINTRESOURCE(ID_MEMBER_CASTSEARCH),i++,MAKEINTRESOURCE(ID_MEMBER_CASTSEARCH)); //��Ա���Ѳ�ѯ
		m_tab[8].AddItem(ID_MEMBER_CZ,MAKEINTRESOURCE(ID_MEMBER_CZ),i++,MAKEINTRESOURCE(ID_MEMBER_CZ)); //��ֵ��ѯ
		m_tab[8].AddItem(ID_MEMBER_ZZ,MAKEINTRESOURCE(ID_MEMBER_ZZ),i++,MAKEINTRESOURCE(ID_MEMBER_ZZ)); //��Աת��
		//m_tab[8].AddItem(ID_MEMBER_BIRTH,MAKEINTRESOURCE(ID_MEMBER_BIRTH),i++,MAKEINTRESOURCE(ID_MEMBER_BIRTH)); //��Ա����

		if ( m_tab[8].m_hWnd ){ 
			m_tab[8].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[8],MAKEINTRESOURCE(ID_TAB_8));
		}
	}

	//ϵͳ����
	if ( op.getM6() )
	{
		if (!m_tab[6].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_6))
			return -1;
		m_tab[6].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[6].AddItem(ID_SYSUSER_SET,MAKEINTRESOURCE(ID_SYSUSER_SET),i++,MAKEINTRESOURCE(ID_SYSUSER_SET_TOOLTIPS));//ϵͳ�û�����
		m_tab[6].AddItem(ID_SYSPARA_SET,MAKEINTRESOURCE(ID_SYSPARA_SET),i++,MAKEINTRESOURCE(ID_SYSPARA_SET_TOOLTIPS));//ϵͳ��������

		if ( m_tab[6].m_hWnd ){ 
			m_tab[6].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[6],MAKEINTRESOURCE(ID_TAB_6));
		}
	}
	//��������
	if ( op.getM7() )
	{
		if (!m_tab[7].Create(WS_VISIBLE,CRect(0,0,0,0), &cf, ID_TAB_7))
			return -1;
		m_tab[7].SetImageList(&m_bitmap,&m_ImageList,32,0,RGB(255,255,255));
		m_tab[7].AddItem(ID_OTHER_CALC,MAKEINTRESOURCE(ID_OTHER_CALC),i++,MAKEINTRESOURCE(ID_OTHER_CALC_TOOLTIPS));//������
		m_tab[7].AddItem(ID_OTHER_PAINT,MAKEINTRESOURCE(ID_OTHER_PAINT),i++,MAKEINTRESOURCE(ID_OTHER_PAINT_TOOLTIPS));//����
		m_tab[7].AddItem(ID_OTHER_NOTEPAD,MAKEINTRESOURCE(ID_OTHER_NOTEPAD),i++,MAKEINTRESOURCE(ID_OTHER_NOTEPAD_TOOLTIPS));//���±�

		if ( m_tab[7].m_hWnd ){ 
			m_tab[7].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[7],MAKEINTRESOURCE(ID_TAB_7));
		}
	}

	/*for ( int i =0; i<CGOut::tsize; i++){
		if ( m_tab[i].m_hWnd ){ 
			m_tab[i].StyleDispl(GUISTYLE_2003);
			cf.AddFolder(&m_tab[i],MAKEINTRESOURCE(ID_TAB_0+i));
		}
	}*/
	cf.SelectFolder(0);
	return 0;
}

void CGOut::OnRepast()
{
	// TODO: �ͲͲ���������Ϣ���͵�CDiningRoomTab
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_REPAST);
}

void CGOut::OnSysparaSet()
{
	//AfxMessageBox(_T("test"));
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_SYSPARA_SET);
	/*CSetpConfigDialog dlg(_T("ϵͳ����"));
	dlg.SetWizardMode();
	dlg.DoModal();*/
}

void CGOut::OnKindSet()
{
	// TODO: ��λ����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_KIND_SET);
	/*CKindUnitSetDialog dlg;
	dlg.DoModal();*/

}

void CGOut::OnMenuModify()
{
	// TODO: ����ά��
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_MENU_MODIFY);
	/*CMenuManagerDialog dlg;
	dlg.DoModal();*/
}



void CGOut::OnFeatureManage()
{
	// TODO: ��ɫ�˹���
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_FEATURE_MANAGE);
	/*CSpecialMenuDialog dlg;
	dlg.DoModal();*/
}

void CGOut::OnReInput()
{
	// TODO: ���Ǽ�
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_RE_INPUT);
	/*CRepertoryDialog dlg;
	dlg.DoModal();*/
}

void CGOut::OnReOutput()
{
	// TODO: ����Ǽ�
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_RE_OUTPUT);
	/*COutStoreDialog dlg;
	dlg.DoModal();*/
}

void CGOut::OnReSearch()
{
	// TODO:����ѯ
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_RE_SEARCH);
}


void CGOut::OnDestine()
{
	// TODO: ����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_DESTINE);
}

void CGOut::OnDestineManage()
{
	// TODO:Ԥ���͹���
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_DESTINE_MANAGE);

	/*CYDDialog dlg;
	dlg.DoModal();*/

}

void CGOut::OnAccount()
{
	// TODO:����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_ACCOUNT);
}

void CGOut::OnArrearageGzjz()
{
	// TODO: ���˽���
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_ARREARAGE_GZJZ);
}

void CGOut::OnChangetable()
{
	// TODO: ����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_CHANGETABLE);
}

void CGOut::OnEmpAdd()
{
	// TODO: �����Ա��
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_EMP_ADD);

	/*CEmployeeDialog dlg;
	dlg.DoModal();*/
	
}

void CGOut::OnEmpManage()
{
	// TODO: Ա������
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_EMP_MANAGE);

	/*CEmpManagerDialog dlg;
	dlg.DoModal();*/
}
void CGOut::OnEmpSetjob()
{
	// TODO: ְλ����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_EMP_SETJOB);

	/*CEmpSetJobDialog dlg;
	dlg.DoModal();*/
}
void CGOut::OnDayReport()
{
	// TODO: ��Ӫ�ձ���
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_DAY_REPORT);
	/*CReportDayDialog dlg;
	dlg.DoModal();*/
}



void CGOut::OnSysuserSet()
{
	// TODO:  ϵͳ�û�����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_SYSUSER_SET);
	/*CSysUserManagerDlg dlg;
	dlg.DoModal();*/
}


void CGOut::OnSearchAccounts()
{
	// TODO �˵���ѯ
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_SEARCH_ACCOUNTS);
}

void CGOut::OnOtherCalc()
{
	// TODO: ������
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_OTHER_CALC);
}

void CGOut::OnOtherNotepad()
{
	// TODO: ���±�
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_OTHER_NOTEPAD);
}

void CGOut::OnOtherPaint()
{
	// TODO: ͼ��
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_OTHER_PAINT);

}

void CGOut::OnLesson()
{
	// TODO: �γ�
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_LESSON);
}



void CGOut::OnCancelMenuSearch()
{
	// TODO: ��ѯ�˲���ϸ
	CCancelMenuSearchDlg dlg;
	dlg.DoModal();
	
}
void CGOut::OnMemberManage()
{
	// TODO: ��Ա����
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_MEMBER_MANAGE);
}

void CGOut::OnMemberBirth()
{
	// TODO: ���ղ�ѯ
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_MEMBER_BIRTH);
}

void CGOut::OnMemberCastsearch()
{
	// TODO: ���Ѳ�ѯ
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_MEMBER_CASTSEARCH);
}

void CGOut::OnMemberCz()
{
	// TODO: ��ֵ��ѯ
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_MEMBER_CZ);
}

void CGOut::OnMemberZz()
{
	// TODO: ת�˲�ѯ
	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_MEMBER_ZZ);
}

//void CGOut::OnAppExit()
//{
//	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
//	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
//	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_APP_EXIT);
//}

//void CGOut::OnAppAbout()
//{
//	CMainFrame* MainFrame1=(CMainFrame*)this->GetParent()->GetParent(); 
//	CTabView* pTabView=(CTabView*)MainFrame1->GetSplitterWnd2().GetPane(0,0);	
//	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_APP_ABOUT);
//}
