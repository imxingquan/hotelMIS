/***********************************************************************
 * Module:  HTableStatusSet.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ19ÈÕ 19:24:36
 * Purpose: Declaration of the class HTableStatusSet
 * Comment: ²Í×À×´Ì¬
 ***********************************************************************/

#if !defined(__hotelMIS_HTableStatusSet_h)
#define __hotelMIS_HTableStatusSet_h

class HTableStatusSet
{
public:
   HTableStatusSet();
   HTableStatusSet(int tableState, string stateName, int personNum);
   ~HTableStatusSet();
   string getState_name(void);
   void setState_name(string newState_name);
   int getTable_state(void);
   void setTable_state(int newTable_state);
   int getPerson_num(void);
   void setPerson_num(int newPerson_num);

protected:
private:
   int table_state;
   string state_name;
   int person_num;


};

#endif