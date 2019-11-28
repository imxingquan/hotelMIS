/***********************************************************************
 * Module:  HRepDetailsCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月6日 21:38:14
 * Purpose: Implementation of the class HRepDetailsCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HRepDetailsCtrl.h"
#include "HRepToTalCtrl.h"
#include "HOutStoreBdy.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::HRepDetailsCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HRepDetailsCtrl::HRepDetailsCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HRepDetailsCtrl::HRepDetailsCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::~HRepDetailsCtrl()
// Purpose:    Implementation of HRepDetailsCtrl::~HRepDetailsCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepDetailsCtrl::~HRepDetailsCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::insert(HRepDetails& repDetails)
// Purpose:    Implementation of HRepDetailsCtrl::insert()
// Parameters:
// - repDetails
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::insert(HRepDetails& repDetails)
{
   // TODO : 插入一个详细记录
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_repDetails ( id,account_id,food_id,food_name,food_num,food_price,food_unit,ck_name,food_cook,food_cancel_msg,kind_zk,kind_id,total_fl) VALUES("
					 <<repDetails.id<<",'"        
					 <<repDetails.account_id<<"',"
                     <<repDetails.food_id<<",'"
                     <<repDetails.food_name<<"',"
                     <<repDetails.food_num<<","
                     <<repDetails.food_price<<",'"
					 <<repDetails.food_unit<<"','"
                     <<repDetails.ck_name<<"',"
					 <<repDetails.food_cook<<",'"
					 <<repDetails.food_cancel_msg<<"',"
					 <<repDetails.kind_zk <<","
					 <<repDetails.kind_id<<","
					 <<repDetails.total_fl<<")";
          query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::Delete(string accountId, int foodId)
// Purpose:    Implementation of HRepDetailsCtrl::Delete()
// Parameters:
// - accountId
// - foodId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::Delete(string accountId, int foodId)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query <<"DELETE FROM t_repDetails WHERE account_id ='"<<accountId<<"' AND food_id = " << foodId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::Delete(string accountId)
// Purpose:    Implementation of HRepDetailsCtrl::Delete()
// Parameters:
// - accountId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::Delete(string accountId)
{
   // TODO : 
   try{
         mysqlpp::Query query = _pCon->query();
         query <<"DELETE FROM t_repDetails WHERE account_id ='"<<accountId <<"'";
         query.execute();
   }mycatch();
}


//根据 id 删除点单

void HRepDetailsCtrl::Delete(int id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"DELETE FROM t_repDetails WHERE id = "<<id;
		query.execute();
	}mycatch();
}

//根据id减少数量

void HRepDetailsCtrl::Delete(int id,int foodNum)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_repDetails SET food_num = food_num -"<<foodNum
			<<" WHERE id = " << id;
		query.execute();
	}mycatch();
}
////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::update(string accountId, int foodId, int foodNum)
// Purpose:    Implementation of HRepDetailsCtrl::update()
// Parameters:
// - accountId
// - foodId
// - foodNum
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepDetailsCtrl::update(string accountId, int foodId, int foodNum,bool bAdd)
{
    //减少库存是否不应该放到这里,这样会增加库的偶合性.
	// TODO : 返回 0为正常, 否则库存量不够,返回剩余库存量 
	//int restNum = 0;
   try{
	   //hotelMIS::HRepToTalCtrl  repTotalCtrl(_pCon);
         mysqlpp::Query query = _pCon->query();
		 if ( bAdd){
				query << "UPDATE t_repDetails SET food_num = food_num + "<<foodNum
						<<" WHERE account_id = '"<<accountId<<"' AND food_id = " << foodId;
				/*if ( repTotalCtrl.getNum(foodId) < foodNum )
					restNum = repTotalCtrl.getNum();
				else
					repTotalCtrl.delNum(foodId,foodNum);*/
		 }
		 else{
				query << "UPDATE t_repDetails SET food_num = food_num - "<<foodNum
						<<" WHERE account_id = '"<<accountId<<"' AND food_id = " << foodId;
				/*repTotalCtrl.addNum(foodId,foodNum);*/	
		 }
         query.execute();
   }mycatch();
  // return restNum;
}

void HRepDetailsCtrl::update(string accountId, float zk_num)
{
   
   try{
	   //hotelMIS::HRepToTalCtrl  repTotalCtrl(_pCon);
         mysqlpp::Query query = _pCon->query();
		 query << "UPDATE t_repDetails SET zk_num = "<<zk_num
						<<" WHERE account_id = '"<<accountId<<"' AND kind_zk != 1 ";
			
         query.execute();
   }mycatch();
  // return restNum;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::getFoodNum(string accountId, int foodId)
// Purpose:    Implementation of HRepDetailsCtrl::getFoodNum()
// Parameters:
// - accountId
// - foodId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepDetailsCtrl::getFoodNum(string accountId, int foodId) 
{
   // TODO : 
   int num = 0;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT food_num FROM t_RepDetails WHERE account_id = '"
                     << accountId << "' AND food_id = " << foodId;
          mysqlpp::Result res = query.store();
          if ( !res.empty() ){
              mysqlpp::Row row;
              mysqlpp::Result::iterator it = res.begin();
              row = *it;
              num = row.lookup_by_name("food_num");
          }
   }mycatch();
   return num;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::getAllDetails(string accountId)
// Purpose:    Implementation of HRepDetailsCtrl::getAllDetails()
// Parameters:
// - accountId
// Return:     vector<HRepDetails>
////////////////////////////////////////////////////////////////////////

vector<HRepDetails> HRepDetailsCtrl::getAllDetails(string accountId)
{
   // TODO : 返回所有账号是 accountId的记录
   vector<HRepDetails> repDetailsVec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_repDetails WHERE account_id = '"<< accountId<<"' order by id";
         mysqlpp::Result res = query.store();
         mysqlpp::Row row ;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               HRepDetails repDetails;
			  
               repDetails.account_id = accountId; 
			   repDetails.id = row.lookup_by_name("id");
               repDetails.food_id = row.lookup_by_name("food_id");
               repDetails.food_name = row.lookup_by_name("food_name");
               repDetails.food_num = row.lookup_by_name("food_num");
               repDetails.food_price = row.lookup_by_name("food_price");
               repDetails.ck_name = row.lookup_by_name("ck_name");
			   repDetails.food_unit = row.lookup_by_name("food_unit");
			   repDetails.food_cook = row.lookup_by_name("food_cook");
			   repDetails.food_cancel_msg = row.lookup_by_name("food_cancel_msg");
			   repDetails.food_status = row.lookup_by_name("food_status");
			   repDetails.kind_zk = row.lookup_by_name("kind_zk");
			   repDetails.zk_num = row.lookup_by_name("zk_num");
			   repDetails.kind_id = row.lookup_by_name("kind_id");
			   repDetails.total_fl = row.lookup_by_name("total_fl");
               repDetailsVec.push_back(repDetails);       
         }
   }mycatch();
   return repDetailsVec;
}

HRepDetails HRepDetailsCtrl::getRepDetails(string accountId,int foodId)
{
	 // TODO : 根据account,foodId取值
   HRepDetails repDetails;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_repDetails WHERE account_id = '"
                     << accountId <<"' AND food_id = " << foodId;
          mysqlpp::Result res = query.store();
          if ( ! res.empty() ){
                  mysqlpp::Row row;
                  mysqlpp::Result::iterator it = res.begin();
                  row = *it;
                  repDetails.account_id = accountId;
                  repDetails.food_id = foodId;
				  repDetails.id = row.lookup_by_name("id");
                  repDetails.food_name = row.lookup_by_name("food_name");
                  repDetails.food_price = row.lookup_by_name("food_price");
				  repDetails.food_unit = row.lookup_by_name("food_unit");
                  repDetails.ck_name = row.lookup_by_name("ck_name");
				  repDetails.food_cook = row.lookup_by_name("food_cook");
				  repDetails.food_num = row.lookup_by_name("food_num");
				  repDetails.food_cancel_msg = row.lookup_by_name("food_cancel_msg");
				  repDetails.food_status = row.lookup_by_name("food_status");
				  repDetails.kind_zk = row.lookup_by_name("kind_zk");
				  repDetails.total_fl = row.lookup_by_name("total_fl");
           }
   }mycatch();
   return repDetails;
}
////////////////////////////////////////////////////////////////////////
// Name:       HRepDetailsCtrl::getAllPrice(string accountId)
// Purpose:    Implementation of HRepDetailsCtrl::getAllPrice()
// Parameters:
// - accountId
// Return:     float
////////////////////////////////////////////////////////////////////////

HTotalPair HRepDetailsCtrl::getAllPrice(string accountId)
{
   // TODO : 获得账号的总价格 
   float total =0.0f,total2=0.0f;
   HTotalPair t;
    try{
         HRepDetailsCtrl repDetailsCtrl(_pCon);
         HRepDetailsVec vec = repDetailsCtrl.getAllDetails(accountId); //获得详细列表
         HRepDetailsVec::iterator it;
        
         for ( it = vec.begin(); it != vec.end(); it++)
		 {
			 if ( it->kind_zk == 1)
				 total2 += (it->food_num * it->food_price*it->zk_num); //不打折菜总价款
			 else
				 total += (it->food_num*it->food_price*it->zk_num);  //打折总价款
		 }
		 t = make_pair<float,float>(total,total2);
    }mycatch();
   return t;
}

bool HRepDetailsCtrl::isExistFoodInAccId(string accountId,int foodId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_RepDetails WHERE account_id ='"
			  << accountId <<"' AND food_id = "<< foodId;
		mysqlpp::Result res = query.store();
		if ( !res.empty() )
			return true;
	}mycatch();
	return false;
}

bool HRepDetailsCtrl::isExistAccountId(string accountId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT account_id FROM t_RepDetails WHERE account_id ='"
				<< accountId << "'";
		mysqlpp::Result res = query.store();
		if ( !res.empty() )
			return true;
	}mycatch();
	return false;
}

void HRepDetailsCtrl::transferToAccDetails(string accountId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "insert into t_accountDetails (account_id,kind_id,food_id,food_name,food_num,food_unit,food_price,ck_name,food_cancel_msg,zk_num,total_fl) \
				select account_id,t_repDetails.kind_id,t_repDetails.food_id,t_repdetails.food_name,t_repdetails.food_num,t_repdetails.food_unit,t_repdetails.food_price, \
				t_repdetails.ck_name,food_cancel_msg,t_repDetails.zk_num,t_repDetails.total_fl from t_repDetails  \
				 WHERE account_id ='"<< accountId << "' order by id asc";
		query.execute();
	}mycatch();
}


//分厨取菜 04/07/2006

vector<HRepDetails> HRepDetailsCtrl::getFengchu(string accountId,int foodCook)
{
	//面点  0  凉菜  1 热菜  2 采用常量表示更好
	vector<HRepDetails> repDetailsVec;
   try{
         mysqlpp::Query query = _pCon->query();
		 if ( foodCook == -1)
			query << "SELECT * FROM t_repDetails WHERE account_id = '"<< accountId<<"'";
		 else
			query << "SELECT * FROM t_repDetails WHERE account_id = '"<< accountId<<"' AND food_cook="<<foodCook;
         mysqlpp::Result res = query.store();
         mysqlpp::Row row ;
         mysqlpp::Result::iterator it;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               HRepDetails repDetails;
               repDetails.account_id = accountId;
			   repDetails.id = row.lookup_by_name("id");
               repDetails.food_id = row.lookup_by_name("food_id");
               repDetails.food_name = row.lookup_by_name("food_name");
               repDetails.food_num = row.lookup_by_name("food_num");
               repDetails.food_price = row.lookup_by_name("food_price");
               repDetails.ck_name = row.lookup_by_name("ck_name");
			   repDetails.food_unit = row.lookup_by_name("food_unit");
			   repDetails.food_cook = row.lookup_by_name("food_cook");
			   repDetails.food_status = row.lookup_by_name("food_status");
			   repDetails.kind_zk = row.lookup_by_name("kind_zk");
			   repDetails.total_fl = row.lookup_by_name("total_fl");
               repDetailsVec.push_back(repDetails);       
         }
   }mycatch();
   return repDetailsVec;
}

//返回id
int HRepDetailsCtrl::GetID()
{
	int id = 0;
	string sId;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT MAX(id) AS id FROM t_repDetails";
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			sId = row.lookup_by_name("id");
		}
	}mycatch();
	id = atoi(sId.c_str());
	return id+1;
}

//根据id集合取回菜谱
vector<HRepDetails> HRepDetailsCtrl::getDetailsByIdVec(vector<int> &vecId)
{
	vector<HRepDetails> repDetailsVec;
	try{
		vector<int>::iterator it;

		mysqlpp::Query query = _pCon->query();

		for ( it = vecId.begin(); it != vecId.end(); it++)
		{
			int id = *it;
			query << "SELECT * FROM t_repDetails WHERE id = " << id;
			mysqlpp::Result res = query.store();
			mysqlpp::Row row;
			mysqlpp::Result::iterator it2;

			for ( it2 = res.begin(); it2!= res.end(); it2++)
			{
				row = *it2;
				HRepDetails repDetails;
				repDetails.account_id = row.lookup_by_name("account_id");
				repDetails.id = row.lookup_by_name("id");
				repDetails.food_id = row.lookup_by_name("food_id");
				repDetails.food_name = row.lookup_by_name("food_name");
				repDetails.food_num = row.lookup_by_name("food_num");
				repDetails.food_price = row.lookup_by_name("food_price");
				repDetails.ck_name = row.lookup_by_name("ck_name");
				repDetails.food_unit = row.lookup_by_name("food_unit");
				repDetails.food_cook = row.lookup_by_name("food_cook");
				repDetails.food_status = row.lookup_by_name("food_status");
				repDetails.kind_zk = row.lookup_by_name("kind_zk");
				repDetails.total_fl = row.lookup_by_name("total_fl");
				repDetailsVec.push_back(repDetails);       
			}
			
		}
	}mycatch();
	return repDetailsVec;
}

//根据id取菜的详细资料
HRepDetails HRepDetailsCtrl::getDetailsById(int id)
{
	HRepDetails repDetails;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_repDetails WHERE id = " << id;
		mysqlpp::Result res =  query.store();
		mysqlpp::Row row ;
		mysqlpp::Result::iterator it;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			repDetails.id = id;
			repDetails.account_id = row.lookup_by_name("account_id");
			repDetails.food_id = row.lookup_by_name("food_id");
			repDetails.food_name = row.lookup_by_name("food_name");
			repDetails.food_num = row.lookup_by_name("food_num");
			repDetails.food_price = row.lookup_by_name("food_price");
			repDetails.ck_name = row.lookup_by_name("ck_name");
			repDetails.food_unit = row.lookup_by_name("food_unit");
			repDetails.food_cook = row.lookup_by_name("food_cook");
			repDetails.food_status = row.lookup_by_name("food_status");
			repDetails.kind_zk = row.lookup_by_name("kind_zk");
			repDetails.total_fl = row.lookup_by_name("kind_id");
			repDetails.total_fl = row.lookup_by_name("zk_num");
			repDetails.total_fl = row.lookup_by_name("total_fl");
		}
	}mycatch();
	return repDetails;
}

//退菜
void HRepDetailsCtrl::foodCancel(int id,int num,string msg)
{
	HRepDetails repDetails = getDetailsById(id);
	repDetails.food_cancel_msg = msg; //退菜原因
	repDetails.food_name +="(退)";
	repDetails.food_num = - num;
	repDetails.food_status = HRepDetails::FOOD_STATUS::FOOD_BACK;
	//repDetails.food_price = - repDetails.food_price;
	repDetails.id = GetID();
	
	insert(repDetails);

	//hotelMIS::HRepToTalCtrl repTotalCtrl(_pCon);
	//hotelMIS::HOutStoreBdy outStoreBdy(_pCon);
	//if ( repTotalCtrl.isExist(repDetails.food_id) ){ //在库存中存在才,增加库存量
	//	outStoreBdy.revertRep(repDetails.account_id,repDetails.food_id,num);
	//}
}

//获得退菜可用的数量
int HRepDetailsCtrl::getCancelNum(string accountId,int foodId)
{
	int num = 0;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT SUM(food_num) AS num FROM t_repDetails WHERE account_id='"
			  << accountId << "' AND food_id = "
			  << foodId;
		mysqlpp::Result res = query.store();
		if ( !res.empty())
		{
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			num = row.lookup_by_name("num");
		}
	}mycatch();
	return num;
}

//
void HRepDetailsCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_repDetails";
		query.execute();
	}mycatch();
}

//
// 顾客赠送
//
void HRepDetailsCtrl::foodAward(int id)
{
	HRepDetails repDetails = getDetailsById(id);
	repDetails.food_name +="(赠)";
	repDetails.food_price = 0.0f;
	repDetails.food_status = HRepDetails::FOOD_STATUS::FOOD_AWARD;
	update(repDetails);
}

void HRepDetailsCtrl::update(HRepDetails &hRepDetails)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_repDetails SET "
			<< "ck_name ='"<< hRepDetails.ck_name << "',"
			<< "food_cook='"<< hRepDetails.food_cook << "',"
			<< "food_id="<<hRepDetails.food_id <<","
			<< "food_name='"<< hRepDetails.food_name <<"',"
			<< "food_num=" << hRepDetails.food_num << ","
			<< "food_price=" << hRepDetails.food_price << ","
			<< "food_unit='"<< hRepDetails.food_unit <<"',"
			<< "account_id='"<< hRepDetails.account_id <<"',"
			<< "food_status=" << hRepDetails.food_status<<","
			<< "kind_zk="<<hRepDetails.kind_zk<<","
			<< "zk_num="<<hRepDetails.zk_num<<","
			<< "total_fl="<<hRepDetails.total_fl
			<< " WHERE id = " << hRepDetails.id;
		query.execute();

	}mycatch();
}

int HRepDetailsCtrl::getFoodStatus(int id)
{
	int retFoodStatus = 0;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT food_status FROM t_repDetails WHERE id = "<< id;
		mysqlpp::Result res = query.store();
		if ( !res.empty() ){
			mysqlpp::Row row= *res.begin();
			retFoodStatus = row.lookup_by_name("food_status");
		}
	}mycatch();
	return retFoodStatus;
}