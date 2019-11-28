//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBeforeRep.h
// 
// Desc: 前台库存表
//
// Author:  邢泉
// 
// Modified: 2006年6月10日 9:57:42
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HBeforeRep_h)
#define __hotelMIS_HBeforeRep_h

namespace hotelMIS{
	class HBeforeRep
	{
	public:
		HBeforeRep();
		~HBeforeRep();

	public:
		int food_id;	//商品编号
		float rep_num;	//库存数量
	}; //end class
}; //end namespace hotelMIS

#endif