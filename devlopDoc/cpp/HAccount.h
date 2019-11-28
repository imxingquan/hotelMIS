/***********************************************************************
 * Module:  HAccount.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ8ÈÕ 11:25:35
 * Purpose: Declaration of the class HAccount
 ***********************************************************************/

#if !defined(__hotelMIS_HAccount_h)
#define __hotelMIS_HAccount_h

class HAccount
{
public:
   HAccount();
   ~HAccount();

   string accound_id;
   int room_id;
   int table_id;
   string cust_date;
   string cust_time;
   string pay_date;
   string pay_time;
   float yscost;
   float erase_zero;
   float zhekou;
   int reckoning;
   float sscost;
   int acc_status;
   string ad_name;

protected:
private:

};

#endif