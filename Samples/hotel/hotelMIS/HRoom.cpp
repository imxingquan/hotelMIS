#include "stdAfx.h"
#include "HRoom.h"
namespace hotelMIS{

	HRoom::HRoom()
	{
	}

	HRoom::HRoom(int roomId, string roomName, int tableNum)
		:room_id(roomId),
		room_name(roomName),
		table_num(tableNum)
	{
		
	}

	void HRoom::setId(int roomId)
	{
		room_id = roomId;
	}

	int HRoom::getId()
	{
		return room_id;
	}

	void HRoom::setName(string name)
	{
		room_name = name;
	}

	string HRoom::getName()
	{
		return room_name;
	}

	void HRoom::setTableNum(int tableNum)
	{
		table_num = tableNum;
	}

	int HRoom::getTableNum()
	{
		return table_num;
	}

}