/***********************************************************************
 * Module:  HReportBdy.cpp
 * Author:  babala
 * Modified: 2005年5月22日 21:59:45
 * Purpose: Implementation of the class HReportBdy
 ***********************************************************************/
#include "stdAfx.h"
#include "HReportBdy.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::HReportBdy()
// Purpose:    Implementation of HReportBdy::HReportBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HReportBdy::HReportBdy()
{
   pAccountCtrl = NULL;
   pAccountCtrl = new HAccountCtrl(m_con.get_con());
   pAccDetailsCtrl = new HAccDetailsCtrl(m_con.get_con());
   
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
	if ( pAccDetailsCtrl){
		delete pAccDetailsCtrl;
		pAccDetailsCtrl = NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByDay(string day)
// Purpose:    Implementation of HReportBdy::totalByDay()
// Parameters:
// - day
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByDay(string sDate,string eDate,int jsfs)
{
   // TODO : 日统计报表
	return pAccountCtrl->getByDay(sDate, eDate,jsfs);
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByMonth()
// Purpose:    Implementation of HReportBdy::totalByMonth()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByMonth(string year,string month)
{
   // TODO : implement
	 
	return pAccountCtrl->getByMonth(year,month);
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByYear()
// Purpose:    Implementation of HReportBdy::totalByYear()
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HReportBdy::totalByYear(string year)
{
   // TODO : implement
	
	return pAccountCtrl->getByYear(year);
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByCookDay()
// Purpose:    Implementation of HReportBdy::totalByCookDay()
// Return:     HTotalByCookVec
////////////////////////////////////////////////////////////////////////

HTotalByCookVec HReportBdy::totalByCookDay(string day)
{
   // TODO : implement
	
	return pAccDetailsCtrl->getByDayCkName(day);
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByCookMonth()
// Purpose:    Implementation of HReportBdy::totalByCookMonth()
// Return:     HTotalByCookVec
////////////////////////////////////////////////////////////////////////

HTotalByCookVec HReportBdy::totalByCookMonth(string year,string month)
{
   // TODO : implement
	
	return pAccDetailsCtrl->getByMonthCkName(year,month);
}

////////////////////////////////////////////////////////////////////////
// Name:       HReportBdy::totalByCookYear()
// Purpose:    Implementation of HReportBdy::totalByCookYear()
// Return:     HTotalByCookVec
////////////////////////////////////////////////////////////////////////

HTotalByCookVec HReportBdy::totalByCookYear(string year)
{
   // TODO : implement
	
	return pAccDetailsCtrl->getByYearCkName(year) ;
}

void HReportBdy::DeleteByAccountId(string accountId)
{
	pAccDetailsCtrl->Delete(accountId);
	pAccountCtrl->Delete(accountId);
}

void HReportBdy::DeleteAll()
{
	pAccDetailsCtrl->DeleteAll();
	pAccountCtrl->DeleteAll();
}

//----------------------------------------------------------------------------------
HAccountVec HReportBdy::totalByDateTime(string start_dtime,string end_dtime,int jsfs)
{
	return pAccountCtrl->getByDay(start_dtime,end_dtime,jsfs);
}

//-----------------------------------------------------------------------------------
HTotalAccountVec  HReportBdy::totalByPayStatus(string start_dtime,string end_dtime)
{
	return pAccountCtrl->totalByPayStatus(start_dtime,end_dtime);
}

// 按月 结算统计
HTotalAccountVec HReportBdy::totalByPayStatus(string year,string month,int bf)
{
	return pAccountCtrl->totalByPayStatus(year,month,bf);
}

// 按年 结算统计
HTotalAccountVec HReportBdy::totalByPayStatus(string year)
{
	return pAccountCtrl->totalByPayStatus(year);
}