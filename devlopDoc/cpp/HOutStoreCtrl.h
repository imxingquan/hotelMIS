/***********************************************************************
 * Module:  HOutStoreCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ5ÈÕ 14:39:12
 * Purpose: Declaration of the class HOutStoreCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HOutStoreCtrl_h)
#define __hotelMIS_HOutStoreCtrl_h

#include <HOutStore.h>

class HOutStoreCtrl
{
public:
   HOutStoreCtrl(mysqlpp::Connection * pCon);
   ~HOutStoreCtrl();
   void insert(HOutStore& outStore, int opType);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif