//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HUnitSet.h
//
// Description:    
//				��λ�������Ӧ t_unit ��
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	��Ȫ	Created	
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