//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HUnitCtrl.cpp
//
// Description:    
//				HUnitCtrl.h 的实现
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HUnitCtrl.h"

using namespace hotelMIS;


HUnitCtrl::HUnitCtrl(mysqlpp::Connection * pCon)
{
   _pCon = pCon;
}


HUnitCtrl::~HUnitCtrl()
{
  
}

//*** 数据库基本操作 ***
//
// 插入
//
void HUnitCtrl::insert(string unitName)
{
 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_unit_set (unit) VALUES('"<<unitName<<"')";
         query.execute();
   }mycatch();
}

//
// 删除
//
void HUnitCtrl::Delete(int unitId)
{
  try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_unit_set WHERE unit_id = " << unitId;
         query.execute();
   }mycatch();
}

// *** 业务逻辑 ***
// 
// 返回所有的单位
//
vector<HUnitSet> HUnitCtrl::getAllUnit(void)
{
   vector<HUnitSet> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_unit_set ORDER BY unit_id";
         mysqlpp::Result res = query.store();
		 mysqlpp::Result::iterator it;
         mysqlpp::Row row ;
        
         HUnitSet unitSet;
         int unit_id;
         string unitName;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               unit_id = row.lookup_by_name("unit_id");
               unitName = row.lookup_by_name("unit");
               unitSet.setUnit_id(unit_id);
               unitSet.setUnit_name(unitName);
               vec.push_back(unitSet);
         }
   }mycatch();
   return vec;
}