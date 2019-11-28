//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HBehindRep.cpp
// 
// Desc: 
//
// Author:  ��Ȫ
//
// Modified: 2006�� �� ��
//--------------------------------------------------------------------------------------


#if !defined(__hotelMIS_HInOutRepCtrl_h)
#define __hotelMIS_HInOutRepCtrl_h

#include "config.h"
#include "HInOutRep.h"

namespace hotelMIS
{
	typedef vector<HInOutRep> HInOutRepVec;
	typedef vector<HTotalInOutRep> HTotalInOutRepVec;

	class HInOutRepCtrl
	{
	public:
		HInOutRepCtrl(mysqlpp::Connection *pCon);
		~HInOutRepCtrl();

	public:
		//��������
		void insert(HInOutRep &rep);
		
		//void update(HInOutRep &rep);

		void DeleteAll();
		
		//���
		void enter(list<HInOutRep> &repList);
		
		////����
		//void leave(list<HInOutRep> &repList);
		//��������������µ�ǰ̨
		void updateBeforeRep(list<HInOutRep> &repList);

		// ���� food_id ���� ������¼
		HInOutRepVec search(int food_id,string dt1,string dt2);

		//�������ڻ��ܿ��
		HTotalInOutRepVec totalByDate(string d1,string d2);

		//�������ڼ��������س�����˵�
		HInOutRepVec search(string d1,string d2,int inoutflag=-1);

		//�����˵��ŷ��ر��˵��ŵ����м�¼
		HInOutRepVec search(string inout_dh);

		//�������г�����¼
		HInOutRepVec getAllInOutRec(string dt1,string dt2);
	protected:
		void _fill(HInOutRep &rep,mysqlpp::Result &res);
		void _fill_vec(HInOutRepVec &vec,mysqlpp::Result &res);
	private:
		mysqlpp::Connection *_pCon;

	};// end class 
}//end namespace hotelMIS

#endif