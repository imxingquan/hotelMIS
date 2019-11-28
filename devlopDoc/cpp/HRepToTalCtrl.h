/***********************************************************************
 * Module:  HRepToTalCtrl.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ4ÈÕ 3:45:29
 * Purpose: Declaration of the class HRepToTalCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HRepToTalCtrl_h)
#define __hotelMIS_HRepToTalCtrl_h

class HRepToTalCtrl
{
public:
   HRepToTalCtrl(mysqlpp::Connection * pCon);
   ~HRepToTalCtrl();
   void insert(int foodId, int totalNum);
   void Delete(int foodId);
   void addNum(int foodId, int repNum);
   void delNum(int foodId, int repNum);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif