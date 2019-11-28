/***********************************************************************
 * Module:  HEmployeeBdy.cpp
 * Author:  babala
 * Modified: 2005年5月20日 11:16:45
 * Purpose: Implementation of the class HEmployeeBdy
 ***********************************************************************/
#include "stdAfx.h"
#include "HEmployeeBdy.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeBdy::HEmployeeBdy()
// Purpose:    Implementation of HEmployeeBdy::HEmployeeBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HEmployeeBdy::HEmployeeBdy()
{
   // TODO : 
   pEmpCtrl = NULL;
   pEmpCtrl = new HEmployeeCtrl(m_con.get_con());
    
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeBdy::~HEmployeeBdy()
// Purpose:    Implementation of HEmployeeBdy::~HEmployeeBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HEmployeeBdy::~HEmployeeBdy()
{
   // TODO : 
   if ( pEmpCtrl ){
      delete pEmpCtrl;
      pEmpCtrl = NULL;
   }
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeBdy::AddEmp(string emp_Id, string name, string sex, int job_id, string job_name, string phone, string birth, string address, string demo, string photo)
// Purpose:    Implementation of HEmployeeBdy::AddEmp()
// Parameters:
// - emp_Id
// - name
// - sex
// - job_id
// - job_name
// - phone
// - birth
// - address
// - demo
// - photo
// Return:     int
////////////////////////////////////////////////////////////////////////

int HEmployeeBdy::AddEmp(string emp_id, string name, string sex, int job_id, string job_name, string phone, string birth, string address, string demo, string photo)
{
   // TODO : 
   assert( pEmpCtrl != NULL);
   HEmployee emp;
   if ( pEmpCtrl->isExist(emp_id)){
         return 1;
   }
   
   emp.emp_id = emp_id;
   emp.emp_name = name;
   emp.emp_sex = sex;
   emp.emp_job_id = job_id;
   emp.emp_job_name = job_name;
   emp.emp_phone =  phone;
   emp.emp_birth = birth;
   emp.emp_address = address;
   emp.emp_demo = demo;
   emp.emp_photo = photo;
   
   pEmpCtrl->insert(emp);
   
   return 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeBdy::getAllEmp()
// Purpose:    Implementation of HEmployeeBdy::getAllEmp()
// Return:     EmployeeVec
////////////////////////////////////////////////////////////////////////

HEmployeeVec HEmployeeBdy::getAllEmp(void)
{
   // TODO : 
    return pEmpCtrl->getAllEmployee();
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeBdy::delEmp(string empId)
// Purpose:    Implementation of HEmployeeBdy::delEmp()
// Parameters:
// - empId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HEmployeeBdy::delEmp(string empId)
{
   // TODO : 删除员工
   pEmpCtrl->Delete(empId);
   
   return 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       HEmployeeBdy::ModifyEmp(int emp_id, string name, string sex, int job_id, string job_name, string photo, string birth, string address, string demo, string phone)
// Purpose:    Implementation of HEmployeeBdy::ModifyEmp()
// Parameters:
// - emp_id
// - name
// - sex
// - job_id
// - job_name
// - photo
// - birth
// - address
// - demo
// - phone
// Return:     int
////////////////////////////////////////////////////////////////////////

int HEmployeeBdy::ModifyEmp(int emp_id, string name, string sex, int job_id, string job_name, string photo, string birth, string address, string demo, string phone)
{
   // TODO : 修改资料
   HEmployee emp;
   emp.emp_id = emp_id;
   emp.emp_name = name;
   emp.emp_sex = sex;
   emp.emp_job_id = job_id;
   emp.emp_job_name = job_name;
   emp.emp_phone = phone;
   emp.emp_birth = birth;
   emp.emp_address = address;
   emp.emp_demo = demo;
   emp.emp_photo = photo;
   
   pEmpCtrl->update(emp);   
   return 0;
}

bool HEmployeeBdy::isExist(string empId)
{
	return pEmpCtrl->isExist(empId);
}

hotelMIS::HJobSetVec HEmployeeBdy::getAllJob()
{
	hotelMIS::HJobSetCtrl jobSetCtrl(m_con.get_con());
	return jobSetCtrl.getAllJob();
}

hotelMIS::HEmployeeVec HEmployeeBdy::searchEmp(string key)
{
	return pEmpCtrl->searchEmp(key);
}