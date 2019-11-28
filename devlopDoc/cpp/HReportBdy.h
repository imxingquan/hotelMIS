/***********************************************************************
 * Module:  HReportBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ22ÈÕ 21:59:45
 * Purpose: Declaration of the class HReportBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HReportBdy_h)
#define __hotelMIS_HReportBdy_h

#include <HAccountCtrl.h>

class HReportBdy
{
public:
   HReportBdy();
   ~HReportBdy();
   HAccountVec totalByDay(string day);
   HAccountVec totalByMonth(void);
   HAccountVec totalByYear(void);
   HTotalByCookVec totalByCookDay(void);
   HTotalByCookVec totalByCookMonth(void);
   HTotalByCookVec totalByCookYear(void);
   HAccountVec totalByDayNoPay(void);
   HAccountVec totalByMonthNoPay(void);
   HAccountVec totalByYearNoPay(void);

protected:
private:
   HAccountCtrl* pAccountCtrl;
   KDBCon m_con;


};

#endif