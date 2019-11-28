/***********************************************************************
 * Module:  HChgTableBdy.cpp
 * Author:  babala
 * Modified: 2005年5月16日 9:13:59
 * Purpose: Implementation of the class HChgTableBdy
 ***********************************************************************/
#include "stdAfx.h"
#include "HChgTableBdy.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::HChgTableBdy(int table_id, int room_id)
// Purpose:    Implementation of HChgTableBdy::HChgTableBdy()
// Parameters:
// - table_id
// - room_id
// Return:     
////////////////////////////////////////////////////////////////////////
HChgTableBdy::HChgTableBdy()
{
	pTableStatusCtrl = NULL;
	pRepastCtrl = NULL;
   pTableStatusCtrl = new  HTableStatusCtrl(m_con.get_con());
   pRepastCtrl = new HRepastCtrl(m_con.get_con());
}

HChgTableBdy::HChgTableBdy(int tableId, int roomId)
{
   // TODO : implement
   table_id = tableId;
   room_id = roomId;
 
   pTableStatusCtrl = NULL;
	pRepastCtrl = NULL;
  
	pTableStatusCtrl = new  HTableStatusCtrl(m_con.get_con());
   pRepastCtrl = new HRepastCtrl(m_con.get_con());
}

////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::~HChgTableBdy()
// Purpose:    Implementation of HChgTableBdy::~HChgTableBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HChgTableBdy::~HChgTableBdy()
{
   // TODO : 
	if ( pTableStatusCtrl ){
      delete pTableStatusCtrl;
	  pTableStatusCtrl = NULL;
	}
   if ( pRepastCtrl ){
      delete pRepastCtrl;
      pRepastCtrl = NULL;
   }
}

////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::getEmptyTable()
// Purpose:    Implementation of HChgTableBdy::getEmptyTable()
// Return:     TableCol
////////////////////////////////////////////////////////////////////////

TableCol HChgTableBdy::getEmptyTable(void)
{
   // TODO : 返回所有空桌
   return pTableStatusCtrl->getEmptyTable(room_id);
}

TableCol HChgTableBdy::getEmptyTable(int roomId)
{
   // TODO : 返回所有空桌
   return pTableStatusCtrl->getEmptyTable(roomId);
}

////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::chgTable(int destTableId)
// Purpose:    Implementation of HChgTableBdy::chgTable()
// Parameters:
// - destTableId
// Return:     int
////////////////////////////////////////////////////////////////////////


int HChgTableBdy::chgTable(int destTableId,int destRoomId)
{
   // TODO : 换桌
  return pRepastCtrl->chgTable(table_id,destTableId,room_id,destRoomId);
}