/***********************************************************************
 * Module:  HDestine.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ12ÈÕ 18:22:45
 * Purpose: Declaration of the class HDestine
 ***********************************************************************/

#if !defined(__hotelMIS_HDestine_h)
#define __hotelMIS_HDestine_h

class HDestine
{
public:
   HDestine();
   ~HDestine();

   string account_id;
   string guest_name;
   string come_date;
   string come_time;
   int person_num;
   float subscription;
   string remark;

protected:
private:

};

#endif