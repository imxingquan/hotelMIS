/***********************************************************************
 * Module:  HPayBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ14ÈÕ 11:35:48
 * Purpose: Declaration of the class HPayBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HPayBdy_h)
#define __hotelMIS_HPayBdy_h

#include <HRepastCtrl.h>
#include <HAccountCtrl.h>

class HPayBdy
{
public:
   HPayBdy(int tableId, int roomId, mysqlpp::Connection* pCon);
   ~HPayBdy();
   float getYsPrice(void);
   float calc(float ml, float zk, float sj);
   float getSsPrice(void);
   void jz(int reckoning);

protected:
private:
   int table_id;
   int room_id;
   HRepastCtrl* repastCtrl;
   HRepastDetailsCtrl* repDetailsCtrl;
   HAccountCtrl* accountCtrl;
   string accountId;
   float yscost;
   float sscost;
   float subscription;
   flaot erase_zero;
   float zhekou;


};

#endif