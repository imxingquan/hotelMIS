/***********************************************************************
 * Module:  HEmployee.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 18:21:40
 * Purpose: Declaration of the class HEmployee
 ***********************************************************************/

#if !defined(__hotelMIS_HEmployee_h)
#define __hotelMIS_HEmployee_h

class HEmployee
{
public:
   HEmployee();
   ~HEmployee();
   string getEmp_id(void);
   void setEmp_id(string newEmp_id);
   string getEmp_name(void);
   void setEmp_name(string newEmp_name);
   string getEmp_sex(void);
   void setEmp_sex(string newEmp_sex);
   int getEmp_job_id(void);
   void setEmp_job_id(int newEmp_job_id);
   string getEmp_job_name(void);
   void setEmp_job_name(string newEmp_job_name);
   string getEmp_phone(void);
   void setEmp_phone(string newEmp_phone);
   string getEmp_photo(void);
   void setEmp_photo(string newEmp_photo);
   string getEmp_birth(void);
   void setEmp_birth(string newEmp_birth);
   string getEmp_address(void);
   void setEmp_address(string newEmp_address);
   string getEmp_demo(void);
   void setEmp_demo(string newEmp_demo);

protected:
private:
   string emp_id;
   string emp_name;
   string emp_sex;
   int emp_job_id;
   string emp_job_name;
   string emp_phone;
   string emp_photo;
   string emp_birth;
   string emp_address;
   string emp_demo;


};

#endif