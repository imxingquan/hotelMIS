/***********************************************************************
 * Module:  HEmployeeCtrl.cpp
 * Author:  babala
 * Modified: 2005年4月23日 18:20:06
 * Purpose: Implementation of the class HEmployeeCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HEmployeeCtrl.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::HEmployeeCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HEmployeeCtrl::HEmployeeCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HEmployeeCtrl::HEmployeeCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::~HEmployeeCtrl()
// Purpose:    Implementation of HEmployeeCtrl::~HEmployeeCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HEmployeeCtrl::~HEmployeeCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::insert(const HEmployee& emp)
// Purpose:    Implementation of HEmployeeCtrl::insert()
// Parameters:
// - emp
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployeeCtrl::insert(HEmployee& emp)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_employee (emp_id,emp_name,emp_sex,emp_job_id,emp_job_name,emp_phone,emp_photo,emp_birth,emp_address,emp_demo) VALUES('"
         << emp.getEmp_id()<<"','"
         << emp.getEmp_name()<<"','"
         << emp.getEmp_sex()<<"',"
         << emp.getEmp_job_id()<<",'"
         << emp.getEmp_job_name()<<"','"
         << emp.getEmp_phone()<<"','"
         << emp.getEmp_photo()<<"','"
         << emp.getEmp_birth()<<"','"
         << emp.getEmp_address()<<"','"
         << emp.getEmp_demo()<<"')";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::update(const HEmployee& emp)
// Purpose:    Implementation of HEmployeeCtrl::update()
// Parameters:
// - emp
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployeeCtrl::update(HEmployee& emp)
{
   // TODO : Modify Employee Information
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE  t_employee SET emp_name = '"
         <<emp.getEmp_name()<<"',"
         <<"emp_sex ='" << emp.getEmp_sex() <<"',"
         <<"emp_job_id ="<< emp.getEmp_job_id() << ","
         <<"emp_job_name ='"<<emp.getEmp_name()<<"',"
         <<"emp_phone='"<<emp.getEmp_phone()<<"',"
         <<"emp_photo ='"<<emp.getEmp_photo()<<"',"
         <<"emp_birth = '"  <<emp.getEmp_birth() << "',"
         <<"emp_address='"<<emp.getEmp_address()<<"',"
         <<"emp_demo = '" << emp.getEmp_demo() << "'  "
         <<" WHERE emp_id ='"<< emp.getEmp_id()<<"'";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::Delete(string empId)
// Purpose:    Implementation of HEmployeeCtrl::Delete()
// Parameters:
// - empId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HEmployeeCtrl::Delete(string empId)
{
   // TODO : Delete employee Information
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_employee WHERE emp_id ='" << empId <<"'";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::getEmployee(string empId)
// Purpose:    Implementation of HEmployeeCtrl::getEmployee()
// Parameters:
// - empId
// Return:     HEmployee
////////////////////////////////////////////////////////////////////////

HEmployee HEmployeeCtrl::getEmployee(string empId)
{
   // TODO : get employee that emp_id equal empid
   HEmployee emp;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_employee WHERE emp_id = '"<<empId<<"'";
         mysqlpp::Result res = query.store();
         string emp_name,emp_sex,emp_job_name,emp_phone,emp_photo,emp_birth,emp_address,emp_demo;
         int emp_job_id;
         
         if ( ! res.empty() )
         {
               mysqlpp::Row  row;
               mysqlpp::Result::iterator it  = res.begin();
               row = *it;
               emp_name = row.lookup_by_name("emp_name");
               emp_sex = row.lookup_by_name("emp_sex");
               emp_job_id = row.lookup_by_name("emp_job_id");
               emp_phone = row.lookup_by_name("emp_phone");
               emp_photo  = row.lookup_by_name("emp_photo");
               emp_birth = row.lookup_by_name("emp_birth");
               emp_address = row.lookup_by_name("emp_address");
               emp_demo = row.lookup_by_name("emp_demo");
               emp.setEmp_id(empId);
               emp.setEmp_name(emp_name);
               emp.setEmp_sex(emp_sex);
               emp.setEmp_job_id(emp_job_id);
               emp.setEmp_job_name(emp_job_name);
               emp.setEmp_phone(emp_phone);
               emp.setEmp_photo(emp_photo);
               emp.setEmp_birth(emp_birth);
               emp.setEmp_address(emp_address);
               emp.setEmp_demo(emp_demo);
         }
         
   }mycatch();
   return emp;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeCtrl::getAllEmployee()
// Purpose:    Implementation of HEmployeeCtrl::getAllEmployee()
// Return:     vector<HEmployee>
////////////////////////////////////////////////////////////////////////

vector<HEmployee> HEmployeeCtrl::getAllEmployee(void)
{
   // TODO : return all employee Information
   vector<HEmployee> vec;
   
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_employee ";
         mysqlpp::Result res = query.store();
         string emp_id,emp_name,emp_sex,emp_job_name,emp_phone,emp_photo,emp_birth,emp_address,emp_demo;
         int emp_job_id;
         HEmployee emp;
        mysqlpp::Row  row;
         mysqlpp::Result::iterator it  ;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
			   emp_id = row.lookup_by_name("emp_id");
               emp_name = row.lookup_by_name("emp_name");
               emp_sex = row.lookup_by_name("emp_sex");
               emp_job_id = row.lookup_by_name("emp_job_id");
			   emp_job_name = row.lookup_by_name("emp_job_name");
               emp_phone = row.lookup_by_name("emp_phone");
               emp_photo  = row.lookup_by_name("emp_photo");
               emp_birth = row.lookup_by_name("emp_birth");
               emp_address = row.lookup_by_name("emp_address");
               emp_demo = row.lookup_by_name("emp_demo");
               emp.setEmp_id(emp_id);
               emp.setEmp_name(emp_name);
               emp.setEmp_sex(emp_sex);
               emp.setEmp_job_id(emp_job_id);
               emp.setEmp_job_name(emp_job_name);
               emp.setEmp_phone(emp_phone);
               emp.setEmp_photo(emp_photo);
               emp.setEmp_birth(emp_birth);
               emp.setEmp_address(emp_address);
               emp.setEmp_demo(emp_demo);
               vec.push_back(emp);
         }
         
   }mycatch();
   return vec;
}
//
//返回所有厨师。
vector<HEmployee>  HEmployeeCtrl::getAllCook()
{
	 vector<HEmployee> vec;
   
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_employee WHERE emp_job_name like '%厨%' ORDER BY emp_id";
         mysqlpp::Result res = query.store();
         string emp_id,emp_name,emp_sex,emp_job_name,emp_phone,emp_photo,emp_birth,emp_address,emp_demo;
         int emp_job_id=0;
         HEmployee emp;
		 mysqlpp::Row row;
         mysqlpp::Result::iterator it  ;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
			   emp_id = row.lookup_by_name("emp_id");
               emp_name = row.lookup_by_name("emp_name");
               emp_sex = row.lookup_by_name("emp_sex");
               emp_job_id = row.lookup_by_name("emp_job_id");
               emp_phone = row.lookup_by_name("emp_phone");
               emp_photo  = row.lookup_by_name("emp_photo");
               emp_birth = row.lookup_by_name("emp_birth");
               emp_address = row.lookup_by_name("emp_address");
               emp_demo = row.lookup_by_name("emp_demo");
               emp.setEmp_id(emp_id);
               emp.setEmp_name(emp_name);
               emp.setEmp_sex(emp_sex);
               emp.setEmp_job_id(emp_job_id);
               emp.setEmp_job_name(emp_job_name);
               emp.setEmp_phone(emp_phone);
               emp.setEmp_photo(emp_photo);
               emp.setEmp_birth(emp_birth);
               emp.setEmp_address(emp_address);
               emp.setEmp_demo(emp_demo);
               vec.push_back(emp);
         }
         
   }mycatch();
   return vec;
}

bool HEmployeeCtrl::isExist(string empId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT emp_id FROM t_employee WHERE emp_id ='"<<empId<<"'";
		mysqlpp::Result res = query.store();
		if ( ! res.empty() )
			return true;
	}mycatch();
	return false;
}

hotelMIS::HEmployeeVec HEmployeeCtrl::searchEmp(string key)
{
	HEmployeeVec vec;
	try{
		 string emp_id,emp_name,emp_sex,emp_job_name,emp_phone,emp_photo,emp_birth,emp_address,emp_demo;
         int emp_job_id=0;
		  HEmployee emp;
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_employee WHERE emp_id LIKE '%"<<key<<"%' OR "
			  << "emp_name LIKE '%" << key <<"%' OR "
			  << "emp_sex = '"<< key <<"' OR "
			  << "emp_job_name LIKE '%"<< key <<"%' OR "
			  << "emp_phone LIKE '%" << key <<"%' OR "
			  << "emp_address LIKE '%" << key <<"%'";
		 mysqlpp::Result res = query.store();
		 mysqlpp::Row row;
         mysqlpp::Result::iterator it  ;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
			   emp_id = row.lookup_by_name("emp_id");
               emp_name = row.lookup_by_name("emp_name");
               emp_sex = row.lookup_by_name("emp_sex");
               emp_job_id = row.lookup_by_name("emp_job_id");
               emp_phone = row.lookup_by_name("emp_phone");
               emp_photo  = row.lookup_by_name("emp_photo");
               emp_birth = row.lookup_by_name("emp_birth");
               emp_address = row.lookup_by_name("emp_address");
               emp_demo = row.lookup_by_name("emp_demo");
               emp.setEmp_id(emp_id);
               emp.setEmp_name(emp_name);
               emp.setEmp_sex(emp_sex);
               emp.setEmp_job_id(emp_job_id);
               emp.setEmp_job_name(emp_job_name);
               emp.setEmp_phone(emp_phone);
               emp.setEmp_photo(emp_photo);
               emp.setEmp_birth(emp_birth);
               emp.setEmp_address(emp_address);
               emp.setEmp_demo(emp_demo);
               vec.push_back(emp);
         }
	}mycatch();
	return vec;
}