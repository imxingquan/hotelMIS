//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBeforeRep.h
// 
// Desc: ǰ̨����
//
// Author:  ��Ȫ
// 
// Modified: 2006��6��10�� 9:57:42
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HBeforeRep_h)
#define __hotelMIS_HBeforeRep_h

namespace hotelMIS{
	class HBeforeRep
	{
	public:
		HBeforeRep();
		~HBeforeRep();

	public:
		int food_id;	//��Ʒ���
		float rep_num;	//�������
	}; //end class
}; //end namespace hotelMIS

#endif