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

#if !defined(__hotelMIS_HTableStatusCtrl_h)
#define __hotelMIS_HTableStatusCtrl_h

#include "config.h"
#include "HTableStatus.h"
#include "HTableInfo.h"
#include <vector>

using namespace std;

namespace hotelMIS{

	// *** global ***
	typedef vector<HTableStatus> HTableStatusVec;
	typedef vector<HTableInfo> HTableInfoVec;
	typedef vector<int> TableCol;
	
	/*----------------------------------------------------------------------------------------------------------
	* class HTableStatusCtrl
	*
	*	member function:
	*		// 返回餐桌的最大ID
	*		getMaxTableId()
	*		
	*		// 是否存在餐桌 
	*		isExist(int tableID)
	*		
	*		// 获得餐桌状态
	*		getTableStatus(int tableId)
	*		
	*		// 返回餐桌所有状态
	*		getAllTableStatus(void)
	*
	*		// 通过特定桌号返回所有的桌号用于创建每一个餐厅的桌子
	*		getTableStatusSpecial(int roomId)
	*
	*		// 创建 餐厅为roomId 的 餐桌
	*		createTable(int roomId, int tableNum)
	*		
	*		// 返回餐厅名称
	*		getRoomName(int roomId);
	*		
	*		// 返回餐桌状态名称
	*		getTableStateName(int tableState);
	*		
	*		//返回餐厅roomId所有空的餐桌
	*		getEmptyTable(int roomId);
	*----------------------------------------------------------------------------------------------------------*/
	class HTableStatusCtrl
	{
	public:
		// Construct / Destruct
		HTableStatusCtrl(mysqlpp::Connection *pCon);
		~HTableStatusCtrl();

		void insert(int tableId, int roomId, int tableState);
		void insert(hotelMIS::HTableStatus& tableStatus);
		void update(hotelMIS::HTableStatus& tableStatus);
		void Delete(int tableId);

		int getMaxTableId()const;

		bool isExist(int tableId);

		HTableStatus getTableStatus(int tableId);

		vector<HTableStatus> getAllTableStatus(void);

		/* 通过特定桌号返回所有的桌号用于创建每一个餐厅的桌子. */
		vector<HTableStatus> getTableStatusSpecial(int roomId);

		void createTable(int roomId, int tableNum);

		string getRoomName(int roomId);
		string getTableStateName(int tableState);
		int getPersonNum(int tableState);
		// 返回一个HTableInfo的对象
		vector<HTableInfo> getAllTableInfo(int roomId);
		//返回所有空的餐桌
		vector<int> getEmptyTable(int roomId);
		//返回餐桌名称
		string getTableStateName(int tableId,int roomId);
		//删除餐厅的所有餐桌
		void DeleteByRoomId(int roomId);

		//返回餐桌状态数
		int getTableStatus(int tableId,int roomId);
		string getTableName(int tableId,int roomId);
		void setTableName(string tableName,int tableId,int roomId);

		void setTableState(int state,int tableId,int roomId);

		bool isExistTableState(int state);

	private:
		mysqlpp::Connection *_pCon;
	}; // end class HTableStatusCtrl
} // end namespace hotelMIS
#endif