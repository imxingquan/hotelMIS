//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HUnitCtrl.cpp
//
// Description:    
//				HUnitCtrl.h ��ʵ��
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	��Ȫ	Created	
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

//*** ���ݿ�������� ***
//
// ����
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
// ɾ��
//
void HUnitCtrl::Delete(int unitId)
{
  try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_unit_set WHERE unit_id = " << unitId;
         query.execute();
   }mycatch();
}

// *** ҵ���߼� ***
// 
// �������еĵ�λ
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