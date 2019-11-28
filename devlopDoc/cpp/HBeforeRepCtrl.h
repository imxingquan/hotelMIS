//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBeforeRepCtrl.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2006Äê6ÔÂ10ÈÕ 20:59:26
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HBeforeRepCtrl_h)
#define __hotelMIS_HBeforeRepCtrl_h

class HBeforeRepCtrl
{
public:
   int beforeOutRep(int food_id, int food_num);
   int modifyBeforeRep(void);

protected:
private:
   mysqlpp::Connection * _pCon;


};

#endif