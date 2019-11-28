/***********************************************************************
 * Module:  HRepastCtrl.cpp
 * Author:  babala
 * Modified: 2005��5��6�� 22:31:20
 * Purpose: Implementation of the class HRepastCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HRepastCtrl.h"
#include <cassert>
using namespace std;
using namespace hotelMIS;

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::HRepastCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HRepastCtrl::HRepastCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HRepastCtrl::HRepastCtrl(mysqlpp::Connection * pCon)
{
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::~HRepastCtrl()
// Purpose:    Implementation of HRepastCtrl::~HRepastCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepastCtrl::~HRepastCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::insert(HRepast& rep)
// Purpose:    Implementation of HRepastCtrl::insert()
// Parameters:
// - rep
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepastCtrl::insert(HRepast& rep)
{
   // TODO : ����
   try{
         mysqlpp::Query query  = _pCon->query();
         query << "INSERT INTO t_Repast (account_id,table_id,cust_date,cust_time,room_id,re_state)VALUES('"
                     << rep.account_id << "',"
                     << rep.table_id << ",'"
                     << rep.cust_date <<"','"
                     << rep.cust_time <<"',"
                     << rep.room_id <<","
                     << rep.re_state <<")";
          query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::Delete(string accountId)
// Purpose:    Implementation of HRepastCtrl::Delete()
// Parameters:
// - accountId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepastCtrl::Delete(string accountId)
{
   // TODO : ɾ��
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_Repast  WHERE account_id = '"
                     << accountId<<"'";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::getRepastState(int tableId, int roomId)
// Purpose:    Implementation of HRepastCtrl::getRepastState()
// Comment:    ��þͲ�״̬
// Parameters:
// - tableId
// - roomId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepastCtrl::getRepastState(int tableId, int roomId)
{
   // TODO : ���ز���״̬
	/*	0: ����
		1: �Ͳ�
		2: Ԥ��
	*/
	int re_state = 0;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT re_state FROM t_Repast WHERE table_id = " << tableId
			<< " AND room_id = " << roomId;
		mysqlpp::Result res = query.store();
		if (!res.empty() ){
			mysqlpp::Row row;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			re_state = row.lookup_by_name("re_state");
		}
	}mycatch();
	return re_state;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::getAccountId(int tableId, int roomId)
// Purpose:    Implementation of HRepastCtrl::getAccountId()
// Parameters:
// - tableId
// - roomId
// Return:     string
////////////////////////////////////////////////////////////////////////

string HRepastCtrl::getAccountId(int tableId, int roomId)
{
   // TODO : implement
   string accountId = "";
   try{
      mysqlpp::Query query  = _pCon->query();
      query << "SELECT account_id FROM t_repast WHERE table_id = " 
                  << tableId << " AND room_id = " << roomId;
       mysqlpp::Result res = query.store();
       if ( !res.empty() ){
            mysqlpp::Row row;
            mysqlpp::Result::iterator it = res.begin();
            row = *it;
            accountId = row.lookup_by_name("account_id");
       }
   }mycatch();
   return accountId;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::chgTable(string accountId, int tableId, int roomId)
// Purpose:    Implementation of HRepastCtrl::chgTable()
// Comment:    ���� 
// Parameters:
// - accountId
// - tableId
// - roomId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepastCtrl::chgTable(int srcTableId,int destTableId,int srcRoomId, int destRoomId)
{
   // TODO : ���� ����-1ΪĿ����������
   try{
	     assert( !isEmptyTable(srcTableId,srcRoomId));  //Դ����Ϊ��
		 assert( isEmptyTable(destTableId,destRoomId)); //Ŀ����Ϊ��
		 
		 if ( ! isEmptyTable(srcTableId,srcRoomId) && isEmptyTable(destTableId,destRoomId) ){
			mysqlpp::Query query = _pCon->query();
			query << "UPDATE t_Repast SET table_id ="<< destTableId
                     << ",room_id ="<< destRoomId
					 <<" WHERE table_id = "<< srcTableId 
                     <<" AND room_id = "<<srcRoomId;
			query.execute();
			if ( query.success() )
			return destTableId;
		 }
   }mycatch();
   return -1;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::isEmptyTable(int tableId, int roomId)
// Purpose:    Implementation of HRepastCtrl::isEmptyTable()
// Parameters:
// - tableId
// - roomId
// Return:     int
////////////////////////////////////////////////////////////////////////

bool HRepastCtrl::isEmptyTable(int tableId, int roomId)
{
   // TODO : ���roomid�Ĳ����Ƿ�Ϊ��,Ϊ�շ���1,���򷵻�0
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT table_id FROM t_Repast WHERE table_id = "
                     << tableId << " AND room_id = "
                     << roomId ;
         mysqlpp::Result res = query.store();
         if ( ! res.empty()){
            return false;
         }
   }mycatch();
   return true;
}
HRepast HRepastCtrl::getRepast(string accountId)
{
	HRepast rep;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_Repast WHERE account_id = '"<< accountId << "'";
		mysqlpp::Result res = query.store();
		if ( ! res.empty() ){
			mysqlpp::Row row;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			rep.account_id = accountId;
			rep.cust_date = row.lookup_by_name("cust_date");
			rep.cust_time = row.lookup_by_name("cust_time");
			rep.re_state = row.lookup_by_name("re_state");
			rep.room_id = row.lookup_by_name("room_id");
			rep.table_id = row.lookup_by_name("table_id");

		}
	}mycatch();
	return rep;
}



void HRepastCtrl::chgState(int tableId, int roomId, int state)
{
	   // TODO : �ı�Ͷ�״̬(����,����,�Ͳ�)
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_Repast SET re_state ="<< state
                     << " WHERE table_id = "<<tableId
                     <<" AND room_id =" << roomId;
		 query.execute();
   }mycatch();
}

void HRepastCtrl::updateRepDateAndTime(string accountId,string date,string time)
{
	//TODO: ���ľͲ�����
	try{
		mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_repast SET cust_date='"
                     << date <<"', cust_time='"
					 << time <<"' WHERE account_id = '"
                     << accountId << "'";
        query.execute();   
	}mycatch();
}

pair<int,int> HRepastCtrl::getTableIdAndRoomId(string accountId)
{
	pair<int,int> tableIdAndroomId;
	try{
		
		mysqlpp::Query query = _pCon->query();
		query << "SELECT table_id,room_id FROM t_repast WHERE account_id = '"
				<< accountId << "'";
		mysqlpp::Result res = query.store();
		if (! res.empty() ){
			mysqlpp::Row row ;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			int table_id = row.lookup_by_name("table_id");
			int room_id = row.lookup_by_name("room_id");
			tableIdAndroomId = make_pair(table_id,room_id);
		}
	}mycatch();
	return tableIdAndroomId;
}
void HRepastCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_repast";
		query.execute();
	}mycatch();
}