/***********************************************************************
 * Module:  HRepertory.h
 * Author:  babala
 * Modified: 2005��5��4�� 3:50:55
 * Purpose: Declaration of the class HRepertory
 ***********************************************************************/

#if !defined(__hotelMIS_HRepertory_h)
#define __hotelMIS_HRepertory_h

class HRepertory
{
public:
   HRepertory();
   ~HRepertory();

   int rep_id;
   int food_id;
   string food_name;
   int rep_num;
   float rep_price;
   string unit;
   string rep_date;
   /* 1: ��� 2: ������ */
   int rep_flag;
   string ad_name;

protected:
private:

};

#endif