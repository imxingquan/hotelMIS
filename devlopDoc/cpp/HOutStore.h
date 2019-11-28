/***********************************************************************
 * Module:  HOutStore.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ5ÈÕ 14:45:18
 * Purpose: Declaration of the class HOutStore
 ***********************************************************************/

#if !defined(__hotelMIS_HOutStore_h)
#define __hotelMIS_HOutStore_h

class HOutStore
{
public:
   HOutStore();
   ~HOutStore();

   long out_id;
   int food_id;
   int food_name;
   float out_price;
   string out_date;
   int out_flag;
   int ad_name;

protected:
private:
   int out_num;
   int out_unit;


};

#endif