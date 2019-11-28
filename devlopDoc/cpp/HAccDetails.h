/***********************************************************************
 * Module:  HAccDetails.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ22ÈÕ 21:09:09
 * Purpose: Declaration of the class HAccDetails
 ***********************************************************************/

#if !defined(__hotelMIS_HAccDetails_h)
#define __hotelMIS_HAccDetails_h

class HAccDetails
{
public:
   HAccDetails();
   ~HAccDetails();

   string account_id;
   string food_name;
   int food_num;
   float food_price;
   string ck_name;

protected:
private:

};

#endif