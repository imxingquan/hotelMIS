/***********************************************************************
 * Module:  HEmployeeCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 18:20:06
 * Purpose: Declaration of the class HEmployeeCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HEmployeeCtrl_h)
#define __hotelMIS_HEmployeeCtrl_h

#include <HEmployee.h>

class HEmployeeCtrl
{
public:
   HEmployeeCtrl(mysqlpp::Connection * pCon);
   ~HEmployeeCtrl();
   void insert(const HEmployee& emp);
   void update(const HEmployee& emp);
   void Delete(string empId);
   HEmployee getEmployee(string empId);
   vector<HEmployee> getAllEmployee(void);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif