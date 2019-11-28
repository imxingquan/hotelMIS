/***********************************************************************
 * Module:  HTableStatusSet.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ19ÈÕ 19:24:36
 * Purpose: Implementation of the class HTableStatusSet
 * Comment: ²Í×À×´Ì¬
 ***********************************************************************/

#include "HTableStatusSet.h"

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::HTableStatusSet()
// Purpose:    Implementation of HTableStatusSet::HTableStatusSet()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatusSet::HTableStatusSet()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::HTableStatusSet(int tableState, string stateName, int personNum)
// Purpose:    Implementation of HTableStatusSet::HTableStatusSet()
// Parameters:
// - tableState
// - stateName
// - personNum
// Return:     void
////////////////////////////////////////////////////////////////////////

HTableStatusSet::HTableStatusSet(int tableState, string stateName, int personNum)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::~HTableStatusSet()
// Purpose:    Implementation of HTableStatusSet::~HTableStatusSet()
// Return:     
////////////////////////////////////////////////////////////////////////

HTableStatusSet::~HTableStatusSet()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::getState_name()
// Purpose:    Implementation of HTableStatusSet::getState_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HTableStatusSet::getState_name(void)
{
   return state_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::setState_name(string newState_name)
// Purpose:    Implementation of HTableStatusSet::setState_name()
// Parameters:
// - newState_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusSet::setState_name(string newState_name)
{
   state_name = newState_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::getTable_state()
// Purpose:    Implementation of HTableStatusSet::getTable_state()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableStatusSet::getTable_state(void)
{
   return table_state;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::setTable_state(int newTable_state)
// Purpose:    Implementation of HTableStatusSet::setTable_state()
// Parameters:
// - newTable_state
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusSet::setTable_state(int newTable_state)
{
   table_state = newTable_state;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::getPerson_num()
// Purpose:    Implementation of HTableStatusSet::getPerson_num()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HTableStatusSet::getPerson_num(void)
{
   return person_num;
}

////////////////////////////////////////////////////////////////////////
// Name:       HTableStatusSet::setPerson_num(int newPerson_num)
// Purpose:    Implementation of HTableStatusSet::setPerson_num()
// Parameters:
// - newPerson_num
// Return:     void
////////////////////////////////////////////////////////////////////////

void HTableStatusSet::setPerson_num(int newPerson_num)
{
   person_num = newPerson_num;
}