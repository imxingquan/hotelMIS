/***********************************************************************
 * Module:  HDestineCtrl.cpp
 * Author:  babala
 * Modified: 2005Äê5ÔÂ12ÈÕ 18:11:35
 * Purpose: Implementation of the class HDestineCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HDestineCtrl.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HDestineCtrl::HDestineCtrl(mysqlpp::Connection* pCon)
// Purpose:    Implementation of HDestineCtrl::HDestineCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HDestineCtrl::HDestineCtrl(mysqlpp::Connection* pCon)
{
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineCtrl::~HDestineCtrl()
// Purpose:    Implementation of HDestineCtrl::~HDestineCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HDestineCtrl::~HDestineCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineCtrl::insert(HDestine& destine)
// Purpose:    Implementation of HDestineCtrl::insert()
// Parameters:
// - destine
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineCtrl::insert(HDestine& destine)
{
   // TODO : ¶©²Í
   try{
	   mysqlpp::Query query = _pCon->query();
	   query << "INSERT INTO t_destine ( guest_name,come_date,come_time,subscription,person_num,remark,guest_phone) VALUES('"
		   <<destine.guest_name<<"',"
		   <<"'"<<destine.come_date<<"',"
		   <<"'"<<destine.come_time<<"',"
				<<destine.subscription<<","
				<<destine.person_num<<","
			<<"'"<<destine.remark <<"','"
			<<destine.guest_phone<<"')";
	   query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineCtrl::Delete()
// Purpose:    Implementation of HDestineCtrl::Delete()
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineCtrl::Delete(int id)
{
   // TODO : implement
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_destine WHERE id ="<<id;
		query.execute();
	}mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HDestineCtrl::update()
// Purpose:    Implementation of HDestineCtrl::update()
// Return:     void
////////////////////////////////////////////////////////////////////////

void HDestineCtrl::update(HDestine &destine)
{
   // TODO : implement
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_destine SET guest_name='"
			<<destine.guest_name<<"',guest_phone='"
			<<destine.guest_phone<<"',come_date='"
			<<destine.come_date<<"',come_time='"
			<<destine.come_time<<"',subscription="
			<<destine.subscription<<",person_num="
			<<destine.person_num<<",remark='"
			<<destine.remark<<"',bdisp="
			<<destine.bdisp<<" WHERE id ="<< destine.id ;
		query.execute();
	}mycatch();

}

HDestine HDestineCtrl::getDestine(int id)
{
	HDestine destine;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_destine WHERE id ="<<id;
		
		mysqlpp::Result res = query.store();
		if ( !res.empty() ){
			mysqlpp::Row row;
			mysqlpp::Result::iterator it = res.begin();
			row = *it;
			destine.id = id;
			destine.guest_name = row.lookup_by_name("guest_name");
			destine.guest_phone = row.lookup_by_name("guest_phone");
			destine.come_date = row.lookup_by_name("come_date");
			destine.come_time = row.lookup_by_name("come_time");
			destine.person_num = row.lookup_by_name("person_num");
			destine.subscription = row.lookup_by_name("subscription");
			destine.remark = row.lookup_by_name("remark");
		}
	}mycatch();
	return destine;
}

vector<HDestine> HDestineCtrl::getAllDestine()
{
	vector<HDestine> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_destine";
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		HDestine destine;
		for ( it = res.begin(); it!= res.end(); it++)
		{
			row = *it;
			destine.id = row.lookup_by_name("id");
			destine.come_date = row.lookup_by_name("come_date");
			destine.come_time = row.lookup_by_name("come_time");
			destine.guest_name = row.lookup_by_name("guest_name");
			destine.guest_phone = row.lookup_by_name("guest_phone");
			destine.person_num = row.lookup_by_name("person_num");
			destine.subscription = row.lookup_by_name("subscription");
			destine.remark = row.lookup_by_name("remark");
			destine.bdisp = row.lookup_by_name("bdisp");
			vec.push_back(destine);
		}
	}mycatch();
	return vec;
}

void HDestineCtrl::setWarning(int id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_destine SET bdisp = 0 WHERE id = "<<id;
		query.execute();
	}mycatch();
}

void HDestineCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_destine";
		query.execute();
	}mycatch();
}