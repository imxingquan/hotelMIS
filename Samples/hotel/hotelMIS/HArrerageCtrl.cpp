#include "stdAfx.h"
#include "HArrerageCtrl.h"

using namespace hotelMIS;

HArrerageZHCtrl::HArrerageZHCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HArrerageZHCtrl::~HArrerageZHCtrl()
{
}

void HArrerageZHCtrl::insertZH(HArrerageZH arrerageZH)
{
	try{
		 mysqlpp::Query query = _pCon->query();
		 query << "INSERT INTO t_arrerage_zh (guest_name,guest_phone,guest_dept,ar_memo,cw) VALUES('"
			 << arrerageZH.guest_name << "','"
			 << arrerageZH.guest_phone <<"','"
			 << arrerageZH.guest_dept <<"','"
			 << arrerageZH.ar_memo << "',"
			 << arrerageZH.cw <<")";
		 query.execute();
	}mycatch();
}

void HArrerageZHCtrl::DeleteZH(int arid)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_arrerage_zh WHERE ar_id = " << arid;
		query.execute();
	}mycatch();
}

void HArrerageZHCtrl::updateZH(HArrerageZH arrerageZH)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_arrerage_zh SET guest_name = '"
			<< arrerageZH.guest_name 
			<<"', guest_phone = '"
			<< arrerageZH.guest_phone
			<<"',"
			<< "guest_dept ='"
			<< arrerageZH.guest_dept 
			<<"', ar_memo ='"
			<< arrerageZH.ar_memo 
			<<"',cw="
			<< arrerageZH.cw
			<< " WHERE ar_id = "
			<< arrerageZH.arid;
		query.execute();
	}mycatch();
}

hotelMIS::HArrerageZHVec HArrerageZHCtrl::getAll()
{
	HArrerageZHVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_arrerage_zh WHERE ar_id !=0";
		mysqlpp::Result res = query.store();
        mysqlpp::Result::iterator it;
        mysqlpp::Row row;
		HArrerageZH arrZH;
		for ( it = res.begin(); it != res.end() ; it++)
		{
			row = *it;
			arrZH.arid = row.lookup_by_name("ar_id");
			arrZH.guest_name = row.lookup_by_name("guest_name");
			arrZH.guest_phone = row.lookup_by_name("guest_phone");
			arrZH.guest_dept = row.lookup_by_name("guest_dept");
			arrZH.ar_memo = row.lookup_by_name("ar_memo");
			arrZH.cw = row.lookup_by_name("cw");
			vec.push_back(arrZH);
		}
	}mycatch();
	return vec;
}

HArrerageZH HArrerageZHCtrl::getArrerageZH(int arid)
{
	HArrerageZH arrZH;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_arrerage_zh WHERE ar_id = " << arid;
		mysqlpp::Result res = query.store();
		if (! res.empty()){
			mysqlpp::Result::iterator it = res.begin();	
			mysqlpp::Row row = *it;
			arrZH.arid = arid;
			arrZH.guest_name = row.lookup_by_name("guest_name");
			arrZH.guest_phone = row.lookup_by_name("guest_phone");
			arrZH.guest_dept = row.lookup_by_name("guest_dept");
			arrZH.ar_memo = row.lookup_by_name("ar_memo");
			arrZH.cw = row.lookup_by_name("cw");
		}
	}mycatch();
	return arrZH;
}

bool HArrerageZHCtrl::isExitGZName(string gzName)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT guest_name FROM t_arrerage_zh WHERE guest_name ='"<<gzName<<"'";
		mysqlpp::Result res = query.store();
		if ( ! res.empty() )
			return true;
	}mycatch();
	return false;
}

void HArrerageZHCtrl::setJZRest(int arid,float price)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_arrerage_zh SET guest_rest = "<<price<<" WHERE ar_id = " << arid;
		query.execute();
	}mycatch();
}



float HArrerageZHCtrl::getJZRest(int arid)
{
	float retVal =0.0f;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT guest_rest FROM t_arrerage_zh WHERE ar_id = "<< arid;
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it = res.begin();
        mysqlpp::Row row;
		if ( ! res.empty() ){
			row = *it;
			retVal = row.lookup_by_name("guest_rest");
		}
	}mycatch();
	return retVal;
}

void HArrerageZHCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_arrerage_zh";
		query.execute();
	}mycatch();
}

//------╧рук---------------------
HArrerageCtrl::HArrerageCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HArrerageCtrl::~HArrerageCtrl()
{

}

void HArrerageCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_arrerage ";
		query.execute();
	}mycatch();
}

void HArrerageCtrl::insert(HArrerage arrerage)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_arrerage (ar_id,account_id,ar_date) VALUES("
			<< arrerage.arid << ",'"<< arrerage.account_id 
			<< "','"<<arrerage.ar_date <<"')";
		query.execute();
	}mycatch();
}

void HArrerageCtrl::Delete(int arid)
{
	mysqlpp::Query query = _pCon->query();
	query << "DELETE FROM t_arrerage WHERE arid = " << arid ;
	query.execute();
}

HArrerageVec HArrerageCtrl::getAll()
{
	HArrerageVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_arrerage";
		mysqlpp::Result res= query.store();
		mysqlpp::Result::iterator it;
        mysqlpp::Row row;
		HArrerage arr;
		for ( it = res.begin(); it != res.end() ; it++)
		{
			row = *it;
			arr.arid = row.lookup_by_name("ar_id");
			arr.account_id = row.lookup_by_name("account_id");
			arr.ar_date = row.lookup_by_name("ar_date");
			vec.push_back(arr);
		}
	}mycatch();
	return vec;
}

HArrerageVec HArrerageCtrl::getByArId(int arid)
{
	HArrerageVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_arrerage WHERE ar_id = "<< arid ;
		mysqlpp::Result res= query.store();
		mysqlpp::Result::iterator it;
        mysqlpp::Row row;
		HArrerage arr;
		for ( it = res.begin(); it != res.end() ; it++)
		{
			row = *it;
			arr.arid = row.lookup_by_name("ar_id");
			arr.account_id = row.lookup_by_name("account_id");
			arr.ar_date = row.lookup_by_name("ar_date");
			vec.push_back(arr);
		}
	}mycatch();
	return vec;
}

void HArrerageCtrl::DeleteByAccountId(string accountId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"DELETE FROM t_arrerage WHERE account_id ='"<<accountId << "'";
		query.execute();
	}mycatch();
}

void HArrerageCtrl::writeArrIdtoAccount(int arid,string accountId)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_account SET arid = "<<arid<<" WHERE account_id = '" << accountId<<"'";
		query.execute();
	}mycatch();
}