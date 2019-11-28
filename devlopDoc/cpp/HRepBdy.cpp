/***********************************************************************
 * Module:  HRepBdy.cpp
 * Author:  babala
 * Modified: 2005年5月6日 22:23:12
 * Purpose: Implementation of the class HRepBdy
 ***********************************************************************/

#include "HRepBdy.h"

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::HRepBdy(mysqlpp::Connection* pCon)
// Purpose:    Implementation of HRepBdy::HRepBdy()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HRepBdy::HRepBdy(mysqlpp::Connection* pCon)
{
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::~HRepBdy()
// Purpose:    Implementation of HRepBdy::~HRepBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepBdy::~HRepBdy()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::addRep(int foodId)
// Purpose:    Implementation of HRepBdy::addRep()
// Parameters:
// - foodId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepBdy::addRep(int foodId)
{
   // TODO : implement
   //取到菜单信息
   HMenuInfoCtrl menuInfoCtrl(_pCon);
   HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(foodId);
    //获得账号
   hotelMIS::HRepastCtrl repastCtrl(_pCon);
   string accountId = repastCtrl.getAccountId(table_id,room_id);
    if ( accountId.empty() ){ //没有账号,则生成
               accountId = createAccount();
     }
     HRepDetails repDetails;
     repDetails.account_id = accountId;
     repDetails.food_id = menuInfo.food_id;
     repDetails.food_name = menuInfo.food_name;
     repDetails.food_price = menuInfo.food_price;
     repDetails.ck_name = menuInfo.ck_name;
     
     HRepDetailsCtrl repDetailsCtrl(_pCon);
     repDetailsCtrl.insert(repDetails);
     
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::delRep(string accountId, int foodId, int foodNum)
// Purpose:    Implementation of HRepBdy::delRep()
// Parameters:
// - accountId
// - foodId
// - foodNum
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepBdy::delRep(string accountId, int foodId, int foodNum)
{
   // TODO : 
   //减少food_id = foodId 数量为 foodNum个记录
   //如果 food_id 的记录数为 1 则删除 
   HRepDetailsCtrl repDetailsCtrl(_pCon);
   if (  repDetailsCtrl.getFoodNum(accountld, foodId) <= foodNum ){
         repDetailsCtrl.Delete(accountId,foodId);
   }else{
         repDetailsCtrl.update(accountId,foodId,foodNum);
   }
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::createAccount()
// Purpose:    Implementation of HRepBdy::createAccount()
// Return:     string
////////////////////////////////////////////////////////////////////////

string HRepBdy::createAccount(void)
{
   // TODO : 生成账号
   HAccountCtrl accountCtrl(_pCon);
   int n = accountCtrl.getNowCnt();
   ++n;
   	/*char tmpbuf[128];
	_tzset();
	_strdate( tmpbuf );
    */
   SYSTEMTIME st;
   ::GetSystemTime(&st);
   CString accountId,date,time;
   date.Format("%d%d%d%d",st.wyear,st..wmonth,st.wday,n);
   time.Format("%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
   
   HRepastCtrl repastCtrl(_pCon);
   HRepast repast;
   repast.account_id = accountId;
   repast.table_id = table_id;
   repast.room_id = room_id;
   repast.cust_date = date.GetBuffer();
   repast.cust_time =  time.GetBuffer();
   repast.re_state = 1; //就餐
   repastCtrl.insert(repast);
   
   HAccountCtrl accountCtrl(_pCon);
   HAccount account;
   account.account_id = accountId;
   account.room_id = room_id;
   account.table_id = table_id;
   account.cust_date = date.GetBuffer();
   account.cust_time = time.GetBuffer();
   account.acc_status = 0; //未结账
   account.ad_name = HAdminBdy.log_name;
   accountCtrl.insert(account);
   
   return accountId.GetBuffer();
   
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::checkOut(HAccount& account)
// Purpose:    Implementation of HRepBdy::checkOut()
// Parameters:
// - account
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepBdy::checkOut(HAccount& account)
{
   // TODO : 结账
   //1) 更新总账
   HAccountCtrl accountCtrl(_pCon);
   accountCtrl.update(account);
   //2) 删除就餐表及其详细表
   HRepastCtrl repastCtrl(_pCon);
   repastCtrl.Delete(account.account_id);
   
   HRepDetailsCtrl repDetailsCtrl(_pCon);
   repDetailsCtrl.Delete(account.account_id);
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepBdy::cancel(string accountId)
// Purpose:    Implementation of HRepBdy::cancel()
// Parameters:
// - accountId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepBdy::cancel(string accountId)
{
   // TODO : 取消
   //1) 删除 t_Repast;
   HRepastCtrl repastCtrl(_pCon);
   repastCtrl.Delete(accountId);
   //2) 删除 t_RepDetailsCtrl
   HRepDetailsCtrl repDetailsCtrl(_pCon);
   repDetailsCtrl.Delete(accountId);
   //3) 设置 t_account的标志为取消
   HAccountCtrl accountCtrl(_pCon);
   accountCtrl.cancel(accountId);
}