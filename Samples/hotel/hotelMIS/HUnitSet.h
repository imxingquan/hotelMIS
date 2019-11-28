//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HUnitSet.h
//
// Description:    
//				��λ�������Ӧ t_unit ��
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	��Ȫ	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HUnitSet_h)
#define __hotelMIS_HUnitSet_h

#include <string>

using namespace std;

namespace hotelMIS{

	class HUnitSet
	{
	public:
		//Construct/Destruct
		HUnitSet();
		~HUnitSet();
	public:
		int getUnit_id(void);
		void setUnit_id(int newUnit_id);
		string getUnit_name(void);
		void setUnit_name(string newUnit_name);
	private:
		int unit_id;
		string unit_name;

	}; //end class HUnitSet
} // end namespace hotelMIS
#endif