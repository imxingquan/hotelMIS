/***********************************************************************
 * Module:  HPayBdy.cpp
 * Author:  babala
 * Modified: 2005年5月14日 11:35:48
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
   yscost = t.first; //打折菜价总和
   yscost2 = t.second; //不打折菜价总和
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
   // TODO : 计算并返回找余
   //找余账款 = 实际收款-(应收账款*折扣比率)-摸零账款
   zhekou = zk;
   erase_zero = ml;
   float rest = 0.0f;
	this->sj = sj;
   if ( zhekou >0 ){ //有折扣情况
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
		//yscost2 不打折菜总价
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
   if ( zhekou >0 ){ //有折扣情况
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


//四舍五入
float HPayBdy::calc2(float ml, float zk, float sj,float zfprice,bool bdaijin,float daijin)
{
	zhekou = zk;
	erase_zero = ml;
	this->daijin = daijin;
	float rest = 0.0f;
	this->sj = sj;
	if ( zhekou >0 ){ //有折扣情况
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

void HPayBdy::jz(int reckoning,int paystatus,float zfprice,string bz,int sswr)
{
   // TODO : 结账
   //1) 将计算结果写入t_account表中,并输入结账日期及时间更改状态为 以结账
   //2) 将菜谱详细资料导入到 t_accountDetails中
   //3) 删除t_repast及t_repastDetails表中的数据
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
   account.yscost = yscost+ yscost2; //应收
   account.erase_zero = erase_zero;
   account.zhekou = zhekou;
   account.sscost = sscost;	//实际应收
   account.acc_status = HAccount::havedAcc; //已经结账
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   account.daijin = daijin;
   account.sj = sj; //现金支付
   account.zy = zy; //找余
   account.paystatus = paystatus; //付款方式
   account.bz = bz;
   account.zfprice = zfprice;
   account.sswr = sswr;
   accountCtrl->update(account);
   //2)将菜谱详细资料导入到 t_accountDetails中
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)删除
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);
}

void HPayBdy::gz(int reckoning,string bz,int sswr)
{
   // TODO : 结账
   //1) 将计算结果写入t_account表中,并输入结账日期及时间更改状态为 以结账
   //2) 将菜谱详细资料导入到 t_accountDetails中
   //3) 删除t_repast及t_repastDetails表中的数据
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
   account.acc_status = HAccount::gzAcc; //挂账
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   account.daijin = daijin;
   account.sj = sj; //实际收款
   account.zy = zy; //找余
   account.bz = bz;
   account.sswr = sswr;
   //account.arid = arid;
   accountCtrl->update(account);
   //2)将菜谱详细资料导入到 t_accountDetails中
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)删除
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);

  

}


//退单操作
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
   account.acc_status = HAccount::cancelAcc; //退单
   account.reckoning = reckoning;
   account.ad_name = HAdminBdy::_log_name;
   account.daijin = daijin;
   account.sj = sj; //实际收款
   account.zy = zy; //找余
   account.bz = bz;

   //account.paystatus = paystatus; //付款方式
   accountCtrl->update(account);
   //2)将菜谱详细资料导入到 t_accountDetails中
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)删除
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);
}

//会员卡结账
void HPayBdy::memberJz(int paystatus,float zfprice , string bh)
{
	// 从会员卡上减去储值金额
	if ( paystatus == HAccount::JSFS::mcard){
		accountCtrl->memberJz(accountId,zfprice,bh);
	}
}