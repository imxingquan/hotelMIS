// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "resource.h"
#include "MainFrm.h"
#include "GOut.h"
#include "Cajon.h"
#include "GuiDrawLayer.h"
#include "GuiToolButton.h"
#include "TabView.h"
#include "DetailsListView.H"
#include "OutlookDemoDoc.h"
#include "KDBCon.h"
#include "HAdminBdy.h"
#include "HOpType.h"

#include "HDestineCtrl.h"
#include "KDBCon.h"
#include ".\mainfrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define IDT_BACK 5555
#define IDT_FORW 5556
#define IDT_GO	 5557 
#define IDT_DEL  5558
#define IDT_UNDO 5559
#define IDT_STANDAR 5560
#define ID_VIEWCAPTION 5000

#define IDO_OUTODAY	   5600
#define IDO_CALENDARIO 5601
#define IDO_CONTACTO   5602
#define IDO_TAREAS     5603
#define IDO_NOTAS	   5604	
#define IDO_ELIMINAR   5605

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(IDT_BACK,OnBack)
	ON_COMMAND(ID_2003, On2003)
	ON_COMMAND(ID_XP, OnXP)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDO_OUTODAY,  OnToday)
	ON_COMMAND(IDO_CALENDARIO, OnCalendario)
	ON_COMMAND(IDO_CONTACTO, OnContacto)
	ON_COMMAND(IDO_TAREAS, OnTareas)
	ON_COMMAND(IDO_NOTAS, OnNotas)
	ON_COMMAND(IDO_ELIMINAR, OnEliminar)
	ON_UPDATE_COMMAND_UI(ID_2003, OnUpdate2003)
	ON_UPDATE_COMMAND_UI(ID_XP, OnUpdateXp)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_MESSAGE(WM_DELMENU,OnDelMenu)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_WM_TIMER()
	ON_WM_CLOSE()
//	ON_COMMAND(ID_APP_EXIT, OnAppExit)
//	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

void CMainFrame::OnBack()
{
	AfxMessageBox("Back");
	
}

void CMainFrame::OnToday()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("OutLook Today");
	pBtn->SetToolTip("OutLook Today");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(0));
	m_guiMiniToolLeft.RecalLayout();
}




void CMainFrame::OnCalendario()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Calendario");
	pBtn->SetToolTip("Calendario");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(1));
	m_guiMiniToolLeft.RecalLayout();
}


void CMainFrame::OnContacto()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Contacto");
	pBtn->SetToolTip("Contacto");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(2));
	m_guiMiniToolLeft.RecalLayout();
}

void CMainFrame::OnTareas()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Tareas");
	pBtn->SetToolTip("Tareas");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(3));
	m_guiMiniToolLeft.RecalLayout();
}

void CMainFrame::OnNotas()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Notas");
	pBtn->SetToolTip("Notas");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(4));
	m_guiMiniToolLeft.RecalLayout();
}

void CMainFrame::OnEliminar()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Eliminar");
	pBtn->SetToolTip("Eliminar");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(15));
	m_guiMiniToolLeft.RecalLayout();
}

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_b2003=true;
	m_bXp = false;
	
}

CMainFrame::~CMainFrame()
{
	vector<CSysWarningDialog*>::iterator pit;
	for ( pit = m_pWarningVec.begin(); pit != m_pWarningVec.end(); pit++)
	{
		//(*pit)->SendMessage(WM_CLOSE);
		delete (*pit);
	}
}
int CMainFrame::InitMenu(UINT uIDMenu)
{
	if (!m_wndMenuBar.CreateEx(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_SIZE_DYNAMIC ) )
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
	
	//m_wndMenuBar.LoadMenuBar(IDR_MAINFRAME);
	//::SetMenu(this->m_hWnd,m_wndMenuBar.m_hMenu);
	//DeleteMenu(GetMenu()->m_hMenu,1,MF_BYPOSITION);
	//DeleteMenu(m_wndMenuBar.m_hMenu,1,MF_BYPOSITION);
	//m_wndMenuBar.DrawMenuBar();
	//m_wndMenuBar.RefreshBar();
	//DrawMenuBar();
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	SetMenu(&menu);
	menu.Detach();
	m_wndCool.Install(this);
	m_wndCool.LoadToolbar(uIDMenu);
	
	return 0;
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitMenu(IDR_MAINFRAME);

	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
	EnableDocking(CBRS_ALIGN_ANY);
//	m_wndToolBar.SetTextButton(0,"&New"); 
//	m_wndToolBar.SetTextButton(1,"&Send/Receiver"); 
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	
	if (!m_CapOutBar.Create (WS_CHILD | WS_VISIBLE , 
			this,ID_VIEWCAPTION))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	if (!m_CapOutBar.SetSplitter(&m_MiniSplitter))
		return FALSE;

	m_MiniSplitter.AddMiniToolLeft(&m_guiMiniToolLeft);
	m_MiniSplitter.AddMiniToolRight(&m_guiMiniToolRight);
	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,"res/bitmap2.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Attach(hbitmap);
	
	 
	m_ImageList.Create(16, 16, TRUE | ILC_COLOR8, 16,0); 
	m_ImageList.Add(&m_bitmap,RGB(255,255,255));
	m_guiMiniToolLeft.SetImageList(&m_bitmap,&m_ImageList,RGB (255, 255, 255));
	m_guiMiniToolRight.SetImageList(&m_bitmap,&m_ImageList,RGB (255, 255,255));
	
	//Left MiniTool 
	//m_guiMiniToolLeft.AddButton(11,IDT_BACK,NULL,"Back ","Back");
	//m_guiMiniToolLeft.AddButton(12,IDT_FORW,NULL,"Forward","Forward");
	CTime t1=CTime::GetCurrentTime();
	CString t;
	t.Format("%s             操作员: %s",t1.Format("%Y年%m月%d日"),hotelMIS::HAdminBdy::_ad_name.c_str());
	m_guiMiniToolLeft.AddButton(3,IDT_STANDAR,NULL,t,t1.Format("今天的日期是%Y-%m-%d %A!"));
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetFontColor(RGB(150,0,0));

	//Right MiniTool
	//m_guiMiniToolRight.CreateCombo(&m_cb,333,100);
	m_guiMiniToolRight.AddButton(13,ID_REFRESH,NULL,"Go  ","单击Go 刷新当前餐厅!");
	pBtn = m_guiMiniToolRight.GetButton(ID_REFRESH);
	pBtn->SetFontColor(RGB(0,255,0));
	//m_guiMiniToolRight.AddButton(15,IDT_UNDO,NULL,"Undo  ","Undo  ");
	//m_MiniSplitter.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorBTNHigh());
	m_guiMiniToolRight.SetCaption("刷新:",CGuiMiniTool::ALIGN_LEFT);
	m_guiMiniToolRight.SetColorCaption(GuiDrawLayer::GetRGBColorBTNHigh());
	m_guiMiniToolRight.AutoSize(TRUE);
	
	/*m_cb.AddString("outlook:Tareas");
	m_cb.AddString("outlook:Notas");
	m_cb.AddString("Toolbar Combobox item four");
	m_cb.AddString("Toolbar Combobox item five");
	m_cb.AddString("Toolbar Combobox item six");*/
	
	m_guiMiniToolLeft.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	m_guiMiniToolRight.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	//m_cb.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	
//	On2003();
	sProfile = _T("DevOutLook");
	//LoadBars();
	//active las las siguientes lineas para ver la etiqueta a la derecha
	//m_guiMiniToolLeft.SetCaption("Fecha del dia de hoy",CGuiMiniTool::ALIGN_RIGHT);
	//m_guiMiniToolLeft.SetColorCaption(GuiDrawLayer::GetRGBColorBTNHigh());
//
	SetTimer(1,1000*60,NULL);
	//设置权限
	SetMenuQX();
	
	//SetMenu(&m_NewMenu);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	//AfxGetApp()->m_pMainWnd->GetMenu()->DeleteMenu(0,MF_BYPOSITION);
	return TRUE;
}

LRESULT  CMainFrame::OnDelMenu(WPARAM wParam,LPARAM lParam)
{
	/*CMenu menu;
	GetMainMenu()->DeleteMenu(0,MF_BYPOSITION);*/

	//::DeleteMenu(this->m_wndMenuBar.m_hMenu,0,MF_BYPOSITION);
	
	//::EnableMenuItem(m_wndMenuBar.m_hMenu,0,MF_DISABLED);
	
	hotelMIS::KDBCon con;
	hotelMIS::HAdminBdy bdy(con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),con.get_con());
	
	/*if ( !op.getM7()){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,7,MF_BYPOSITION);
		
	}
	if ( !op.getM6()){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,6,MF_BYPOSITION);
		
	}
	if ( !op.getM5()){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,5,MF_BYPOSITION);
		
	}
	if ( !op.getM4()){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,4,MF_BYPOSITION);
		
	}
	
	if ( !op.getM3()){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,3,MF_BYPOSITION);
		
	}
	
	if ( !op.getM2() ){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,2,MF_BYPOSITION);
		
	}
	
	if ( !op.getM1() ){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,1,MF_BYPOSITION);
		
	}

	if ( !op.getM0() ){
		::DeleteMenu(this->m_wndMenuBar.m_hMenu,0,MF_BYPOSITION);
		
	}*/
	
	
	
	
	
	//::DrawMenuBar(m_wndMenuBar.GetOwner()->m_hWnd);
	/*this->m_wndMenuBar.RefreshBar();
	this->DrawMenuBar();
	this->m_wndMenuBar.DrawMenuBar();*/
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}
	
	// Outlook bar view.
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CGOut),
		CSize(150, 0), pContext))
	{
		TRACE0("Failed to create CGOut\n"); 
		return FALSE;
	}	
	/*if (!m_wndSplitter.CreateView(0,1, RUNTIME_CLASS(CTabView),
		CSize(90, 0), pContext))
	{
		TRACE0("Failed to create CGOut\n"); 
		return FALSE;
	}*/
	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter,2,1,WS_CHILD|WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0,1)))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}
	m_wndSplitter2.SetBorderFlat(7);
	if ( !m_wndSplitter2.CreateView(0,0,RUNTIME_CLASS(CTabView),CSize(0,500),pContext) )
	{
		return FALSE;
	}
	if ( !m_wndSplitter2.CreateView(1,0,RUNTIME_CLASS(CDetailsListView),CSize(0,0),pContext) )
	{
		return FALSE;
	}
	/*if (!m_wndSplitter.CreateView(1,0, RUNTIME_CLASS(CGOut),
		CSize(10, 0), pContext))
	{
		TRACE0("Failed to create CGOut\n"); 
		return FALSE;
	}	
	if (!m_wndSplitter.CreateView(1,1, RUNTIME_CLASS(CGOut),
		CSize(10, 0), pContext))
	{
		TRACE0("Failed to create CGOut\n"); 
		return FALSE;
	}*/
	return TRUE; //CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSysColorChange() 
{
	CFrameWnd::OnSysColorChange();
	GuiDrawLayer::IsThemeXP();
	m_MiniSplitter.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorBTNHigh());	
	m_guiMiniToolLeft.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	m_guiMiniToolRight.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
}

void CMainFrame::OnEditCut()
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::On2003()
{
	GuiDrawLayer::m_Style=GUISTYLE_2003;
	StyleDispl(GUISTYLE_2003);
	m_guiMiniToolLeft.StyleDispl(GUISTYLE_2003);
	m_guiMiniToolRight.StyleDispl(GUISTYLE_2003);
	m_CapOutBar.StyleDispl(GUISTYLE_2003);
	m_wndSplitter.StyleDispl(GUISTYLE_2003);
	CGOut* pWnd =(CGOut*)m_wndSplitter.GetPane(0, 0);
	for ( int i =0; i<CGOut::tsize; i++)
	{	if ( pWnd->m_tab[i].m_hWnd )
			pWnd->m_tab[i].StyleDispl(GUISTYLE_2003);
	}
	pWnd->cf.StyleDispl(GUISTYLE_2003);
	m_b2003 = true;
	m_bXp = false;
	CTabView* pTabView=(CTabView*)this->GetSplitterWnd2().GetPane(0,0);	
	pTabView->SendMessage(WM_ONREDRAW);
}

void CMainFrame::OnXP()
{
	GuiDrawLayer::m_Style=GUISTYLE_XP;
	StyleDispl(GUISTYLE_XP);
	m_guiMiniToolLeft.StyleDispl(GUISTYLE_XP);
	m_guiMiniToolRight.StyleDispl(GUISTYLE_XP);
	m_CapOutBar.StyleDispl(GUISTYLE_XP);
	m_wndSplitter.StyleDispl(GUISTYLE_XP);
	CGOut* pWnd =(CGOut*)m_wndSplitter.GetPane(0, 0);
	for ( int i =0; i<CGOut::tsize; i++)
	{
		if ( pWnd->m_tab[i].m_hWnd )
			pWnd->m_tab[i].StyleDispl(GUISTYLE_XP);
	}
	pWnd->cf.StyleDispl(GUISTYLE_XP);
	m_bXp=true;
	m_b2003=false;
	CTabView* pTabView=(CTabView*)this->GetSplitterWnd2().GetPane(0,0);	
	pTabView->SendMessage(WM_ONREDRAW);
	
}


BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( CGuiFrameWnd::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
		return TRUE;	
	COutlookDemoDoc *pDoc = ( COutlookDemoDoc *) GetActiveDocument();
	if ( pDoc != NULL)
		return pDoc->RoteCmdToAllViews(GetActiveView(),nID,nCode,pExtra,pHandlerInfo);
	return FALSE;
	//return CGuiFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnUpdate2003(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_b2003);
	
}

void CMainFrame::OnUpdateXp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bXp);
}

void CMainFrame::OnViewToolbar()
{
	// TODO: 在此添加命令处理程序代码
	ShowHideBar(&m_wndToolBar);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_wndToolBar.IsVisible());
}

void CMainFrame::OnRefresh()
{
	// TODO: 在此添加命令处理程序代码
	CTabView* pTabView=(CTabView*)this->GetSplitterWnd2().GetPane(0,0);	
	pTabView->PostMessage(WM_COMMAND,(WPARAM)ID_REFRESH);
}


void CMainFrame::WarningDestine()
{
	COleDateTime t = COleDateTime::GetCurrentTime();
	TRACE("%4d-%2d-%2d,%2d:%2d:%2d\n",t.GetYear(),t.GetMonth(),t.GetDay(),
		t.GetHour(),t.GetMinute(),t.GetSecond());
	hotelMIS::KDBCon m_con;
	hotelMIS::HDestineCtrl destineCtrl(m_con.get_con());
	hotelMIS::HDestineVec vec = destineCtrl.getAllDestine();
	hotelMIS::HDestineVec::iterator it;
	vector<int> vd;
	int hour = 0;
	int min  = 0;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		if ( it->bdisp == 1){
			string::size_type pos =0 ,prev_pos  = 0;
			while ( (pos = it->come_date.find('-',pos))
				!= string::npos)
			{
				vd.push_back(atoi(it->come_date.substr(prev_pos,pos-prev_pos).c_str()));
				prev_pos = ++pos;
			}
			vd.push_back(atoi(it->come_date.substr(prev_pos,pos-prev_pos).c_str())); //get last one.

			TRACE("%d-%d-%d\n",vd[0],vd[1],vd[2]);
			pos=0;
			pos = it->come_time.find_first_of(":",pos);
			hour = static_cast<int>(atoi(it->come_time.substr(0,pos).c_str()));
			min = static_cast<int>(atoi(it->come_time.substr(pos+1,2).c_str()));

			COleDateTime t2(vd[0],vd[1],vd[2],hour,min,0);
			if ( t2 <= t )
			{
				hotelMIS::HDestineCtrl destineCtrl(m_con.get_con());
				destineCtrl.setWarning(it->id);
				
				CString msg;
				msg.Format("顾客 %s 在 %d:%d 时间定餐\n\n 联系电话: %s",it->guest_name.c_str(),
					hour,min,it->guest_phone.c_str());
				m_warningdlg = new CSysWarningDialog;
				m_pWarningVec.push_back(m_warningdlg);
				m_warningdlg->SetWarningMsg(msg);
				m_warningdlg->Create(IDD_SYS_WARNING_DLG);
				m_warningdlg->ShowWindow(SW_SHOW);
				
			}
		}
        
	}	
	TRACE("------------------------\n");
	UpdateData(FALSE);
	//Release 
	
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
WarningDestine();
	CGuiFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int result = MessageBox(_T("确定真的要退出本系统!"),_T("系统提醒"),MB_ICONINFORMATION|MB_YESNO);
	if ( result == IDYES)
		CGuiFrameWnd::OnClose();
}

void CMainFrame::SetMenuQX()
{
	hotelMIS::KDBCon con;
	hotelMIS::HAdminBdy bdy(con.get_con());
	hotelMIS::HAdmin admin = bdy.getLoginUserInfo();
	hotelMIS::HOpType op(admin.getOpType(),con.get_con());
	
		
	//其他功能
	if ( !op.getM7())
		GetMenu()->DeleteMenu(9,MF_BYPOSITION);
	
	//系统设置 
	if ( !op.getM6())
		GetMenu()->DeleteMenu(8,MF_BYPOSITION);

	//会员管理
	if ( !op.getM8())
		GetMenu()->DeleteMenu(7,MF_BYPOSITION);
		
	//统计报表	
	if ( !op.getM5())
		GetMenu()->DeleteMenu(6,MF_BYPOSITION);
		
	//菜谱管理
	if ( !op.getM4())
		GetMenu()->DeleteMenu(5,MF_BYPOSITION);
		
	//员工管理
	if ( !op.getM3())
		GetMenu()->DeleteMenu(4,MF_BYPOSITION);
	
	//账单查询	
	if ( !op.getM2() )
		GetMenu()->DeleteMenu(3,MF_BYPOSITION);
		
	//库存管理
	if ( !op.getM1() )
		GetMenu()->DeleteMenu(2,MF_BYPOSITION);
		
	//餐饮管理	
	if ( !op.getM0() )
		GetMenu()->DeleteMenu(1,MF_BYPOSITION);

	GetMenu()->DeleteMenu(0,MF_BYPOSITION);

	DrawMenuBar();
}

