/***********************************************************************
 * Module:  HRepDetails.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ6ÈÕ 20:38:06
 * Purpose: Declaration of the class HRepDetails
 ***********************************************************************/

#if !defined(__hotelMIS_HRepDetails_h)
#define __hotelMIS_HRepDetails_h

class HRepDetails
{
public:
   HRepDetails();
   ~HRepDetails();

   string accound_id;
   int food_id;
   string food_name;
   int food_num;
   float food_price;
   string ck_name;

protected:
private:

};

#endif