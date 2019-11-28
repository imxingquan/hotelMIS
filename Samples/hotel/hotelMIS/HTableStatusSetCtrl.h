//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HTableStatusSetCtrl.h
//
// Description:    
//				HTabelStatusSet ������ݿ������
//				
// Version: 1.0
//
// Hostory:		
//			05-22-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HTableStatusSetCtrl_h)
#define __hotelMIS_HTableStatusSetCtrl_h

#include "config.h"
#include "HTableStatusSet.h"
#include <vector>

using namespace std;

namespace hotelMIS{

	//*** global ***
	typedef vector<HTableStatusSet> HTableStatusSetVec;
	
	/*----------------------------------------------------------------------------------------
	* class HTableStatusSetCtrl
	*	
	*	member function:
	*		
	*		// ���ز���״̬
	*		getHTableStatus(int tableState);
	*
	*		// �������в���״̬
	*		getAllTableStatusSet();
	*
	*		// ���ؿղ�����ͼƬ id
	*		getTableEmptyBmp(int tableState);
	*	
	*		// ���ؾͲ�״̬ͼƬ
	*		getTableRepastBmp(int tableState);
	*		
	*		// ���ò���״̬ͼƬ
	*		SetTaleBmp(int tableState, int bmpIndex);
	*/
	
	class HTableStatusSetCtrl
	{
	public:
		// Construct/Destruct
		HTableStatusSetCtrl(mysqlpp::Connection *pCon);
		~HTableStatusSetCtrl();
		
		// *** ���ݿ�Ļ������� ***
		void insert(string stateName,int personNum);
		void update(HTableStatusSet& tableSset);
		void delete0(int tssate);
		
		HTableStatusSet getHTableStatus(int tableState);
		
		vector<HTableStatusSet> getAllTableStatusSet();
		
		int getTableEmptyBmp(int tableState);
		int getTableRepastBmp(int tableState);
		void SetTaleBmp(int tableState, int bmpIndex);

	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif