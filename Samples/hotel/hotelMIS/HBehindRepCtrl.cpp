//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File: HBehindRepCtrl.cpp
// 
// Desc: 
//
// Author:  xq
//
// Modified: 2006年6月10日 9:54:22
//-----------------------------------------------------------------------
#include "StdAfx.h"
#include "HBehindRepCtrl.h"
#include <cassert>
using namespace std;
using namespace hotelMIS;

//--------------------------------------------------------------------------------------------
HBehindRepCtrl::HBehindRepCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

//--------------------------------------------------------------------------------------------
HBehindRepCtrl::~HBehindRepCtrl()
{
}


//--------------------------------------------------------------------------------------------
 //基础操作
void HBehindRepCtrl::insert(HBehindRep &behindRep)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_behindrep  ( food_id, rep_num,next_out_price,total_price) VALUES("
			  << behindRep.food_id << ","
			  << behindRep.rep_num<<","
			  << behindRep.food_price << ","
			  << behindRep.total_price<<")";
			query.execute();
	}mycatch();

}

//-------------------------------------------------------------------------------------------
void HBehindRepCtrl::insert(int food_id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_behindrep ( food_id ) VALUES("
			<< food_id << ")";
		query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------------
void HBehindRepCtrl::Delete(int food_id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_behindrep WHERE food_id ="<<food_id;
			query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------------
void HBehindRepCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_behindrep ";
			query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------------
int HBehindRepCtrl::outRep(void)
{
	return 0;
}

//---------------------------------------------------------------------------------------------
float HBehindRepCtrl::getCurRep(int food_id)
{
	float nCurRep = 0;
	try{
		mysqlpp::Query query  = _pCon->query();
		query << "SELECT rep_num FROM t_behindRep WHERE food_id = " << food_id;
		mysqlpp::Result res = query.store();
		if  ( !res.empty() ){
			mysqlpp::Row row = *res.begin();
			nCurRep = row.lookup_by_name("rep_num");
		}
	}mycatch();
	return nCurRep;
}

//----------------------------------------------------------------------------------------------
bool HBehindRepCtrl::isExist(int food_id)
{
	try{
		mysqlpp::Query  query = _pCon->query();
		query << "SELECT food_id FROM t_behindRep WHERE food_id="<<food_id;
		mysqlpp::Result res = query.store();
		if ( !res.empty())
			return true;
	}mycatch();
	return false;
}

//----------------------------------------------------------------------------------------------
HBehindRep HBehindRepCtrl::getByfoodId(int food_id)
{
	HBehindRep behindRep;
	try{
		mysqlpp::Query query  = _pCon->query();
		query << "SELECT * FROM t_behindRep WHERE food_id = " << food_id;
		mysqlpp::Result res = query.store();
		if  ( !res.empty() ){
			mysqlpp::Row row = *res.begin();
			behindRep.food_id = food_id;
			behindRep.food_price = row.lookup_by_name("next_out_price");
			behindRep.rep_num = row.lookup_by_name("rep_num");
			behindRep.total_price = row.lookup_by_name("total_price");
		}
	}mycatch();
	return behindRep;
}


//----------------------------------------------------------------------------------------------
HBehindRep HBehindRepCtrl::calc(int food_id,float num,float price,int repertory_flag)
{
	HBehindRep behindRep;
	try{
		behindRep = getByfoodId(food_id);
		if ( HBehindRep::IN_REP == repertory_flag)
		{
			behindRep.rep_num += num;
			behindRep.total_price += round(num * price,2);
			//if ( behindRep.rep_num == 0)
			assert( behindRep.rep_num != 0);
			behindRep.food_price = round(behindRep.total_price / behindRep.rep_num,2);
		}
		else if ( HBehindRep::OUT_REP == repertory_flag)
		{
			behindRep.rep_num -= num;
			behindRep.total_price -= round(num * price,2);
			//behindRep.food_price = behindRep.total_price / behindRep.rep_num;
		}
	}mycatch();
	return behindRep;
}

//----------------------------------------------------------------------------------------------
void HBehindRepCtrl::update(HBehindRep &behindRep)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_behindRep SET rep_num="
			<< behindRep.rep_num <<",next_out_price="
			<< behindRep.food_price <<",total_price="
			<< behindRep.total_price<<" WHERE food_id="
			<< behindRep.food_id;
		query.execute();
	}mycatch();
}

//------------------------------------------------------------------------------------------------
float HBehindRepCtrl::getOutPrice(int food_id)
{
	float price = 0.0f;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT next_out_price FROM t_behindRep WHERE food_id = "<< food_id;
		mysqlpp::Result res = query.store();
		if ( !res.empty())
		{
			mysqlpp::Row row = *res.begin();
			price = row.lookup_by_name("next_out_price");
		}
	}mycatch();
	return price;
}

//----------------------------------------------------------------------------------------------
HBehindRepVec HBehindRepCtrl::search(int food_id)
{
	HBehindRepVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT t_behindRep.food_id as food_id,food_name,rep_num,next_out_price,total_price \
				 FROM t_behindRep LEFT JOIN t_menuInfo \
				 ON t_behindRep.food_id = t_menuInfo.food_id WHERE t_behindRep.food_id = "<< food_id;
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		HBehindRep rep;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			rep.food_id = food_id;
			rep.food_price = row.lookup_by_name("next_out_price");
			rep.rep_num = row.lookup_by_name("rep_num");
			rep.total_price = row.lookup_by_name("total_price");
			vec.push_back(rep);
		}
	}mycatch();
	return vec;
}

HBehindRepVec HBehindRepCtrl::search(string name_or_jm)
{
	HBehindRepVec vec;
	try{
		mysqlpp::Query query = _pCon->query();

			query << "SELECT t_behindRep.food_id as food_id,food_name,rep_num,next_out_price,total_price \
				 FROM t_behindRep LEFT JOIN t_menuInfo \
				 ON t_behindRep.food_id = t_menuInfo.food_id WHERE food_name like '"
				 << name_or_jm
				 << "%' OR food_py like '"
				 << name_or_jm
				 << "%'";

		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		HBehindRep rep;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			rep.food_id = row.lookup_by_name("food_id");
			rep.food_price = row.lookup_by_name("next_out_price");
			rep.rep_num = row.lookup_by_name("rep_num");
			rep.total_price = row.lookup_by_name("total_price");
			vec.push_back(rep);
		}
	}mycatch();
	return vec;
}

HBehindRepVec HBehindRepCtrl::getAll()
{
	HBehindRepVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT t_behindRep.food_id as food_id,food_name,rep_num,next_out_price,total_price \
				 FROM t_behindRep LEFT JOIN t_menuInfo \
				 ON t_behindRep.food_id = t_menuInfo.food_id";
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		HBehindRep rep;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			rep.food_id = row.lookup_by_name("food_id");
			rep.food_price = row.lookup_by_name("next_out_price");
			rep.rep_num = row.lookup_by_name("rep_num");
			rep.total_price = row.lookup_by_name("total_price");
			vec.push_back(rep);
		}
	}mycatch();
	return vec;
}