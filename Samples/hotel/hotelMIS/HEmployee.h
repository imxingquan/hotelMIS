/***********************************************************************
* Module:  HEmployee.h
* Author:  babala
* Modified: 2005年4月23日 18:21:40
* Purpose: Declaration of the class HEmployee
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HEmployee_h)
#define __hotelMIS_HEmployee_h
#include <string>
using namespace std;
namespace hotelMIS{
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
	public:
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
}
#endif