#pragma once

#include "OutPutlist.h"
// CTabView ��ͼ
#include "DiningRoomTab.h"
#include "HRoomCtrl.h"
class CTabView : public CGuiViewWorkTab
{
	DECLARE_DYNCREATE(CTabView)

protected:
	CTabView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTabView();
	
public:
	COutPutList m_list;
	COutPutList m_TotalList;

	CDiningRoomTab *m_pDiningRoom;	//���ò���

	CImageList m_ImageList;
	int m_roomSize;
	int m_curRoomNo;
	hotelMIS::HRoomVector vec;
	map<int,CDiningRoomTab*> m_roomTabmap;

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSetRoomNo(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnReDraw(WPARAM wParam,LPARAM lParam);
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnAccount();
	afx_msg void OnViewLarger();
	afx_msg void OnViewList();
	afx_msg void OnViewSmall();

	afx_msg void On2003();
};


