/***********************************************************************
 * Module:  HAccDetailsCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月22日 21:13:04
 * Purpose: Implementation of the class HAccDetailsCtrl
 ***********************************************************************/

#include "HAccDetails.h"
#include "HAccDetailsCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HAccDetailsCtrl::HAccDetailsCtrl(mysqlpp::Connection* pCon)
// Purpose:    Implementation of HAccDetailsCtrl::HAccDetailsCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HAccDetailsCtrl::HAccDetailsCtrl(mysqlpp::Connection* pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccDetailsCtrl::~HAccDetailsCtrl()
// Purpose:    Implementation of HAccDetailsCtrl::~HAccDetailsCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HAccDetailsCtrl::~HAccDetailsCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccDetailsCtrl::insert(HAccDetails accDetails)
// Purpose:    Implementation of HAccDetailsCtrl::insert()
// Parameters:
// - accDetails
// Return:     void
////////////////////////////////////////////////////////////////////////

void HAccDetailsCtrl::insert(HAccDetails accDetails)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->quey();
         query << "INSERT INTO t_accountDetails (account_id,food_name,food_num,food_price,ck_name) VALUES('"
                     <<  accDetails.account_id <<"','"
                     <<  accDetails.food_name <<"',"
                     <<  accDetails.food_num <<","
                     <<  accDetails.food_price <<",'"
                     <<  accDetails.ck_name <<"')";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccDetailsCtrl::update(HAccDetails accDetails)
// Purpose:    Implementation of HAccDetailsCtrl::update()
// Parameters:
// - accDetails
// Return:     void
////////////////////////////////////////////////////////////////////////

void HAccDetailsCtrl::update(HAccDetails accDetails)
{
   // TODO : 更新
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_accountDetails SET food_name = '"
                      << accDetails.food_name <<"', food_num = "
                      << accDetails.food_num << "', food_price ="
                      << accDetails.food_price << ", ck_name ='"
                      << accDetails.ck_name << "'  WHERE account_id ='"
                      << accDetails.account_id <<"' AND food_name ='"
                      << accDetails.food_name <<"'";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccDetailsCtrl::Delete(string accountId, string foodName)
// Purpose:    Implementation of HAccDetailsCtrl::Delete()
// Parameters:
// - accountId
// - foodName
// Return:     void
////////////////////////////////////////////////////////////////////////

void HAccDetailsCtrl::Delete(string accountId, string foodName)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_accountDetails WHERE account_id = '"
                     << accountId <<"' AND food_name = '" << foodName <<"'";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccDetailsCtrl::getAccDetails(string accountId)
// Purpose:    Implementation of HAccDetailsCtrl::getAccDetails()
// Parameters:
// - accountId
// Return:     vector<HAccDetails>
////////////////////////////////////////////////////////////////////////

vector<HAccDetails> HAccDetailsCtrl::getAccDetails(string accountId)
{
   // TODO : 
   vector<HAccDetails> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_accountDetails WHERE account_id = '"
                     << accountId << "'";
         mysqlpp::Result res = query.store();
         mysqlpp::Result::iterator it;
         mysqlpp::Row row;
         HAccDetails ac;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               ac.account_id = accountId;
               ac.food_name = row.lookup_by_name("food_name");
               ac.food_num = row.lookup_by_name("food_num");
               ac.food_price = row.lookup_by_name("food_price");
               ac.ck_name = row.lookup_by_name("ck_name");
               vec.push_back(ac);
         }
   }mycatch();
   return vec;
}