//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HAccountCtrl.h
//
// Description:    
//				ʵ�� HAccount ������ݿ����,
//			����˵���ҵ���߼�
//		
//
// Version: 1.0
//
// Hostory:		
//			05-6-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#if !defined(__hotelMIS_HAccountCtrl_h)
#define __hotelMIS_HAccountCtrl_h

#include "config.h"
#include <HAccount.h>
#include <string>
using namespace std;

namespace hotelMIS{
	
	// *** global ***
	typedef vector<HAccount> HAccountVec;  //HAccount ���м�
	typedef vector<HTotalAccount> HTotalAccountVec; 
	/*---------------------------------------------------------------------------------------------------
	*	class HAccountCtrl
	*		member function
	*			//
	*			// �޸Ķ���
	*			void updateSubscription(string accountId, float subscription);
	*			
	*			// �����˵����޸��������ں�ʱ��
	*			void updateRepDateAndTime(string accountId,string date,string time);	
	*
	*			// ȡ���˵�
	*			void cancel(string accountId);
	*			
	*			// ���ص������ѵ��˵�����
	*			int getNowCnt(void);
	*			
	*			// �����˵���ȡ�ض���
	*			float getSubscription(string accountId);
	*			
	*			// �����˵���ȡ���˵�����ϸ����
	*			HAccount getAccount(string accountId);
	*			
	*			// �����������˵���ϸ
	*			vector<HAccount> getAllAccount();
	*			
	*			// ���ص�����˵���ϸ
	*			vector<HAccount> getByDay(string day);
	*			
	*			// �����µ��˵���ϸ
	*			vector<HAccount> getByMonth(string year,string month);
	*			
	*			// ��������˵���ϸ
	*			vector<HAccount> getByYear(string year);
	*
	*			// ���� sData �� eDate �������� ״̬Ϊ accStatus ���˵���ϸ
	*			vector<HAccount> search(string sDate,string eDate,int accStatus);
	*			   parameter:
	*					accStatus Ϊ 
	*						enum {	notAcc=0,			//δ����
	*								havedAcc=1,			//�ѽ���
	*								cancelAcc=-1		//�˵�
	*						 }; 
	*					 �е�ֵ
	*
	*			// ���ر��˵��ŵ����ѽ��
	*			float getPriceByAccountId(string accountId);
	*
	*			// ���˽���
	*			bool gzJZ(string accountId,float* restMoney,int reckoning,string date,string time);
	*				parameter :
	*						accoutId	string	[in]		�˵���
	*						restMoney	float*	[in/out]	���˺��ʣ����
	*						reckoning	int		[in]		1: ��Ҫ��Ʊ 0: ����Ҫ��Ʊ
	*						date		string	[in]		��������
	*						time		string	[in]		����ʱ��
	*---------------------------------------------------------------------------------------------------*/

	class HAccountCtrl
	{
	public:
		// Construct / Destruct
		HAccountCtrl(mysqlpp::Connection * pCon);
		~HAccountCtrl();
	public:
		// *** ���ݿ�������� ***
		void insert(HAccount& account);
		void update(HAccount& account);
		void Delete(string accountId);
		void DeleteAll();	
		
		// *** ҵ���߼� ***
		void updateSubscription(string accountId, float subscription);
		void updateRepDateAndTime(string accountId,string date,string time);	

		void cancel(string accountId);
		int getNowCnt(void);
		float getSubscription(string accountId);
		
		HAccount getAccount(string accountId);
		
		vector<HAccount> getAllAccount();
		vector<HAccount> getByDay(string sDate,string eDate,int jsfs);
		vector<HAccount> getByMonth(string year,string month);
		vector<HAccount> getByYear(string year);

		//for acc
		vector<HAccount> search(string sDate,string eDate,int accStatus,int arid=0,int cw=0,int jsfs=0);

		float getPriceByAccountId(string accountId);

		bool gzJZ(string accountId,float* restMoney,int reckoning,string date,string time);
		
		// ��Ա������
		void memberJz(string accountId,float czmoney,string mbh);

		//HAccountVec totalByDateTime(string start_dtime,string end_dtime); 
		HTotalAccountVec totalByPayStatus(string start_dtime,string end_dtime);

		// ���� ����ͳ��
		HTotalAccountVec totalByPayStatus(string year,string month,int bf);
		
		// ���� ����ͳ��
		HTotalAccountVec totalByPayStatus(string year);
		
		// ����������
		HAccountVec getAccount(string d1,string d2,string bh);

	private:
		void _fill_(HAccount &acc,mysqlpp::Result &res);
		void _fill_vec(HAccountVec &vec,mysqlpp::Result &res);
		mysqlpp::Connection * _pCon;
	};
}
#endif