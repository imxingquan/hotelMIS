/***********************************************************************
 * Module:  HRepBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ6ÈÕ 22:23:12
 * Purpose: Declaration of the class HRepBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HRepBdy_h)
#define __hotelMIS_HRepBdy_h

#include <HAccount.h>

class HRepBdy
{
public:
   HRepBdy(mysqlpp::Connection* pCon);
   ~HRepBdy();
   void addRep(int foodId);
   int delRep(string accountId, int foodId, int foodNum);
   void checkOut(HAccount& account);
   int cancel(string accountId);

   int table_id;
   int room_id;

protected:
   string createAccount(void);

private:
   mysqlpp::Connection* _pCon;


};

#endif