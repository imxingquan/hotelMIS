/***********************************************************************
 * Module:  HPayBdy.cpp
 * Author:  babala
 * Modified: 2005年5月14日 11:35:48
 * Purpose: Implementation of the class HPayBdy
 ***********************************************************************/

#include "HPayBdy.h"

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::HPayBdy(int tableId, int roomId, mysqlpp::Connection* pCon)
// Purpose:    Implementation of HPayBdy::HPayBdy()
// Parameters:
// - tableId
// - roomId
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HPayBdy::HPayBdy(int tableId, int roomId, mysqlpp::Connection* pCon)
{
   // TODO : implement
   table_id = tableId;
   room_id = roomId;
   repastCtrl = NULL;
   repDetailsCtrl = NULL;
   accountCtrl = NULL;
   repastCtrl = new HRepastCtrl(pCon);
   repDetailsCtrl = new HRepastDetailsCtrl(pCon);
   accountCtrl = new HAccountCtrl(pCon);
   accountId = repastCtrl->getAccountId(tableId,roomId);
   yscost = repDetailsCtrl->getAllPrice(accountId);
   subscription = accountCtrl.getSubscription(accountId);
}

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::~HPayBdy()
// Purpose:    Implementation of HPayBdy::~HPayBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HPayBdy::~HPayBdy()
{
   // TODO : implement
   if ( repastCtrl){
      delete repastCtrl;
      repastCtrl = NULL;
   }
   if ( repDetailsCtrl){
      delete repDetailsCtrl;
   repDetailsCtrl = NULL;
   }
   if ( accountCtrl ){
      delete accountCtrl;
      accountCtrl = NULL;
   }
}

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::getYsPrice()
// Purpose:    Implementation of HPayBdy::getYsPrice()
// Return:     float
////////////////////////////////////////////////////////////////////////

float HPayBdy::getYsPrice(void)
{
   // TODO : implementj
   return yscost;
}

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::calc(float ml, float zk, float sj)
// Purpose:    Implementation of HPayBdy::calc()
// Parameters:
// - ml
// - zk
// - sj
// Return:     float
////////////////////////////////////////////////////////////////////////

float HPayBdy::calc(float ml, float zk, float sj)
{
   // TODO : 计算并返回找余
   //找余账款 = 实际收款-(应收账款*折扣比率)-摸零账款
   zhekou = zk;
   erase_zero = ml;
   sscost = yscost*zhekou-erase_zero-subscription;
   float rest = sj - sscost;
   return rest;
}

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::getSsPrice()
// Purpose:    Implementation of HPayBdy::getSsPrice()
// Return:     float
////////////////////////////////////////////////////////////////////////

float HPayBdy::getSsPrice(void)
{
   // TODO : implement
   //实收账款 = 应收账款*折扣比率-摸零账款
   return sscost;
}

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::jz(int reckoning)
// Purpose:    Implementation of HPayBdy::jz()
// Parameters:
// - reckoning
// Return:     void
////////////////////////////////////////////////////////////////////////

void HPayBdy::jz(int reckoning)
{
   // TODO : 结账
   //1) 将计算结果写入t_account表中,并输入结账日期及时间
   //2) 删除t_repast及t_repastDetails表中的数据
   //1)
    SYSTEMTIME st;
   ::GetLocalTime(&st);
   CString accountId,date,time;
   date.Format("%d-%d-%d",st.wYear,st.wMonth,st.wDay);
   time.Format("%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
   HAccount account = accountCtrl->getAccount(accountId);
   account.pay_date = date.GetBuffer();
   account.pay_time =  time.GetBuffer();
   account.subscription = subscription;
   account.yscost = yscost;
   account.erase_zero = erase_zero;
   account.zhekou = zhekou;
   account.sscost = sscost;
   account.acc_status = HAccount::havedAcc;
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   accountCtrl->update(account);
   //2)
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);
}