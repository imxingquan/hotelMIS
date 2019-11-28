/***********************************************************************
 * Module:  HRepertoryCtrl.h
 * Author:  babala
 * Modified: 2005年5月1日 23:31:04
 * Purpose: Declaration of the class HRepertoryCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HRepertoryCtrl_h)
#define __hotelMIS_HRepertoryCtrl_h

#include <HRepertory.h>

class HRepertoryCtrl
{
public:
   HRepertoryCtrl(mysqlpp::Connection * pCon);
   ~HRepertoryCtrl();
   /* 入库 */
   void insert(HRepertory& rep);
   /* 入库调整 */
   void update(HRepertory& rep);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif