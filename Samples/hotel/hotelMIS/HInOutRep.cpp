//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HBehindRep.cpp
// 
// Desc: 
//
// Author:  ÐÏÈª
//
// Modified: 2006Äê ÔÂ ÈÕ
//--------------------------------------------------------------------------------------

#include "stdafx.h"
#include ".\hinoutrep.h"

using namespace hotelMIS;

HInOutRep::HInOutRep(void)
:food_id(0),	
 inout_dh(""),
 food_name(""),		
 food_num(0),
 food_unit(""),
 food_price(0),		
 t_num(0),
 t_price(0),		
 t_sprice(0),	
 rep_flag(0),
 opdate(""),		
 ad_name("")	
{
}

HInOutRep::~HInOutRep(void)
{
}
