/***********************************************************************
 * Module:  HAccDetailsCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ22ÈÕ 21:13:04
 * Purpose: Declaration of the class HAccDetailsCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HAccDetailsCtrl_h)
#define __hotelMIS_HAccDetailsCtrl_h

class HAccDetails;

#include <HAccDetails.h>

class HAccDetailsCtrl
{
public:
   HAccDetailsCtrl(mysqlpp::Connection* pCon);
   ~HAccDetailsCtrl();
   void insert(HAccDetails accDetails);
   void update(HAccDetails accDetails);
   void Delete(string accountId, string foodName);
   vector<HAccDetails> getAccDetails(string accountId);

   HAccDetails** Association_1;

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif