//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HTableStatusSet.h
//
// Description:    
//				餐桌状态 对应数据库表 t_tableStatusSet
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	邢泉	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HTableStatusSet_h)
#define __hotelMIS_HTableStatusSet_h

#include <string>
using namespace std;

namespace hotelMIS{

	class HTableStatusSet
	{
	public:
		//Construct/Destruct
		HTableStatusSet();
		HTableStatusSet(int tableState,string stateName,int personNum);
		~HTableStatusSet();

	public:
		string getState_name(void);
		void setState_name(string newState_name);
		int getTable_state(void);
		void setTable_state(int newTable_state);
		void setPerson_num(int newPerson_num);
		int getPerson_num(void);
	
		int table_state;
		string state_name;
		int person_num;
		int empty_bmp;
		int repast_bmp;
	};
}
#endif