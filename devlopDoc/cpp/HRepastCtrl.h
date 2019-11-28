/***********************************************************************
 * Module:  HRepastCtrl.h
 * Author:  babala
 * Modified: 2005��5��6�� 22:31:20
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
   /* ��þͲ�״̬ */
   int getRepastState(int tableId, int roomId);
   string getAccountId(int tableId, int roomId);
   /* ����  */
   int chgTable(string accountId, int tableId, int roomId);
   int isEmptyTable(int tableId, int roomId);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif