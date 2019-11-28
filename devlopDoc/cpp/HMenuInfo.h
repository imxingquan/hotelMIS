/***********************************************************************
 * Module:  HMenuInfo.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ25ÈÕ 2:29:10
 * Purpose: Declaration of the class HMenuInfo
 ***********************************************************************/

#if !defined(__hotelMIS_HMenuInfo_h)
#define __hotelMIS_HMenuInfo_h

class HMenuInfo
{
public:
   HMenuInfo();
   ~HMenuInfo();

   int food_id;
   int kind_id;
   string food_name;
   float food_price;
   string food_unit;
   int repertory_flag;
   string ck_name;

protected:
private:

};

#endif