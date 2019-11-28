//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HAccDetails.h
//
// Description:    
//				��Ӧ���ݿ��е� t_accDetails ���е��ֶ�,
//			�����洢 �ʵ���ϸ�������ݱ��е�һ�м�¼
//
// Version: 1.0
//
// Hostory:		
//			05-8-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HAccDetails_h)
#define __hotelMIS_HAccDetails_h
#include <string>
using namespace std;
namespace hotelMIS{

	class HAccDetails
	{
	public:
		// Construct /Destruct
		HAccDetails();
		~HAccDetails();
		
	public:
		// member data
		int id;					//auto id
		string account_id;		//�˵���
		int food_id;			//�������
		string food_name;		//��Ʒ����
		int food_num;			//����
		float food_price;		//�۸�
		string ck_name;			//��ʦ����
		string food_unit;		//��λ
		string food_cancel_msg; //�˵�ԭ��
		float zk_num; //���۱���
		int kind_id;
		int total_fl;
	}; // end class HAccDetails

	
}	// end namespace hotelMIS
#endif