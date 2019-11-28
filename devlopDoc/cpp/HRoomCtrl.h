/***********************************************************************
 * Module:  HRoomCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ15ÈÕ 11:01:03
 * Purpose: Declaration of the class HRoomCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HRoomCtrl_h)
#define __hotelMIS_HRoomCtrl_h

#include <HRoom.h>

class HRoomCtrl
{
public:
   void deleteRoom(int id);
   vector<HRoom> getAllRoom(void);
   void insertRoom(string name, int tableNum);
   void updateRoom(HRoom& room);
   HRoomCtrl(mysqlpp::Connection * pCon);
   ~HRoomCtrl();

protected:
private:
   int getRoomMax(void);

   mysqlpp::Connection * _pCon;


};

#endif