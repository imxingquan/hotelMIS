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
	*		// ���ز��������ID
	*		getMaxTableId()
	*		
	*		// �Ƿ���ڲ��� 
	*		isExist(int tableID)
	*		
	*		// ��ò���״̬
	*		getTableStatus(int tableId)
	*		
	*		// ���ز�������״̬
	*		getAllTableStatus(void)
	*
	*		// ͨ���ض����ŷ������е��������ڴ���ÿһ������������
	*		getTableStatusSpecial(int roomId)
	*
	*		// ���� ����ΪroomId �� ����
	*		createTable(int roomId, int tableNum)
	*		
	*		// ���ز�������
	*		getRoomName(int roomId);
	*		
	*		// ���ز���״̬����
	*		getTableStateName(int tableState);
	*		
	*		//���ز���roomId���пյĲ���
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

		/* ͨ���ض����ŷ������е��������ڴ���ÿһ������������. */
		vector<HTableStatus> getTableStatusSpecial(int roomId);

		void createTable(int roomId, int tableNum);

		string getRoomName(int roomId);
		string getTableStateName(int tableState);
		int getPersonNum(int tableState);
		// ����һ��HTableInfo�Ķ���
		vector<HTableInfo> getAllTableInfo(int roomId);
		//�������пյĲ���
		vector<int> getEmptyTable(int roomId);
		//���ز�������
		string getTableStateName(int tableId,int roomId);
		//ɾ�����������в���
		void DeleteByRoomId(int roomId);

		//���ز���״̬��
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