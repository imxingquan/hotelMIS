//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HTotalByCook.h
//
// Description:    
//				按厨师统计做菜的数量及价格  对应 t_totalByCook 表
//				
// Version: 1.0
//
// Hostory:		
//			05-22-2005	邢泉	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HTotalByCook_h)
#define __hotelMIS_HTotalByCook_h

#include <string>
#include <vector>

using namespace std;

namespace hotelMIS{

	class HTotalByCook
	{
	public:
		//Construct/Destruct
		HTotalByCook();
		~HTotalByCook();
		
	public:
		//member data
		string food_name;
		int total_food_num;
		float total_food_price;
		string ck_name;
	};
	
}
#endif