//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HBehindRep.h
// 
// Desc: 后厨库存
//
// Author:  邢泉
//
// Modified: 2006年 06 月 14 日
//--------------------------------------------------------------------------------------

#if !defined(__hotelMIS_HBehindRep_h)
#define __hotelMIS_HBehindRep_h

namespace hotelMIS
{
	class HBehindRep
	{
	public:
		enum { OUT_REP = 2, IN_REP = 1};
		HBehindRep(void);
		~HBehindRep(void);

	public:
		int		food_id;		//商品编号
		float	rep_num;		//后厨库存量
		float	food_price;		//出库单价变化中	单价 = 金额 / 数量
		float	total_price;	//总金额

	}; // end class HBehindRep

}//end namespace hotelMIS
#endif