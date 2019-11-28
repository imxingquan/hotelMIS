/***********************************************************************
 * Module:  HDestineBdy.cpp
 * Author:  babala
 * Modified: 2005��5��12�� 17:44:33
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
// Comment:    �ͲͲ���
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
   // TODO : ����
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
   //��������µ��˵�����
   HAccountCtrl accountCtrl(_pCon);
   accountCtrl.updateSubscription(destine.account_id,subscription);
   //�ı䵱ǰ״̬Ϊ����״̬
   HRepastCtrl repastCtrl(_pCon);
   repastCtrl.chgState(HRepast::destineState);
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::chgRepast()
// Purpose:    Implementation of HDestineBdy::chgRepast()
// Comment:    �ɶ���״̬,ת�����Ͳ�״̬
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineBdy::chgRepast(void)
{
   // TODO : �ɶ���״̬ת��Ͳ�״̬
   try{
         HRepastCtrl repastCtr(_pCon);
         repastCtrl.chgState(table_id,room_id,HRepast::repastState);
         //ɾ�����ͱ��е�account_id��¼
         _ctrl->Delete(repastCtrl.getAccountId(table_id,room_id));
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineBdy::cancelDestine()
// Purpose:    Implementation of HDestineBdy::cancelDestine()
// Comment:    ȡ������
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineBdy::cancelDestine(void)
{
   // TODO : ȡ������
   try{
         HRepastCtrl repastCtrl(_pCon);
         string accountId = repastCtrl.getAccountId(table_id,room_id);
         _ctrl->Delete(accountId);
         //ȡ���˵���¼
         HAccountCtrl accountCtrl(_pCon);
         accountCtrl.cancel(accountId);
   }mycatch();
}