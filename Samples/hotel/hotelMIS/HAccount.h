//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HAccount.h
//
// Description:    
//				��Ӧ�˵����ݱ� t_account �е�һ������   
//		
// 
// Version: 1.0
//
// Hostory:		
//			05-8-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HAccount_h)
#define __hotelMIS_HAccount_h
#include <string>

using namespace std;

namespace hotelMIS{
	
	class HAccount
	{
	public:
		// Construct /Destruct
		HAccount();
		~HAccount();

		//public member data
	public:
		//
		// ����״̬
		//
		enum {	notAcc=0,			//δ����
				havedAcc=1,			//�ѽ���
				cancelAcc=-1,		//�˵�
				gzAcc = 2,			//����
				gzhavedAcc=3		//���˽���
			 }; 
		enum JSFS{ xj = 1,				//�ֽ�
				mcard =2,			//��Ա��
				xycard =3,			//���ÿ�
				zp = 4				//֧Ʊ
		};

		string account_id;			//�˵���
		int room_id;				//������
		int table_id;				//������
		string cust_date;			//��������
		string cust_time;			//����ʱ��
		string pay_date;			//��������
		string pay_time;			//����ʱ��
		float subscription;			//����
		float yscost;				//Ӧ���˿�
		float erase_zero;			//Ĩ����
		float zhekou;				//�ۿ�
		int reckoning;				//�Ƿ���Ҫ��Ʊ 1: ���� 0:����Ҫ
		float sscost;				//ʵ���˿�
		int acc_status;				//�Ͳ�״̬ 
		string ad_name;				//ϵͳ����Ա����
		float daijin;				//����ȯ���
		float sj;					//ʵ���տ�
		float zy;					//������
		int paystatus;				//���ʽ
		string bz;					//��ע
		int arid;					//���˵�λ
		float zfprice;				//��Ա����֧Ʊ�����ÿ�
		int sswr;					//��������

	};

	class HTotalAccount
	{
	public:
		HTotalAccount()
			:pay_status(0)
			,sum_sscost(0.0f)
		{
		}
	public:
		int pay_status;
		float sum_sscost;
	};
}
#endif