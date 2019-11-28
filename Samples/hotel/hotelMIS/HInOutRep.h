//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HInOutRep.cpp
// 
// Desc: 
//
// Author:  ��Ȫ
//
// Modified: 2006�� �� ��
//--------------------------------------------------------------------------------------

#if !defined(__hotelMIS_HInOutRep_h)
#define __hotelMIS_HInOutRep_h


#include <string>
#include <vector>
using namespace std;

namespace hotelMIS
{
	
	class HInOutRep
	{
	public:
		enum { OUT_REP = 2, IN_REP = 1};
		HInOutRep(void);
		~HInOutRep(void);
	public:
		int		food_id;		//��Ʒ���
		string  inout_dh;		//�˵��� "RK" ,"CK"
		string	food_name;		//��Ʒ����
		string  food_unit;		//��λ
		float	food_num;		//��������
		float	food_price;		//��ⵥ��
		
		float	t_num;			//������Ȿ��Ʒ�������
		float	t_price;		//����������Ʒ�ĵ���
		float	t_sprice;		//����������Ʒ���ܽ��

		int		rep_flag;		//0: �� 1: ��
		string	opdate;			//����������ʱ��
		string	ad_name;		//������
	}; //end class HInOutRep

	class HTotalInOutRep 
	{
	public:
		HTotalInOutRep()
			:sum_price(0)
			, rep_flag(-1)
			, sdate("")
		{
		}
		~HTotalInOutRep(){}

	public:
		float sum_price;
		int	   rep_flag;
		string	sdate;
	};
} // end namespace hotelMIS
#endif