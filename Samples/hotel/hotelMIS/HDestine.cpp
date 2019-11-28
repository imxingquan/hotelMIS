/***********************************************************************
 * Module:  HDestine.cpp
 * Author:  babala
 * Modified: 2005Äê5ÔÂ12ÈÕ 18:22:45
 * Purpose: Implementation of the class HDestine
 ***********************************************************************/
#include "stdAfx.h"
#include "HDestine.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HDestine::HDestine()
// Purpose:    Implementation of HDestine::HDestine()
// Return:     
////////////////////////////////////////////////////////////////////////

HDestine::HDestine():
id(0),
guest_name(""),
guest_phone(""),
come_date(""),
come_time(""),
person_num(0),
subscription(0.0f),
remark(""),
bdisp(1)
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestine::~HDestine()
// Purpose:    Implementation of HDestine::~HDestine()
// Return:     
////////////////////////////////////////////////////////////////////////

HDestine::~HDestine()
{
   // TODO : implement
}