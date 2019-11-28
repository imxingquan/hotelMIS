//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HBehindRepCtrl.h
// 
// Desc: 
//
// Author:  xq
// 
// Modified: 2006年6月10日 9:54:22
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
		 //基础操作
		void insert(HBehindRep &behindRep);
		void insert(int food_id);
		void Delete(int food_id);
		void DeleteAll();
		
		//后厨房出库
		int outRep(void);
		
		// 根据 food_id 返回库存量
		float getCurRep(int food_id);

		// 根据 food_id 返回出库单价
		float getOutPrice(int food_id);

		// 判断是否已经存
		bool isExist(int food_id);

		//根据 food_id 返回库存
		HBehindRep getByfoodId(int food_id);

		// 根据入库的数量和单价计算本次
		HBehindRep calc(int food_id,float num,float price,int repertory_flag);
		
		//入
		void update(HBehindRep &behindRep);

		//查询
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