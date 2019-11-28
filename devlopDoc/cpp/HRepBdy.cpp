/***********************************************************************
 * Module:  HRepBdy.cpp
 * Author:  babala
 * Modified: 2005��5��6�� 22:23:12
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
   //ȡ���˵���Ϣ
   HMenuInfoCtrl menuInfoCtrl(_pCon);
   HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(foodId);
    //����˺�
   hotelMIS::HRepastCtrl repastCtrl(_pCon);
   string accountId = repastCtrl.getAccountId(table_id,room_id);
    if ( accountId.empty() ){ //û���˺�,������
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
   //����food_id = foodId ����Ϊ foodNum����¼
   //��� food_id �ļ�¼��Ϊ 1 ��ɾ�� 
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
   // TODO : �����˺�
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
   repast.re_state = 1; //�Ͳ�
   repastCtrl.insert(repast);
   
   HAccountCtrl accountCtrl(_pCon);
   HAccount account;
   account.account_id = accountId;
   account.room_id = room_id;
   account.table_id = table_id;
   account.cust_date = date.GetBuffer();
   account.cust_time = time.GetBuffer();
   account.acc_status = 0; //δ����
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
   // TODO : ����
   //1) ��������
   HAccountCtrl accountCtrl(_pCon);
   accountCtrl.update(account);
   //2) ɾ���Ͳͱ�����ϸ��
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
   // TODO : ȡ��
   //1) ɾ�� t_Repast;
   HRepastCtrl repastCtrl(_pCon);
   repastCtrl.Delete(accountId);
   //2) ɾ�� t_RepDetailsCtrl
   HRepDetailsCtrl repDetailsCtrl(_pCon);
   repDetailsCtrl.Delete(accountId);
   //3) ���� t_account�ı�־Ϊȡ��
   HAccountCtrl accountCtrl(_pCon);
   accountCtrl.cancel(accountId);
}