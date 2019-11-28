/***********************************************************************
 * Module:  HPayBdy.cpp
 * Author:  babala
 * Modified: 2005��5��14�� 11:35:48
 * Purpose: Implementation of the class HPayBdy
 ***********************************************************************/
#include "stdAfx.h"
#include "HPayBdy.h"
#include "HAdminBdy.h"
#include "math.h"
using namespace hotelMIS;
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
   repDetailsCtrl = new HRepDetailsCtrl(pCon);
   accountCtrl = new HAccountCtrl(pCon);
   accountId = repastCtrl->getAccountId(tableId,roomId);
   //yscost = repDetailsCtrl->getAllPrice(accountId);
   HTotalPair t = repDetailsCtrl->getAllPrice(accountId);
   yscost = t.first; //���۲˼��ܺ�
   yscost2 = t.second; //�����۲˼��ܺ�
   subscription = accountCtrl->getSubscription(accountId);
   
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
   return yscost + yscost2;
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
   // TODO : ���㲢��������
   //�����˿� = ʵ���տ�-(Ӧ���˿�*�ۿ۱���)-�����˿�
   zhekou = zk;
   erase_zero = ml;
   float rest = 0.0f;
	this->sj = sj;
   if ( zhekou >0 ){ //���ۿ����
		  // 
	   //if ( subscription >= yscost){
		  // sscost = yscost*zhekou-erase_zero;
		  // sj = subscription;
	   //}
	   //else{
		  // sscost = yscost*zhekou-erase_zero;
	   //}
	   //
	   //rest = sj - sscost;
		//yscost2 �����۲��ܼ�
	   sscost = yscost*zhekou + yscost2 -erase_zero-subscription;
	   rest = sj  - sscost;

	    repDetailsCtrl->update(accountId,zhekou);
   }
   else{
	    
		/* if ( subscription >= yscost){
		   sscost = yscost-erase_zero;
		   sj = subscription;
	   }
	   else{
		   sscost = yscost-erase_zero;
	   }
	   
	   rest = sj - sscost;*/
	   sscost = yscost+ yscost2-erase_zero-subscription;
	   rest = sj - sscost;

	    repDetailsCtrl->update(accountId,1);
   }

zy = rest;
   return rest;
}




float HPayBdy::calc(float ml, float zk, float sj,float zfprice,bool bdaijin,float daijin)
{
   zhekou = zk;
   erase_zero = ml;
   this->daijin = daijin;
   float rest = 0.0f;
   this->sj = sj;
   if ( zhekou >0 ){ //���ۿ����
	   if ( bdaijin){
		   if ( (yscost * zhekou+ yscost2-erase_zero) <= daijin ){
				sscost = 0.0f;
				rest = 0.0f;
		   }else{
		 	sscost = yscost*zhekou+ yscost2-erase_zero-subscription-daijin;
			rest =sj+zfprice  - sscost;
		   }
				   
	   }else{
			sscost = yscost*zhekou+ yscost2-subscription-erase_zero;
			rest = sj+zfprice  - sscost;
	   }
	   
	   repDetailsCtrl->update(accountId,zhekou);
   }
   else{
	   if ( bdaijin){
		    if ( (yscost+ yscost2 -erase_zero) <= daijin ){
				sscost = 0.0f;
				rest = 0.0f;
		   }else{
		  	sscost = yscost+ yscost2-erase_zero -subscription- daijin;
			rest = sj+zfprice  - sscost;
		   }
		  
	   }else{
			sscost = yscost+ yscost2-subscription-erase_zero;
			rest =sj+zfprice  - sscost;
	   }
	   repDetailsCtrl->update(accountId,1);
   }
   zy = rest;
   return rest;
}

float HPayBdy::myRound(float x)
{
	if((int)x*10+5 > (int)(x*10))
		return floor(x);
	else
		return ceil(x);
}


//��������
float HPayBdy::calc2(float ml, float zk, float sj,float zfprice,bool bdaijin,float daijin)
{
	zhekou = zk;
	erase_zero = ml;
	this->daijin = daijin;
	float rest = 0.0f;
	this->sj = sj;
	if ( zhekou >0 ){ //���ۿ����
		if ( bdaijin)
		{
			if ( myRound(yscost * zhekou+ yscost2-erase_zero) <= daijin )
			{
				sscost = 0.0f;
				rest = 0.0f;
			}
			else
			{
				sscost = myRound(yscost*zhekou+ yscost2-erase_zero-subscription-daijin);
				rest = sj+zfprice  - sscost;
			}

		}
		else
		{
			sscost = myRound(yscost*zhekou+ yscost2-subscription-erase_zero);
			rest = sj+zfprice  - sscost;
		}

		repDetailsCtrl->update(accountId,zhekou);
	}
	else{
		if ( bdaijin)
		{
			if ( myRound(yscost+ yscost2 -erase_zero) <= daijin )
			{
				sscost = 0.0f;
				rest = 0.0f;
			}
			else
			{
				sscost = myRound(yscost+ yscost2-erase_zero -subscription- daijin);
				rest = sj+zfprice  - sscost;
			}

		}
		else
		{
			sscost = myRound(yscost+ yscost2-subscription-erase_zero);
			rest = sj+zfprice  - sscost;
		}
		repDetailsCtrl->update(accountId,1);
	}
	zy = rest;
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
   //ʵ���˿� = Ӧ���˿�*�ۿ۱���-�����˿�
   return sscost;
}

////////////////////////////////////////////////////////////////////////
// Name:       HPayBdy::jz(int reckoning)
// Purpose:    Implementation of HPayBdy::jz()
// Parameters:
// - reckoning
// Return:     void
////////////////////////////////////////////////////////////////////////

void HPayBdy::jz(int reckoning,int paystatus,float zfprice,string bz,int sswr)
{
   // TODO : ����
   //1) ��������д��t_account����,������������ڼ�ʱ�����״̬Ϊ �Խ���
   //2) ��������ϸ���ϵ��뵽 t_accountDetails��
   //3) ɾ��t_repast��t_repastDetails���е�����
   //1)
    SYSTEMTIME st;
   ::GetLocalTime(&st);
   CString date,time;
   date.Format("%4d-%.2d-%.2d %.2d:%.2d:%.2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
   time.Format("%.2d:%.2d:%.2d",st.wHour,st.wMinute,st.wSecond);
   HAccount account = accountCtrl->getAccount(accountId);
   account.pay_date = date.GetBuffer();
   account.pay_time =  time.GetBuffer();
   account.table_id = table_id;
   account.room_id = room_id;
   account.subscription = subscription;
   account.yscost = yscost+ yscost2; //Ӧ��
   account.erase_zero = erase_zero;
   account.zhekou = zhekou;
   account.sscost = sscost;	//ʵ��Ӧ��
   account.acc_status = HAccount::havedAcc; //�Ѿ�����
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   account.daijin = daijin;
   account.sj = sj; //�ֽ�֧��
   account.zy = zy; //����
   account.paystatus = paystatus; //���ʽ
   account.bz = bz;
   account.zfprice = zfprice;
   account.sswr = sswr;
   accountCtrl->update(account);
   //2)��������ϸ���ϵ��뵽 t_accountDetails��
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)ɾ��
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);
}

void HPayBdy::gz(int reckoning,string bz,int sswr)
{
   // TODO : ����
   //1) ��������д��t_account����,������������ڼ�ʱ�����״̬Ϊ �Խ���
   //2) ��������ϸ���ϵ��뵽 t_accountDetails��
   //3) ɾ��t_repast��t_repastDetails���е�����
   //1)
    SYSTEMTIME st;
   ::GetLocalTime(&st);
   CString date,time;
   date.Format("%4d-%.2d-%.2d %.2d:%.2d:%.2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
   time.Format("%.2d:%.2d:%.2d",st.wHour,st.wMinute,st.wSecond);
   HAccount account = accountCtrl->getAccount(accountId);
   account.pay_date = date.GetBuffer();
   account.pay_time =  time.GetBuffer();
   account.table_id = table_id;
   account.room_id = room_id;
   account.subscription = subscription;
   account.yscost = yscost+ yscost2;
   account.erase_zero = erase_zero;
   account.zhekou = zhekou;
   account.sscost = sscost;
   account.acc_status = HAccount::gzAcc; //����
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   account.daijin = daijin;
   account.sj = sj; //ʵ���տ�
   account.zy = zy; //����
   account.bz = bz;
   account.sswr = sswr;
   //account.arid = arid;
   accountCtrl->update(account);
   //2)��������ϸ���ϵ��뵽 t_accountDetails��
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)ɾ��
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);

  

}


//�˵�����
void HPayBdy::cancelMenu(int reckoning,string bz)
{
	 SYSTEMTIME st;
   ::GetLocalTime(&st);
   CString date,time;
   date.Format("%4d-%.2d-%.2d",st.wYear,st.wMonth,st.wDay);
   time.Format("%.2d:%.2d:%.2d",st.wHour,st.wMinute,st.wSecond);
   HAccount account = accountCtrl->getAccount(accountId);
   account.pay_date = date.GetBuffer();
   account.pay_time =  time.GetBuffer();
   account.table_id = table_id;
   account.room_id = room_id;
   account.subscription = subscription;
   account.yscost = yscost+ yscost2;
   account.erase_zero = erase_zero;
   account.zhekou = zhekou;
   account.sscost = sscost;
   account.acc_status = HAccount::cancelAcc; //�˵�
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   account.daijin = daijin;
   account.sj = sj; //ʵ���տ�
   account.zy = zy; //����
   account.bz = bz;

   //account.paystatus = paystatus; //���ʽ
   accountCtrl->update(account);
   //2)��������ϸ���ϵ��뵽 t_accountDetails��
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)ɾ��
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);
}

//��Ա������
void HPayBdy::memberJz(int paystatus,float zfprice , string bh)
{
	// �ӻ�Ա���ϼ�ȥ��ֵ���
	if ( paystatus == HAccount::JSFS::mcard){
		accountCtrl->memberJz(accountId,zfprice,bh);
	}
}