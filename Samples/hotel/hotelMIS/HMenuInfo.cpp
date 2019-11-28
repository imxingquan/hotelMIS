/***********************************************************************
 * Module:  HMenuInfo.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ25ÈÕ 2:29:10
 * Purpose: Implementation of the class HMenuInfo
 ***********************************************************************/
#include "stdAfx.h"
#include "HMenuInfo.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfo::HMenuInfo()
// Purpose:    Implementation of HMenuInfo::HMenuInfo()
// Return:     
////////////////////////////////////////////////////////////////////////

HMenuInfo::HMenuInfo()
:food_id(0),
kind_id(0),
food_name(""),
food_price(0.0f),
food_num(1),
food_unit(""),
repertory_flag(0),
ck_name(""),
food_cook(-1),
food_py(""),
bTaocan(false),
total_fl(0)
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfo::~HMenuInfo()
// Purpose:    Implementation of HMenuInfo::~HMenuInfo()
// Return:     
////////////////////////////////////////////////////////////////////////

HMenuInfo::~HMenuInfo()
{
   // TODO : implement
}