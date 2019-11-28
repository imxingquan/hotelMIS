//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File: HBeforeRepCtrl.cpp
// 
// Desc: 
//
// Author:  xq
//
// Modified: 2006Äê6ÔÂ10ÈÕ 20:59:26
//--------------------------------------------------------------------------------------

#include "stdAfx.h"
#include "HBeforeRepCtrl.h"

using namespace hotelMIS;

//--------------------------------------------------------------------------------------
HBeforeRepCtrl::HBeforeRepCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

//--------------------------------------------------------------------------------------
HBeforeRepCtrl::~HBeforeRepCtrl()
{
}

//--------------------------------------------------------------------------------------
void HBeforeRepCtrl::insert(int food_id,float food_num )
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_beforerep (food_id,rep_num) VALUES("
			 << food_id << "," 
			 << food_num << ")";
		query.execute();
	}mycatch();
}

//-------------------------------------------------------------------------------------
void HBeforeRepCtrl::Delete(int food_id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_beforerep WHERE food_id =" << food_id;
		query.execute();
	}mycatch();
    
}

//-------------------------------------------------------------------------------------
void HBeforeRepCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_beforerep";
		query.execute();
	}mycatch();
}
//--------------------------------------------------------------------------------------
void HBeforeRepCtrl::beforeOutRep(int food_id, float food_num)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"UPDATE t_beforerep SET rep_num = rep_num -"<<food_num
			<< " WHERE food_id = "<<food_id;
		query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------
void HBeforeRepCtrl::modifyBeforeRep(int food_id,float food_num)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"UPDATE t_beforerep SET rep_num = rep_num +"<<food_num
			<< " WHERE food_id = "<< food_id;
		query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------
float HBeforeRepCtrl::getCurRep(int food_id)
{
	float nCurRep = 0;
	try{
			mysqlpp::Query query = _pCon->query();
			query << "SELECT rep_num FROM t_beforerep WHERE food_id="<< food_id;
			mysqlpp::Result res = query.store();
			if ( !res.empty() ){
				mysqlpp::Row row = *res.begin();
				nCurRep = row.lookup_by_name("rep_num");
			}
	}mycatch();
	return nCurRep;
}

//------------------------------------------------------------------------------------
bool HBeforeRepCtrl::isExist(int food_id)
{
	try{
		mysqlpp::Query  query = _pCon->query();
		query << "SELECT food_id FROM t_beforerep WHERE food_id="<<food_id;
		mysqlpp::Result res = query.store();
		if ( !res.empty())
			return true;
	}mycatch();
	return false;
}
