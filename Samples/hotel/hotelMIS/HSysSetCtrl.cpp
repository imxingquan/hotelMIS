#include "stdAfx.h"
#include "HRoom.h"
#include "HSysSetCtrl.h"
namespace hotelMIS{
	HSysSetCtrl::HSysSetCtrl(mysqlpp::Connection* pCon)
	{
		_pCon = pCon;
	}
	
	int HSysSetCtrl::getMaxRoomNo()
	{
		int maxRoomNo = -1;
		try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT MAX(room_id) as maxRoomNo FROM t_roomSet ";
		mysqlpp::Result res = query.store();
		if ( !res.empty() ){
			mysqlpp::Row row;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			maxRoomNo = row.lookup_by_name("maxRoomNo");
		}
		}mycatch();
		return maxRoomNo;
	}

	void HSysSetCtrl::createRoom(string roomName,int tableNum)
	{
		//创建餐厅及桌子数量
		mysqlpp::Query query = _pCon->query();
		int roomId = getMaxRoomNo();
		query <<"INSERT INTO t_roomSet (room_id,room_name,talbe_num) VALUES(roomId+1,'"
			<<roomName << "',"<<tableNum<<")";
		//根据输入初始桌子状态
		for ( int i = 0; i <= tableNum; i++)
		{
			mysqlpp::Query query = _pCon->query();
			query << "
		}
	}
	
	void HSysSetCtrl::updateRoom(const HRoom& room)
	{
	}

	void HSysSetCtrl::deleteRoom(int roomId)
	{
	}

	void HSysSetCtrl::createTableStatus(const HTableStatus& tableStatus)
	{
	}

	void HSysSetCtrl::updateTableStatus(const HTableStatus& tableStatus)
	{
	}

	void HSysSetCtrl::deleteTableStatus(int tableId)
	{
	}

	void HSysSetCtrl::createTableSset(const HTableStatusSet tss)
	{
	}

	void HSysSetCtrl::updateTableSset(const HTableStatusSet& tss)
	{
	}

	void HSysSetCtrl::deleteTableSset(int tableStatus)
	{
	}
	
	vecTableStatusSet HSysSetCtrl::getAllTableStatusSet()
	{

	}
	vecTableStatus HSysSetCtrl::getAllTableStatus()
	{

	}
	vecRoom HSysSetCtrl::getAllRoom()
	{

	}

}