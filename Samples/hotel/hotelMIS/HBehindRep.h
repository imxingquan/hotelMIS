//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HBehindRep.h
// 
// Desc: ������
//
// Author:  ��Ȫ
//
// Modified: 2006�� 06 �� 14 ��
//--------------------------------------------------------------------------------------

#if !defined(__hotelMIS_HBehindRep_h)
#define __hotelMIS_HBehindRep_h

namespace hotelMIS
{
	class HBehindRep
	{
	public:
		enum { OUT_REP = 2, IN_REP = 1};
		HBehindRep(void);
		~HBehindRep(void);

	public:
		int		food_id;		//��Ʒ���
		float	rep_num;		//��������
		float	food_price;		//���ⵥ�۱仯��	���� = ��� / ����
		float	total_price;	//�ܽ��

	}; // end class HBehindRep

}//end namespace hotelMIS
#endif