/***********************************************************************
 * Module:  HTableStatus.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ20ÈÕ 8:30:24
 * Purpose: Implementation of the class HTableStatus
 ***********************************************************************/

#include "HTableStatus.h"

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::HTableStatus()
// Purpose:    Implementation of HTableStatus::HTableStatus()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatus::HTableStatus()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::HTableStatus(int tableId, int roomId, int tableState)
// Purpose:    Implementation of HTableStatus::HTableStatus()
// Parameters:
// - tableId
// - roomId
// - tableState
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatus::HTableStatus(int tableId, int roomId, int tableState)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::~HTableStatus()
// Purpose:    Implementation of HTableStatus::~HTableStatus()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatus::~HTableStatus()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::getTable_id()
// Purpose:    Implementation of HTableStatus::getTable_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableStatus::getTable_id(void)
{
   return table_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::setTable_id(int newTable_id)
// Purpose:    Implementation of HTableStatus::setTable_id()
// Parameters:
// - newTable_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatus::setTable_id(int newTable_id)
{
   table_id = newTable_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::getRoom_id()
// Purpose:    Implementation of HTableStatus::getRoom_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableStatus::getRoom_id(void)
{
   return room_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::setRoom_id(int newRoom_id)
// Purpose:    Implementation of HTableStatus::setRoom_id()
// Parameters:
// - newRoom_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatus::setRoom_id(int newRoom_id)
{
   room_id = newRoom_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::getTable_state()
// Purpose:    Implementation of HTableStatus::getTable_state()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableStatus::getTable_state(void)
{
   return table_state;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatus::setTable_state(int newTable_state)
// Purpose:    Implementation of HTableStatus::setTable_state()
// Parameters:
// - newTable_state
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatus::setTable_state(int newTable_state)
{
   table_state = newTable_state;
}