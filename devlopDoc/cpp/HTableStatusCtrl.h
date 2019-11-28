/***********************************************************************
 * Module:  HTableStatusCtrl.h
 * Author:  babala
 * Modified: 2005年4月21日 23:49:26
 * Purpose: Declaration of the class HTableStatusCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HTableStatusCtrl_h)
#define __hotelMIS_HTableStatusCtrl_h

#include <HTableStatus.h>

class HTableStatusCtrl
{
public:
   HTableStatusCtrl(mysqlpp::Connection * pCon);
   ~HTableStatusCtrl();
   void insert(int tableId, int roomId, int tableState);
   void insert(mysqlpp::HTableStatus& tableStatus);
   void update(mysqlpp::HTableStatus tableStatus);
   void Delete(int tableId);
   HTableStatus getTableStatus(int tableId);
   vector<HTableStatus> getAllTableStatus(void);
   vector<HTableStatus> getTableStatusSpecial(int roomId);
   void createTable(int roomId, int tableNum);
   int getMaxTableId(void) const;
   bool isExist(int tableId);
   string getRoomName(int roomId);
   string getTableStateName(int tableState);
   /* 通过特定桌号返回所有的桌号用于创建每一个餐厅的桌子. */
   vector<HTableStatus> getAllTableFromRoomNo(int roomNo);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif