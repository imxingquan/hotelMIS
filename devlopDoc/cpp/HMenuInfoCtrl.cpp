/***********************************************************************
 * Module:  HMenuInfoCtrl.cpp
 * Author:  babala
 * Modified: 2005年4月25日 2:29:41
 * Purpose: Implementation of the class HMenuInfoCtrl
 ***********************************************************************/

#include "HMenuInfoCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::HMenuInfoCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HMenuInfoCtrl::HMenuInfoCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HMenuInfoCtrl::HMenuInfoCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::~HMenuInfoCtrl()
// Purpose:    Implementation of HMenuInfoCtrl::~HMenuInfoCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HMenuInfoCtrl::~HMenuInfoCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::insert(HMenuInfo& menuInfo)
// Purpose:    Implementation of HMenuInfoCtrl::insert()
// Parameters:
// - menuInfo
// Return:     void
////////////////////////////////////////////////////////////////////////

void HMenuInfoCtrl::insert(HMenuInfo& menuInfo)
{
   // TODO : 添加菜谱
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_menuInfo (kind_id,food_name,food_price,food_unit,repertory_flag,ck_name) VALUES("
                     << menuInfo.kind_id << ",'"
                     << menuInfo.food_name << "',"
                     << menuInfo.price << ",'"
                     << menuInfo.unit << "',"
                     << menuInfo.repertory_flag <<",'"
                     << menuInfo.ck_name <<"')";
          query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::update(HMenuInfo& menuInfo)
// Purpose:    Implementation of HMenuInfoCtrl::update()
// Parameters:
// - menuInfo
// Return:     void
////////////////////////////////////////////////////////////////////////

void HMenuInfoCtrl::update(HMenuInfo& menuInfo)
{
   // TODO : 修改
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE  t_menuInfo SET kind_id = "
                     << menuInfo.kind_id << ", food_name = '"
                     << menuInfo.kind_name << "', food_price = "
                     << menuInfo.kind_price <<", food_unit = '"
                     << menuInfo.kind_unit << "',repertory_flag = "
                     << menuInfo.kind_flag << ", ck_name = '"
                     << menuInfo.ck_name << "'"
                     << " WHERE food_id = " 
                     << menuInfo.food_id;
           query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::Delete(int foodId)
// Purpose:    Implementation of HMenuInfoCtrl::Delete()
// Parameters:
// - foodId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HMenuInfoCtrl::Delete(int foodId)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_menuInfo WHERE food_id = " foodId ;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::getMenuInfo(int foodId)
// Purpose:    Implementation of HMenuInfoCtrl::getMenuInfo()
// Parameters:
// - foodId
// Return:     HMenuInfo
////////////////////////////////////////////////////////////////////////

HMenuInfo HMenuInfoCtrl::getMenuInfo(int foodId)
{
   // TODO : 获得一个菜谱的详细清单
   HMenuInfo menuInfo;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo WHERE food_id = " << foodId;
         mysqlpp::Result res = query.store();
         if ( ! res.empty() ){
               mysqlpp::Row row;
               mysqlpp::Result::iterator it = res.begin();
               row = *it;
               menuInfo.food_id = foodId;
               menuInfo.kind_id = row.lookup_by_name("kind_id");
               menuInfo.food_name = row.lookup_by_name("food_name");
               menuInfo.food_price = row.lookup_by_name("food_price");
               menuInfo.food_unit = row.lookup_by_name("food_unit");
               menuInfo.repertory_flag = row.lookup_by_name("repertory_flag");
               menuInfo.ck_name = row.lookup_by_name("ck_name");
         }
   }mycatch();
   return menuInfo;
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::getAllMenuInfo()
// Purpose:    Implementation of HMenuInfoCtrl::getAllMenuInfo()
// Return:     vector<HMenuInfo>
////////////////////////////////////////////////////////////////////////

vector<HMenuInfo> HMenuInfoCtrl::getAllMenuInfo(void)
{
   // TODO : implement
   vector<HMenuInfo> vec; 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo ;
         mysqlpp::Result res = query.store();
         if ( ! res.empty() ){
               mysqlpp::Row row;
               HMenuInfo menuInfo;
               mysqlpp::Result::iterator it = res.begin();
               row = *it;
               menuInfo.food_id = row.lookup_by_name("food_id");
               menuInfo.kind_id = row.lookup_by_name("kind_id");
               menuInfo.food_name = row.lookup_by_name("food_name");
               menuInfo.food_price = row.lookup_by_name("food_price");
               menuInfo.food_unit = row.lookup_by_name("food_unit");
               menuInfo.repertory_flag = row.lookup_by_name("repertory_flag");
               menuInfo.ck_name = row.lookup_by_name("ck_name");
               vec.push_back(menuInfo);
         }
   }mycatch();
   return vec;
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::getMenuInfoByKind(int kindId)
// Purpose:    Implementation of HMenuInfoCtrl::getMenuInfoByKind()
// Parameters:
// - kindId
// Return:     vector<HMenuInfo>
////////////////////////////////////////////////////////////////////////

vector<HMenuInfo> HMenuInfoCtrl::getMenuInfoByKind(int kindId)
{
   // TODO : implement
      vector<HMenuInfo> vec; 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo WHERE kind_id = " << kindId ;
         mysqlpp::Result res = query.store();
         if ( ! res.empty() ){
               mysqlpp::Row row;
               HMenuInfo menuInfo;
               mysqlpp::Result::iterator it = res.begin();
               row = *it;
               menuInfo.food_id = row.lookup_by_name("food_id");
               menuInfo.kind_id = kindId;
               menuInfo.food_name = row.lookup_by_name("food_name");
               menuInfo.food_price = row.lookup_by_name("food_price");
               menuInfo.food_unit = row.lookup_by_name("food_unit");
               menuInfo.repertory_flag = row.lookup_by_name("repertory_flag");
               menuInfo.ck_name = row.lookup_by_name("ck_name");
               vec.push_back(menuInfo);
         }
   }mycatch();
   return vec;
}