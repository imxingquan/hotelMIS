//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HTableStatusCtrl.cpp
//
// Description:    
//				HTableStatus �����ݿ������
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	��Ȫ	Created	
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
// ����
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
// ����
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
// ����
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
// ɾ��
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
// ɾ�� roomId ����
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
// ���ز���״̬
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
// �������еĲ���״̬
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
// ���ݲ����ŷ��ز���״̬
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
// ���� roomId ���������в���
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
// ������Ĳ���ID
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
// �жϲ����Ƿ����
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
// ���ز�������
//
string HTableStatusCtrl::getRoomName(int roomId)
{
	HRoomCtrl roomCtrl(_pCon);
	HRoom room = roomCtrl.getRoom(roomId);
	return room.getName();
}

//
// ��ò���״̬��
//
string HTableStatusCtrl::getTableStateName(int tableState)
{
	
	HTableStatusSetCtrl tableSetCtrl(_pCon);
	HTableStatusSet tableSet = tableSetCtrl.getHTableStatus(tableState);
	return tableSet.getState_name();
}

//
// �������
//
int HTableStatusCtrl::getPersonNum(int tableState)
{ 
	HTableStatusSetCtrl tableSetCtrl(_pCon);
	HTableStatusSet tableSet = tableSetCtrl.getHTableStatus(tableState);
	return tableSet.getPerson_num();
}

//
// ���ز�������ϸ��Ϣ
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
// ��õ�ǰ��������δʹ�õĲ���
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
// ���ز���״̬��
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
// ���ز���״̬id
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
// ���ز�������
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
// ���ò�������
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
// ���ò���״̬
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
// �жϲ����Ƿ����ĳ��״̬
//
bool HTableStatusCtrl::isExistTableState(int state)
{
	//�жϴ�״̬�������Ƿ��Ա�Ӧ��
	try{
		mysqlpp::Query query = _pCon->query();
		query <<" SELECT  table_state FROM t_tableStatus WHERE table_state = "<< state;
		mysqlpp::Result res = query.store();
		if (!res.empty() )
			return true;
	}mycatch();
	return false;
}