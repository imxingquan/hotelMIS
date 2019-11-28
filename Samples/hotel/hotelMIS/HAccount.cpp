//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HAccount.cpp
//
// Description:    
//				对应账单数据表 t_account 中的一行数据   
//		
//
// Version: 1.0
//
// Hostory:		
//			05-8-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HAccount.h"
using namespace hotelMIS;

HAccount::HAccount()
: account_id(""),
  room_id(0),
  table_id(0),
 cust_date(""),
 cust_time(""),
 pay_date(""),
 pay_time(""),
 subscription(0.0f),
 yscost(0.0f),
 erase_zero(0.0f),
zhekou(0.0f),
reckoning(0),
sscost(0.0f),
acc_status(0),
ad_name(""),
daijin(0.0f),
sj(0.0f),
zy(0.0f),
paystatus(0),
bz(""),
arid(0),
zfprice(0.0f),
sswr(0)
{
}


HAccount::~HAccount()
{
  
}