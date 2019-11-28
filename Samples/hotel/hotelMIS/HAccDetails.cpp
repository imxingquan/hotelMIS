//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccDetails.cpp
//
// Description:    
//				
// Version: 1.0
//
// Hostory:		
//			05-8-2005	邢泉	Created	
//			
//---------------------------------------------------------
#include "stdAfx.h"
#include "HAccDetails.h"
using namespace hotelMIS;


HAccDetails::HAccDetails()
:account_id(""),
food_id(0),
food_name(""),
food_num(0),
food_price(0.0f),
ck_name(""),
food_unit(""),
id(0),
zk_num(0.0f),
kind_id(0),
total_fl(0)
{
}



HAccDetails::~HAccDetails()
{
  
}