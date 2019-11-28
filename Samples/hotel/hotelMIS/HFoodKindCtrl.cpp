/***********************************************************************
 * Module:  HFoodKindCtrl.cpp
 * Author:  babala
 * Modified: 2005��4��25�� 1:53:51
 * Purpose: Implementation of the class HFoodKindCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HFoodKindCtrl.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::HFoodKindCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HFoodKindCtrl::HFoodKindCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HFoodKindCtrl::HFoodKindCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::~HFoodKindCtrl()
// Purpose:    Implementation of HFoodKindCtrl::~HFoodKindCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HFoodKindCtrl::~HFoodKindCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::insert(string name, int flag, int ts)
// Purpose:    Implementation of HFoodKindCtrl::insert()
// Parameters:
// - name
// - flag
// - ts
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKindCtrl::insert(string name, int flag, int ts,int zk,int zdyprice)
{
   // TODO : ������
   try{
		

         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_foodKind ( kind_name,kind_flag,kind_ts,kind_zk,zdy_price) VALUES ('"
					 << name << "',"
                     << flag << ","
					 << ts <<","
                     << zk <<","
					 << zdyprice << ")";
         query.execute();
   }mycatch();
}


////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::update(HFoodKind& foodKind)
// Purpose:    Implementation of HFoodKindCtrl::update()
// Parameters:
// - foodKind
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKindCtrl::update(HFoodKind& foodKind)
{
   // TODO : �޸�
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_foodKind SET kind_name ='"
                     << foodKind.getKind_name() << "',kind_flag="
                     << foodKind.getKind_flag() << ",kind_ts = "
                     << foodKind.getKind_ts()<<",kind_zk= "
					 << foodKind.getKind_zk()<<",zdy_price= "
					 << foodKind.getZdy_price()
                     << " WHERE kind_id = " << foodKind.getKind_id();
          query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::Delete(int kindId)
// Purpose:    Implementation of HFoodKindCtrl::Delete()
// Parameters:
// - kindId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HFoodKindCtrl::Delete(int kindId)
{
   // TODO : ɾ����֮������Ĳ���
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_foodKind WHERE kind_id = " 
                     << kindId;
         query.execute();
		/* 
			���δ˴���. Ӧ����ɾ�������Ƿ��ڱ�ʹ��.
			query << "DELETE FROM t_menuInfo WHERE kind_id = "
					<< kindId;
		 query.execute();*/
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getKind(int kindId)
// Purpose:    Implementation of HFoodKindCtrl::getKind()
// Parameters:
// - kindId
// Return:     HFoodKind
////////////////////////////////////////////////////////////////////////

HFoodKind HFoodKindCtrl::getKind(int kindId)
{
   // TODO : ���һ�����
   HFoodKind foodKind;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind WHERE kind_id = " << kindId;
         mysqlpp::Result res = query.store();
         if ( ! res.empty() ){
            mysqlpp::Row row;
            mysqlpp::Result::iterator it = res.begin();
            row = *it;
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
			int kind_zk = row.lookup_by_name("kind_zk");
			int zdy_price= row.lookup_by_name("zdy_price");
            foodKind.setKind_id(kindId);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
			foodKind.setKind_zk(kind_zk);
			foodKind.setZdy_price(zdy_price);
         }
   }mycatch();
   return foodKind;
}


////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getAllKind()
// Purpose:    Implementation of HFoodKindCtrl::getAllKind()
// Return:     vector<HFoodKind>
////////////////////////////////////////////////////////////////////////

vector<HFoodKind> HFoodKindCtrl::getAllKind(void)
{
   // TODO : implement
    vector<HFoodKind> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind ORDER BY kind_id" ;
         mysqlpp::Result res = query.store();
         HFoodKind foodKind;
         mysqlpp::Row row;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
            row = *it;
			int kind_id = row.lookup_by_name("kind_id");
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
			int kind_zk = row.lookup_by_name("kind_zk");
			int zdy_price= row.lookup_by_name("zdy_price");
            foodKind.setKind_id(kind_id);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
			foodKind.setKind_zk(kind_zk);
			foodKind.setZdy_price(zdy_price);
            vec.push_back(foodKind);
         }
   }mycatch();
   return vec;
}

////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getAllKindExceptTs()
// Purpose:    Implementation of HFoodKindCtrl::getAllKindExceptTs()
// Return:     vector<HFoodKind>
////////////////////////////////////////////////////////////////////////

vector<HFoodKind> HFoodKindCtrl::getAllKindExceptTs(void)
{
   // TODO : implement
    vector<HFoodKind> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind WHERE kind_ts != 1 ORDER BY kind_id" ;
         mysqlpp::Result res = query.store();
         HFoodKind foodKind;
         mysqlpp::Row row;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
            row = *it;
			int kind_id = row.lookup_by_name("kind_id");
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
			int kind_zk = row.lookup_by_name("kind_zk");
			int zdy_price= row.lookup_by_name("zdy_price");
            foodKind.setKind_id(kind_id);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
			foodKind.setKind_zk(kind_zk);
			foodKind.setZdy_price(zdy_price);
            vec.push_back(foodKind);
         }
   }mycatch();
   return vec;
}
////////////////////////////////////////////////////////////////////////
// Name:       HFoodKindCtrl::getTsKind()
// Purpose:    Implementation of HFoodKindCtrl::getTsKind()
// Return:     vector<HFoodKind>
////////////////////////////////////////////////////////////////////////

vector<HFoodKind> HFoodKindCtrl::getTsKind(void)
{
   // TODO : implement
    vector<HFoodKind> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_foodKind WHERE kind_ts != 0" ;
         mysqlpp::Result res = query.store();
         HFoodKind foodKind;
         mysqlpp::Row row;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
            row = *it;
			int kind_id = row.lookup_by_name("kind_id");
            string kind_name = row.lookup_by_name("kind_name");
            int kind_flag = row.lookup_by_name("kind_flag");
            int kind_ts = row.lookup_by_name("kind_ts");
			int kind_zk = row.lookup_by_name("kind_zk");
            foodKind.setKind_id(kind_id);
            foodKind.setKind_name(kind_name);
            foodKind.setKind_flag(kind_flag);
            foodKind.setKind_ts(kind_ts);
			foodKind.setKind_zk(kind_zk);
            vec.push_back(foodKind);
         }
   }mycatch();
   return vec;
}

void HFoodKindCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_foodKind";
		query.execute();
	}mycatch();
}

//------------------------------------------------------------ -------------------------------------------
//
// �ж��Ƿ��ڲ�������ʾ
//
bool HFoodKindCtrl::isHideKind(int kindId)
{
	if ( kindId < 0 && kindId !=  hotelMIS::HFoodKind::SYS_MENU::TC ) //�ǿ���Ʒ,����ʾ
		return true;
	return false;
}

//----------------------------------------------------------------------------------------------------------
// �жϴ����Ƿ���ϵͳ������
//
bool HFoodKindCtrl::isInnerKind(int kindId)
{
	/*try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_foodKind WHERE kind_name='����Ʒ' AND kind_id ="<<kindId;
		mysqlpp::Result res = query.store();
		if ( !res.empty() )
			return true;
	}mycatch();
	return false;*/
	// С��  0 �Ķ�Ϊ ϵͳ����
	if ( kindId == hotelMIS::HFoodKind::SYS_MENU::TC || kindId== hotelMIS::HFoodKind::SYS_MENU::ZDY){
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------------
// �жϴ�������Ƿ��в�
bool HFoodKindCtrl::haveChild(int kindId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT kind_id FROM t_menuInfo WHERE kind_id ="<<kindId;
		mysqlpp::Result res = query.store();
		if ( !res.empty() )
			return true;
	}mycatch();
	return false;
}

//�Ƿ����Զ���۸�
bool HFoodKindCtrl::isZdyPrice(int kindId)
{
	try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT zdy_price FROM t_foodKind WHERE kind_id = " << kindId;
         mysqlpp::Result res = query.store();
         if ( ! res.empty() ){
            mysqlpp::Row row;
            mysqlpp::Result::iterator it = res.begin();
            row = *it;
          
			int zdy_price= row.lookup_by_name("zdy_price");
            if ( zdy_price == 1)
				return true;
         }
   }mycatch();
   return false;
}