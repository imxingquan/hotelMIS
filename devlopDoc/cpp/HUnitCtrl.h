/***********************************************************************
 * Module:  HUnitCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 8:27:22
 * Purpose: Declaration of the class HUnitCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HUnitCtrl_h)
#define __hotelMIS_HUnitCtrl_h

class HUnitCtrl
{
public:
   HUnitCtrl(mysqlpp::Connection * pCon);
   ~HUnitCtrl();
   void insert(string unitName);
   void Delete(int unitId);
   vector<HUnitSet> getAllUnit(void);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif