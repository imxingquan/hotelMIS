//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HTableStatusSetCtrl.cpp
//
// Description:    
//				HTabelStatusSetCtrl.h ���ʵ��
//				
// Version: 1.0
//
// Hostory:		
//			05-22-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HTableStatusSetCtrl.h"

using namespace hotelMIS;


HTableStatusSetCtrl::HTableStatusSetCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}


HTableStatusSetCtrl::~HTableStatusSetCtrl()
{
   
}

//
// ����
//
void HTableStatusSetCtrl::insert(string stateName,int personNum)
{
   
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_tableStatusSet (state_name,person_num) VALUES('"
			<< stateName << "',"<<personNum<<")";
		query.execute();
	}mycatch();
}


//
// �޸�
//
void HTableStatusSetCtrl::update(HTableStatusSet& tableSset)
{
   // TODO : implement
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_tableStatusSet SET state_name = '"<<tableSset.getState_name()
			<<"',person_num="<<tableSset.getPerson_num()<<" WHERE table_state = " << tableSset.getTable_state();
		query.execute();
	}mycatch();
}

//
// ɾ��
//
void HTableStatusSetCtrl::delete0(int tssate)
{
   // TODO : implement
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"DELETE FROM t_tableStatusSet WHERE table_state = " << tssate;
		query.execute();
	}mycatch();
}

//
// ���ز���״̬
//
HTableStatusSet HTableStatusSetCtrl::getHTableStatus(int tableState)
{
	HTableStatusSet tableStatusSet;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_tableStatusSet WHERE table_state = " << tableState;
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		int tableState = -1;
		string stateName ="";
		int personNum = -1;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			tableState = row.lookup_by_name("table_state");
			string stateName = row.lookup_by_name("state_name");
			personNum = row.lookup_by_name("person_num");
			tableStatusSet.setTable_state(tableState);
			tableStatusSet.setState_name(stateName);
			tableStatusSet.setPerson_num(personNum);
		}
	}mycatch();
	return tableStatusSet;
}

//
// �������в���״̬
//
vector<HTableStatusSet> HTableStatusSetCtrl::getAllTableStatusSet()
{
	vector<HTableStatusSet> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_tableStatusSet ORDER BY table_state ";
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		int tableState=-1;
		string stateName="";
		int personNum=-1;
		for ( it = res.begin(); it != res.end(); ++it)
		{
			HTableStatusSet tableStatusSet;
			
			row = *it;
			tableStatusSet.table_state= row.lookup_by_name("table_state");
			tableStatusSet.state_name = row.lookup_by_name("state_name");
			tableStatusSet.person_num = row.lookup_by_name("person_num");
			tableStatusSet.empty_bmp  = row.lookup_by_name("empty_bmp");
			tableStatusSet.repast_bmp = row.lookup_by_name("repast_bmp");

			vec.push_back(tableStatusSet);
		}
	}mycatch();
	return vec;
}

//
// ���ؿղ�����ͼƬ id
//
int HTableStatusSetCtrl::getTableEmptyBmp(int tableState)
{
	int n = -1;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT empty_bmp FROM t_tableStatusSet WHERE table_state =" << tableState;
		mysqlpp::Result res = query.store();
		if (  !res.empty()){
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			n = row.lookup_by_name("empty_bmp");
		}	
	}mycatch();
	return n;
}

//
// ���ؾͲ�״̬ͼƬ
//
int HTableStatusSetCtrl::getTableRepastBmp(int tableState)
{
int n = -1;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT repast_bmp FROM t_tableStatusSet WHERE table_state =" << tableState;
		mysqlpp::Result res = query.store();
		if (  !res.empty()){
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			n = row.lookup_by_name("repast_bmp");
		}	
	}mycatch();
	return n;
}

//
// ���ò���״̬ͼƬ
//
void HTableStatusSetCtrl::SetTaleBmp(int tableState, int bmpIndex)
{
	try{
		mysqlpp::Query query = _pCon->query();
		bmpIndex = bmpIndex *2;
		query << "UPDATE t_tableStatusSet SET empty_bmp = "<< bmpIndex 
			<<", repast_bmp = "<< bmpIndex +1 
			<<" WHERE table_state = " << tableState;
		query.execute();
	}mycatch();
}