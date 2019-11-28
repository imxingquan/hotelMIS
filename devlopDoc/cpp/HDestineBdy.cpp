/***********************************************************************
 * Module:  HDestineBdy.cpp
 * Author:  babala
 * Modified: 2005年5月12日 17:44:33
 * Purpose: Implementation of the class HDestineBdy
 ***********************************************************************/

#include "HDestineBdy.h"

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::HDestineBdy(mysqlpp::Connection * pCon, int roomId, int tableId)
// Purpose:    Implementation of HDestineBdy::HDestineBdy()
// Parameters:
// - pCon
// - roomId
// - tableId
// Return:     
////////////////////////////////////////////////////////////////////////

HDestineBdy::HDestineBdy(mysqlpp::Connection * pCon, int roomId, int tableId)
{
      _ctrl = new HDestineCtrl(pCon);
      room_id = roomId;
      table_id = tableId;
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::~HDestineBdy()
// Purpose:    Implementation of HDestineBdy::~HDestineBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HDestineBdy::~HDestineBdy()
{
   // TODO : implement
   if ( _ctrl)
      delete _ctrl;
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::destine(string guest_name, string come_date, string come_time, int person_num, float subscription, string remark)
// Purpose:    Implementation of HDestineBdy::destine()
// Comment:    就餐操作
// Parameters:
// - guest_name
// - come_date
// - come_time
// - person_num
// - subscription
// - remark
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineBdy::destine(string guest_name, string come_date, string come_time, int person_num, float subscription, string remark)
{
   // TODO : 定餐
   HRepBdy repBdy(_pCon);
   repBdy.room_id = room_id;
   repBdy.table_id = table_id;
   HDestine destine;
   destine.account_id = repBdy.createAccount();
   destine.guest_name = guest_name;
   destine.come_date = come_date;
   destine.come_time = come_time;
   destine.person_num = person_num;
   destine.subscription = subscription;
   destine.remark = remark;
   _ctrl->insert(destine);
   //将订金更新到账单表中
   HAccountCtrl accountCtrl(_pCon);
   accountCtrl.updateSubscription(destine.account_id,subscription);
   //改变当前状态为定餐状态
   HRepastCtrl repastCtrl(_pCon);
   repastCtrl.chgState(HRepast::destineState);
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::chgRepast()
// Purpose:    Implementation of HDestineBdy::chgRepast()
// Comment:    由订餐状态,转换到就餐状态
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineBdy::chgRepast(void)
{
   // TODO : 由订餐状态转向就餐状态
   try{
         HRepastCtrl repastCtr(_pCon);
         repastCtrl.chgState(table_id,room_id,HRepast::repastState);
         //删除订餐表中的account_id记录
         _ctrl->Delete(repastCtrl.getAccountId(table_id,room_id));
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::cancelDestine()
// Purpose:    Implementation of HDestineBdy::cancelDestine()
// Comment:    取消定餐
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineBdy::cancelDestine(void)
{
   // TODO : 取消定餐
   try{
         HRepastCtrl repastCtrl(_pCon);
         string accountId = repastCtrl.getAccountId(table_id,room_id);
         _ctrl->Delete(accountId);
         //取消账单记录
         HAccountCtrl accountCtrl(_pCon);
         accountCtrl.cancel(accountId);
   }mycatch();
}