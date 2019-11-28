/***********************************************************************
 * Module:  HRepDetailsCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ6ÈÕ 21:38:14
 * Purpose: Declaration of the class HRepDetailsCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HRepDetailsCtrl_h)
#define __hotelMIS_HRepDetailsCtrl_h

#include <HRepDetails.h>

class HRepDetailsCtrl
{
public:
   HRepDetailsCtrl(mysqlpp::Connection * pCon);
   ~HRepDetailsCtrl();
   void insert(HRepDetails& repDetails);
   void Delete(string accountId, int foodId);
   void Delete(string accountId);
   void update(string accountId, int foodId, int foodNum);
   int getFoodNum(string accountId, int foodId);
   vector<HRepDetails> getAllDetails(string accountId);
   float getAllPrice(string accountId);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif