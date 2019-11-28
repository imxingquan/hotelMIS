#include "stdAfx.h"
#include "HRoomCtrl.h"
#include <cassert>
using namespace std;

namespace hotelMIS{

	HRoomCtrl::HRoomCtrl(mysqlpp::Connection *pCon )
	{
		_pCon = pCon;
	}
	
	bool HRoomCtrl::isExistRoom(int roomid)
	{
		try{
			mysqlpp::Query query = _pCon->query();
			query << "SELECT room_id FROM t_roomSet WHERE room_id = "<< roomid;
			mysqlpp::Result res = query.store();
			if ( res.empty())
				return false;
		}mycatch();
		return true;
	}

	int HRoomCtrl::insertRoom(int roomid,string name,int tableNum)
	{
		if ( isExistRoom(roomid) ) return -1; //如果要添加的room已经存在.

		try{
		/*id = getRoomMax() +1;
		assert(id != -1);*/
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_roomSet (room_id,room_name,table_num) VALUES("<< roomid
			<<",'"<<name<<"',"<<tableNum<<")";
		query.execute();
		}mycatch();
		
		return roomid;
	}

	void HRoomCtrl::updateRoom(HRoom &room)
	{
		try{
			mysqlpp::Query query = _pCon->query();
			query << "UPDATE t_roomSet SET room_name ='"<<room.room_name<<"',table_num="
				<<room.table_num <<" WHERE room_id = " << room.room_id;
			query.execute();
		}mycatch();
	}

	void HRoomCtrl::deleteRoom(int id)
	{
		try{
			mysqlpp::Query query = _pCon->query();
			query << "DELETE FROM  t_roomSet WHERE room_id = " << id;
			query.execute();
		}mycatch();
	}

	vector<HRoom> HRoomCtrl::getAllRoom()
	{
		vector<HRoom> vec;
		try{
			mysqlpp::Query query = _pCon->query();
			query << "SELECT * FROM t_roomSet ORDER BY room_id ";
			mysqlpp::Result res = query.store();
			mysqlpp::Row row ;
			mysqlpp::Result::iterator it;
			for ( it = res.begin(); it != res.end(); it++){
				row = *it;
				int roomId = row.lookup_by_name("room_id");
				string room_name = row.lookup_by_name("room_name");
				int tableNum = row.lookup_by_name("table_num");
				HRoom room(roomId,room_name,tableNum);
				vec.push_back(room);
			}
		}mycatch();
		return vec;
	}
	
	HRoom HRoomCtrl::getRoom(int roomId)
	{	
		HRoom room;
		try{
			mysqlpp::Query query = _pCon->query();
			query << "SELECT * FROM t_roomSet WHERE room_id = " << roomId;
			mysqlpp::Result res = query.store();
			if ( !res.empty() )
			{
				mysqlpp::Row row;
				mysqlpp::Result::iterator it = res.begin();
				row = *it;
				string roomName = row.lookup_by_name("room_name");
				int tableNum = row.lookup_by_name("table_num");
				room.setId(roomId);
				room.setName(roomName);
				room.setTableNum(tableNum);
			}
		}mycatch();
		return room;
	}

	int HRoomCtrl::getRoomMax()
	{
		int id = -1;
		try{
			mysqlpp::Query  query = _pCon->query();
			query << "SELECT MAX(room_id) as roomMaxId FROM t_roomSet ";
			mysqlpp::Result res = query.store();
			if (! res.empty())
			{
				mysqlpp::Row row ;
				mysqlpp::Result::iterator it = res.begin();
				row = *it;
				string sid = row.lookup_by_name("roomMaxId");
				if ( "NULL"== sid)
					id = 0;
				else
					id = row.lookup_by_name("roomMaxId");
			}
		}mycatch();
		return id;
	}

	int	 HRoomCtrl::getRoomCount()const
	{
		int id = -1;
		try{
			mysqlpp::Query  query = _pCon->query();
			query << "SELECT COUNT(*) as roomCount FROM t_roomSet ";
			mysqlpp::Result res = query.store();
			if (! res.empty())
			{
				mysqlpp::Row row ;
				mysqlpp::Result::iterator it = res.begin();
				row = *it;
				id = row.lookup_by_name("roomCount");
			}
		}mycatch();
		return id;
	}
	
	string HRoomCtrl::getRoomName(int roomId)
	{
		string roomName;
		try{
			mysqlpp::Query query = _pCon->query();
			query << "SELECT room_name FROM t_roomSet WHERE room_id = "
				<<roomId;
			mysqlpp::Result res = query.store();
			if ( !res.empty())
			{
				mysqlpp::Row row;
				mysqlpp::Result::iterator it = res.begin();
				row = *it;
				roomName = row.lookup_by_name("room_name");
			}
		}mycatch();
		return roomName;
	}
}