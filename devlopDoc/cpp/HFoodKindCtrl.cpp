/***********************************************************************
 * Module:  HFoodKindCtrl.cpp
 * Author:  babala
 * Modified: 2005年4月25日 1:53:51
 * Purpose: Implementation of the class HFoodKindCtrl
 ***********************************************************************/

#include "HFoodKindCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::HFoodKindCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HFoodKindCtrl::HFoodKindCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HFoodKindCtrl::HFoodKindCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::~HFoodKindCtrl()
// Purpose:    Implementation of HFoodKindCtrl::~HFoodKindCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HFoodKindCtrl::~HFoodKindCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::insert(string name, int flag, int ts)
// Purpose:    Implementation of HFoodKindCtrl::insert()
// Parameters:
// - name
// - flag
// - ts
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKindCtrl::insert(string name, int flag, int ts)
{
   // TODO : 添加类别
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_foodKind ( kind_name,kind_flag,kind_ts) VALUES ('"
                     << name << "',"
                     << flag << ","
                     << ts << ")";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::update(HFoodKind& foodKind)
// Purpose:    Implementation of HFoodKindCtrl::update()
// Parameters:
// - foodKind
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKindCtrl::update(HFoodKind& foodKind)
{
   // TODO : 修改
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_foodKind SET kind_name ='"
                     << foodKind.getKind_name() << "',kind_flag="
                     << foodKind.getKind_flag() << ",kind_ts = "
                     << foodKind.getKind_ts()
                     << " WHERE kind_id = " << foodKind.getKind_id();
          query.execute();
   }mycatch():
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::Delete(int kindId)
// Purpose:    Implementation of HFoodKindCtrl::Delete()
// Parameters:
// - kindId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKindCtrl::Delete(int kindId)
{
   // TODO : 删除
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_foodKind WHERE kind_id = " 
                     << kindId;
          query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getKind(int kindId)
// Purpose:    Implementation of HFoodKindCtrl::getKind()
// Parameters:
// - kindId
// Return:     HFoodKind
////////////////////////////////////////////////////////////////////////

HFoodKind HFoodKindCtrl::getKind(int kindId)
{
   // TODO : 获得一个类别
   HFoodKind foodKind;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind WHERE kind_id = " << kindId;
         mysqlpp::Result res = query.store();
         if ( ! res.empty() ){
            mysqlpp::Row row;
            mysqlpp::Result::iterator it = res.begin();
            row = *it;
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
            foodKind.setKind_id(kindId);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
         }
   }mycatch();
   return foodKind;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getAllKind()
// Purpose:    Implementation of HFoodKindCtrl::getAllKind()
// Return:     vector<HFoodKind>
////////////////////////////////////////////////////////////////////////

vector<HFoodKind> HFoodKindCtrl::getAllKind(void)
{
   // TODO : implement
    vector<HFoodKind> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind " ;
         mysqlpp::Result res = query.store();
         HFoodKind foodKind;
         mysqlpp::Row row;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
            row = *it;
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
            foodKind.setKind_id(kindId);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
            vec.push_back(foodKind);
         }
   }mycatch();
   return vec;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getTsKind()
// Purpose:    Implementation of HFoodKindCtrl::getTsKind()
// Return:     vector<HFoodKind>
////////////////////////////////////////////////////////////////////////

vector<HFoodKind> HFoodKindCtrl::getTsKind(void)
{
   // TODO : implement
    vector<HFoodKind> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind WHERE kind_ts != 0" ;
         mysqlpp::Result res = query.store();
         HFoodKind foodKind;
         mysqlpp::Row row;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
            row = *it;
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
            foodKind.setKind_id(kindId);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
            vec.push_back(foodKind);
         }
   }mycatch();
   return vec;
}