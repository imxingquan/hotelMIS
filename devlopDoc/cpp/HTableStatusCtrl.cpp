/***********************************************************************
 * Module:  HTableStatusCtrl.cpp
 * Author:  babala
 * Modified: 2005年4月21日 23:49:26
 * Purpose: Implementation of the class HTableStatusCtrl
 ***********************************************************************/

#include "HTableStatusCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::HTableStatusCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HTableStatusCtrl::HTableStatusCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatusCtrl::HTableStatusCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::~HTableStatusCtrl()
// Purpose:    Implementation of HTableStatusCtrl::~HTableStatusCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatusCtrl::~HTableStatusCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::insert(int tableId, int roomId, int tableState)
// Purpose:    Implementation of HTableStatusCtrl::insert()
// Parameters:
// - tableId
// - roomId
// - tableState
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusCtrl::insert(int tableId, int roomId, int tableState)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::insert(mysqlpp::HTableStatus& tableStatus)
// Purpose:    Implementation of HTableStatusCtrl::insert()
// Parameters:
// - tableStatus
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusCtrl::insert(mysqlpp::HTableStatus& tableStatus)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::update(mysqlpp::HTableStatus tableStatus)
// Purpose:    Implementation of HTableStatusCtrl::update()
// Parameters:
// - tableStatus
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusCtrl::update(mysqlpp::HTableStatus tableStatus)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::Delete(int tableId)
// Purpose:    Implementation of HTableStatusCtrl::Delete()
// Parameters:
// - tableId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusCtrl::Delete(int tableId)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getTableStatus(int tableId)
// Purpose:    Implementation of HTableStatusCtrl::getTableStatus()
// Parameters:
// - tableId
// Return:     HTableStatus
////////////////////////////////////////////////////////////////////////

HTableStatus HTableStatusCtrl::getTableStatus(int tableId)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getAllTableStatus()
// Purpose:    Implementation of HTableStatusCtrl::getAllTableStatus()
// Return:     vector<HTableStatus>
////////////////////////////////////////////////////////////////////////

vector<HTableStatus> HTableStatusCtrl::getAllTableStatus(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getTableStatusSpecial(int roomId)
// Purpose:    Implementation of HTableStatusCtrl::getTableStatusSpecial()
// Parameters:
// - roomId
// Return:     vector<HTableStatus>
////////////////////////////////////////////////////////////////////////

vector<HTableStatus> HTableStatusCtrl::getTableStatusSpecial(int roomId)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::createTable(int roomId, int tableNum)
// Purpose:    Implementation of HTableStatusCtrl::createTable()
// Parameters:
// - roomId
// - tableNum
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusCtrl::createTable(int roomId, int tableNum)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getMaxTableId()
// Purpose:    Implementation of HTableStatusCtrl::getMaxTableId()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableStatusCtrl::getMaxTableId(void) const
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::isExist(int tableId)
// Purpose:    Implementation of HTableStatusCtrl::isExist()
// Parameters:
// - tableId
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool HTableStatusCtrl::isExist(int tableId)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getRoomName(int roomId)
// Purpose:    Implementation of HTableStatusCtrl::getRoomName()
// Parameters:
// - roomId
// Return:     string
////////////////////////////////////////////////////////////////////////

string HTableStatusCtrl::getRoomName(int roomId)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getTableStateName(int tableState)
// Purpose:    Implementation of HTableStatusCtrl::getTableStateName()
// Parameters:
// - tableState
// Return:     string
////////////////////////////////////////////////////////////////////////

string HTableStatusCtrl::getTableStateName(int tableState)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusCtrl::getAllTableFromRoomNo(int roomNo)
// Purpose:    Implementation of HTableStatusCtrl::getAllTableFromRoomNo()
// Comment:    通过特定桌号返回所有的桌号用于创建每一个餐厅的桌子.
// Parameters:
// - roomNo
// Return:     vector<HTableStatus>
////////////////////////////////////////////////////////////////////////

vector<HTableStatus> HTableStatusCtrl::getAllTableFromRoomNo(int roomNo)
{
   // TODO : implement
}