//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HUnitCtrl.h
//
// Description:    
//				HUnitSet 的数据库操作类
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HUnitCtrl_h)
#define __hotelMIS_HUnitCtrl_h

#include "config.h"
#include "HunitSet.h"
#include <vector>

using namespace std;

namespace hotelMIS{

	// *** global ***
	typedef vector<HUnitSet> HUnitVec;

	class HUnitCtrl
	{
	public:
		//Construct / Destruct
		HUnitCtrl(mysqlpp::Connection * pCon);
		~HUnitCtrl();
	public:
		// *** 数据库基本操作 ***
		void insert(string unitName);
		void Delete(int unitId);
		
		// *** 业务逻辑 ***
		vector<HUnitSet> getAllUnit(void);
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif