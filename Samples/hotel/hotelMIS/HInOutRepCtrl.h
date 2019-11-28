//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HBehindRep.cpp
// 
// Desc: 
//
// Author:  邢泉
//
// Modified: 2006年 月 日
//--------------------------------------------------------------------------------------


#if !defined(__hotelMIS_HInOutRepCtrl_h)
#define __hotelMIS_HInOutRepCtrl_h

#include "config.h"
#include "HInOutRep.h"

namespace hotelMIS
{
	typedef vector<HInOutRep> HInOutRepVec;
	typedef vector<HTotalInOutRep> HTotalInOutRepVec;

	class HInOutRepCtrl
	{
	public:
		HInOutRepCtrl(mysqlpp::Connection *pCon);
		~HInOutRepCtrl();

	public:
		//基础操作
		void insert(HInOutRep &rep);
		
		//void update(HInOutRep &rep);

		void DeleteAll();
		
		//入库
		void enter(list<HInOutRep> &repList);
		
		////出库
		//void leave(list<HInOutRep> &repList);
		//将出库的数量更新到前台
		void updateBeforeRep(list<HInOutRep> &repList);

		// 根据 food_id 返回 出入库记录
		HInOutRepVec search(int food_id,string dt1,string dt2);

		//根据日期汇总库存
		HTotalInOutRepVec totalByDate(string d1,string d2);

		//根据日期及条件返回出入库账单
		HInOutRepVec search(string d1,string d2,int inoutflag=-1);

		//根据账单号返回本账单号的所有记录
		HInOutRepVec search(string inout_dh);

		//返回所有出入库记录
		HInOutRepVec getAllInOutRec(string dt1,string dt2);
	protected:
		void _fill(HInOutRep &rep,mysqlpp::Result &res);
		void _fill_vec(HInOutRepVec &vec,mysqlpp::Result &res);
	private:
		mysqlpp::Connection *_pCon;

	};// end class 
}//end namespace hotelMIS

#endif