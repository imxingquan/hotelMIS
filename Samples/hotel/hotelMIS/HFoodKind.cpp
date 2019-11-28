/***********************************************************************
 * Module:  HFoodKind.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ25ÈÕ 0:56:22
 * Purpose: Implementation of the class HFoodKind
 ***********************************************************************/
#include "stdAfx.h"
#include "HFoodKind.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::HFoodKind()
// Purpose:    Implementation of HFoodKind::HFoodKind()
// Return:     
////////////////////////////////////////////////////////////////////////

HFoodKind::HFoodKind()
:kind_id(0),
kind_name(""),
kind_flag(0),
kind_ts(0),
kind_zk(0),
zdy_price(0)
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::~HFoodKind()
// Purpose:    Implementation of HFoodKind::~HFoodKind()
// Return:     
////////////////////////////////////////////////////////////////////////

HFoodKind::~HFoodKind()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::getKind_id()
// Purpose:    Implementation of HFoodKind::getKind_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HFoodKind::getKind_id(void)
{
   return kind_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::setKind_id(int newKind_id)
// Purpose:    Implementation of HFoodKind::setKind_id()
// Parameters:
// - newKind_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKind::setKind_id(int newKind_id)
{
   kind_id = newKind_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::getKind_name()
// Purpose:    Implementation of HFoodKind::getKind_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HFoodKind::getKind_name(void)
{
   return kind_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::setKind_name(string newKind_name)
// Purpose:    Implementation of HFoodKind::setKind_name()
// Parameters:
// - newKind_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKind::setKind_name(string newKind_name)
{
   kind_name = newKind_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::getKind_flag()
// Purpose:    Implementation of HFoodKind::getKind_flag()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HFoodKind::getKind_flag(void)
{
   return kind_flag;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::setKind_flag(int newKind_flag)
// Purpose:    Implementation of HFoodKind::setKind_flag()
// Parameters:
// - newKind_flag
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKind::setKind_flag(int newKind_flag)
{
   kind_flag = newKind_flag;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::getKind_ts()
// Purpose:    Implementation of HFoodKind::getKind_ts()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HFoodKind::getKind_ts(void)
{
   return kind_ts;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKind::setKind_ts(int newKind_ts)
// Purpose:    Implementation of HFoodKind::setKind_ts()
// Parameters:
// - newKind_ts
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKind::setKind_ts(int newKind_ts)
{
   kind_ts = newKind_ts;
}

int HFoodKind::getKind_zk(void)
{
	return kind_zk;
}

void HFoodKind::setKind_zk(int newKind_zk)
{
	kind_zk = newKind_zk;
}

void HFoodKind::setZdy_price(int newZdy_price)
{
	zdy_price = newZdy_price;
}

int HFoodKind::getZdy_price(void)
{
	return zdy_price;
}