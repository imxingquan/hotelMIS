/***********************************************************************
 * Module:  HTableStatus.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ20ÈÕ 8:30:24
 * Purpose: Declaration of the class HTableStatus
 ***********************************************************************/

#if !defined(__hotelMIS_HTableStatus_h)
#define __hotelMIS_HTableStatus_h

class HTableStatus
{
public:
   HTableStatus();
   HTableStatus(int tableId, int roomId, int tableState);
   ~HTableStatus();
   int getTable_id(void);
   void setTable_id(int newTable_id);
   int getRoom_id(void);
   void setRoom_id(int newRoom_id);
   int getTable_state(void);
   void setTable_state(int newTable_state);

protected:
private:
   int table_id;
   int room_id;
   int table_state;


};

#endif