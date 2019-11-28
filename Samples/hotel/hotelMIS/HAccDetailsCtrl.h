//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccDetailsCtrl.h
//
// Description:    
//			   实现对HAccDetails 类的数据库操作,
//		统计经营报表及退菜的详细记录
//
// Version: 1.0
//
// Hostory:		
//			05-8-2005	邢泉	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HAccDetailsCtrl_h)
#define __hotelMIS_HAccDetailsCtrl_h

#include <HAccDetails.h>
#include <HTotalByCook.h>
#include "config.h"

namespace hotelMIS{

	// *** global ***
	typedef vector<HTotalByCook> HTotalByCookVec;	//根据厨师做菜量的统计结果
	typedef vector<HAccDetails> HAccDetailsVec;		//HAccDetails的集合

	/*+--------------------------------------------------------------------------------
	*	 class HAccDetailsCtrl
	*
	*      member function:
	*		
	*		//根据账单号返回历史消费详细列表
	*		vector<HAccDetails> getAccDetails(string accountId);	
	*		
	*		//按日统计厨师的做菜量
	*		vector<HTotalByCook> getByDayCkName(string day);
	*		
	*		//按年月统计厨师的做菜量
	*		vector<HTotalByCook> getByMonthCkName(string year,string month);
	*		
	*		//按年统计厨师的做菜量
	*		vector<HTotalByCook> getByYearCkName(string year);
	*
	*		//按指定的日期区间统计退菜的详细清单
	*		HAccDetailsVec GetCancelMenuByDate(string date1,string date2);
	*
	*
	----------------------------------------------------------------------------------*/

	class HAccDetailsCtrl
	{
	public:
		// Construct /Destruct
		HAccDetailsCtrl(mysqlpp::Connection* pCon);
		~HAccDetailsCtrl();

		//
		// 数据库的基本操作
		//
		void insert(HAccDetails accDetails);
		void update(HAccDetails accDetails);
		void Delete(string accountId, string foodName);
		void Delete(string accountId);
		void DeleteAll();

		//
		// 业务操作
		//
		vector<HAccDetails> getAccDetails(string accountId);
		vector<HTotalByCook> getByDayCkName(string day);
		vector<HTotalByCook> getByMonthCkName(string year,string month);
		vector<HTotalByCook> getByYearCkName(string year);
		HAccDetailsVec GetCancelMenuByDate(string date1,string date2);


	private:
		mysqlpp::Connection * _pCon;	 //数据库连接

	}; // end class HAccDetailsClass

} // end namespace hotelMIS
#endif