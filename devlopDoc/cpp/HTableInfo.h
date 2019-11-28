/***********************************************************************
 * Module:  HTableInfo.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ22ÈÕ 4:12:42
 * Purpose: Declaration of the class HTableInfo
 ***********************************************************************/

#if !defined(__hotelMIS_HTableInfo_h)
#define __hotelMIS_HTableInfo_h

class HTableInfo
{
public:
   HTableInfo();
   ~HTableInfo();
   int getTable_id(void);
   void setTable_id(int newTable_id);
   int getRoom_id(void);
   void setRoom_id(int newRoom_id);
   string getRoom_name(void);
   void setRoom_name(string newRoom_name);
   string getState_name(void);
   void setState_name(string newState_name);
   int getPerson_num(void);
   void setPerson_num(int newPerson_num);
   int getRe_state(void);
   void setRe_state(int newRe_state);

protected:
private:
   int table_id;
   int room_id;
   string room_name;
   string state_name;
   int person_num;
   int re_state;


};

#endif