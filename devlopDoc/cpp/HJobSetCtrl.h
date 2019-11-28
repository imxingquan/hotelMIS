/***********************************************************************
 * Module:  HJobSetCtrl.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 17:27:41
 * Purpose: Declaration of the class HJobSetCtrl
 ***********************************************************************/

#if !defined(__hotelMIS_HJobSetCtrl_h)
#define __hotelMIS_HJobSetCtrl_h

class HJobSetCtrl
{
public:
   HJobSetCtrl(mysqlpp::Connection * pCon);
   ~HJobSetCtrl();
   void insert(string jobName);
   void Delete(int jobId);
   vector<HJobset> getAllJob(void);

protected:
private:
   mysqlpp::Connection _pCon;


};

#endif