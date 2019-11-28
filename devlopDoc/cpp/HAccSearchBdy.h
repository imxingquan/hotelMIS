/***********************************************************************
 * Module:  HAccSearchBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ29ÈÕ 12:47:22
 * Purpose: Declaration of the class HAccSearchBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HAccSearchBdy_h)
#define __hotelMIS_HAccSearchBdy_h

#include <HAccount.h>

class HAccSearchBdy
{
public:
   HAccSearchBdy();
   ~HAccSearchBdy();
   HAccountVec search(string sDate, string eDate, int accStatus);
   HAccount search(string accid);
   HAccDetailsVec searchDetails(string accid);

protected:
private:
   hotelMIS::HAccountCtrl* pAccCtrl;
   hotelMIS::HAccDetailsCtrl* pAccDetailsCtrl;
   hotelMIS::KDBCon m_con;


};

#endif