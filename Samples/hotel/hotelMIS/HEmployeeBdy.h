/***********************************************************************
* Module:  HEmployeeBdy.h
* Author:  babala
* Modified: 2005年5月20日 11:16:45
* Purpose: Declaration of the class HEmployeeBdy
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/20/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HEmployeeBdy_h)
#define __hotelMIS_HEmployeeBdy_h
#include "HEmployeeCtrl.h"
#include "KDBCon.h"
#include "HJobSetCtrl.h"
#include <cassert>
using namespace std;
namespace hotelMIS{
	class HEmployeeBdy
	{
	public:
		HEmployeeBdy();
		~HEmployeeBdy();
		int AddEmp(string emp_id, string name, string sex, int job_id, string job_name, string phone, string birth, string address, string demo, string photo);
		hotelMIS::HEmployeeVec getAllEmp(void);
		hotelMIS::HEmployeeVec searchEmp(string key);
		int delEmp(string empId);
		int ModifyEmp(int emp_id, string name, string sex, int job_id, string job_name, string photo, string birth, string address, string demo, string phone);
		bool isExist(string empId);
		hotelMIS::HJobSetVec getAllJob();
	
	protected:
	private:
		hotelMIS::HEmployeeCtrl * pEmpCtrl;
		hotelMIS::KDBCon m_con;

	};
}
#endif