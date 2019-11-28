/***********************************************************************
 * Module:  HTotalByCook.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ22ÈÕ 22:06:13
 * Purpose: Declaration of the class HTotalByCook
 ***********************************************************************/

#if !defined(__hotelMIS_HTotalByCook_h)
#define __hotelMIS_HTotalByCook_h

class HTotalByCook
{
public:
   HTotalByCook();
   ~HTotalByCook();

   string food_name;
   int total_food_num;
   float total_food_price;
   string ck_name;

protected:
private:

};

#endif