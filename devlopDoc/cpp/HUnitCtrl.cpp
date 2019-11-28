/***********************************************************************
 * Module:  HUnitCtrl.cpp
 * Author:  babala
 * Modified: 2005年4月23日 8:27:22
 * Purpose: Implementation of the class HUnitCtrl
 ***********************************************************************/

#include "HUnitCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HUnitCtrl::HUnitCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HUnitCtrl::HUnitCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HUnitCtrl::HUnitCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitCtrl::~HUnitCtrl()
// Purpose:    Implementation of HUnitCtrl::~HUnitCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HUnitCtrl::~HUnitCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitCtrl::insert(string unitName)
// Purpose:    Implementation of HUnitCtrl::insert()
// Parameters:
// - unitName
// Return:     void
////////////////////////////////////////////////////////////////////////

void HUnitCtrl::insert(string unitName)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_unit_set (unit) VALUES('"<<unitName<<"')";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitCtrl::Delete(int unitId)
// Purpose:    Implementation of HUnitCtrl::Delete()
// Parameters:
// - unitId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HUnitCtrl::Delete(int unitId)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_unit_set WHERE unit_id = " << unitId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitCtrl::getAllUnit()
// Purpose:    Implementation of HUnitCtrl::getAllUnit()
// Return:     vector<HUnitSet>
////////////////////////////////////////////////////////////////////////

vector<HUnitSet> HUnitCtrl::getAllUnit(void)
{
   // TODO : 获取所有单位 
   vector<HUnitSet> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_unit_set ";
         mysqlpp::Result res = query.store();
         mysqlpp::Result::Iterator it;
         mysqlpp::Row row ;
        
         HUnitSet; unitSet;
         int unitId;
         string unitName;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
                unitId = row.lookup_by_name("unit_id");
                unitName = row.lookup_by_name("unit");
               unitSet.setUnit_id(unitId);
               unitSet.setUnit_name(unitName);
               vec.push_back(unitSet);
         }
   }mycatch();
   return vec;
}