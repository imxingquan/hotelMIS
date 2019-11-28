#ifndef HSYSSETCTRL_H_HEADER_INCLUDED_BDA367B3
#define HSYSSETCTRL_H_HEADER_INCLUDED_BDA367B3
//#include "HRoom.h"
#include "config.h"

namespace hotelMIS{

	typedef vector<HTableStatusSet> vecTableStatusSet;
	typedef vector<HTableStatus> vecTableStatus;
	typedef vector<HRoom> vecRoom;
	class HSysSetCtrl
	{
	public:
		HSysSetCtrl(mysqlpp::Connection* pCon);
		//���������������ڵ���������
		void createRoom(string roomName,int tableNum);
		//���������ţ�������Ϊ���ɵĲ�����
		int  getMaxRoomNo();	

		void updateRoom(const HRoom& room);

		void deleteRoom(int roomId);

		void createTableStatus(const HTableStatus& tableStatus);

		void updateTableStatus(const HTableStatus& tableStatus);

		void deleteTableStatus(int tableId);

		void createTableSset(const HTableStatusSet tss);

		void updateTableSset(const HTableStatusSet& tss);

		void deleteTableSset(int tableStatus);

		//
		vecTableStatusSet getAllTableStatusSet();
		vecTableStatus	getAllTableStatus();
		vector<HRoom> getAllRoom();
	private:
		vecTableStatusSet _vecTableStatusSet;
		vecTableStatus _vecTableStatus;
		vecRoom _vecRoom;

		mysqlpp::Connection* _pCon;
	};

}

#endif /* HSYSSETCTRL_H_HEADER_INCLUDED_BDA367B3 */
