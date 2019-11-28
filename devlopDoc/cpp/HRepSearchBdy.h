/***********************************************************************
 * Module:  HRepSearchBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ28ÈÕ 14:31:53
 * Purpose: Declaration of the class HRepSearchBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HRepSearchBdy_h)
#define __hotelMIS_HRepSearchBdy_h

class HRepSearchBdy
{
public:
   HRepSearchBdy();
   ~HRepSearchBdy();
   HRepTotalVec RestRepSearch(void);
   HRepertoryVec InRepSearch(string startDate, string endDate);
   HOutStoreVec OutRepSearch(int startDate, int endDate);

protected:
private:
   hotelMIS::HOutStoreCtrl* pOutStoreCtrl;
   hotelMIS::HRepertoryCtrl* pRepertoryCtrl;
   hotelMIS::HRepTotalCtrl* pRepTotalCtrl;
   hotelMIS::KDBCon m_con;


};

#endif