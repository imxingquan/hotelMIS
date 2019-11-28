//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBehindRepCtrl.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2006��6��10�� 9:54:22
//-----------------------------------------------------------------------

#if !defined(__hotelMIS_HBehindRepCtrl_h)
#define __hotelMIS_HBehindRepCtrl_h

#include "config.h"
#include "HBehindRep.h"
#include <math.h>
#include <float.h>
namespace hotelMIS{
	
	typedef vector<HBehindRep> HBehindRepVec;

	class HBehindRepCtrl
	{
	public:
		HBehindRepCtrl(mysqlpp::Connection *pCon);
		~HBehindRepCtrl();

	public:
		 //��������
		void insert(HBehindRep &behindRep);
		void insert(int food_id);
		void Delete(int food_id);
		void DeleteAll();
		
		//���������
		int outRep(void);
		
		// ���� food_id ���ؿ����
		float getCurRep(int food_id);

		// ���� food_id ���س��ⵥ��
		float getOutPrice(int food_id);

		// �ж��Ƿ��Ѿ���
		bool isExist(int food_id);

		//���� food_id ���ؿ��
		HBehindRep getByfoodId(int food_id);

		// �������������͵��ۼ��㱾��
		HBehindRep calc(int food_id,float num,float price,int repertory_flag);
		
		//��
		void update(HBehindRep &behindRep);

		//��ѯ
		HBehindRepVec search(int food_id);
		HBehindRepVec search(string name_or_jm);

		HBehindRepVec getAll();
	protected:
		inline long double roundl(long double d,short dec){ 
			long double div=powl(10,dec);
			d*=div;
			d*=(1.+LDBL_EPSILON); 
			__asm{ 
				fld d 
					frndint
					fstp d
			}
			return d/div; 
		}  

		inline double round(double d,short dec){ 
			double div=pow(10.,dec);
			d*=div;
			d*=(1.+DBL_EPSILON); 
			__asm{ 
				fld d 
					frndint
					fstp d
			}
			return d/div; 
		}  
	private:
		mysqlpp::Connection *_pCon;

	};
}

#endif