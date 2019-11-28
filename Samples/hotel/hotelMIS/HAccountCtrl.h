//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccountCtrl.h
//
// Description:    
//				实现 HAccount 类的数据库操作,
//			针对账单的业务逻辑
//		
//
// Version: 1.0
//
// Hostory:		
//			05-6-2005	邢泉	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HAccountCtrl_h)
#define __hotelMIS_HAccountCtrl_h

#include "config.h"
#include <HAccount.h>
#include <string>
using namespace std;

namespace hotelMIS{
	
	// *** global ***
	typedef vector<HAccount> HAccountVec;  //HAccount 的行集
	typedef vector<HTotalAccount> HTotalAccountVec; 
	/*---------------------------------------------------------------------------------------------------
	*	class HAccountCtrl
	*		member function
	*			//
	*			// 修改定金
	*			void updateSubscription(string accountId, float subscription);
	*			
	*			// 根据账单号修改消费日期和时间
	*			void updateRepDateAndTime(string accountId,string date,string time);	
	*
	*			// 取消账单
	*			void cancel(string accountId);
	*			
	*			// 返回当天消费的账单数量
	*			int getNowCnt(void);
	*			
	*			// 根据账单号取回定金
	*			float getSubscription(string accountId);
	*			
	*			// 根据账单号取加账单的详细资料
	*			HAccount getAccount(string accountId);
	*			
	*			// 返回所有有账单详细
	*			vector<HAccount> getAllAccount();
	*			
	*			// 返回当天的账单详细
	*			vector<HAccount> getByDay(string day);
	*			
	*			// 返回月的账单详细
	*			vector<HAccount> getByMonth(string year,string month);
	*			
	*			// 返回年的账单详细
	*			vector<HAccount> getByYear(string year);
	*
	*			// 返回 sData 至 eDate 日期区间 状态为 accStatus 的账单详细
	*			vector<HAccount> search(string sDate,string eDate,int accStatus);
	*			   parameter:
	*					accStatus 为 
	*						enum {	notAcc=0,			//未结账
	*								havedAcc=1,			//已结账
	*								cancelAcc=-1		//退单
	*						 }; 
	*					 中的值
	*
	*			// 返回本账单号的消费金额
	*			float getPriceByAccountId(string accountId);
	*
	*			// 挂账结账
	*			bool gzJZ(string accountId,float* restMoney,int reckoning,string date,string time);
	*				parameter :
	*						accoutId	string	[in]		账单号
	*						restMoney	float*	[in/out]	结账后的剩余金额
	*						reckoning	int		[in]		1: 需要发票 0: 不需要发票
	*						date		string	[in]		结账日期
	*						time		string	[in]		结账时间
	*---------------------------------------------------------------------------------------------------*/

	class HAccountCtrl
	{
	public:
		// Construct / Destruct
		HAccountCtrl(mysqlpp::Connection * pCon);
		~HAccountCtrl();
	public:
		// *** 数据库基本操作 ***
		void insert(HAccount& account);
		void update(HAccount& account);
		void Delete(string accountId);
		void DeleteAll();	
		
		// *** 业务逻辑 ***
		void updateSubscription(string accountId, float subscription);
		void updateRepDateAndTime(string accountId,string date,string time);	

		void cancel(string accountId);
		int getNowCnt(void);
		float getSubscription(string accountId);
		
		HAccount getAccount(string accountId);
		
		vector<HAccount> getAllAccount();
		vector<HAccount> getByDay(string sDate,string eDate,int jsfs);
		vector<HAccount> getByMonth(string year,string month);
		vector<HAccount> getByYear(string year);

		//for acc
		vector<HAccount> search(string sDate,string eDate,int accStatus,int arid=0,int cw=0,int jsfs=0);

		float getPriceByAccountId(string accountId);

		bool gzJZ(string accountId,float* restMoney,int reckoning,string date,string time);
		
		// 会员卡结账
		void memberJz(string accountId,float czmoney,string mbh);

		//HAccountVec totalByDateTime(string start_dtime,string end_dtime); 
		HTotalAccountVec totalByPayStatus(string start_dtime,string end_dtime);

		// 按月 结算统计
		HTotalAccountVec totalByPayStatus(string year,string month,int bf);
		
		// 按年 结算统计
		HTotalAccountVec totalByPayStatus(string year);
		
		// 按条件检索
		HAccountVec getAccount(string d1,string d2,string bh);

	private:
		void _fill_(HAccount &acc,mysqlpp::Result &res);
		void _fill_vec(HAccountVec &vec,mysqlpp::Result &res);
		mysqlpp::Connection * _pCon;
	};
}
#endif