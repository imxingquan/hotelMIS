//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HUnitSet.h
//
// Description:    
//				单位设置类对应 t_unit 表
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HUnitSet.h"

using namespace hotelMIS;

HUnitSet::HUnitSet()
: unit_id(0),
unit_name("")
{
}


HUnitSet::~HUnitSet()
{
   // TODO : implement
}

int HUnitSet::getUnit_id(void)
{
   return unit_id;
}


void HUnitSet::setUnit_id(int newUnit_id)
{
   unit_id = newUnit_id;
}


string HUnitSet::getUnit_name(void)
{
   return unit_name;
}


void HUnitSet::setUnit_name(string newUnit_name)
{
   unit_name = newUnit_name;
}