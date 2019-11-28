/***********************************************************************
 * Module:  HRepDetails.cpp
 * Author:  babala
 * Modified: 2005Äê5ÔÂ6ÈÕ 20:38:06
 * Purpose: Implementation of the class HRepDetails
 ***********************************************************************/
#include "stdAfx.h"
#include "HRepDetails.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HRepDetails::HRepDetails()
// Purpose:    Implementation of HRepDetails::HRepDetails()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepDetails::HRepDetails()
:account_id(""),
food_id(0),
food_name(""),
food_num(0),
food_price(0.0f),
ck_name(""),
food_unit(""),
food_cook(-1),
id(-1),
food_cancel_msg(""),
food_status(0),
kind_zk(0),
kind_id(0),
zk_num(1.0f),
total_fl(0)
{
   
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetails::~HRepDetails()
// Purpose:    Implementation of HRepDetails::~HRepDetails()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepDetails::~HRepDetails()
{
   // TODO : implement
}