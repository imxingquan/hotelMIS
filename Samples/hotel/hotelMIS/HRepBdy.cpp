//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HRepBdy.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2005年5月6日 22:23:12
//			2006年6月10日 9:54:22
//-----------------------------------------------------------------------

#include "stdAfx.h"
#include "HRepBdy.h"
#include "HMenuInfoCtrl.h"
#include "HRepastCtrl.h"
#include "HRepDetails.h"
#include "HRepDetailsCtrl.h"
#include "HAccountCtrl.h"
#include "HAdminBdy.h"
#include "HBeforeRepCtrl.h"

#include "..\RepNumWarning.h"

using namespace hotelMIS;

//------------------------------------------------------------------------------------------------------------
HRepBdy::HRepBdy(int tableId,int roomId,mysqlpp::Connection* pCon)
{
	table_id = tableId;
	room_id = roomId;
   _pCon = pCon;
}


//-------------------------------------------------------------------------------------------------------------
HRepBdy::~HRepBdy()
{
   // TODO : implement
}

//-------------------------------------------------------------------------------------------------------------
void HRepBdy::addRep(int foodId,int foodNum,float dj,float zdyPrice)
//void HRepBdy::addRep(HMenuInfo &menuInfo,int roomId,int tableId)  //两种方法哪个更好理解?
{
	// TODO : 先检查库存在,增加菜谱
	
	//如果库存小于所需数量foodNum则返回库存在剩余数量!
	m_subcription = dj;
	
	/*int nVal = outRep(foodId,foodNum);
	if ( nVal == 0)
		return ;*/

	//取到菜单信息
	HMenuInfoCtrl menuInfoCtrl(_pCon);
	HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(foodId);
	HRepDetails repDetails;
	//HAccDetails accDetails;

	//获得账号
	hotelMIS::HRepastCtrl repastCtrl(_pCon);
	HRepDetailsCtrl repDetailsCtrl(_pCon);
	string accountId = repastCtrl.getAccountId(table_id,room_id);
	if ( accountId.empty() ){ //没有账号,则生成
		accountId = createAccount();
		repDetails.id = repDetailsCtrl.GetID();
		repDetails.account_id = accountId;
		repDetails.food_id = menuInfo.food_id;
		repDetails.food_name = menuInfo.food_name;
		if ( menuInfo.kind_id ==HFoodKind::SYS_MENU::ZDY || menuInfo.foodKind.zdy_price==1)
			repDetails.food_price =zdyPrice;
		else
			repDetails.food_price =  menuInfo.food_price;
		repDetails.ck_name = menuInfo.ck_name;
		repDetails.food_unit = menuInfo.food_unit;
		repDetails.food_num = foodNum;
		repDetails.food_cook = menuInfo.food_cook;
		repDetails.kind_zk = menuInfo.foodKind.getKind_zk();
		repDetails.kind_id = menuInfo.kind_id;
		repDetails.total_fl = menuInfo.total_fl;
		repDetailsCtrl.insert(repDetails);

		/*hotelMIS::HAccDetailsCtrl accDetails(_pCon);
		
		accDetails.insert(*/
	}
	/*else if(repDetailsCtrl.isExistFoodInAccId(accountId,foodId)){ //如果账号已经存在foodId的菜,只需要新数量
		repDetailsCtrl.update(accountId,foodId,foodNum);
	}
		去除这一部分,充许重复,以方便打印到后厨
	*/ 
	else{ //如果账号已经存在且没有foodId的菜,填加
		repDetails.id = repDetailsCtrl.GetID();
		repDetails.account_id = accountId;
		repDetails.food_id = menuInfo.food_id;
		repDetails.food_name = menuInfo.food_name;
		if ( menuInfo.kind_id ==HFoodKind::SYS_MENU::ZDY || menuInfo.foodKind.zdy_price==1)
			repDetails.food_price =zdyPrice;
		else
			repDetails.food_price =  menuInfo.food_price;
		repDetails.ck_name = menuInfo.ck_name;
		repDetails.food_unit = menuInfo.food_unit;
		repDetails.food_num = foodNum;
		repDetails.food_cook = menuInfo.food_cook;
		repDetails.kind_zk = menuInfo.foodKind.getKind_zk();
		repDetails.kind_id = menuInfo.kind_id;
		repDetails.total_fl = menuInfo.total_fl;
		repDetailsCtrl.insert(repDetails);
	}
}

////-------------------------------------------------------------------------------------------------------------
////此函数已过期
//void HRepBdy::delRep(string accountId, int foodId, int foodNum)
//{
//   // TODO : 
//   //减少food_id = foodId 数量为 foodNum个记录
//   //如果 food_id 的记录数为 1 则删除 
//   HRepDetailsCtrl repDetailsCtrl(_pCon); 
//   hotelMIS::HRepToTalCtrl repTotalCtrl(_pCon);
//   hotelMIS::HOutStoreBdy outStoreBdy(_pCon);
//   int restNum =  repDetailsCtrl.getFoodNum(accountId, foodId);
//
//   if ( restNum <= foodNum){
//	     outStoreBdy.revertRep(accountId,foodId,restNum);
//		 repDetailsCtrl.Delete(accountId,foodId);
//		 //如果已经没有accountId的账号了,就说明要撤消就餐
//		 if ( ! repDetailsCtrl.isExistAccountId(accountId) ){
//			//清除账号
//			 hotelMIS::HRepastCtrl repCtrl(_pCon);
//			 repCtrl.Delete(accountId);
//			 hotelMIS::HAccountCtrl accountCtrl(_pCon);
//			 accountCtrl.cancel(accountId);
//		 }
//		 		 
//   }else{
//         repDetailsCtrl.update(accountId,foodId,foodNum,false); //false为减少
//		 outStoreBdy.revertRep(accountId,foodId,foodNum);
//   }
//}

//----------------------------------------------------------------------------------------------------------------
//04-08-2006
//修改删除菜单的操作
//param id 标识
//foodNum 要减少的数量
void HRepBdy::delRep(int id,int foodNum,string accountId, int foodId) //
{
	HRepDetailsCtrl repDetailsCtrl(_pCon);
	repDetailsCtrl.Delete(id);	//删除

	//还原库存
	//revert(foodId,foodNum);

}

//退菜后不删除

//void HRepBdy::foodCancel(int id,int foodNum,string cancelmsg)
//{
//	
//}

//----------------------------------------------------------------------------------------------------------------
string HRepBdy::createAccount(void)
{
   // TODO : 生成账号
   HAccountCtrl accountCtrl(_pCon);
   /*int n = accountCtrl.getNowCnt();
   ++n;*/
   	/*char tmpbuf[128];
	_tzset();
	_strdate( tmpbuf );
    */
   SYSTEMTIME st;
   ::GetLocalTime(&st);
   CString accountId,date,time;
   time.Format("%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
   date.Format("%d-%d-%d %s",st.wYear,st.wMonth,st.wDay,time);
   accountId.Format("%4d%.2d%.2d%.2d%.2d%.2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
   TRACE("accountId = %s",accountId);
   //ASSERT(!accountId.IsEmpty());
   
   HRepastCtrl repastCtrl(_pCon);
   HRepast repast;
   repast.account_id = accountId;
   repast.table_id = table_id;
   repast.room_id = room_id;
   repast.cust_date = date.GetBuffer();
   repast.cust_time =  time.GetBuffer();
   repast.re_state = HRepast::repastState; //就餐
   repastCtrl.insert(repast);
   
   //HAccountCtrl accountCtrl(_pCon);
   HAccount account;
   account.account_id = accountId;
   account.room_id = room_id;
   account.table_id = table_id;
   account.cust_date = date.GetBuffer();
   account.cust_time = time.GetBuffer();
   account.subscription = m_subcription;
   account.acc_status = HAccount::notAcc; //未结账
   account.ad_name = HAdminBdy::_log_name;
   accountCtrl.insert(account);
   
   return accountId.GetBuffer();
   
}

//----------------------------------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------------------------------
//已过期
void HRepBdy::cancel(string accountId)
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

//------------------------------------------------------------------------------------------------------------------------
int HRepBdy::outRep(int food_id,int food_num)
{
	HMenuInfoCtrl menuInfoCtrl(_pCon);
	HBeforeRepCtrl beforeRepCtrl(_pCon);

	HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(food_id);

	if ( menuInfo.bTaocan == true )
	{
		int rval = testTaoCan(food_id,food_num);
		if ( rval == 0){
			//减少套餐库存
			outTcREpNum(food_id,food_num);
			return 1;
		}
		else {
			CWinApp* pApp = AfxGetApp();
			int bWarning = pApp->GetProfileInt("Settings", "repNumWarning",1);
			if ( bWarning == 1)
			{
				CRepNumWarning dlg(rval,TRUE);
				int r = dlg.DoModal();
				if ( r== IDOK){
				// 减少套餐库存
				outTcREpNum(food_id,food_num);
				return 1;
				}
			}
			else
			{
				outTcREpNum(food_id,food_num);
				return 1;
			}

			return 0;
		}
	}else if ( menuInfo.repertory_flag == HMenuInfo::REP_CALC ){
		float rep_num = beforeRepCtrl.getCurRep(food_id);
		if ( food_num <= rep_num){
			//减少库存
			beforeRepCtrl.beforeOutRep(food_id,food_num);
			return 1;
		}
		else
		{
			CWinApp* pApp = AfxGetApp();
			int bWarning = pApp->GetProfileInt("Settings", "repNumWarning",1);
			if ( bWarning == 1)
			{
				CRepNumWarning dlg(food_id);
				int r = dlg.DoModal();
				if ( r== IDOK){
					// 减少套餐库存
					beforeRepCtrl.beforeOutRep(food_id,food_num);
				return 1;
				}
			}
			else
			{
				beforeRepCtrl.beforeOutRep(food_id,food_num);
				return 1;
			}
			return 0;
		}
	}
	return 1;
}

//---------------------------------------------------------------------------------------------------
int HRepBdy::testTaoCan(int food_id,int food_num)
{
		HMenuInfoCtrl menuInfoCtrl(_pCon);
		HBeforeRepCtrl beforeRepCtrl(_pCon);
		HTcMenuInfoVec tcVec= menuInfoCtrl.getTcMenuInfo(food_id);
		HTcMenuInfoVec::iterator it = tcVec.begin(); 
		for ( ; it != tcVec.end(); it++)
		{
			HMenuInfo menu = menuInfoCtrl.getMenuInfo(it->food_id);
			if ( menu.repertory_flag == HMenuInfo::REP_CALC)
			{
			int rep_num = beforeRepCtrl.getCurRep(it->food_id);
			if ( it->food_num > rep_num )
				return it->food_id;	//返回库存不够的 food_id;
			}
		}
	
	return 0;
}

//----------------------------------------------------------------------------------------------------
void HRepBdy::outTcREpNum(int food_id,int food_num)
{
	HMenuInfoCtrl menuInfoCtrl(_pCon);
	HBeforeRepCtrl repCtrl(_pCon);	
	HTcMenuInfoVec tcVec= menuInfoCtrl.getTcMenuInfo(food_id);
		HTcMenuInfoVec::iterator it = tcVec.begin(); 
		for ( ; it != tcVec.end(); it++)
		{
			HMenuInfo menu = menuInfoCtrl.getMenuInfo(it->food_id);
			if ( menu.repertory_flag == HMenuInfo::REP_CALC)
				repCtrl.beforeOutRep(it->food_id,it->food_num*food_num);
		}
}

//----------------------------------------------------------------------------------------------------
void HRepBdy::revert(int food_id,int food_num)
{
	HMenuInfoCtrl menuInfoCtrl(_pCon);
	HBeforeRepCtrl beforeRepCtrl(_pCon);

	HMenuInfo menuInfo = menuInfoCtrl.getMenuInfo(food_id);

	if ( menuInfo.bTaocan == true )
	{
		inTcRepNum(food_id,food_num);
	}
	else if ( menuInfo.repertory_flag == HMenuInfo::REP_CALC )
	{
		beforeRepCtrl.modifyBeforeRep(food_id,food_num);
	}
}

//--------------------------------------------------------------------------------------------------------
void HRepBdy::inTcRepNum(int food_id,int food_num)
{
	HMenuInfoCtrl menuInfoCtrl(_pCon);
	HBeforeRepCtrl repCtrl(_pCon);	
	HTcMenuInfoVec tcVec= menuInfoCtrl.getTcMenuInfo(food_id);
		HTcMenuInfoVec::iterator it = tcVec.begin(); 
		for ( ; it != tcVec.end(); it++)
		{
			HMenuInfo menu = menuInfoCtrl.getMenuInfo(it->food_id);
			if ( menu.repertory_flag == HMenuInfo::REP_CALC)
				repCtrl.modifyBeforeRep(it->food_id,it->food_num*food_num);
		}
}