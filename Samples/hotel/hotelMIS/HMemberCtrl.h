//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HMemberCtrl.h
//
// Description:    
//			   对 HMember 对应 t_member 表的基础操作
//
// Version: 1.4
//
// Hostory:		
//			06-03-2006	邢泉	Created	
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
		// 数据库的基本操作
		//
		void insert(HMember &hMember);
		void update(HMember &hMember);
		void Delete(string bh);
		void DeleteAll();
		bool isExist(string bh); //已经存在

		HMember getMember(string bh); //取一个
		HMemberVec getAllMember(); //返回所有

		HMember getByName(string name); //按姓名检索
		
		void cz(string bh,float czmoney); //会员充值

		void xf(string bh,float czmoney); //会员消费

		void zz(string sbh,string dbh, float zzmoney); //会员转账

	public:
		//业务操作
		
		private:
		mysqlpp::Connection * _pCon;	 //数据库连接

	}; //end class HMemberCtrl

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//会员等级控制类
	typedef vector<HMdj> HMdjVec;
	class HMdjCtrl
	{
	public:
		//Construct/Destruct
		HMdjCtrl(mysqlpp::Connection *pCon);
		~HMdjCtrl();

	public:
		// 操作
		void insert(string djname,float zhekou);
		void Delete(int id);
		void Update(int id,string djname,float zhekou);
		
		HMdj getMdj(int id);
		HMdjVec getAllMdj();
		
		void DeleteAll();

	private:
		mysqlpp::Connection *_pCon; //数据连接
	};//end class HMdjCtrl

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 会员充值记录
	typedef vector<HMcz> HMczVec;
	class HMczCtrl
	{
	public:
		HMczCtrl(mysqlpp::Connection *pCon);
		~HMczCtrl();

	public:
		//操作
		void insert(HMcz &hmcz);
		void Delete(int id);
		
		HMczVec getAllMcz();
	
		//删除会员所有充值记录
		void Delete(string bh); 

		void DeleteAll();
		
		// 充值
		HMczVec getMCz(string d1,string d2,string bh);
	private:
		mysqlpp::Connection *_pCon; //数据连接
	}; //end class HMczCtrl

	//------------------------------------------------------------------------------------------------------
	// 会员转账类
	typedef vector<HMzz> HMzzVec;
	class HMzzCtrl
	{
	public:
		HMzzCtrl(mysqlpp::Connection *pCon);
		~HMzzCtrl();

	public:
		//操作
		void insert(HMzz &hmzz);
		void Delete(int id);
		
		HMzzVec getAllMzz();

		void DeleteAll();

		//根据 sbh 返回所有转账记录
		HMzzVec getMzz(string sbh);
		
		//清除本账号的转账记录
		void DeleteBySbh(string sbh);
		
		//根据条件返回转账记录
		HMzzVec getMzz(string d1,string d2,string bh);

	private:
		mysqlpp::Connection *_pCon;
		
	}; // end class HMzzCtrl
} //end namespace hotelMIS