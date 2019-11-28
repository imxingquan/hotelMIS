/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		餐厅选项卡,动态生成多个
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "KDBCon.h"
#include "HTableInfo.h"
#include "JCDialog.h"

#include <map>
using namespace std;

// CDiningRoomTab

class CDiningRoomTab : public CListCtrl
{
	DECLARE_DYNAMIC(CDiningRoomTab)

public:
	CDiningRoomTab();
	virtual ~CDiningRoomTab();
	virtual BOOL CreateRoom(int roomNo,DWORD dwStyle,const RECT &rect, CWnd *pParentWnd,UINT nID);
	
	void Init(); //初始化餐桌
	void ChangeTableState(int tableId);
	void Refresh();
	void RefreshDownList(); //单击,双击,对话框关时刷新
protected:
	CBitmap m_bitmap,m_bitmap2;
	CImageList m_ImageList,m_ImageSmall;
	int m_roomId;
	int m_tableId;
	static int m_nPos;
	hotelMIS::KDBCon m_con;
	mysqlpp::Connection *m_pCon;
	map<int,hotelMIS::HTableInfo> m_tableInfoMap; //将餐桌信息与图标索引绑定
	/*CJCDialog m_jcDlg;*/
	CToolTipCtrl	m_ToolTipCtrl;
	LPCTSTR			m_lpMsg;
	int m_sFlag ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	void RepastToAccount();
	void SetToolTip(LPCTSTR lpMsg);
	void PrintReport(CDC *dc);
	LRESULT OnReDraw(WPARAM wParam,LPARAM lParam);
	afx_msg void OnViewLarger();
	afx_msg void OnRepast();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestine();
	afx_msg void OnDestineManage();
	afx_msg void OnAccount();
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangetable();
	afx_msg void OnReInput();
	afx_msg void OnReOutput();
	afx_msg void OnReSearch();
	afx_msg void OnEmpAdd();
	afx_msg void OnEmpManage();
	afx_msg void OnEmpSearch();
	afx_msg void OnEmpSetjob();
	afx_msg void OnMenuModify();
	//afx_msg void OnSnackManage();
	afx_msg void OnFeatureManage();
	afx_msg void OnKindSet();
	afx_msg void OnDayReport();
	afx_msg void OnSysuserSet();
	afx_msg void OnSysparaSet();
	afx_msg void OnOtherCalc();
	afx_msg void OnOtherNotepad();
	afx_msg void OnOtherPaint();
	afx_msg void OnSearchAccounts();
	afx_msg void OnRefresh();
	afx_msg void OnLesson();
	afx_msg void OnArrearage();
	afx_msg void OnArrearageManage();
	afx_msg void OnArrearageGzjz();
	afx_msg void OnViewList();
	afx_msg void OnViewSmall();
	afx_msg void OnUpdateViewList(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewLarger(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewSmall(CCmdUI *pCmdUI);
//	afx_msg void OnTimer(UINT nIDEvent);
	/*afx_msg void OnNMHover(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnHotTrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnGetInfoTip(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNMHover(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnHotTrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPopupSetTable();
	afx_msg void OnRegisterMenu();
	
	afx_msg void OnPopupPrint();
	afx_msg void OnRecalltable();
	afx_msg void OnFengchuPrint();
	afx_msg void On2003();
	afx_msg void OnXp();
	afx_msg void OnMemberManage();
//	afx_msg void OnMemberBirth();
	afx_msg void OnMemberCastsearch();
	afx_msg void OnMemberCz();
	afx_msg void OnMemberZz();
	afx_msg void OnReportDetails();
	afx_msg void OnRepDetailsSearch();
	afx_msg void OnRepKindSet();
	afx_msg void OnRepPManag();
	afx_msg void OnRepTotalSearch();
	afx_msg void OnAppExit();
	afx_msg void OnInoutZdSearch();
	afx_msg void OnCancelMenuSearch();
	afx_msg void OnSkyMenu();
};


