/***********************************************************************
 * Module:  HAccSearchBdy.cpp
 * Author:  babala
 * Modified: 2005Äê5ÔÂ29ÈÕ 12:47:22
 * Purpose: Implementation of the class HAccSearchBdy
 ***********************************************************************/
#include "stdAfx.h"
#include "HAccSearchBdy.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HAccSearchBdy::HAccSearchBdy()
// Purpose:    Implementation of HAccSearchBdy::HAccSearchBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HAccSearchBdy::HAccSearchBdy()
{
      pAccCtrl = new HAccountCtrl(m_con.get_con());
      pAccDetailsCtrl = new HAccDetailsCtrl(m_con.get_con());
      
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccSearchBdy::~HAccSearchBdy()
// Purpose:    Implementation of HAccSearchBdy::~HAccSearchBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HAccSearchBdy::~HAccSearchBdy()
{
   // TODO : implement
   if ( pAccCtrl ){
         delete pAccCtrl;
         pAccCtrl = NULL;
   }
   if ( pAccDetailsCtrl){
         delete pAccDetailsCtrl;
         pAccDetailsCtrl = NULL;
   }
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccSearchBdy::search(string sDate, string eDate, int accStatus)
// Purpose:    Implementation of HAccSearchBdy::search()
// Parameters:
// - sDate
// - eDate
// - accStatus
// Return:     HAccountVec
////////////////////////////////////////////////////////////////////////

HAccountVec HAccSearchBdy::search(string sDate, string eDate, int accStatus,int arid,int cw,int jsfs)
{
   // TODO : implement
	return pAccCtrl->search(sDate,eDate,accStatus,arid,cw,jsfs);
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccSearchBdy::search(string accid)
// Purpose:    Implementation of HAccSearchBdy::search()
// Parameters:
// - accid
// Return:     HAccount
////////////////////////////////////////////////////////////////////////

HAccount HAccSearchBdy::search(string accid)
{
   // TODO : implement
	return pAccCtrl->getAccount(accid);
}

////////////////////////////////////////////////////////////////////////
// Name:       HAccSearchBdy::searchDetails(string accid)
// Purpose:    Implementation of HAccSearchBdy::searchDetails()
// Parameters:
// - accid
// Return:     HAccDetailsVec
////////////////////////////////////////////////////////////////////////

HAccDetailsVec HAccSearchBdy::searchDetails(string accid)
{
   // TODO : implement
	return pAccDetailsCtrl->getAccDetails(accid);
}