/***********************************************************************
 * Module:  HEmployee.cpp
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 18:21:40
 * Purpose: Implementation of the class HEmployee
 ***********************************************************************/
#include "stdAfx.h"
#include "HEmployee.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::HEmployee()
// Purpose:    Implementation of HEmployee::HEmployee()
// Return:     
////////////////////////////////////////////////////////////////////////

HEmployee::HEmployee()
: emp_id(""),
emp_name(""),
emp_sex(""),
emp_job_id(0),
emp_job_name(""),
emp_phone(""),
emp_photo(""),
emp_birth(""),
emp_address(""),
emp_demo("")
{
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::~HEmployee()
// Purpose:    Implementation of HEmployee::~HEmployee()
// Return:     
////////////////////////////////////////////////////////////////////////

HEmployee::~HEmployee()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_id()
// Purpose:    Implementation of HEmployee::getEmp_id()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_id(void)
{
   return emp_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_id(string newEmp_id)
// Purpose:    Implementation of HEmployee::setEmp_id()
// Parameters:
// - newEmp_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_id(string newEmp_id)
{
   emp_id = newEmp_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_name()
// Purpose:    Implementation of HEmployee::getEmp_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_name(void)
{
   return emp_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_name(string newEmp_name)
// Purpose:    Implementation of HEmployee::setEmp_name()
// Parameters:
// - newEmp_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_name(string newEmp_name)
{
   emp_name = newEmp_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_sex()
// Purpose:    Implementation of HEmployee::getEmp_sex()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_sex(void)
{
   return emp_sex;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_sex(string newEmp_sex)
// Purpose:    Implementation of HEmployee::setEmp_sex()
// Parameters:
// - newEmp_sex
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_sex(string newEmp_sex)
{
   emp_sex = newEmp_sex;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_job_id()
// Purpose:    Implementation of HEmployee::getEmp_job_id()
// Return:     int
////////////////////////////////////////////////////////////////////////

int HEmployee::getEmp_job_id(void)
{
   return emp_job_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_job_id(int newEmp_job_id)
// Purpose:    Implementation of HEmployee::setEmp_job_id()
// Parameters:
// - newEmp_job_id
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_job_id(int newEmp_job_id)
{
   emp_job_id = newEmp_job_id;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_job_name()
// Purpose:    Implementation of HEmployee::getEmp_job_name()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_job_name(void)
{
   return emp_job_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_job_name(string newEmp_job_name)
// Purpose:    Implementation of HEmployee::setEmp_job_name()
// Parameters:
// - newEmp_job_name
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_job_name(string newEmp_job_name)
{
   emp_job_name = newEmp_job_name;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_phone()
// Purpose:    Implementation of HEmployee::getEmp_phone()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_phone(void)
{
   return emp_phone;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_phone(string newEmp_phone)
// Purpose:    Implementation of HEmployee::setEmp_phone()
// Parameters:
// - newEmp_phone
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_phone(string newEmp_phone)
{
   emp_phone = newEmp_phone;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_photo()
// Purpose:    Implementation of HEmployee::getEmp_photo()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_photo(void)
{
   return emp_photo;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_photo(string newEmp_photo)
// Purpose:    Implementation of HEmployee::setEmp_photo()
// Parameters:
// - newEmp_photo
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_photo(string newEmp_photo)
{
   emp_photo = newEmp_photo;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_birth()
// Purpose:    Implementation of HEmployee::getEmp_birth()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_birth(void)
{
   return emp_birth;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_birth(string newEmp_birth)
// Purpose:    Implementation of HEmployee::setEmp_birth()
// Parameters:
// - newEmp_birth
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_birth(string newEmp_birth)
{
   emp_birth = newEmp_birth;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_address()
// Purpose:    Implementation of HEmployee::getEmp_address()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_address(void)
{
   return emp_address;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_address(string newEmp_address)
// Purpose:    Implementation of HEmployee::setEmp_address()
// Parameters:
// - newEmp_address
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_address(string newEmp_address)
{
   emp_address = newEmp_address;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::getEmp_demo()
// Purpose:    Implementation of HEmployee::getEmp_demo()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HEmployee::getEmp_demo(void)
{
   return emp_demo;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployee::setEmp_demo(string newEmp_demo)
// Purpose:    Implementation of HEmployee::setEmp_demo()
// Parameters:
// - newEmp_demo
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployee::setEmp_demo(string newEmp_demo)
{
   emp_demo = newEmp_demo;
}