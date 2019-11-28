/***********************************************************************
 * Module:  HRepToTalCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月4日 3:45:29
 * Purpose: Implementation of the class HRepToTalCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HRepToTalCtrl.h"

using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HRepToTalCtrl::HRepToTalCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HRepToTalCtrl::HRepToTalCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HRepToTalCtrl::HRepToTalCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepToTalCtrl::~HRepToTalCtrl()
// Purpose:    Implementation of HRepToTalCtrl::~HRepToTalCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepToTalCtrl::~HRepToTalCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepToTalCtrl::insert(int foodId, int totalNum)
// Purpose:    Implementation of HRepToTalCtrl::insert()
// Parameters:
// - foodId
// - totalNum
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepToTalCtrl::insert(int foodId, int totalNum)
{
   // TODO : implement
   try{
	   mysqlpp::Query query = _pCon->query();
       query  <<" INSERT INTO t_repertory_total  (food_id) VALUES ( " << foodId  <<")";
       query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepToTalCtrl::Delete(int foodId)
// Purpose:    Implementation of HRepToTalCtrl::Delete()
// Parameters:
// - foodId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepToTalCtrl::Delete(int foodId)
{
   // TODO : implement
   try{
	   mysqlpp::Query query = _pCon->query();
      query << "DELETE FROM t_repertory_total WHERE food_id = " << foodId;
      query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepToTalCtrl::addNum(int foodId, int repNum)
// Purpose:    Implementation of HRepToTalCtrl::addNum()
// Parameters:
// - foodId
// - repNum
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepToTalCtrl::addNum(int foodId, int repNum)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_repertory_total SET rep_num = rep_num + "<<repNum 
                     << " WHERE food_id = " << foodId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepToTalCtrl::delNum(int foodId, int repNum)
// Purpose:    Implementation of HRepToTalCtrl::delNum()
// Parameters:
// - foodId
// - repNum
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepToTalCtrl::delNum(int foodId, int repNum)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_repertory_total SET rep_num = rep_num - "<<repNum 
                     << " WHERE food_id = " << foodId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       int HRepToTalCtrl::getNum(int foodId)
// Desc:	返回 food_id 的库存 
//
////////////////////////////////////////////////////////////////////////
int HRepToTalCtrl::getNum(int foodId)
{
	int num = 0;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT rep_num FROM t_repertory_total WHERE food_id = " << foodId;
		mysqlpp::Result res = query.store();
		if ( !res.empty() )
		{
			mysqlpp::Row row;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			num = row.lookup_by_name("rep_num");
		}
	}mycatch();
	return num;
}

bool HRepToTalCtrl::isExist(int foodId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"SELECT food_id FROM t_repertory_total WHERE food_id = " << foodId;
		mysqlpp::Result res = query.store();
		if ( !res.empty())
			return true;
	}mycatch();
	return false;
}

HRepTotalVec HRepToTalCtrl::getAllRepTotal()
{
	HRepTotalVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT food_name,rep_num FROM t_repertory_total,t_menuinfo WHERE t_repertory_total.food_id = t_menuinfo.food_id";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HRepTotal repTotal;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			repTotal.food_name = row.lookup_by_name("food_name");
			repTotal.rep_num = row.lookup_by_name("rep_num");
			vec.push_back(repTotal);
		}

	}mycatch();
	return vec;
}

void HRepToTalCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_repertory_total";
		query.execute();
	}mycatch();
}