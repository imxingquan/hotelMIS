/***********************************************************************
* Module:  HChgTableBdy.h
* Author:  babala
* Modified: 2005��5��16�� 9:13:59
* Purpose: Declaration of the class HChgTableBdy
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/22/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HChgTableBdy_h)
#define __hotelMIS_HChgTableBdy_h
#include "KDBCon.h"
#include "HTableStatusCtrl.h"
#include "HRepastCtrl.h"

namespace hotelMIS{
	class HChgTableBdy
	{
	public:
		HChgTableBdy();
		HChgTableBdy(int tableId, int roomId);
		~HChgTableBdy();
		TableCol getEmptyTable(void);
		TableCol getEmptyTable(int roomId);
		int chgTable(int destTableId,int destRoomId);
	protected:
	private:
		int table_id;
		int room_id;
		hotelMIS::KDBCon m_con;
		hotelMIS::HTableStatusCtrl* pTableStatusCtrl;
		hotelMIS::HRepastCtrl* pRepastCtrl;
	};
}
#endif