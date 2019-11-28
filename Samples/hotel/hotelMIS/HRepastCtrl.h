/***********************************************************************
 * Module:  HRepastCtrl.h
 * Author:  babala
 * Modified: 2005年5月6日 22:31:20
 * Purpose: Declaration of the class HRepastCtrl
 ***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/06/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HRepastCtrl_h)
#define __hotelMIS_HRepastCtrl_h
#include "config.h"
#include <HRepast.h>
namespace hotelMIS{
class HRepastCtrl
{
public:
   HRepastCtrl(mysqlpp::Connection * pCon);
   ~HRepastCtrl();
   void insert(HRepast& rep);
   void Delete(string accountId);
   /* 获得就餐状态 */
   int getRepastState(int tableId, int roomId);
   string getAccountId(int tableId, int roomId);
   /* 返回  */
   int chgTable(int srcTableId,int destTableId,int srcRoomId, int destRoomId);
   bool isEmptyTable(int tableId, int roomId);
   HRepast getRepast(string accountId);
   /*改变餐桌状态*/
   void chgState(int tableId, int roomId, int state);
   void updateRepDateAndTime(string accountId,string date,string time);
   pair<int,int> getTableIdAndRoomId(string accountId);

   void DeleteAll();
protected:
private:
   mysqlpp::Connection * _pCon;


};
}
#endif