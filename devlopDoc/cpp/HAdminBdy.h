/***********************************************************************
 * Module:  HAdminBdy.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ15ÈÕ 10:18:53
 * Purpose: Declaration of the class HAdminBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HAdminBdy_h)
#define __hotelMIS_HAdminBdy_h

#include <HAdmin.h>

class HAdminBdy
{
public:
   hotelMIS::HAdmin getAdminInfo(const string& name);
   vector<HAdmin> getAllAdminInfo(void);
   HAdminBdy();
   ~HAdminBdy();
   bool login(const string& name, const string& password);

protected:
private:
   string _log_name;
   mysqlpp::Connection* _pCon;


};

#endif