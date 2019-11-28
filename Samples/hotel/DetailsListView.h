#pragma once


// CDetailsListView 视图

class CDetailsListView : public CListView
{
	DECLARE_DYNCREATE(CDetailsListView)

protected:
	CDetailsListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDetailsListView();

protected:
	CListCtrl *m_pListCtrl;
	hotelMIS::KDBCon m_con;
	map<int,pair<string,int> > m_repMap; //map<pos,pair<account_id,food_id> >
	map<int,int> m_repPosMap; //map<pos,repId>
protected:
	void Init();
	void Refresh(int roomId,int tableId);
public:
	LRESULT OnGetTableInfo(WPARAM wParam,LPARAM lParam);
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


