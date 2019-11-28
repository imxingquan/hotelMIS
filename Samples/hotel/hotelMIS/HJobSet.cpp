/***********************************************************************
 * Module:  HJobSet.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 17:12:10
 * Purpose: Implementation of the class HJobSet
 ***********************************************************************/
#include "stdAfx.h"
#include "HJobSet.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HJobSet::HJobSet()
// Purpose:    Implementation of HJobSet::HJobSet()
// Return:     
////////////////////////////////////////////////////////////////////////

HJobSet::HJobSet()
:job_id(0),
job_name("")
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSet::~HJobSet()
// Purpose:    Implementation of HJobSet::~HJobSet()
// Return:     
////////////////////////////////////////////////////////////////////////

HJobSet::~HJobSet()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSet::getJob_id()
// Purpose:    Implementation of HJobSet::getJob_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HJobSet::getJob_id(void)
{
   return job_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSet::setJob_id(int newJob_id)
// Purpose:    Implementation of HJobSet::setJob_id()
// Parameters:
// - newJob_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HJobSet::setJob_id(int newJob_id)
{
   job_id = newJob_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSet::getJob_name()
// Purpose:    Implementation of HJobSet::getJob_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HJobSet::getJob_name(void)
{
   return job_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSet::setJob_name(string newJob_name)
// Purpose:    Implementation of HJobSet::setJob_name()
// Parameters:
// - newJob_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HJobSet::setJob_name(string newJob_name)
{
   job_name = newJob_name;
}