//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HTableStatusSet.cpp
//
// Description:    
//				HTableStatusSet 类实现
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HTableStatusSet.h"
using namespace hotelMIS;


HTableStatusSet::HTableStatusSet()
:state_name(""),
table_state(-1),
person_num(-1),
empty_bmp(-1),
repast_bmp(-1)
{
	
}


HTableStatusSet::HTableStatusSet(int tableState,string stateName,int personNum)
:table_state(tableState),
state_name(stateName),
person_num(personNum)
{
}


HTableStatusSet::~HTableStatusSet()
{
   // TODO : implement
}


string HTableStatusSet::getState_name(void)
{
   return state_name;
}



void HTableStatusSet::setState_name(string newState_name)
{
   state_name = newState_name;
}



int HTableStatusSet::getTable_state(void)
{
   return table_state;
}


void HTableStatusSet::setTable_state(int newTable_state)
{
   table_state = newTable_state;
}

void HTableStatusSet::setPerson_num(int newPerson_num)
{
	person_num = newPerson_num;
}

int HTableStatusSet::getPerson_num(void)
{
	return person_num;
}