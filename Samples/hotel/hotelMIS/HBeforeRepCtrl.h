//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBeforeRepCtrl.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2006��6��10�� 20:59:26
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HBeforeRepCtrl_h)
#define __hotelMIS_HBeforeRepCtrl_h

#include "config.h"

namespace hotelMIS{

	class HBeforeRepCtrl
	{
	public:
		HBeforeRepCtrl::HBeforeRepCtrl(mysqlpp::Connection *pCon);
		HBeforeRepCtrl::~HBeforeRepCtrl();

	public:
		//db��������
		void insert(int food_id,float food_num = 0);
		void Delete(int food_id);
		void DeleteAll();

		//ǰ̨���� -
		void beforeOutRep(int food_id, float food_num);

		//��ֵǰ̨ +
		void modifyBeforeRep(int food_id,float food_num);

		//���� ĳһ��Ʒ�ĵ�ǰ���
		float getCurRep(int food_id);

        //�жϿ�����Ƿ���ڴ���
		bool isExist(int food_id);

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}

#endif