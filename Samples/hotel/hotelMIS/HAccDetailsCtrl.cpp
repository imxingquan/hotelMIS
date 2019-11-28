//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccDetailsCtrl.cpp
//
// Description:    
//			   HAccDetailsCtrl 类的实现
//
// Version: 1.0
//
// Hostory:		
//			05-8-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HAccDetails.h"
#include "HAccDetailsCtrl.h"

using namespace hotelMIS;


HAccDetailsCtrl::HAccDetailsCtrl(mysqlpp::Connection* pCon)
{
   _pCon = pCon;
}


HAccDetailsCtrl::~HAccDetailsCtrl()
{

}

//  
// *** 数据库的基本操作 ***
//
// 插入
//
void HAccDetailsCtrl::insert(HAccDetails accDetails)
{
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_accountDetails ( account_id,food_id,food_name,food_num,food_price,food_unit,ck_name) VALUES('"
                     <<accDetails.account_id<<"',"
                     <<accDetails.food_id<<",'"
                     <<accDetails.food_name<<"',"
                     <<accDetails.food_num<<","
                     <<accDetails.food_price<<",'"
					 <<accDetails.food_unit<<"','"
                     <<accDetails.ck_name<<"')";
          query.execute();
   }mycatch();
}

//
// 更新
//
void HAccDetailsCtrl::update(HAccDetails accDetails)
{
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_accountDetails SET food_name = '"
                      << accDetails.food_name <<"',food_id="
					  << accDetails.food_id <<" food_num = "
                      << accDetails.food_num << ", food_price ="
                      << accDetails.food_price << ",food_unit='"
					  << accDetails.food_unit << "',ck_name ='"
                      << accDetails.ck_name << "'  WHERE account_id ='"
                      << accDetails.account_id <<"' AND food_name ='"
                      << accDetails.food_name <<"'";
         query.execute();
   }mycatch();
}

//
// 根据 账单号,菜品名 删除数据
//
void HAccDetailsCtrl::Delete(string accountId, string foodName)
{ 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_accountDetails WHERE account_id = '"
                     << accountId <<"' AND food_name = '" << foodName <<"'";
         query.execute();
   }mycatch();
}

//
// 根据账单号删除数据
//
void HAccDetailsCtrl::Delete(string accountId)
{
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_accountDetails WHERE account_id = '"
                     << accountId <<"'";
         query.execute();
   }mycatch();
}

//
// 删除所有
//
 void HAccDetailsCtrl::DeleteAll()
 {
	try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_accountDetails ";
         query.execute();
   }mycatch();
 }

 //
 // *** 业务操作 ***
 // 
 // 根据账单号返回历史消费详细列表
 //
vector<HAccDetails> HAccDetailsCtrl::getAccDetails(string accountId)
{
   vector<HAccDetails> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_accountDetails WHERE account_id = '"
                     << accountId << "' order by id";
         mysqlpp::Result res = query.store();
         mysqlpp::Result::iterator it;
         mysqlpp::Row row;
         HAccDetails ac;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               ac.account_id = accountId;
			   ac.food_id = row.lookup_by_name("food_id");
               ac.food_name = row.lookup_by_name("food_name");
               ac.food_num = row.lookup_by_name("food_num");
               ac.food_price = row.lookup_by_name("food_price");
			   ac.food_unit = row.lookup_by_name("food_unit");
               ac.ck_name = row.lookup_by_name("ck_name");
			   ac.zk_num = row.lookup_by_name("zk_num");
			   ac.kind_id= row.lookup_by_name("kind_id");
			   ac.total_fl = row.lookup_by_name("total_fl");
               vec.push_back(ac);
         }
   }mycatch();
   return vec;
}

//
// 按日统计厨师的做菜量
//
vector<HTotalByCook> HAccDetailsCtrl::getByDayCkName(string day)
{
	vector<HTotalByCook> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT food_name,ck_name,sum(food_num)as total_food_num ,sum(food_price)as total_food_price FROM `t_accountDetails` \
				 WHERE account_id IN(select account_id from t_account \
				 WHERE cust_date='"<< day <<"') GROUP BY ck_name HAVING ck_name<>'无'";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HTotalByCook totalByCook;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			totalByCook.food_name = row.lookup_by_name("food_name");
			totalByCook.total_food_num = row.lookup_by_name("total_food_num");
			totalByCook.total_food_price = row.lookup_by_name("total_food_price");
			totalByCook.ck_name= row.lookup_by_name("ck_name");
			vec.push_back(totalByCook);
		}
	}mycatch();
	return vec;
}

//
// 按年月统计厨师的做菜量
//
vector<HTotalByCook> HAccDetailsCtrl::getByMonthCkName(string year,string month)
{
	vector<HTotalByCook> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT food_name,ck_name,sum(food_num)as total_food_num ,sum(food_price)as total_food_price FROM `t_accountDetails` \
				 where account_id IN(select account_id from t_account \
				 where year(cust_date) ='"
				 << year <<"' AND month(cust_date)='"
				 << month <<"') group by ck_name HAVING ck_name<>'无'";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HTotalByCook totalByCook;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			totalByCook.food_name = row.lookup_by_name("food_name");
			totalByCook.total_food_num = row.lookup_by_name("total_food_num");
			totalByCook.total_food_price = row.lookup_by_name("total_food_price");
			totalByCook.ck_name= row.lookup_by_name("ck_name");
			vec.push_back(totalByCook);
		}
	}mycatch();
	return vec;
}

//
// 按年统计厨师的做菜量
//
vector<HTotalByCook> HAccDetailsCtrl::getByYearCkName(string year)
{
	vector<HTotalByCook> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT food_name,ck_name,sum(food_num)as total_food_num ,sum(food_price)as total_food_price FROM `t_accountDetails` \
				 where account_id IN(select account_id from t_account \
				 where year(cust_date)='"<< year <<"') group by ck_name HAVING ck_name<>'无'";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HTotalByCook totalByCook;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			totalByCook.food_name = row.lookup_by_name("food_name");
			totalByCook.total_food_num = row.lookup_by_name("total_food_num");
			totalByCook.total_food_price = row.lookup_by_name("total_food_price");
			totalByCook.ck_name= row.lookup_by_name("ck_name");
			vec.push_back(totalByCook);
		}
	}mycatch();
	return vec;
}

//
// 按指定的日期区间统计退菜的详细清单
//
HAccDetailsVec HAccDetailsCtrl::GetCancelMenuByDate(string date1,string date2)
{
	HAccDetailsVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT t_accountDetails.id AS id,t_accountDetails.account_id AS account_id, \
			t_accountDetails.food_id AS food_id,t_accountDetails.food_name AS food_name,t_accountDetails.food_num AS food_num, \
			t_accountDetails.food_price AS food_price,t_accountDetails.food_unit AS food_unit, \
			t_accountDetails.food_cancel_msg AS food_cancel_msg, \
			t_accountDetails.zk_num as zk_num, \
			t_accountDetails.total_fl as total_fl, \
			t_accountDetails.kind_id as kind_id \
			FROM t_accountDetails LEFT JOIN t_account \
			ON t_accountDetails.account_id= t_account.account_id \
			WHERE t_account.cust_date >='"
			<<date1 << "' AND t_account.cust_date <='"
			<<date2 << "' AND( t_accountDetails.food_num < 0 OR t_account.acc_status = -1)";
		
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HAccDetails acc;
		for ( it = res.begin(); it != res.end() ; it++)
		{
			row = *it;
			acc.account_id = row.lookup_by_name("account_id");
			//acc.ck_name = row.lookup_by_name("ck_name");
			acc.food_id = row.lookup_by_name("food_id");
			acc.food_name = row.lookup_by_name("food_name");
			acc.food_num = row.lookup_by_name("food_num");
			acc.food_price = row.lookup_by_name("food_price");
			acc.food_unit = row.lookup_by_name("food_unit");
			acc.food_cancel_msg = row.lookup_by_name("food_cancel_msg");
			acc.zk_num = row.lookup_by_name("zk_num");
			acc.total_fl = row.lookup_by_name("total_fl");
			acc.kind_id = row.lookup_by_name("kind_id");
			vec.push_back(acc);
		}
	}mycatch();
	return vec;
}