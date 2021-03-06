/***********************************************************************
 * Module:  HRepast.h
 * Author:  babala
 * Modified: 2005年5月6日 15:39:10
 * Purpose: Declaration of the class HRepast
 ***********************************************************************/

#if !defined(__hotelMIS_HRepast_h)
#define __hotelMIS_HRepast_h

class HRepast
{
public:
   HRepast();
   ~HRepast();

   /* 账号 */
   string account_id;
   /* 桌号 */
   int table_id;
   /* 消费日期 */
   string cust_date;
   /* 消费时间 */
   string cust_time;
   /* 餐厅号 */
   int room_id;
   /* 消费状态
    * 0: 空桌
    * 1: 就餐
    * 2: 预定 */
   int re_state;

protected:
private:

};

#endif