/***********************************************************************
 * Module:  HRepastCtrl.cpp
 * Author:  babala
 * Modified: 2005��5��6�� 22:31:20
 * Purpose: Implementation of the class HRepastCtrl
 ***********************************************************************/

#include "HRepastCtrl.h"

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
                     << room_id <<","
                     << re_state <<")";
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
         mysqlpp::Query query = _pCon->query():
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
      query << "SELECT accound_id FROM t_repast WHERE table_id = " 
                  << tableId << "AND room_id = " << roomId;
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

int HRepastCtrl::chgTable(string accountId, int tableId, int roomId)
{
   // TODO : ���� ����0ΪĿ����������
   try{
         if ( isEmptyTable(tableId,roomId) ){
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_Repast SET table_id ="<<tableId
                     << " WHERE account_id = '"<<accountId<<"'";
          return 1;
         }
       
   }mycatch();
   return 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepastCtrl::isEmptyTable(int tableId, int roomId)
// Purpose:    Implementation of HRepastCtrl::isEmptyTable()
// Parameters:
// - tableId
// - roomId
// Return:     int
////////////////////////////////////////////////////////////////////////

int HRepastCtrl::isEmptyTable(int tableId, int roomId)
{
   // TODO : ���roomid�Ĳ����Ƿ�Ϊ��,Ϊ�շ���1,���򷵻�0
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT tableId FROM t_Repast WHERE table_id = "
                     << tableId << " AND room_id = "
                     << roomId ;
         mysqlpp::Result res = query.store();
         if ( ! res.empty()){
            return 1;
         }
   }mycatch();
   return 0;
}