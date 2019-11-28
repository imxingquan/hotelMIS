/***********************************************************************
 * Module:  HOutStore.cpp
 * Author:  babala
 * Modified: 2005Äê5ÔÂ5ÈÕ 14:45:18
 * Purpose: Implementation of the class HOutStore
 ***********************************************************************/

#include "HOutStore.h"

////////////////////////////////////////////////////////////////////////
// Name:       HOutStore::HOutStore()
// Purpose:    Implementation of HOutStore::HOutStore()
// Return:     
////////////////////////////////////////////////////////////////////////

HOutStore::HOutStore()
: out_id(0),
food_id(0),
food_name(""),
out_num(0),
out_price(0.0f),
out_unit(""),
out_date(""),
rep_flag(0),
ad_name("")
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HOutStore::~HOutStore()
// Purpose:    Implementation of HOutStore::~HOutStore()
// Return:     
////////////////////////////////////////////////////////////////////////

HOutStore::~HOutStore()
{
   // TODO : implement
}