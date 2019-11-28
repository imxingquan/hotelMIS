/***********************************************************************
* Module:  HEmployeeCtrl.h
* Author:  babala
* Modified: 2005年4月23日 18:20:06
* Purpose: Declaration of the class HEmployeeCtrl
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
#if !defined(__hotelMIS_HEmployeeCtrl_h)
#define __hotelMIS_HEmployeeCtrl_h
#include "config.h"
#include <HEmployee.h>
namespace hotelMIS{
	typedef vector<HEmployee> HEmployeeVec;
	class HEmployeeCtrl
	{
	public:
		HEmployeeCtrl(mysqlpp::Connection * pCon);
		~HEmployeeCtrl();
		void insert(HEmployee& emp);
		void update(HEmployee& emp);
		void Delete(string empId);
		HEmployee getEmployee(string empId);
		vector<HEmployee> getAllCook();
		vector<HEmployee> getAllEmployee(void);
		bool isExist(string empId);
		hotelMIS::HEmployeeVec searchEmp(string key);
	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif