/***********************************************************************
 * Module:  HRepSearchBdy.cpp
 * Author:  babala
 * Modified: 2005年5月28日 14:31:53
 * Purpose: Implementation of the class HRepSearchBdy
 ***********************************************************************/
#include "stdAfx.h"
#include "HRepSearchBdy.h"

using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HRepSearchBdy::HRepSearchBdy()
// Purpose:    Implementation of HRepSearchBdy::HRepSearchBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepSearchBdy::HRepSearchBdy()
{
      pOutStoreCtrl  = new HOutStoreCtrl(m_con.get_con());
      pRepertoryCtrl = new HRepertoryCtrl(m_con.get_con());
      pRepTotalCtrl = new HRepToTalCtrl(m_con.get_con());
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepSearchBdy::~HRepSearchBdy()
// Purpose:    Implementation of HRepSearchBdy::~HRepSearchBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepSearchBdy::~HRepSearchBdy()
{
   // TODO : 
   if (  pOutStoreCtrl ){
         delete pOutStoreCtrl;
         pOutStoreCtrl = NULL;
   }
   if ( pRepertoryCtrl){
         delete pRepertoryCtrl;
         pRepertoryCtrl = NULL;
   }
   
   if ( pRepTotalCtrl ){
        delete pRepTotalCtrl;
        pRepTotalCtrl = NULL;
   }
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepSearchBdy::RestRepSearch()
// Purpose:    Implementation of HRepSearchBdy::RestRepSearch()
// Return:     HRepTotalVec
////////////////////////////////////////////////////////////////////////

HRepTotalVec HRepSearchBdy::RestRepSearch(void)
{
   // TODO : 返回所有剩余库存
	return pRepTotalCtrl->getAllRepTotal();
   
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepSearchBdy::InRepSearch(string startDate, string endDate)
// Purpose:    Implementation of HRepSearchBdy::InRepSearch()
// Parameters:
// - startDate
// - endDate
// Return:     HRepertoryVec
////////////////////////////////////////////////////////////////////////

HRepertoryVec HRepSearchBdy::InRepSearch(string startDate, string endDate)
{
   // TODO : implement
	return pRepertoryCtrl->getAllRepertory(startDate,endDate);
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepSearchBdy::OutRepSearch(int startDate, int endDate)
// Purpose:    Implementation of HRepSearchBdy::OutRepSearch()
// Parameters:
// - startDate
// - endDate
// Return:     HOutStoreVec
////////////////////////////////////////////////////////////////////////

HOutStoreVec HRepSearchBdy::OutRepSearch(string startDate, string endDate)
{
   // TODO : implement
	return pOutStoreCtrl->getAllOutStore(startDate,endDate);
}