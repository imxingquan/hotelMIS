/***********************************************************************
 * Module:  HRepastCtrl.h
 * Author:  babala
 * Modified: 2005年5月6日 22:31:20
 * Purpose: Declaration of the class HRepastCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HRepastCtrl_h)
#define __hotelMIS_HRepastCtrl_h

#include <HRepast.h>

class HRepastCtrl
{
public:
   HRepastCtrl(mysqlpp::Connection * pCon);
   ~HRepastCtrl();
   void insert(HRepast& rep);
   void Delete(string accountId);
   /* 获得就餐状态 */
   int getRepastState(int tableId, int roomId);
   string getAccountId(int tableId, int roomId);
   /* 返回  */
   int chgTable(string accountId, int tableId, int roomId);
   int isEmptyTable(int tableId, int roomId);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif