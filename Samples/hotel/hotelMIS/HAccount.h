//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccount.h
//
// Description:    
//				对应账单数据表 t_account 中的一行数据   
//		
// 
// Version: 1.0
//
// Hostory:		
//			05-8-2005	邢泉	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HAccount_h)
#define __hotelMIS_HAccount_h
#include <string>

using namespace std;

namespace hotelMIS{
	
	class HAccount
	{
	public:
		// Construct /Destruct
		HAccount();
		~HAccount();

		//public member data
	public:
		//
		// 结账状态
		//
		enum {	notAcc=0,			//未结账
				havedAcc=1,			//已结账
				cancelAcc=-1,		//退单
				gzAcc = 2,			//挂账
				gzhavedAcc=3		//挂账结账
			 }; 
		enum JSFS{ xj = 1,				//现金
				mcard =2,			//会员卡
				xycard =3,			//信用卡
				zp = 4				//支票
		};

		string account_id;			//账单号
		int room_id;				//餐厅号
		int table_id;				//餐桌号
		string cust_date;			//开单日期
		string cust_time;			//开单时间
		string pay_date;			//付款日期
		string pay_time;			//付款时间
		float subscription;			//定金
		float yscost;				//应收账款
		float erase_zero;			//抹零数
		float zhekou;				//折扣
		int reckoning;				//是否需要发票 1: 需求 0:不需要
		float sscost;				//实收账款
		int acc_status;				//就餐状态 
		string ad_name;				//系统操作员姓名
		float daijin;				//代金券金额
		float sj;					//实际收款
		float zy;					//找余金额
		int paystatus;				//付款方式
		string bz;					//备注
		int arid;					//挂账单位
		float zfprice;				//会员卡，支票，信用卡
		int sswr;					//四舍五入

	};

	class HTotalAccount
	{
	public:
		HTotalAccount()
			:pay_status(0)
			,sum_sscost(0.0f)
		{
		}
	public:
		int pay_status;
		float sum_sscost;
	};
}
#endif