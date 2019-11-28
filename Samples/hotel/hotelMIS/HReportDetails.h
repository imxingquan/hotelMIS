//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HReportDetails.h
// 
// Desc:  经营明细报表
//
// Author:  xq
// 
// Modified: 2005年6月14日 6:09
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HReportDetails_h)
#define __hotelMIS_HReportDetails_h

#include <string>
#include <vector>
using namespace std;

namespace hotelMIS{

class HReportDetails
	{
	public:
		HReportDetails()
			:kind_id(0),
			food_id(0),
			food_unit(""),
			sum_num(0),
			sum_price(0),
			food_name("")
		{}
		~HReportDetails()
		{}

	public:
		int		kind_id;
		int		food_id;
		string	food_name;
		string  food_unit;
		float	sum_num;
		float	sum_price;
			
	}; //end class HReportDetails

} //end namespace

#endif