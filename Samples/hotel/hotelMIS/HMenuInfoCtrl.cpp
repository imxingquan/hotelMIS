/***********************************************************************
 * Module:  HMenuInfoCtrl.cpp
 * Author:  babala
 * Modified: 2005年4月25日 2:29:41
 * Purpose: Implementation of the class HMenuInfoCtrl

	hostory:
		2006-6-5	邢泉	更正修改的时候进不了库存

		2006-6-9	邢泉	创建充一填充菜单信息的内部函数 _fill, _fill_vec
							将 HFoodKind 类组合到 HMmenuInfo中
 ***********************************************************************/
#include "stdAfx.h"
#include "HMenuInfoCtrl.h"
#include "KDBCon.h"
#include "HFoodKindCtrl.h"

#include "HBeforeRepCtrl.h"
#include "HBehindRepCtrl.h"
using namespace hotelMIS;

//----------------------------------------------------------------------------------------------------
HMenuInfoVec HMenuInfoCtrl::_menuInfoVec;

//---------------------------------------------------------------------------------------------------
HMenuInfoCtrl::HMenuInfoCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}


HMenuInfoCtrl::~HMenuInfoCtrl()
{
   // TODO : implement
}

//-------------------------------------------------------------------------------------------------------
// private 
void HMenuInfoCtrl::_fill(HMenuInfo &menuInfo,mysqlpp::Result &res)
{
	
		/* mysqlpp::Query query = _pCon->query();

		query << "SELECT * FROM t_menuInfo WHERE food_id = " << foodId ;
		mysqlpp::Result res = query.store();*/
		if ( ! res.empty() ){
			mysqlpp::Row row;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			menuInfo.food_id = row.lookup_by_name("food_id");
			 menuInfo.kind_id = row.lookup_by_name("kind_id");
			 menuInfo.food_name = row.lookup_by_name("food_name");
			 menuInfo.food_price = row.lookup_by_name("food_price");
			 menuInfo.food_num = row.lookup_by_name("food_num");
			 menuInfo.food_unit = row.lookup_by_name("food_unit");
			 
			 //return MENU_STATUS::REP_CALC or MENU_STATUS::REP_NOCALC
			 menuInfo.repertory_flag = row.lookup_by_name("repertory_flag");
			 
			 menuInfo.ck_name = row.lookup_by_name("ck_name");
			 menuInfo.food_cook = row.lookup_by_name("food_cook");
			 menuInfo.food_py = row.lookup_by_name("food_py");

			 // 设置当前商品是否为套餐
			 if ( menuInfo.kind_id == HMenuInfo::TC )
				menuInfo.bTaocan = true;
			 else
			    menuInfo.bTaocan = false;

			 menuInfo.total_fl = row.lookup_by_name("total_fl");

			 // get foodKind Info by menuInfo.kind_id
			 hotelMIS::HFoodKindCtrl foodKind(_pCon);
			 menuInfo.foodKind = foodKind.getKind(menuInfo.kind_id);
			
		}
	
}

//-------------------------------------------------------------------------------------------------------
// private
void HMenuInfoCtrl::_fill_vec(HMenuInfoVec &vec,mysqlpp::Result &res)
{

        /* mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo ";
         
		 mysqlpp::Result res = query.store();*/
		 mysqlpp::Result::iterator it ;
		 mysqlpp::Row row;
		 HMenuInfo menuInfo;
		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 menuInfo.food_id = row.lookup_by_name("food_id");
			 menuInfo.kind_id = row.lookup_by_name("kind_id");
			 menuInfo.food_name = row.lookup_by_name("food_name");
			 menuInfo.food_price = row.lookup_by_name("food_price");
			 menuInfo.food_num = row.lookup_by_name("food_num");
			 menuInfo.food_unit = row.lookup_by_name("food_unit");
			 
			 //return MENU_STATUS::REP_CALC or MENU_STATUS::REP_NOCALC
			 menuInfo.repertory_flag = row.lookup_by_name("repertory_flag");
			 
			 menuInfo.ck_name = row.lookup_by_name("ck_name");
			 menuInfo.food_cook = row.lookup_by_name("food_cook");
			 menuInfo.food_py = row.lookup_by_name("food_py");
			 menuInfo.total_fl = row.lookup_by_name("total_fl");
			 // 设置当前商品是否为套餐
			 if ( menuInfo.kind_id == HMenuInfo::TC )
				menuInfo.bTaocan = true;
			 else
				 menuInfo.bTaocan = false;

			 // get foodKind Info by menuInfo.kind_id
			 hotelMIS::HFoodKindCtrl foodKind(_pCon);
			 menuInfo.foodKind = foodKind.getKind(menuInfo.kind_id);
			 
			 vec.push_back(menuInfo);
		 }
	
}

//-------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::insert(HMenuInfo& menuInfo)
// Purpose:    Implementation of HMenuInfoCtrl::insert()
// Parameters:
// - menuInfo
// Return:     void
////////////////////////////////////////////////////////////////////////

void HMenuInfoCtrl::insert(HMenuInfo& menuInfo,bool sp)
{
   // TODO : 添加菜谱
   try{
         mysqlpp::Query query = _pCon->query();
		    
		 query << "INSERT INTO t_menuInfo (kind_id,food_name,food_price,food_num,food_unit,repertory_flag,ck_name,food_py,total_fl) VALUES("
                     << menuInfo.kind_id    << ",'"
                     << menuInfo.food_name  << "',"	
					 << menuInfo.food_price << ","
					 << menuInfo.food_num   << ",'"
					 << menuInfo.food_unit  << "',"
                     << menuInfo.repertory_flag <<",'"
                     << menuInfo.ck_name <<"','"
					 << menuInfo.food_py <<"',"
					 << menuInfo.total_fl<<")";
		
          query.execute();
		  
		  
		  ////库存标记为1,将 kind_id 写入
		  ////menuInfo.repertory_flag == 1
		  //if ( 1== menuInfo.repertory_flag  ){
			 // hotelMIS::HRepToTalCtrl repTotalCtrl(_pCon);
			 // TRACE("insertid=%d\n",_pCon->insert_id());
			 // repTotalCtrl.insert(_pCon->insert_id());
		  //}

		  //if ( HMenuInfo::REP_CALC == menuInfo.repertory_flag ){
			 // //参于库存并计算
			 // hotelMIS::HBeforeRepCtrl beforeRepCtrl(_pCon);
			 // beforeRepCtrl.insert(_pCon->insert_id());
			 // hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
			 // behindRepCtrl.insert(_pCon->insert_id( ) );
		  //}else if ( HMenuInfo::REP_NOCALC == menuInfo.repertory_flag){
			 // hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
			 // behindRepCtrl.insert(_pCon->insert_id( ));
		  //}
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::update(HMenuInfo& menuInfo)
// Purpose:    Implementation of HMenuInfoCtrl::update()
// Parameters:
// - menuInfo
// Return:     void
////////////////////////////////////////////////////////////////////////

void HMenuInfoCtrl::update(HMenuInfo& menuInfo)
{
   // TODO : 修改
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE  t_menuInfo SET kind_id = "
                     << menuInfo.kind_id << ", food_name = '"
					 << menuInfo.food_name << "', food_price = "
					 << menuInfo.food_price <<", food_unit = '"
					 << menuInfo.food_unit << "',repertory_flag = "
					 << menuInfo.repertory_flag << ", ck_name = '"
                     << menuInfo.ck_name << "',food_py='"
					 << menuInfo.food_py << "',total_fl="
					 << menuInfo.total_fl
                     << " WHERE food_id = " 
                     << menuInfo.food_id ;
					 /*<< " AND kind_id NOT IN (SELECT kind_id FROM t_foodKind WHERE kind_ts = 1)";*/
          	   string sql = query.str(); 
		 query.execute();

	

		  // if ( HMenuInfo::REP_CALC == menuInfo.repertory_flag){
				////参于库存并计算
			 //  hotelMIS::HBeforeRepCtrl beforeRepCtrl(_pCon);
			 //  if ( ! beforeRepCtrl.isExist(menuInfo.food_id) ){
				//   beforeRepCtrl.insert(menuInfo.food_id);
			 //  }
			 //  hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
			 //  if ( ! behindRepCtrl.isExist(menuInfo.food_id) ){
				//   behindRepCtrl.insert(menuInfo.food_id);
			 //  }
		  // }else if ( HMenuInfo::REP_NOCALC == menuInfo.repertory_flag){
			 //  hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
			 //  if ( ! behindRepCtrl.isExist(menuInfo.food_id) ){
				//   behindRepCtrl.insert(menuInfo.food_id);
			 //  }
		  // }else if ( HMenuInfo::REP_NO == menuInfo.repertory_flag){
			 // hotelMIS::HBeforeRepCtrl beforeRepCtrl(_pCon);
			 //  if ( beforeRepCtrl.isExist(menuInfo.food_id) ){
				//   beforeRepCtrl.Delete(menuInfo.food_id);
			 //  }
			 //  hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
			 //  if ( behindRepCtrl.isExist(menuInfo.food_id) ){
				//   behindRepCtrl.Delete(menuInfo.food_id);
			 //  }
		  // }
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::Delete(int foodId)
// Purpose:    Implementation of HMenuInfoCtrl::Delete()
// Parameters:
// - foodId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HMenuInfoCtrl::Delete(int foodId,bool sp)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
		 
		query << "DELETE FROM t_menuInfo WHERE food_id = "<< foodId ;
		 
         query.execute();

		////从库存中删除
		// hotelMIS::HBeforeRepCtrl beforeRepCtrl(_pCon);
		// if ( beforeRepCtrl.isExist(foodId) ){
		//	 beforeRepCtrl.Delete(foodId);
		// }
		// hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
		// if ( behindRepCtrl.isExist(foodId) ){
		//	 behindRepCtrl.Delete(foodId);
		// }
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::getMenuInfo(int foodId)
// Purpose:    Implementation of HMenuInfoCtrl::getMenuInfo()
// Parameters:
// - foodId
// Return:     HMenuInfo
////////////////////////////////////////////////////////////////////////

HMenuInfo HMenuInfoCtrl::getMenuInfo(int foodId)
{
   // TODO : 获得一个菜谱的详细清单
   HMenuInfo menuInfo;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo WHERE food_id = " << foodId ;
         mysqlpp::Result res = query.store();
        _fill(menuInfo,res);
   }mycatch();
   return menuInfo;
}

////////////////////////////////////////////////////////////////////////
// Name:       HMenuInfoCtrl::getAllMenuInfo()
// Purpose:    Implementation of HMenuInfoCtrl::getAllMenuInfo()
// Return:     vector<HMenuInfo>
////////////////////////////////////////////////////////////////////////

vector<HMenuInfo> HMenuInfoCtrl::getAllMenuInfo(void)
{
   // TODO : implement
   vector<HMenuInfo> vec; 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo order by kind_id";
         
		 mysqlpp::Result res = query.store();
		 _fill_vec(vec,res);
   }mycatch();
   return vec;
}

//---------------------------------------------------------------------------------------------------------------------------
// invalidate 
vector<HMenuInfo> HMenuInfoCtrl::getAllMenuInfoExceptSpKind(void)
{
   // TODO : implement
   vector<HMenuInfo> vec; 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo WHERE kind_id NOT IN ( SELECT kind_id FROM t_foodKind WHERE kind_ts = 1 )";
          mysqlpp::Result res = query.store();
		 mysqlpp::Result::iterator it ;
		 mysqlpp::Row row;
		 HMenuInfo menuInfo;

		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 menuInfo.food_id = row.lookup_by_name("food_id");
			 menuInfo.kind_id = row.lookup_by_name("kind_id");
			 menuInfo.food_name = row.lookup_by_name("food_name");
			 menuInfo.food_price = row.lookup_by_name("food_price");
			 menuInfo.food_num = row.lookup_by_name("food_num");
			 menuInfo.food_unit = row.lookup_by_name("food_unit");
			 menuInfo.repertory_flag = row.lookup_by_name("repertory_flag");
			 menuInfo.ck_name = row.lookup_by_name("ck_name");
			 menuInfo.food_cook = row.lookup_by_name("food_cook");
			 menuInfo.food_py = row.lookup_by_name("food_py");
			 menuInfo.total_fl = row.lookup_by_name("total_fl");
			 vec.push_back(menuInfo);
		 }
   }mycatch();
   return vec;
}

//------------------------------------------------------------------------------------------------------
vector<HMenuInfo> HMenuInfoCtrl::getMenuInfoByKind(int kindId)
{
   // TODO : implement
      vector<HMenuInfo> vec; 
   try{
         mysqlpp::Query query = _pCon->query();
		 query << "SELECT * FROM t_menuInfo WHERE kind_id = " << kindId ;
		 mysqlpp::Result res = query.store();
		 _fill_vec(vec,res);
   }mycatch();
   return vec;
}

//------------------------------------------------------------------------------------------------------
bool HMenuInfoCtrl::isExist(int kindId,int foodId)
{	
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_menuInfo WHERE food_id ="<< foodId 
			<<" AND kind_id =" << kindId;
		mysqlpp::Result res = query.store();
		if ( ! res.empty() )
			return true;
	}mycatch();
	return false;
}

//-------------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::AddSpecialMenu(int kindTsId,int foodId)
{
	try{
		HMenuInfo menuInfo = getMenuInfo(foodId);
		if ( isExist(kindTsId,foodId) ){
			//更改数量
			mysqlpp::Query query = _pCon->query();
			query << "UPDATE t_menuInfo SET food_num = food_num +1 WHERE food_name='" << menuInfo.food_name << "'" 
					<< " AND kind_id IN(SELECT kind_id FROM t_foodKind WHERE kind_ts = 1 ) ";
			query.execute();
		}else{
			//修改kindId,添加
			menuInfo.food_id = foodId;
			menuInfo.kind_id = kindTsId;
			menuInfo.food_num = 1;
			insert(menuInfo,true);
		}
	}mycatch();
}

//----------------------------------------------------------------------------------------------------
vector<HMenuInfo>HMenuInfoCtrl::getAllMenuInfoRep()
{
   vector<HMenuInfo> vec; 
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT * FROM t_menuInfo WHERE repertory_flag =1";
         mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
   }mycatch();
   return vec;
}

//---------------------------------------------------------------------------------------------------
vector<HMenuInfo> HMenuInfoCtrl::getMenuByCook(int cookId)
{
	vector<HMenuInfo> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_menuInfo WHERE food_cook = "<< cookId;
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//-----------------------------------------------------------------------------------------------
void HMenuInfoCtrl::AddToChuFang(int cookId,int foodId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_menuInfo SET food_cook = " << cookId << " WHERE food_id = "
			<< foodId;
		query.execute();
	}mycatch();
}

//------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::AddToChuFangByKind(int cookId,int kindId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_menuInfo SET food_cook = " << cookId << " WHERE kind_id ="
			<<kindId;
		query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::RemoveFromChuFang(int foodId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_menuInfo SET food_cook = -1 WHERE food_id = "
			<< foodId;
		query.execute();
	}mycatch();
}

//-----------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_menuInfo";
		query.execute();
		query << "DELETE FROM t_childmenuinfo";
		query.execute();
	}mycatch();
}


//---------------------------------------------------------------------------------------------------
HMenuInfoVec HMenuInfoCtrl::getTaoCanList()
{	
	vector<HMenuInfo> vec;
	
	try{
		mysqlpp::Query query = _pCon->query();

		query << "SELECT * FROM t_menuInfo WHERE kind_id ="<< HFoodKind::SYS_MENU::TC;
		_fill_vec(vec,query.store());
	}mycatch();

	return vec;
}


//--------------------------------------------------------------------------------------------------
HMenuInfoVec HMenuInfoCtrl::getChildMenu(int parent_food_id)
{
	vector<HMenuInfo> vec;

	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_menuInfo WHERE food_id IN \
				 ( SELECT food_id FROM t_childmenuinfo WHERE parent_food_id ="
				 << parent_food_id
				 << ")";
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();

	return vec;
}

//-------------------------------------------------------------------------------------------------------
/**

*/
HMenuInfoVec  HMenuInfoCtrl::getMenuByPy(string py)
{
	vector<HMenuInfo> vec;

	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_menuInfo WHERE food_py LIKE '"<<py<<"%'";
		_fill_vec(vec,query.store());
	}mycatch();
		
	return vec;
}

//------------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::addToTaoCan(int parent_food_id,int food_id,int food_num)
{
	try{
		mysqlpp::Query query = _pCon->query();
		if ( isExistTaoCan(parent_food_id,food_id) )
		{
			query << "UPDATE t_childmenuInfo SET food_num = food_num + "
				<< food_num << " WHERE parent_food_id = "
				<< parent_food_id << " AND food_id = "
				<< food_id;
			query.execute();
		}
		else
		{
			query << "INSERT INTO t_childmenuInfo(parent_food_id,food_id,food_num) VALUES("
				<< parent_food_id <<","
				<< food_id << ","
				<< food_num << ")";
			query.execute();
		}
	}mycatch();
}

//------------------------------------------------------------------------------------------------------
bool HMenuInfoCtrl::isExistTaoCan(int parent_food_id,int food_id)
{
	try{
	mysqlpp::Query query = _pCon->query();

	query << "SELECT * FROM t_childmenuInfo WHERE parent_food_id = "
		  << parent_food_id << " AND food_id = "
		  << food_id;
	mysqlpp::Result res = query.store();
	if ( ! res.empty() )
		return true;
	}mycatch();

	return false;
}

//---------------------------------------------------------------------------------------------------------
int HMenuInfoCtrl::getNum(int parent_food_id,int food_id)
{
	int food_num = 0;
	try{
		mysqlpp::Query query = _pCon->query();

		query << "SELECT food_num FROM t_childmenuInfo WHERE parent_food_id="
			<< parent_food_id << " AND food_id = "
			<< food_id ;
		mysqlpp::Result res = query.store();
		if ( ! res.empty() ){
			food_num = (*res.begin()).lookup_by_name("food_num");
		}
	}mycatch();
	return food_num;
}

//---------------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::delTaoCan(int parent_food_id,int food_id)
{
	try{
		mysqlpp::Query query = _pCon->query();

		query << "DELETE FROM t_childmenuInfo WHERE parent_food_id="
			<< parent_food_id << " AND food_id = "
			<< food_id ;
		query.execute();
	}mycatch();
}

//----------------------------------------------------------------------------------------------------------
void HMenuInfoCtrl::delTaoCan(int parent_food_id)
{
	try{
		mysqlpp::Query query = _pCon->query();

		query << "DELETE FROM t_childmenuInfo WHERE parent_food_id="
			<< parent_food_id;
		query.execute();
	}mycatch();
}

//---------------------------------------------------------------------------------------------------------
int HMenuInfoCtrl::getFoodFlag(int food_id)
{
	int food_flag = 0;
	try{
		mysqlpp::Query query = _pCon->query();

		query << "SELECT kind_flag FROM t_foodKind LEFT JOIN t_menuInfo \
				 ON t_foodKind.kind_id = t_menuInfo.kind_id \
				 WHERE t_menuInfo.food_id = "
				 << food_id;
		mysqlpp::Result res = query.store();
		
		if ( !res.empty() ){
			food_flag = (*res.begin()).lookup_by_name("kind_flag");
		}
	}mycatch();

	return food_flag;
}

//-----------------------------------------------------------------------------------------------------------
// static
HMenuInfoVec HMenuInfoCtrl::menuInfoFactory()
{
	if ( _menuInfoVec.empty() ){
		hotelMIS::KDBCon con;
		HMenuInfoCtrl Info(con.get_con());
		_menuInfoVec = Info.getAllMenuInfo();

	}

	return _menuInfoVec;
}

//-----------------------------------------------------------------------------------------------------------
bool HMenuInfoCtrl::isHouChu(int flag)
{
	if ( HFoodKind::HOUCHU_FLAG == flag )
		return true;
	return false;
}

//------------------------------------------------------------------------------------------------------------
bool HMenuInfoCtrl::isTaoCan(int food_id)
{
	HMenuInfo info = this->getMenuInfo(food_id);
	if ( info.kind_id == HMenuInfo::TC)
		return true;
	else
		return false;
}

HTcMenuInfoVec HMenuInfoCtrl::getTcMenuInfo(int parent_food_id)
{
	HTcMenuInfoVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_childmenuinfo WHERE parent_food_id = "
			<< parent_food_id;
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HTcMenuInfo menuInfo;
		for ( it = res.begin(); it != res.end(); it++)
		{
				row = *it;
				menuInfo.parent_food_id = parent_food_id;
				menuInfo.food_id = row.lookup_by_name("food_id");
				menuInfo.food_num = row.lookup_by_name("food_num");
				vec.push_back(menuInfo);
		}
	}mycatch();
	return vec;
}

//-----------------------------------------------------------------------------------------------------------
HMenuInfo HMenuInfoCtrl::getMenuInfoByName(string foodName)
{
	HMenuInfo menuInfo;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_menuInfo WHERE food_name ='"
			<<foodName
			<<"'";
		mysqlpp::Result res = query.store();
		_fill(menuInfo,res);
	}mycatch();
	return menuInfo;
}