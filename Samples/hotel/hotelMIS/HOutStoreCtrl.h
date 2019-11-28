/***********************************************************************
 * Module:  HOutStoreCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ5ÈÕ 14:39:12
 * Purpose: Declaration of the class HOutStoreCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HOutStoreCtrl_h)
#define __hotelMIS_HOutStoreCtrl_h
#include "config.h"
#include <HOutStore.h>
#include <string>
using namespace std;
namespace hotelMIS{
	typedef vector<HOutStore> HOutStoreVec;
class HOutStoreCtrl
{
public:
   HOutStoreCtrl(mysqlpp::Connection * pCon);
   ~HOutStoreCtrl();
   int insert(HOutStore& outStore, int opType);
   HOutStoreVec getAllOutStore(string sDate, string eDate);
   void DeleteAll();
protected:
private:
   mysqlpp::Connection * _pCon;


};
}
#endif