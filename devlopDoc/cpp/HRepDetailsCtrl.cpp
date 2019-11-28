/***********************************************************************
 * Module:  HRepDetailsCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月6日 21:38:14
 * Purpose: Implementation of the class HRepDetailsCtrl
 ***********************************************************************/

#include "HRepDetailsCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::HRepDetailsCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HRepDetailsCtrl::HRepDetailsCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HRepDetailsCtrl::HRepDetailsCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::~HRepDetailsCtrl()
// Purpose:    Implementation of HRepDetailsCtrl::~HRepDetailsCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepDetailsCtrl::~HRepDetailsCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::insert(HRepDetails& repDetails)
// Purpose:    Implementation of HRepDetailsCtrl::insert()
// Parameters:
// - repDetails
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::insert(HRepDetails& repDetails)
{
   // TODO : 插入一个详细记录
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_repDetails ( accound_id,food_id,food_name,food_num,food_price,ck_name) VALUES('"
                     <<repDetails.accound_id<<"',"
                     <<repDetails.food_id<<<",'"
                     <<repDetails.food_name<<"',"
                     <<repDetails.food_num<<","
                     <<repDetails.food_price<<",'"
                     <<repDetails.ck_name<<"')";
          query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::Delete(string accountId, int foodId)
// Purpose:    Implementation of HRepDetailsCtrl::Delete()
// Parameters:
// - accountId
// - foodId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::Delete(string accountId, int foodId)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query <<"DELETE FROM t_repDetails WHERE accountld ='"<<accountId<<"' AND food_id = " << foodId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::Delete(string accountId)
// Purpose:    Implementation of HRepDetailsCtrl::Delete()
// Parameters:
// - accountId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::Delete(string accountId)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query <<"DELETE FROM t_repDetails WHERE accountld ='"<<accountId <<"'";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::update(string accountId, int foodId, int foodNum)
// Purpose:    Implementation of HRepDetailsCtrl::update()
// Parameters:
// - accountId
// - foodId
// - foodNum
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::update(string accountId, int foodId, int foodNum)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_repDetails SET food_num = food_num - "<<foodNum
                     <<" WHERE accountld = '"<<accountld<<"' AND food_id = " << foodId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::getFoodNum(string accountId, int foodId)
// Purpose:    Implementation of HRepDetailsCtrl::getFoodNum()
// Parameters:
// - accountId
// - foodId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepDetailsCtrl::getFoodNum(string accountId, int foodId)
{
   // TODO : 
   int num = 0;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT count(*) as cnt FROM t_RepDetails WHERE account_id = '"
                     << account_id << "', AND foodId = " << foodId;
          mysqlpp::Result res = query.store();
          if ( !res.empty() ){
              mysqlpp::Row row;
              mysqlpp::Result::iterator it = res.begin();
              row = *it;
              num = row.lookup_by_name("cnt");
          }
   }mycatch();
   return num;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::getAllDetails(string accountId)
// Purpose:    Implementation of HRepDetailsCtrl::getAllDetails()
// Parameters:
// - accountId
// Return:     vector<HRepDetails>
////////////////////////////////////////////////////////////////////////

vector<HRepDetails> HRepDetailsCtrl::getAllDetails(string accountId)
{
   // TODO : 返回所有账号是 accountId的记录
   vector<HRepDetails> repDetailsVec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_repDetails WHERE account_id = '"<< accountId<<"'";
         mysqlpp::Result res = query.store();
         mysqlpp::Row row ;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               HRepDetails repDetails;
               repDetails.account_id = accountId;
               repDetails.food_id = row.lookup_by_name("food_id");
               repDetails.food_name = row.lookup_by_name("food_name");
               repDetails.food_num = row.lookup_by_name("food_num");
               repDetails.food_price = row.lookup_by_name("food_price");
               repDetails.ck_name = row.lookup_by_name("ck_name");
               repDetailsVec.push_back(repDetails);       
         }
   }mycatch();
   return repDetailsVec;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::getAllPrice(string accountId)
// Purpose:    Implementation of HRepDetailsCtrl::getAllPrice()
// Parameters:
// - accountId
// Return:     float
////////////////////////////////////////////////////////////////////////

float HRepDetailsCtrl::getAllPrice(string accountId)
{
   // TODO : 获得账号的总价格 
   float total =0.0f;
    try{
         HRepDetailsCtrl repDetailsCtrl(_pCon);
         HRepDetailsVec vec = repDetailsCtrl.getAllDetails(account.account_id); //获得详细列表
         HRepDetailsVec::iterator it;
        
         for ( it = vec.begin(); it != vec.end(); it++)
                    total += (it->food_num * it->food_price); //总价格
    }mycatch();
   return total;
}