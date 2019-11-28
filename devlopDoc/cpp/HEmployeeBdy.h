/***********************************************************************
 * Module:  HEmployeeBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ20ÈÕ 11:16:45
 * Purpose: Declaration of the class HEmployeeBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HEmployeeBdy_h)
#define __hotelMIS_HEmployeeBdy_h

class HEmployeeBdy
{
public:
   HEmployeeBdy();
   ~HEmployeeBdy();
   int AddEmp(string emp_Id, string name, string sex, int job_id, string job_name, string phone, string birth, string address, string demo, string photo);
   EmployeeVec getAllEmp(void);
   int delEmp(string empId);
   int ModifyEmp(int emp_id, string name, string sex, int job_id, string job_name, string photo, string birth, string address, string demo, string phone);

protected:
private:
   hotelMIS::HRepastCtrl * pEmpCtrl;
   hotelMIS::KDBCon m_con;


};

#endif