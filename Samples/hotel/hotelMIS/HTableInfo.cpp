/***********************************************************************
 * Module:  HTableInfo.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ22ÈÕ 0:52:20
 * Purpose: Implementation of the class HTableInfo
 ***********************************************************************/
#include "stdAfx.h"

#include "HTableInfo.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::HTableInfo()
// Purpose:    Implementation of HTableInfo::HTableInfo()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableInfo::HTableInfo()
:table_id(0),
  room_id(0),
  room_name(""),
  state_name(""),
  person_num(0),
  re_state(0)
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::~HTableInfo()
// Purpose:    Implementation of HTableInfo::~HTableInfo()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableInfo::~HTableInfo()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::getTable_id()
// Purpose:    Implementation of HTableInfo::getTable_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableInfo::getTable_id(void)
{
   return table_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::setTable_id(int newTable_id)
// Purpose:    Implementation of HTableInfo::setTable_id()
// Parameters:
// - newTable_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableInfo::setTable_id(int newTable_id)
{
   table_id = newTable_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::getRoom_id()
// Purpose:    Implementation of HTableInfo::getRoom_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableInfo::getRoom_id(void)
{
   return room_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::setRoom_id(int newRoom_id)
// Purpose:    Implementation of HTableInfo::setRoom_id()
// Parameters:
// - newRoom_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableInfo::setRoom_id(int newRoom_id)
{
   room_id = newRoom_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::getRoom_name()
// Purpose:    Implementation of HTableInfo::getRoom_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HTableInfo::getRoom_name(void)
{
   return room_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::setRoom_name(string newRoom_name)
// Purpose:    Implementation of HTableInfo::setRoom_name()
// Parameters:
// - newRoom_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableInfo::setRoom_name(string newRoom_name)
{
   room_name = newRoom_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::getState_name()
// Purpose:    Implementation of HTableInfo::getState_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HTableInfo::getState_name(void)
{
   return state_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::setState_name(string newState_name)
// Purpose:    Implementation of HTableInfo::setState_name()
// Parameters:
// - newState_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableInfo::setState_name(string newState_name)
{
   state_name = newState_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::getPerson_num()
// Purpose:    Implementation of HTableInfo::getPerson_num()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableInfo::getPerson_num(void)
{
   return person_num;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::setPerson_num(int newPerson_num)
// Purpose:    Implementation of HTableInfo::setPerson_num()
// Parameters:
// - newPerson_num
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableInfo::setPerson_num(int newPerson_num)
{
   person_num = newPerson_num;
}
///////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::getRe_state()
// Purpose:    Implementation of HTableInfo::getRe_state()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableInfo::getRe_state(void)
{
   return re_state;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableInfo::setRe_state(int newRe_state)
// Purpose:    Implementation of HTableInfo::setRe_state()
// Parameters:
// - newRe_state
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableInfo::setRe_state(int newRe_state)
{
   re_state = newRe_state;
}