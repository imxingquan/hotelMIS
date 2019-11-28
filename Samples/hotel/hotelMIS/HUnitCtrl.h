//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HUnitCtrl.h
//
// Description:    
//				HUnitSet �����ݿ������
//		
//
// Version: 1.0
//
// Hostory:		
//			04-23-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HUnitCtrl_h)
#define __hotelMIS_HUnitCtrl_h

#include "config.h"
#include "HunitSet.h"
#include <vector>

using namespace std;

namespace hotelMIS{

	// *** global ***
	typedef vector<HUnitSet> HUnitVec;

	class HUnitCtrl
	{
	public:
		//Construct / Destruct
		HUnitCtrl(mysqlpp::Connection * pCon);
		~HUnitCtrl();
	public:
		// *** ���ݿ�������� ***
		void insert(string unitName);
		void Delete(int unitId);
		
		// *** ҵ���߼� ***
		vector<HUnitSet> getAllUnit(void);
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif