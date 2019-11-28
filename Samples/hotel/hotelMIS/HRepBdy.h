//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HRepBdy.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2005年5月6日 22:23:12
//			 2006年6月10日 9:54:22
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HRepBdy_h)
#define __hotelMIS_HRepBdy_h
#include "config.h"
#include <HAccount.h>
namespace hotelMIS{
	class HRepBdy
	{
	public:
		HRepBdy(int tableId,int roomId,mysqlpp::Connection* pCon);
		~HRepBdy();
		void addRep(int foodId,int foodNum,float dj=0.0f,float zdyPrice=0.0f);
		//void delRep(string accountId, int foodId, int foodNum);
		void checkOut(HAccount& account);
		void cancel(string accountId);
		void delRep(int id,int foodNum,string accountId, int foodId);
		int table_id;
		int room_id;
		float m_subcription;
	//protected:
		string createAccount(void);

	public:
		//前台出库
		int outRep(int food_id,int food_num);
		//还原库存
		void revert(int food_id,int food_num);

	protected:
		int testTaoCan(int food_id,int food_num);
		void outTcREpNum(int food_id,int food_num);
		void inTcRepNum(int food_id,int food_num);

	private:
		mysqlpp::Connection* _pCon;


	};
}
#endif