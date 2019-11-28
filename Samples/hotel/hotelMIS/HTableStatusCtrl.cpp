//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HTableStatusCtrl.cpp
//
// Description:    
//				HTableStatus 的数据库操作类
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HTableStatusCtrl.h"
#include "HTableStatusSetCtrl.h"
#include "HRoomCtrl.h"
#include "HRepastCtrl.h"

using namespace hotelMIS;

HTableStatusCtrl::HTableStatusCtrl(mysqlpp::Connection *pCon)
{
   // TODO : implement
	_pCon = pCon;
}


HTableStatusCtrl::~HTableStatusCtrl()
{
   
}

//
// 插入
//
void HTableStatusCtrl::insert(int tableId, int roomId, int tableState)
{
   	try{
	mysqlpp::Query query = _pCon->query();
	query << "INSERT INTO t_tableStatus(table_id,room_id,table_state) VALUES("
		<< tableId <<","<<roomId<<","<<tableState<<")";
	query.execute();
	}mycatch();
}

//
// 插入
//
void HTableStatusCtrl::insert(hotelMIS::HTableStatus& tableStatus)
{
   	try{
	mysqlpp::Query query = _pCon->query();
	query << "INSERT INTO t_tableStatus(table_id,room_id,table_state) VALUES("
		<< tableStatus.getTable_id() <<","<<tableStatus.getRoom_id()<<","<<tableStatus.getTable_state()<<")";
		query.execute();
	}mycatch();
}

// 
// 更新
//
void HTableStatusCtrl::update(hotelMIS::HTableStatus& tableStatus)
{
   // TODO : implement
	try{
	mysqlpp::Query query = _pCon->query();
	query << "UPDATE t_tableStatus SET room_id = " << tableStatus.getRoom_id() 
		<< ",table_state = "<<tableStatus.getTable_state();
	query.execute();
	}mycatch();
}

//
// 删除
//
void HTableStatusCtrl::Delete(int tableId)
{
   // TODO : implement
	try{
	mysqlpp::Query query = _pCon->query();
	query << "DELETE FROM t_tableStatus WHERE table_id = " << tableId;
	query.execute();
	}mycatch();
}

//
// 删除 roomId 餐厅
//
void  HTableStatusCtrl::DeleteByRoomId(int roomId)
{
	try{
	mysqlpp::Query query = _pCon->query();
	query << "DELETE FROM t_tableStatus WHERE room_id = " << roomId;
	query.execute();
	}mycatch();
}

//
// 返回餐桌状态
//
HTableStatus HTableStatusCtrl::getTableStatus(int tableId)
{
   // TODO : implement
	HTableStatus hTableStatus;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM  t_tableStatus WHERE table_id = " << tableId;
		mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
	
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			int roomId = row.lookup_by_name("room_id");
			int tableState = row.lookup_by_name("table_state");
			hTableStatus.setTable_id(tableId);
			hTableStatus.setRoom_id(roomId);
			hTableStatus.setTable_state(tableState);
		}	
	}mycatch();
	return hTableStatus;
}

//
// 返回所有的餐桌状态
//
vector<HTableStatus> HTableStatusCtrl::getAllTableStatus(void)
{
   // TODO : implement	
	HTableStatusVec vec;
   try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM  t_tableStatus ORDER BY table_id ";
		mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
	
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			int tableId = row.lookup_by_name("table_id");
			int roomId = row.lookup_by_name("room_id");
			int tableState = row.lookup_by_name("table_state");
			HTableStatus hTableStatus;
			hTableStatus.setTable_id(tableId);
			hTableStatus.setRoom_id(roomId);
			hTableStatus.setTable_state(tableState);
			vec.push_back(hTableStatus);
		}	
		
	}mycatch();
   return vec;
}

// 
// 根据餐厅号返回餐桌状态
//
vector<HTableStatus> HTableStatusCtrl::getTableStatusSpecial(int roomId)
{
	HTableStatusVec vec;
	 try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM  t_tableStatus WHERE room_id =" << roomId << " ORDER BY table_id ";
		mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			int tableId = row.lookup_by_name("table_id");
			int roomId = row.lookup_by_name("room_id");
			int tableState = row.lookup_by_name("table_state");
			HTableStatus hTableStatus;
			hTableStatus.setTable_id(tableId);
			hTableStatus.setRoom_id(roomId);
			hTableStatus.setTable_state(tableState);
			vec.push_back(hTableStatus);
		}	
	
	}mycatch();
	return vec;
}

//
// 创建 roomId 餐厅的所有餐桌
//
void HTableStatusCtrl::createTable(int roomId, int tableNum)
{
   // TODO : implement
	try{
		mysqlpp::Query query = _pCon->query();
		for ( int i = 1; i <=tableNum; i++)
		{
			query << "INSERT INTO t_tableStatus (table_id,room_id) VALUES ("<< i 
				<<","<<roomId<<")";
			query.execute();
		}
	}mycatch();
}

//
// 获得最大的餐桌ID
//
int HTableStatusCtrl::getMaxTableId(void) const
{
   // TODO : implement
	int maxId = 0;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT MAX(table_id) as maxId FROM t_tableStatus";
		mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		if ( !res.empty() ){
			mysqlpp::Result::iterator it;
			for (it = res.begin(); it != res.end(); it++)
			{
				row = *it;
				maxId = row.lookup_by_name("maxId");
			}
		}
	}mycatch();
	return maxId;
}

//
// 判断餐桌是否存在
//
bool HTableStatusCtrl::isExist(int tableId)
{
   // TODO : implement
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT table_id FROM t_tableStatus WHERE table_id ="<<tableId;
		mysqlpp::Result res = query.store();
		if ( !res.empty() )
			return true;
	}mycatch();
	return false;
}

//
// 返回餐厅名称
//
string HTableStatusCtrl::getRoomName(int roomId)
{
	HRoomCtrl roomCtrl(_pCon);
	HRoom room = roomCtrl.getRoom(roomId);
	return room.getName();
}

//
// 获得餐桌状态名
//
string HTableStatusCtrl::getTableStateName(int tableState)
{
	
	HTableStatusSetCtrl tableSetCtrl(_pCon);
	HTableStatusSet tableSet = tableSetCtrl.getHTableStatus(tableState);
	return tableSet.getState_name();
}

//
// 获得人数
//
int HTableStatusCtrl::getPersonNum(int tableState)
{ 
	HTableStatusSetCtrl tableSetCtrl(_pCon);
	HTableStatusSet tableSet = tableSetCtrl.getHTableStatus(tableState);
	return tableSet.getPerson_num();
}

//
// 返回餐桌的详细信息
//
vector<HTableInfo> HTableStatusCtrl::getAllTableInfo(int roomId)
{
	
	hotelMIS::HTableStatusVec vec = getTableStatusSpecial(roomId);
	hotelMIS::HRepastCtrl repastCtrl(_pCon);
	hotelMIS::HTableStatusVec::iterator it;
	
	vector<HTableInfo> tVec;
	int re_state = 0;
	int tableId = 0;
	int tableState = 0;

	for ( it = vec.begin(); it!= vec.end(); it++)
	{	
		hotelMIS::HTableInfo tableInfo;
		tableId = it->getTable_id();
		tableState = it->getTable_state();
		re_state = repastCtrl.getRepastState(tableId,roomId);
		tableInfo.setTable_id(tableId);
		tableInfo.setRoom_id(roomId);
		tableInfo.setRoom_name(getRoomName(roomId));
		tableInfo.setState_name(getTableStateName(tableState));
		tableInfo.setPerson_num(getPersonNum(tableState));
		tableInfo.setRe_state(re_state);
		tVec.push_back(tableInfo);
	}
	return tVec;
}

//
// 获得当前餐厅所有未使用的餐桌
//
vector<int> HTableStatusCtrl::getEmptyTable(int roomId)
{
   vector<int> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT table_id FROM t_tableStatus WHERE room_id ="
               <<roomId 
               <<" AND table_id NOT IN (SELECT table_id FROM t_repast WHERE room_id = "
               <<roomId << ")";
          mysqlpp::Result res = query.store();
          mysqlpp::Result::iterator it;
          mysqlpp::Row row;
          int tId;
          for ( it = res.begin(); it != res.end(); it++)
          {
                  row = *it;
                  tId = row.lookup_by_name("table_id");
                  vec.push_back(tId);
          }
   }mycatch();
   return vec;
}

//
// 返回餐桌状态名
//
string HTableStatusCtrl::getTableStateName(int tableId,int roomId)
{
	string tName="";
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT state_name FROM t_tableStatusSet WHERE table_state = "
			  << "(SELECT table_state FROM t_tableStatus WHERE table_id = "
			  << tableId << " AND room_id = "
			  << roomId << " )";
		mysqlpp::Result res = query.store();
		if (!res.empty() ){
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			tName = row.lookup_by_name("state_name");
		}
	}mycatch();
	return tName;
}

//
// 返回餐桌状态id
//
int HTableStatusCtrl::getTableStatus(int tableId,int roomId)
{
	int tableState = -1;
	try{
		mysqlpp::Query query = _pCon->query();
		query <<" SELECT table_state FROM t_tableStatus WHERE table_id = "
			  << tableId << " AND room_id = "
			  << roomId ;
		mysqlpp::Result res = query.store();
		if (!res.empty() ){
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			tableState = row.lookup_by_name("table_state");
		}
	}mycatch();
	return tableState;
}

//
// 返回餐桌名称
//
string HTableStatusCtrl::getTableName(int tableId,int roomId)
{
	string tName="";
	try{
		mysqlpp::Query query = _pCon->query();
		query <<" SELECT table_name FROM t_tableStatus WHERE table_id = "
			  << tableId << " AND room_id = "
			  << roomId ;
		mysqlpp::Result res = query.store();
		if (!res.empty() ){
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			tName = row.lookup_by_name("table_name");
		}
	}mycatch();
	return tName;
}

//
// 设置餐桌名称
//
void HTableStatusCtrl::setTableName(string tableName,int tableId,int roomId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<" UPDATE t_tableStatus SET table_name ='"<<tableName<<"' WHERE table_id = "
			  << tableId << " AND room_id = "
			  << roomId ;
		query.execute();
	}mycatch();
}

//
// 设置餐桌状态
//
void HTableStatusCtrl::setTableState(int state,int tableId,int roomId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<" UPDATE t_tableStatus SET table_state ="<<state<<" WHERE table_id = "
			  << tableId << " AND room_id = "
			  << roomId ;
		query.execute();
	}mycatch();
}

//
// 判断餐桌是否存在某个状态
//
bool HTableStatusCtrl::isExistTableState(int state)
{
	//判断此状态的桌型是否以被应用
	try{
		mysqlpp::Query query = _pCon->query();
		query <<" SELECT  table_state FROM t_tableStatus WHERE table_state = "<< state;
		mysqlpp::Result res = query.store();
		if (!res.empty() )
			return true;
	}mycatch();
	return false;
}