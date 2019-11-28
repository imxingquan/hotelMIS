//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccDetails.h
//
// Description:    
//				对应数据库中的 t_accDetails 表中的字段,
//			用来存储 帐单详细消费数据表中的一行记录
//
// Version: 1.0
//
// Hostory:		
//			05-8-2005	邢泉	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HAccDetails_h)
#define __hotelMIS_HAccDetails_h
#include <string>
using namespace std;
namespace hotelMIS{

	class HAccDetails
	{
	public:
		// Construct /Destruct
		HAccDetails();
		~HAccDetails();
		
	public:
		// member data
		int id;					//auto id
		string account_id;		//账单号
		int food_id;			//菜名编号
		string food_name;		//菜品名称
		int food_num;			//数量
		float food_price;		//价格
		string ck_name;			//厨师姓名
		string food_unit;		//单位
		string food_cancel_msg; //退单原因
		float zk_num; //打折比例
		int kind_id;
		int total_fl;
	}; // end class HAccDetails

	
}	// end namespace hotelMIS
#endif