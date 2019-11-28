/***********************************************************************
 * Module:  HOutStoreBdy.cpp
 * Author:  babala
 * Modified: 2005��5��11�� 2:53:44
 * Purpose: Implementation of the class HOutStoreBdy
 * Comment: ���������
 ***********************************************************************/
#include "stdAfx.h"
#include "KDBCon.h"
#include "HOutStoreBdy.h"
#include "HRepDetailsCtrl.h"
#include "HOutStore.h"
#include "HRepastCtrl.h"
#include "HAdminBdy.h"
#include "HOutStoreCtrl.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreBdy::HOutStoreBdy()
// Purpose:    Implementation of HOutStoreBdy::HOutStoreBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HOutStoreBdy::HOutStoreBdy(mysqlpp::Connection * pCon)
{
	//hotelMIS::KDBCon con;
	//_pCon = con.get_con();
	_pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreBdy::~HOutStoreBdy()
// Purpose:    Implementation of HOutStoreBdy::~HOutStoreBdy()
// Return:     
////////////////////////////////////////////////////////////////////////

HOutStoreBdy::~HOutStoreBdy()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreBdy::outStore(string accountId, int foodId, int foodNum)
// Purpose:    Implementation of HOutStoreBdy::outStore()
// Parameters:
// - accountId
// - foodId
// - foodNum
// Return:     int
////////////////////////////////////////////////////////////////////////

int HOutStoreBdy::outStore(string accountId, int foodId, int foodNum)
{
   // TODO : ����Զ�����
   /*
      1)����accountId��foodId��repDetialȡ��
          food_name,food_price,food_unit,cust_date
      2)����ȡ����ֵ���HOutStore������ out_flag = 0 //����
      3)����HOutStoreCtrl��insert����
   */
   int nReturnVal= 0;
   try{
         HRepDetailsCtrl repDetailsCtrl(_pCon);
         HRepDetails repDetails = repDetailsCtrl.getRepDetails(accountId,foodId);
		 HRepastCtrl repastCtrl(_pCon);
         HOutStore outStore;
         outStore.food_id = foodId;
         outStore.food_name = repDetails.food_name;
         outStore.out_num = foodNum;
         outStore.out_price = repDetails.food_price;
         outStore.out_unit = repDetails.food_unit;
		 outStore.out_date = repastCtrl.getRepast(accountId).cust_date;
         outStore.out_flag = 0;
		 outStore.ad_name = hotelMIS::HAdminBdy::_log_name;
		 hotelMIS::HOutStoreCtrl outStoreCtrl(_pCon);
		 nReturnVal = outStoreCtrl.insert(outStore,0);//0:�����ܵĿ����
   }mycatch();
   return nReturnVal;
}

////////////////////////////////////////////////////////////////////////
// Name:       HOutStoreBdy::revertRep(string accountId, int foodId, int foodNum)
// Purpose:    Implementation of HOutStoreBdy::revertRep()
// Parameters:
// - accountId
// - foodId
// - foodNum
// Return:     int
////////////////////////////////////////////////////////////////////////

int HOutStoreBdy::revertRep(string accountId, int foodId, int foodNum)
{
   // TODO : �������
   /*
       1)����accountId��foodId��repDetialȡ��
          food_name,food_price,food_unit,cust_date
      2)����ȡ����ֵ���HOutStore��,���� out_flag = 2
      3)����HOutStoreCtrl��insert����,
      ����� foodNum �Ѿ��Ǽ����Ĳ��ᳬ����Χ
   */
    int nReturnVal= -1;
   try{
         HRepDetailsCtrl repDetailsCtrl(_pCon);
         HRepDetails repDetails = repDetailsCtrl.getRepDetails(accountId,foodId);
         HOutStore outStore;
		 HRepastCtrl repastCtrl(_pCon);
         outStore.food_id = foodId;
         outStore.food_name = repDetails.food_name;
         outStore.out_num = foodNum;
         outStore.out_price = repDetails.food_price;
         outStore.out_unit = repDetails.food_unit;
         outStore.out_date = repastCtrl.getRepast(accountId).cust_date;
         outStore.out_flag = 2;
         outStore.ad_name = HAdminBdy::_log_name;
		 hotelMIS::HOutStoreCtrl outStoreCtrl(_pCon);
		nReturnVal= outStoreCtrl.insert(outStore,1);//1:�����ܵĿ����
   }mycatch();
   return nReturnVal;
}