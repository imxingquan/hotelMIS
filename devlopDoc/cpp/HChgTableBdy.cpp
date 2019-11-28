/***********************************************************************
 * Module:  HChgTableBdy.cpp
 * Author:  babala
 * Modified: 2005年5月16日 9:13:59
 * Purpose: Implementation of the class HChgTableBdy
 ***********************************************************************/

#include "HChgTableBdy.h"

////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::HChgTableBdy(int table_id, int room_id)
// Purpose:    Implementation of HChgTableBdy::HChgTableBdy()
// Parameters:
// - table_id
// - room_id
// Return:     
////////////////////////////////////////////////////////////////////////

HChgTableBdy::HChgTableBdy(int table_id, int room_id)
{
   // TODO : implement
   table_id = tableId;
   room_id = roomId;
   pTableStatusCtrl = NULL;
   pTableStatusCtrl = new  HTableStatusCtrl(m_con.get_con());
}

////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::~HChgTableBdy()
// Purpose:    Implementation of HChgTableBdy::~HChgTableBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HChgTableBdy::~HChgTableBdy()
{
   // TODO : 
   if ( pTableStatusCtrl )
      delete pTableStatusCtrl;
}

////////////////////////////////////////////////////////////////////////
// Name:       HChgTableBdy::getEmptyTable()
// Purpose:    Implementation of HChgTableBdy::getEmptyTable()
// Return:     TableCol
////////////////////////////////////////////////////////////////////////

TableCol HChgTableBdy::getEmptyTable(void)
{
   // TODO : 返回所有空桌
   pTableStatusCtrl->getEmptyTable(table_id,room_id);
}