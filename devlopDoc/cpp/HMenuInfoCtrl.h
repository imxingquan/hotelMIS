/***********************************************************************
 * Module:  HMenuInfoCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ25ÈÕ 2:29:41
 * Purpose: Declaration of the class HMenuInfoCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HMenuInfoCtrl_h)
#define __hotelMIS_HMenuInfoCtrl_h

#include <HMenuInfo.h>

class HMenuInfoCtrl
{
public:
   HMenuInfoCtrl(mysqlpp::Connection * pCon);
   ~HMenuInfoCtrl();
   void insert(HMenuInfo& menuInfo);
   void update(HMenuInfo& menuInfo);
   void Delete(int foodId);
   HMenuInfo getMenuInfo(int foodId);
   vector<HMenuInfo> getAllMenuInfo(void);
   vector<HMenuInfo> getMenuInfoByKind(int kindId);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif