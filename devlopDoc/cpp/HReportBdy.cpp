/***********************************************************************
 * Module:  HReportBdy.cpp
 * Author:  babala
 * Modified: 2005年5月22日 21:59:45
 * Purpose: Implementation of the class HReportBdy
 ***********************************************************************/

#include "HReportBdy.h"

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::HReportBdy()
// Purpose:    Implementation of HReportBdy::HReportBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HReportBdy::HReportBdy()
{
   pAccountCtrl = NULL;
   pAccountCtrl = new HAccountCtrl(m_con.get_con());
   
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::~HReportBdy()
// Purpose:    Implementation of HReportBdy::~HReportBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HReportBdy::~HReportBdy()
{
   // TODO : 删除
    if ( pAccountCtrl ){
         delete pAccountCtrl;
         pAccountCtrl = NULL;
     }
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByDay(string day)
// Purpose:    Implementation of HReportBdy::totalByDay()
// Parameters:
// - day
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByDay(string day)
{
   // TODO : 日统计报表
   
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByMonth()
// Purpose:    Implementation of HReportBdy::totalByMonth()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByMonth(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByYear()
// Purpose:    Implementation of HReportBdy::totalByYear()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByYear(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByCookDay()
// Purpose:    Implementation of HReportBdy::totalByCookDay()
// Return:     HTotalByCookVec
////////////////////////////////////////////////////////////////////////

HTotalByCookVec HReportBdy::totalByCookDay(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByCookMonth()
// Purpose:    Implementation of HReportBdy::totalByCookMonth()
// Return:     HTotalByCookVec
////////////////////////////////////////////////////////////////////////

HTotalByCookVec HReportBdy::totalByCookMonth(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByCookYear()
// Purpose:    Implementation of HReportBdy::totalByCookYear()
// Return:     HTotalByCookVec
////////////////////////////////////////////////////////////////////////

HTotalByCookVec HReportBdy::totalByCookYear(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByDayNoPay()
// Purpose:    Implementation of HReportBdy::totalByDayNoPay()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByDayNoPay(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByMonthNoPay()
// Purpose:    Implementation of HReportBdy::totalByMonthNoPay()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByMonthNoPay(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByYearNoPay()
// Purpose:    Implementation of HReportBdy::totalByYearNoPay()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByYearNoPay(void)
{
   // TODO : implement
}