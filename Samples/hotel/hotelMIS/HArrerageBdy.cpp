#include "stdAfx.h"

#include <HArrerageBdy.h>
#include <HRepastCtrl.h>
#include <HRepDetailsCtrl.h>
#include <HAccountCtrl.H>
#include <HAdminBdy.h>
using namespace hotelMIS;

HArrerageBdy::HArrerageBdy()
{
	pArrCtrl = NULL;
	pArrZHCtrl = NULL;
	pAccountCtrl = NULL;
	pArrCtrl = new HArrerageCtrl(m_con.get_con());
	pArrZHCtrl = new HArrerageZHCtrl(m_con.get_con());
	pAccountCtrl = new HAccountCtrl(m_con.get_con());
}

HArrerageBdy::~HArrerageBdy()
{
	if ( pArrCtrl ){
		delete pArrCtrl;
		pArrCtrl = NULL;
	}
	if ( pArrZHCtrl ){
		delete pArrZHCtrl;
		pArrZHCtrl = NULL;
	}
	if ( pAccountCtrl){
		delete pAccountCtrl;
		pAccountCtrl = NULL;
	}
}

int HArrerageBdy::Add(string gzName,string gzPhone,string gzDept,string gzMemo,int cw) //添加操作
{
	if ( pArrZHCtrl->isExitGZName(gzName)){
		return 1; //用户名已经存在
	}

	HArrerageZH zh;
	zh.guest_name = gzName;
	zh.guest_phone = gzPhone;
	zh.guest_dept = gzDept;
	zh.ar_memo = gzMemo;
	zh.cw = cw;
	pArrZHCtrl->insertZH(zh);
	return 0;
}
int HArrerageBdy::Delete(int arid) //删除操作
{
	if ( pArrCtrl->getByArId(arid).empty()){
		pArrZHCtrl->DeleteZH(arid);
		return 1;
	}
	return 0;
}
int HArrerageBdy::Modify(int arid,string gzName,string gzPhone,string gzDept,string gzMemo,int cw)//修改操作
{
	HArrerageZH zh;
	zh.arid = arid;
	zh.guest_name = gzName;
	zh.guest_phone = gzPhone;
	zh.guest_dept = gzDept;
	zh.ar_memo = gzMemo;
	zh.cw = cw;
	pArrZHCtrl->updateZH(zh);
	return 0;
}

hotelMIS::HArrerageZHVec HArrerageBdy::getAllZH()
{
	return pArrZHCtrl->getAll();
}

hotelMIS::HArrerageZH HArrerageBdy::getArrerageZH(int arid)
{
	return pArrZHCtrl->getArrerageZH(arid);
}


void HArrerageBdy::gz(int arid,string accoundId)
{

	HArrerage arr;
	arr.arid = arid;
	arr.account_id = accoundId;
	SYSTEMTIME st;
	::GetLocalTime(&st);
	CString date,time;
	date.Format("%d-%d-%d %d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	arr.ar_date = date.GetBuffer(1);
	pArrCtrl->DeleteByAccountId(accoundId);
	pArrCtrl->insert(arr);
	writeArrIdtoAccount(arid,accoundId);
}

void HArrerageBdy::tranToAcc(int tableId,int roomId,string accountId,float gz)
{
	HRepastCtrl *repastCtrl = new HRepastCtrl(m_con.get_con());
    HRepDetailsCtrl *repDetailsCtrl = new HRepDetailsCtrl(m_con.get_con());
    HAccountCtrl *accountCtrl = new HAccountCtrl(m_con.get_con());

	SYSTEMTIME st;
   ::GetLocalTime(&st);
   CString date,time;
   date.Format("%d-%d-%d",st.wYear,st.wMonth,st.wDay);
   time.Format("%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
   HAccount account = accountCtrl->getAccount(accountId);
   account.pay_date = date.GetBuffer();
   account.pay_time =  time.GetBuffer();
   account.table_id = tableId;
   account.room_id = roomId;
   account.subscription = 0.0f;
   account.yscost = gz;
   account.erase_zero = 0.0f;
   account.zhekou = 0.0f;
   account.sscost = 0.0f;
   account.acc_status = HAccount::gzAcc; //挂账
   account.reckoning = 0;
   account.ad_name = HAdminBdy::_log_name;
   accountCtrl->update(account);
   //2)将菜谱详细资料导入到 t_accountDetails中
   repDetailsCtrl->transferToAccDetails(accountId);
   //3)删除
   repastCtrl->Delete(accountId);
   repDetailsCtrl->Delete(accountId);

  delete repastCtrl ;
  delete repDetailsCtrl ;
  delete accountCtrl ;

}

hotelMIS::HArrerageVec HArrerageBdy::getArrerageByArId(int arid)
{
	return pArrCtrl->getByArId(arid);
}

float HArrerageBdy::getPriceByAccountId(string accountId)
{
	hotelMIS::HAccountCtrl accCtrl(m_con.get_con());
	return accCtrl.getPriceByAccountId(accountId);
}

void HArrerageBdy::writeArrIdtoAccount(int arid,string accountId)
{
	pArrCtrl->writeArrIdtoAccount(arid,accountId);
}