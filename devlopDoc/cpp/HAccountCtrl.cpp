/***********************************************************************
 * Module:  HAccountCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月6日 22:31:30
 * Purpose: Implementation of the class HAccountCtrl
 ***********************************************************************/

#include "HAccountCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HAccountCtrl::HAccountCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HAccountCtrl::HAccountCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HAccountCtrl::HAccountCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon  = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccountCtrl::~HAccountCtrl()
// Purpose:    Implementation of HAccountCtrl::~HAccountCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HAccountCtrl::~HAccountCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccountCtrl::insert(HAccount& account)
// Purpose:    Implementation of HAccountCtrl::insert()
// Parameters:
// - account
// Return:     void
////////////////////////////////////////////////////////////////////////

void HAccountCtrl::insert(HAccount& account)
{
   // TODO : 
   try{
         mysqlpp::Query query  = _pCon->query();
         query << "INSERT INTO t_account (account_id,room_id,table_id,cust_date,cust_time,acc_status,ad_name)VALUES('"
                     <<  account.account_id << "',"
                     << account.room_id <<","
                     << account.table_id <<",'"
                     << account.cust_date<<"','"
                     << account.cust_time<<"',"
                     << account.acc_status<<",'"
                     << account.ad_name <<"')";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccountCtrl::update(HAccount& account)
// Purpose:    Implementation of HAccountCtrl::update()
// Parameters:
// - account
// Return:     int
////////////////////////////////////////////////////////////////////////

int HAccountCtrl::update(HAccount& account)
{
   // TODO : 结账
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_account SET room_id ="
                     << account.room_id <<",table_id ="
                     << account.table_id <<",pay_date = '" 
                     << account.cust_date <<"',pay_time='"
                     << account.cust_time <<"',yscost="
                     << account.yscost <<",erase_zero="
                     << account.erase_zero<<",zhekou="
                     << account.zhekou<<",reckoning="
                     << account.reckoning<<",sscost="
                     << account.sscost <<",acc_status="
                     << account.acc_status<<",ad_name='"
                     << account.ad_name <<"' WHERE account_id = '"
                     << account.account_id << "'";
        query.execute();              
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccountCtrl::getNowCnt()
// Purpose:    Implementation of HAccountCtrl::getNowCnt()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HAccountCtrl::getNowCnt(void)
{
   int cnt = 0;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT count(*)as acnt FROM t_account WHERE cust_date = NOW()";
         mysqlpp::Result res = query.store();
         if ( !res.empty()){
            mysqlpp::Row row;
            mysqlpp::Result::iterator it = res.begin();
            row = *it;
            cnt = row.lookup_by_name("acnt");
         }
         
   }mycatch();
   return cnt;
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccountCtrl::cancel(int accountId)
// Purpose:    Implementation of HAccountCtrl::cancel()
// Parameters:
// - accountId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HAccountCtrl::cancel(int accountId)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_account SET acc_status = -1 WHERE account_id = '"
                     << accountId <<"'";
         query.execute();
   }mycatch();
}