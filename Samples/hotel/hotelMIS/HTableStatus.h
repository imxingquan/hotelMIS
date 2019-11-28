//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HTableStatus.h 
//
// Description:    
//				����״̬�� ��Ӧ t_tableStatus
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	��Ȫ	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HTableStatus_h)
#define __hotelMIS_HTableStatus_h

namespace hotelMIS{

	class HTableStatus
	{
	public:
		//Construct /Destruct
		HTableStatus();
		HTableStatus(int tableId,int roomId,int tableState);
		~HTableStatus();

		int getTable_id(void);
		void setTable_id(int newTable_id);
		int getRoom_id(void);
		void setRoom_id(int newRoom_id);
		int getTable_state(void);
		void setTable_state(int newTable_state);

	public:
		int table_id;
		int room_id;
		int table_state;

	};
}
#endif