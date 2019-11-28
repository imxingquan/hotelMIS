/***********************************************************************
 * Module:  HRepToTalCtrl.cpp
 * Author:  babala
 * Modified: 2005Äê5ÔÂ4ÈÕ 3:45:29
 * Purpose: Implementation of the class HRepToTalCtrl
 ***********************************************************************/

#include "HRepToTalCtrl.h"

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
         mysqlpp::Query query = _pCon->get_con();
         query  <<" INSERT INTO t_repertoryTotal  (food_id) VALUES ( " << foodId  <<")";
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
      mysqlpp::Query query = _pCon->get_con();
      query << "DELETE FROM t_repertory_total WHERE food_id = " << foodId;
      query.execute();
   }mycatch():
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