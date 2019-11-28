/***********************************************************************
 * Module:  HAdmin.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ15ÈÕ 9:57:44
 * Purpose: Implementation of the class HAdmin
 ***********************************************************************/

#include "HAdmin.h"

using namespace hotelMIS;

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::get_id()
// Purpose:    Implementation of HAdmin::get_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int hotelMIS::HAdmin::get_id(void)
{
   return _id;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::set_id(int new_id)
// Purpose:    Implementation of HAdmin::set_id()
// Parameters:
// - new_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void hotelMIS::HAdmin::set_id(int new_id)
{
   _id = new_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::get_login_id()
// Purpose:    Implementation of HAdmin::get_login_id()
// Return:     string
////////////////////////////////////////////////////////////////////////

string hotelMIS::HAdmin::get_login_id(void)
{
   return _login_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::set_login_id(string new_login_id)
// Purpose:    Implementation of HAdmin::set_login_id()
// Parameters:
// - new_login_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void hotelMIS::HAdmin::set_login_id(string new_login_id)
{
   _login_id = new_login_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::get_name()
// Purpose:    Implementation of HAdmin::get_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string hotelMIS::HAdmin::get_name(void)
{
   return _name;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::set_name(string new_name)
// Purpose:    Implementation of HAdmin::set_name()
// Parameters:
// - new_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void hotelMIS::HAdmin::set_name(string new_name)
{
   _name = new_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::get_opType()
// Purpose:    Implementation of HAdmin::get_opType()
// Return:     string
////////////////////////////////////////////////////////////////////////

string hotelMIS::HAdmin::get_opType(void)
{
   return _opType;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::set_opType(string new_opType)
// Purpose:    Implementation of HAdmin::set_opType()
// Parameters:
// - new_opType
// Return:     void
////////////////////////////////////////////////////////////////////////

void hotelMIS::HAdmin::set_opType(string new_opType)
{
   _opType = new_opType;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::get_password()
// Purpose:    Implementation of HAdmin::get_password()
// Return:     string
////////////////////////////////////////////////////////////////////////

string hotelMIS::HAdmin::get_password(void)
{
   return _password;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::set_password(string new_password)
// Purpose:    Implementation of HAdmin::set_password()
// Parameters:
// - new_password
// Return:     void
////////////////////////////////////////////////////////////////////////

void hotelMIS::HAdmin::set_password(string new_password)
{
   _password = new_password;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::get_desc()
// Purpose:    Implementation of HAdmin::get_desc()
// Return:     string
////////////////////////////////////////////////////////////////////////

string hotelMIS::HAdmin::get_desc(void)
{
   return _desc;
}

////////////////////////////////////////////////////////////////////////
// Name:       hotelMIS::HAdmin::set_desc(string new_desc)
// Purpose:    Implementation of HAdmin::set_desc()
// Parameters:
// - new_desc
// Return:     void
////////////////////////////////////////////////////////////////////////

void hotelMIS::HAdmin::set_desc(string new_desc)
{
   _desc = new_desc;
}