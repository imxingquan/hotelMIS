/***********************************************************************
 * Module:  HOutStoreCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月5日 14:39:12
 * Purpose: Implementation of the class HOutStoreCtrl
 ***********************************************************************/

#include "HOutStoreCtrl.h"

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

void HOutStoreCtrl::insert(HOutStore& outStore, int opType)
{
   // TODO : 出库
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
   hotelMIS::HRepToTalCtrl totalCtrl(_pCon);
   if ( 0 == opType )
         totalCtrl.delNum(outStore.food_id,outStore.rep_num);
   else
	     totalCtrl.addNum(outStore.food_id,outStore.rep_num);
}