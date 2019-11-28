//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HInOutRep.cpp
// 
// Desc: 
//
// Author:  邢泉
//
// Modified: 2006年 月 日
//--------------------------------------------------------------------------------------

#if !defined(__hotelMIS_HInOutRep_h)
#define __hotelMIS_HInOutRep_h


#include <string>
#include <vector>
using namespace std;

namespace hotelMIS
{
	
	class HInOutRep
	{
	public:
		enum { OUT_REP = 2, IN_REP = 1};
		HInOutRep(void);
		~HInOutRep(void);
	public:
		int		food_id;		//商品编号
		string  inout_dh;		//账单号 "RK" ,"CK"
		string	food_name;		//商品名称
		string  food_unit;		//单位
		float	food_num;		//入量数量
		float	food_price;		//入库单价
		
		float	t_num;			//本次入库本商品库存数量
		float	t_price;		//本次入库后本商品的单价
		float	t_sprice;		//本次入库后商品的总金额

		int		rep_flag;		//0: 出 1: 入
		string	opdate;			//操作的日期时间
		string	ad_name;		//操作人
	}; //end class HInOutRep

	class HTotalInOutRep 
	{
	public:
		HTotalInOutRep()
			:sum_price(0)
			, rep_flag(-1)
			, sdate("")
		{
		}
		~HTotalInOutRep(){}

	public:
		float sum_price;
		int	   rep_flag;
		string	sdate;
	};
} // end namespace hotelMIS
#endif