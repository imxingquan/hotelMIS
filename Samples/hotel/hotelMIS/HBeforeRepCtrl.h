//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBeforeRepCtrl.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2006年6月10日 20:59:26
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HBeforeRepCtrl_h)
#define __hotelMIS_HBeforeRepCtrl_h

#include "config.h"

namespace hotelMIS{

	class HBeforeRepCtrl
	{
	public:
		HBeforeRepCtrl::HBeforeRepCtrl(mysqlpp::Connection *pCon);
		HBeforeRepCtrl::~HBeforeRepCtrl();

	public:
		//db基本操作
		void insert(int food_id,float food_num = 0);
		void Delete(int food_id);
		void DeleteAll();

		//前台出库 -
		void beforeOutRep(int food_id, float food_num);

		//充值前台 +
		void modifyBeforeRep(int food_id,float food_num);

		//返回 某一商品的当前库存
		float getCurRep(int food_id);

        //判断库存中是否存在此项
		bool isExist(int food_id);

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}

#endif