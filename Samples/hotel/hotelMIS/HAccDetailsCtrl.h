//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HAccDetailsCtrl.h
//
// Description:    
//			   ʵ�ֶ�HAccDetails ������ݿ����,
//		ͳ�ƾ�Ӫ�����˲˵���ϸ��¼
//
// Version: 1.0
//
// Hostory:		
//			05-8-2005	��Ȫ	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HAccDetailsCtrl_h)
#define __hotelMIS_HAccDetailsCtrl_h

#include <HAccDetails.h>
#include <HTotalByCook.h>
#include "config.h"

namespace hotelMIS{

	// *** global ***
	typedef vector<HTotalByCook> HTotalByCookVec;	//���ݳ�ʦ��������ͳ�ƽ��
	typedef vector<HAccDetails> HAccDetailsVec;		//HAccDetails�ļ���

	/*+--------------------------------------------------------------------------------
	*	 class HAccDetailsCtrl
	*
	*      member function:
	*		
	*		//�����˵��ŷ�����ʷ������ϸ�б�
	*		vector<HAccDetails> getAccDetails(string accountId);	
	*		
	*		//����ͳ�Ƴ�ʦ��������
	*		vector<HTotalByCook> getByDayCkName(string day);
	*		
	*		//������ͳ�Ƴ�ʦ��������
	*		vector<HTotalByCook> getByMonthCkName(string year,string month);
	*		
	*		//����ͳ�Ƴ�ʦ��������
	*		vector<HTotalByCook> getByYearCkName(string year);
	*
	*		//��ָ������������ͳ���˲˵���ϸ�嵥
	*		HAccDetailsVec GetCancelMenuByDate(string date1,string date2);
	*
	*
	----------------------------------------------------------------------------------*/

	class HAccDetailsCtrl
	{
	public:
		// Construct /Destruct
		HAccDetailsCtrl(mysqlpp::Connection* pCon);
		~HAccDetailsCtrl();

		//
		// ���ݿ�Ļ�������
		//
		void insert(HAccDetails accDetails);
		void update(HAccDetails accDetails);
		void Delete(string accountId, string foodName);
		void Delete(string accountId);
		void DeleteAll();

		//
		// ҵ�����
		//
		vector<HAccDetails> getAccDetails(string accountId);
		vector<HTotalByCook> getByDayCkName(string day);
		vector<HTotalByCook> getByMonthCkName(string year,string month);
		vector<HTotalByCook> getByYearCkName(string year);
		HAccDetailsVec GetCancelMenuByDate(string date1,string date2);


	private:
		mysqlpp::Connection * _pCon;	 //���ݿ�����

	}; // end class HAccDetailsClass

} // end namespace hotelMIS
#endif