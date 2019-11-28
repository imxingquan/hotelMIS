/***********************************************************************
 * Module:  HTableStatusSetCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ19ÈÕ 22:40:20
 * Purpose: Declaration of the class HTableStatusSetCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HTableStatusSetCtrl_h)
#define __hotelMIS_HTableStatusSetCtrl_h

#include <HTableStatusSet.h>

class HTableStatusSetCtrl
{
public:
   HTableStatusSetCtrl(mysqlpp::Connnection * pCon);
   ~HTableStatusSetCtrl();
   void insert(string stateName, int person_num);
   void update(HTableStatusSet& tableSset);
   void delete(int tssate);
   HTableStatusSet getHTableStatus(int tableState);
   vector<HTableStatusSet> getAllTableStatusSet(void);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif