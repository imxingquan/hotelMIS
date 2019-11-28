//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HUnitSet.h
//
// Description:    
//				单位设置类对应 t_unit 表
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HUnitSet_h)
#define __hotelMIS_HUnitSet_h

#include <string>

using namespace std;

namespace hotelMIS{

	class HUnitSet
	{
	public:
		//Construct/Destruct
		HUnitSet();
		~HUnitSet();
	public:
		int getUnit_id(void);
		void setUnit_id(int newUnit_id);
		string getUnit_name(void);
		void setUnit_name(string newUnit_name);
	private:
		int unit_id;
		string unit_name;

	}; //end class HUnitSet
} // end namespace hotelMIS
#endif