/***********************************************************************
 * Module:  HRoom.h
 * Author:  babala
 * Modified: 2005年4月15日 10:25:21
 * Purpose: Declaration of the class HRoom
 ***********************************************************************/

#if !defined(__hotelMIS_HRoom_h)
#define __hotelMIS_HRoom_h

class HRoom
{
public:
   int getRoom_id(void);
   void setRoom_id(int newRoom_id);
   string getRoom_name(void);
   void setRoom_name(string newRoom_name);
   int getTable_num(void);
   void setTable_num(int newTable_num);
   HRoom();
   ~HRoom();

protected:
private:
   /* 餐厅编号 */
   int room_id;
   /* 餐厅名称 */
   string room_name;
   /* 餐桌数量 */
   int table_num;


};

#endif