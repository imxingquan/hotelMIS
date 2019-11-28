//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HTableStatusSetCtrl.h
//
// Description:    
//				HTabelStatusSet 类的数据库操作类
//				
// Version: 1.0
//
// Hostory:		
//			05-22-2005	邢泉	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HTableStatusSetCtrl_h)
#define __hotelMIS_HTableStatusSetCtrl_h

#include "config.h"
#include "HTableStatusSet.h"
#include <vector>

using namespace std;

namespace hotelMIS{

	//*** global ***
	typedef vector<HTableStatusSet> HTableStatusSetVec;
	
	/*----------------------------------------------------------------------------------------
	* class HTableStatusSetCtrl
	*	
	*	member function:
	*		
	*		// 返回餐桌状态
	*		getHTableStatus(int tableState);
	*
	*		// 返回所有餐桌状态
	*		getAllTableStatusSet();
	*
	*		// 返回空餐桌的图片 id
	*		getTableEmptyBmp(int tableState);
	*	
	*		// 返回就餐状态图片
	*		getTableRepastBmp(int tableState);
	*		
	*		// 设置餐桌状态图片
	*		SetTaleBmp(int tableState, int bmpIndex);
	*/
	
	class HTableStatusSetCtrl
	{
	public:
		// Construct/Destruct
		HTableStatusSetCtrl(mysqlpp::Connection *pCon);
		~HTableStatusSetCtrl();
		
		// *** 数据库的基本操作 ***
		void insert(string stateName,int personNum);
		void update(HTableStatusSet& tableSset);
		void delete0(int tssate);
		
		HTableStatusSet getHTableStatus(int tableState);
		
		vector<HTableStatusSet> getAllTableStatusSet();
		
		int getTableEmptyBmp(int tableState);
		int getTableRepastBmp(int tableState);
		void SetTaleBmp(int tableState, int bmpIndex);

	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif