/***********************************************************************
 * Module:  HDestineCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ12ÈÕ 18:11:35
 * Purpose: Declaration of the class HDestineCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HDestineCtrl_h)
#define __hotelMIS_HDestineCtrl_h

#include <HDestine.h>

class HDestineCtrl
{
public:
   HDestineCtrl(mysqlpp::Connection* pCon);
   ~HDestineCtrl();
   void insert(HDestine& destine);
   void Delete(void);
   void update(void);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif