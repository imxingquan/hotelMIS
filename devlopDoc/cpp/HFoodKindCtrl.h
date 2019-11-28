/***********************************************************************
 * Module:  HFoodKindCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ25ÈÕ 1:53:51
 * Purpose: Declaration of the class HFoodKindCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HFoodKindCtrl_h)
#define __hotelMIS_HFoodKindCtrl_h

#include <HFoodKind.h>

class HFoodKindCtrl
{
public:
   HFoodKindCtrl(mysqlpp::Connection * pCon);
   ~HFoodKindCtrl();
   void insert(string name, int flag, int ts);
   void update(HFoodKind& foodKind);
   void Delete(int kindId);
   HFoodKind getKind(int kindId);
   vector<HFoodKind> getAllKind(void);
   vector<HFoodKind> getTsKind(void);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif