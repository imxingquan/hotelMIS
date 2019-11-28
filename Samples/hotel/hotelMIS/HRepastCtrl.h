/***********************************************************************
 * Module:  HRepastCtrl.h
 * Author:  babala
 * Modified: 2005��5��6�� 22:31:20
 * Purpose: Declaration of the class HRepastCtrl
 ***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/06/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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
   /* ��þͲ�״̬ */
   int getRepastState(int tableId, int roomId);
   string getAccountId(int tableId, int roomId);
   /* ����  */
   int chgTable(int srcTableId,int destTableId,int srcRoomId, int destRoomId);
   bool isEmptyTable(int tableId, int roomId);
   HRepast getRepast(string accountId);
   /*�ı����״̬*/
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