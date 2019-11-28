/***********************************************************************
 * Module:  HAccountCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ6ÈÕ 22:31:30
 * Purpose: Declaration of the class HAccountCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HAccountCtrl_h)
#define __hotelMIS_HAccountCtrl_h

#include <HAccount.h>

class HAccountCtrl
{
public:
   HAccountCtrl(mysqlpp::Connection * pCon);
   ~HAccountCtrl();
   void insert(HAccount& account);
   int update(HAccount& account);
   int getNowCnt(void);
   int cancel(int accountId);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif