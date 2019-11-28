//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  HBehindRep.cpp
// 
// Desc: 
//
// Author:  邢泉
//
// Modified: 2006年 月 日
//--------------------------------------------------------------------------------------

#include "stdAfx.h"
#include "HInOutRepCtrl.h"
#include "HBehindRepCtrl.h"
#include "HBeforeRepCtrl.h"

using namespace hotelMIS;

//--------------------------------------------------------------------------------------
HInOutRepCtrl::HInOutRepCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

//--------------------------------------------------------------------------------------
HInOutRepCtrl::~HInOutRepCtrl()
{

}

//-------------------------------------------------------------------------------------
void HInOutRepCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_inoutrep";
		query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------
void HInOutRepCtrl::insert(HInOutRep &rep)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_inoutrep(food_id,inout_dh,food_name,food_unit,food_num, \
				 food_price,opdate,ad_name,t_num,t_price,t_sprice,rep_flag ) VALUES("
				 << rep.food_id<<",'"
				 << rep.inout_dh <<"','"
				 << rep.food_name <<"','"
				 << rep.food_unit <<"',"
				 << rep.food_num <<","
				 << rep.food_price <<",'"
				 << rep.opdate <<"','"
				 << rep.ad_name <<"',"
				 << rep.t_num <<","
				 << rep.t_price <<","
				 << rep.t_sprice <<","
				 << rep.rep_flag <<")";
		query.execute();
	}mycatch();
}

//--------------------------------------------------------------------------------------
void HInOutRepCtrl::_fill(HInOutRep &rep,mysqlpp::Result &res)
{
	if ( ! res.empty() ){
		mysqlpp::Row row;
		mysqlpp::Result::iterator it = res.begin();
		row = *it;
		rep.food_id = row.lookup_by_name("food_id");
		rep.inout_dh = row.lookup_by_name("inout_dh");
		rep.food_name = row.lookup_by_name("food_name");
		rep.food_unit = row.lookup_by_name("food_unit");
		rep.food_num = row.lookup_by_name("food_num");
		rep.food_price = row.lookup_by_name("food_price");
		rep.opdate = row.lookup_by_name("opdate");
		rep.ad_name = row.lookup_by_name("ad_name");
		rep.t_num = row.lookup_by_name("t_num");
		rep.t_price = row.lookup_by_name("t_price");
		rep.t_sprice = row.lookup_by_name("t_sprice");
		rep.rep_flag = row.lookup_by_name("rep_flag");
	}
}

void HInOutRepCtrl::_fill_vec(HInOutRepVec &vec,mysqlpp::Result &res)
{
	
	mysqlpp::Row row;
	mysqlpp::Result::iterator it = res.begin();
	HInOutRep rep;
	for ( ; it != res.end(); it++)
	{
		row = *it;
		rep.food_id = row.lookup_by_name("food_id");
		rep.inout_dh = row.lookup_by_name("inout_dh");
		rep.food_name = row.lookup_by_name("food_name");
		rep.food_unit = row.lookup_by_name("food_unit");
		rep.food_num = row.lookup_by_name("food_num");
		rep.food_price = row.lookup_by_name("food_price");
		rep.opdate = row.lookup_by_name("opdate");
		rep.ad_name = row.lookup_by_name("ad_name");
		rep.t_num = row.lookup_by_name("t_num");
		rep.t_price = row.lookup_by_name("t_price");
		rep.t_sprice = row.lookup_by_name("t_sprice");
		rep.rep_flag = row.lookup_by_name("rep_flag");

		vec.push_back(rep);
	}
}

//---------------------------------------------------------------------------------------------------
//void HInOutRepCtrl::update(HInOutRep &rep)
//{
//	try{
//		mysqlpp::Query query = _pCon->query();
//		query << "UPDATE t_inoutrep SET 
//	}mycatch();
//}
//----------------------------------------------------------------------------------------------------
void HInOutRepCtrl::enter(list<HInOutRep> &repList)
{
	hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
	hotelMIS::HBehindRep behindRep;
	list<HInOutRep>::iterator it = repList.begin();
	for ( ; it != repList.end(); it++)
	{
		insert(*it);
		//修改总库存
		behindRep.food_id = it->food_id;
		behindRep.rep_num = it->t_num;
		behindRep.food_price = it->t_price;
		behindRep.total_price = it->t_sprice;
		if ( behindRepCtrl.isExist(it->food_id) ){
			behindRepCtrl.update(behindRep);
		}else{
			behindRepCtrl.insert(behindRep);
		}
		
	}
}

////--------------------------------------------------------------------------------------------------------
//void HInOutRepCtrl::leave(list<HInOutRep> &repList)
//{
//	hotelMIS::HBehindRepCtrl behindRepCtrl(_pCon);
//	hotelMIS::HBehindRep behindRep;
//	list<HInOutRep>::iterator it = repList.begin();
//	for ( ; it != repList.end(); it++)
//	{
//		insert(*it);
//		//修改总库存
//		behindRep.food_id = it->food_id;
//		behindRep.rep_num = it->t_num;
//		behindRep.food_price = it->t_price;
//		behindRep.total_price = it->t_sprice;
//		if ( behindRepCtrl.isExist(it->food_id) ){
//			behindRepCtrl.update(behindRep);
//		}else{
//			behindRepCtrl.insert(behindRep);
//		}
//		
//	}
//}

//-----------------------------------------------------------------------------------------------------------
void HInOutRepCtrl::updateBeforeRep(list<HInOutRep> &repList)
{
	hotelMIS::HBeforeRepCtrl beforeRepCtrl(_pCon);
	list<HInOutRep>::iterator it = repList.begin();
	for ( ; it != repList.end(); it++)
	{
		if ( beforeRepCtrl.isExist(it->food_id) ){
			beforeRepCtrl.modifyBeforeRep(it->food_id,it->food_num);
		}
	}
}

//------------------------------------------------------------------------------------------------------------
HInOutRepVec HInOutRepCtrl::search(int food_id,string dt1,string dt2)
{
	hotelMIS::HInOutRepVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_inoutrep WHERE food_id = "
			<< food_id 
			<< " AND (opdate >='"
			<< dt1
			<<"' AND opdate <='"
			<< dt2
			<<"') ORDER BY opdate ASC";
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//----------------------------------------------------------------------------------------------------------
//返回所有的出入库记录
HInOutRepVec HInOutRepCtrl::getAllInOutRec(string dt1,string dt2)
{
	hotelMIS::HInOutRepVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_inoutrep WHERE "
			<< " opdate >='"
			<< dt1
			<<"' AND opdate <='"
			<< dt2
			<<"' ORDER BY opdate ASC";
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//--------------------------------------------------------------------------------------------------------
HTotalInOutRepVec HInOutRepCtrl::totalByDate(string d1,string d2)
{
	HTotalInOutRepVec vec;
	try{
		HTotalInOutRep totalInOutRep;
		mysqlpp::Query query = _pCon->query();
		query << "SELECT sum(food_num*food_price)as sum_price, rep_flag,date_format(opdate,'%Y-%m-%d') as sdate \
				 FROM t_inoutrep group by rep_flag,sdate  having sdate >='"
			  << d1 << "' AND sdate <='"
			  << d2 << "'  order by opdate asc";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		for ( it = res.begin(); it != res.end(); it++)
		{	row = *it;
			totalInOutRep.sum_price = row.lookup_by_name("sum_price");
			totalInOutRep.rep_flag = row.lookup_by_name("rep_flag");
			totalInOutRep.sdate = row.lookup_by_name("sdate");
			vec.push_back(totalInOutRep);
		}
	}mycatch();
	return vec;
}

//-------------------------------------------------------------------------------------------------------------------
//根据日期及条件返回出入库账单
HInOutRepVec HInOutRepCtrl::search(string d1,string d2,int inoutflag)
{
	HInOutRepVec vec;

	try{
		mysqlpp::Query query = _pCon->query();
		if ( inoutflag == -1)
		{
			query << "SELECT * FROM t_inoutrep  where opdate >='" << d1
				 << "' and opdate <='" << d2 
				 << "' group by inout_dh ";
			mysqlpp::Result res = query.store();
			_fill_vec(vec,res);

		}else {
			query << "SELECT * FROM t_inoutrep  where (opdate >='" << d1
				 << "' and opdate <='" << d2 
				 << "') and rep_flag = " << inoutflag
				 << " group by inout_dh ";
			mysqlpp::Result res = query.store();
			_fill_vec(vec,res);
		}
		
	}mycatch();
	return vec;
}

//----------------------------------------------------------------------------------------------------------------------
//根据账单号返回本账单号的所有记录
HInOutRepVec HInOutRepCtrl::search(string inout_dh)
{
	HInOutRepVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_inoutrep WHERE inout_dh='"
			<< inout_dh <<"'";
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}