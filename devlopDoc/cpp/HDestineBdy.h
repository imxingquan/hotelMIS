/***********************************************************************
 * Module:  HDestineBdy.h
 * Author:  babala
 * Modified: 2005年5月12日 17:44:33
 * Purpose: Declaration of the class HDestineBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HDestineBdy_h)
#define __hotelMIS_HDestineBdy_h

#include <HDestineCtrl.h>

class HDestineBdy
{
public:
   HDestineBdy(mysqlpp::Connection * pCon, int roomId, int tableId);
   ~HDestineBdy();
   /* 就餐操作 */
   void destine(string guest_name, string come_date, string come_time, int person_num, float subscription, string remark);
   /* 由订餐状态,转换到就餐状态 */
   void chgRepast(void);
   /* 取消定餐 */
   void cancelDestine(void);

protected:
private:
   HDestineCtrl* _ctrl;
   int table_id;
   int room_id;


};

#endif