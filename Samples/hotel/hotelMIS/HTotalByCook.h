//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HTotalByCook.h
//
// Description:    
//				����ʦͳ�����˵��������۸�  ��Ӧ t_totalByCook ��
//				
// Version: 1.0
//
// Hostory:		
//			05-22-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HTotalByCook_h)
#define __hotelMIS_HTotalByCook_h

#include <string>
#include <vector>

using namespace std;

namespace hotelMIS{

	class HTotalByCook
	{
	public:
		//Construct/Destruct
		HTotalByCook();
		~HTotalByCook();
		
	public:
		//member data
		string food_name;
		int total_food_num;
		float total_food_price;
		string ck_name;
	};
	
}
#endif