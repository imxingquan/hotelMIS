/***********************************************************************
 * Module:  HUnitSet.cpp
 * Author:  babala
 * Modified: 2005年4月23日 8:24:13
 * Purpose: Implementation of the class HUnitSet
 * Comment: 单位设置
 ***********************************************************************/

#include "HUnitSet.h"

////////////////////////////////////////////////////////////////////////
// Name:       HUnitSet::HUnitSet()
// Purpose:    Implementation of HUnitSet::HUnitSet()
// Return:     
////////////////////////////////////////////////////////////////////////

HUnitSet::HUnitSet()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitSet::~HUnitSet()
// Purpose:    Implementation of HUnitSet::~HUnitSet()
// Return:     
////////////////////////////////////////////////////////////////////////

HUnitSet::~HUnitSet()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitSet::getUnit_id()
// Purpose:    Implementation of HUnitSet::getUnit_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HUnitSet::getUnit_id(void)
{
   return unit_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitSet::setUnit_id(int newUnit_id)
// Purpose:    Implementation of HUnitSet::setUnit_id()
// Parameters:
// - newUnit_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HUnitSet::setUnit_id(int newUnit_id)
{
   unit_id = newUnit_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitSet::getUnit_name()
// Purpose:    Implementation of HUnitSet::getUnit_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HUnitSet::getUnit_name(void)
{
   return unit_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HUnitSet::setUnit_name(string newUnit_name)
// Purpose:    Implementation of HUnitSet::setUnit_name()
// Parameters:
// - newUnit_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HUnitSet::setUnit_name(string newUnit_name)
{
   unit_name = newUnit_name;
}