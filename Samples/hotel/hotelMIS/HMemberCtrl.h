//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HMemberCtrl.h
//
// Description:    
//			   �� HMember ��Ӧ t_member ��Ļ�������
//
// Version: 1.4
//
// Hostory:		
//			06-03-2006	��Ȫ	Created	
//			
//---------------------------------------------------------

#pragma once

#include "config.h"
#include "HMember.h"

#include <vector>
using namespace std;

namespace hotelMIS{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	typedef vector<HMember> HMemberVec;

	class HMemberCtrl
	{
	public:
		//Construct /Destruct
		HMemberCtrl(mysqlpp::Connection* pCon);
		~HMemberCtrl();

	public:
//
		// ���ݿ�Ļ�������
		//
		void insert(HMember &hMember);
		void update(HMember &hMember);
		void Delete(string bh);
		void DeleteAll();
		bool isExist(string bh); //�Ѿ�����

		HMember getMember(string bh); //ȡһ��
		HMemberVec getAllMember(); //��������

		HMember getByName(string name); //����������
		
		void cz(string bh,float czmoney); //��Ա��ֵ

		void xf(string bh,float czmoney); //��Ա����

		void zz(string sbh,string dbh, float zzmoney); //��Աת��

	public:
		//ҵ�����
		
		private:
		mysqlpp::Connection * _pCon;	 //���ݿ�����

	}; //end class HMemberCtrl

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��Ա�ȼ�������
	typedef vector<HMdj> HMdjVec;
	class HMdjCtrl
	{
	public:
		//Construct/Destruct
		HMdjCtrl(mysqlpp::Connection *pCon);
		~HMdjCtrl();

	public:
		// ����
		void insert(string djname,float zhekou);
		void Delete(int id);
		void Update(int id,string djname,float zhekou);
		
		HMdj getMdj(int id);
		HMdjVec getAllMdj();
		
		void DeleteAll();

	private:
		mysqlpp::Connection *_pCon; //��������
	};//end class HMdjCtrl

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// ��Ա��ֵ��¼
	typedef vector<HMcz> HMczVec;
	class HMczCtrl
	{
	public:
		HMczCtrl(mysqlpp::Connection *pCon);
		~HMczCtrl();

	public:
		//����
		void insert(HMcz &hmcz);
		void Delete(int id);
		
		HMczVec getAllMcz();
	
		//ɾ����Ա���г�ֵ��¼
		void Delete(string bh); 

		void DeleteAll();
		
		// ��ֵ
		HMczVec getMCz(string d1,string d2,string bh);
	private:
		mysqlpp::Connection *_pCon; //��������
	}; //end class HMczCtrl

	//------------------------------------------------------------------------------------------------------
	// ��Աת����
	typedef vector<HMzz> HMzzVec;
	class HMzzCtrl
	{
	public:
		HMzzCtrl(mysqlpp::Connection *pCon);
		~HMzzCtrl();

	public:
		//����
		void insert(HMzz &hmzz);
		void Delete(int id);
		
		HMzzVec getAllMzz();

		void DeleteAll();

		//���� sbh ��������ת�˼�¼
		HMzzVec getMzz(string sbh);
		
		//������˺ŵ�ת�˼�¼
		void DeleteBySbh(string sbh);
		
		//������������ת�˼�¼
		HMzzVec getMzz(string d1,string d2,string bh);

	private:
		mysqlpp::Connection *_pCon;
		
	}; // end class HMzzCtrl
} //end namespace hotelMIS