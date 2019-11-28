/***********************************************************************
 * Module:  HOutStoreCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月5日 14:39:12
 * Purpose: Implementation of the class HOutStoreCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HOutStoreCtrl.h"
#include "HRepToTalCtrl.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreCtrl::HOutStoreCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HOutStoreCtrl::HOutStoreCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HOutStoreCtrl::HOutStoreCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreCtrl::~HOutStoreCtrl()
// Purpose:    Implementation of HOutStoreCtrl::~HOutStoreCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HOutStoreCtrl::~HOutStoreCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreCtrl::insert(HOutStore& outStore, int opType)
// Purpose:    Implementation of HOutStoreCtrl::insert()
// Parameters:
// - outStore
// - opType
// Return:     void
////////////////////////////////////////////////////////////////////////

int HOutStoreCtrl::insert(HOutStore& outStore, int opType)
{
   // TODO : 出库
   hotelMIS::HRepToTalCtrl totalCtrl(_pCon);
   
   mysqlpp::Query query = _pCon->query();
   query << "INSERT INTO t_outStore (food_id,food_name,out_num,out_price,out_unit,out_date,out_flag,ad_name) VALUES("
               << outStore.food_id << ",'"
               << outStore.food_name <<"',"
               << outStore.out_num << ","
               << outStore.out_price <<",'"
               << outStore.out_unit <<"','"
               << outStore.out_date<<"',"
               << outStore.out_flag <<",'"
               << outStore.ad_name<<"')";
   query.execute();
   if ( 0 == opType )
	   totalCtrl.delNum(outStore.food_id,outStore.out_num);
   else
	   totalCtrl.addNum(outStore.food_id,outStore.out_num);

 
   int num =  totalCtrl.getNum(outStore.food_id);
   if ( 1 != opType && num < outStore.out_num ) //操作为出库且数量不够时返回剩余库存
	   return num;
   return -1; //正常出库返回-1,否则返回当前剩余库存;
}


HOutStoreVec HOutStoreCtrl::getAllOutStore(string sDate, string eDate)
{
	HOutStoreVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_outStore WHERE out_date >='"
			<< sDate << "' AND out_date <='"
			<< eDate <<"'";
		mysqlpp::Result res  = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HOutStore out;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			out.food_id = row.lookup_by_name("food_id");
			out.food_name = row.lookup_by_name("food_name");
			out.out_date = row.lookup_by_name("out_date");
			out.out_flag = row.lookup_by_name("out_flag");
			out.out_id = row.lookup_by_name("out_id");
			out.out_num = row.lookup_by_name("out_num");
			out.out_price = row.lookup_by_name("out_price");
			out.out_unit = row.lookup_by_name("out_unit");
			vec.push_back(out);

		}
	}mycatch();
	return vec;
}

void HOutStoreCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_outStore";
		query.execute();
	}mycatch();
}