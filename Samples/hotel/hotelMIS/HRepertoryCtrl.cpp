/***********************************************************************
 * Module:  HRepertoryCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月1日 23:31:04
 * Purpose: Implementation of the class HRepertoryCtrl
 ***********************************************************************/
#include "stdAfx.h"
#include "HRepertoryCtrl.h"
#include "HRepToTalCtrl.h"
using namespace hotelMIS;
////////////////////////////////////////////////////////////////////////
// Name:       HRepertoryCtrl::HRepertoryCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HRepertoryCtrl::HRepertoryCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HRepertoryCtrl::HRepertoryCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
	_pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepertoryCtrl::~HRepertoryCtrl()
// Purpose:    Implementation of HRepertoryCtrl::~HRepertoryCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HRepertoryCtrl::~HRepertoryCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepertoryCtrl::insert(HRepertory& rep)
// Purpose:    Implementation of HRepertoryCtrl::insert()
// Comment:    入库
// Parameters:
// - rep
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepertoryCtrl::insert(HRepertory& rep,int opType)
{
   // TODO : 入库
	//opType = 0 入库
	//opType = 1 入库调整
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_repertory ( food_id,food_name,rep_num,rep_price,unit,rep_date,rep_flag,ad_name ) VALUES("
         << rep.food_id << ",'"
         << rep.food_name<<"',"
         << rep.rep_num << ","
         << rep.rep_price << ",'"
         << rep.unit <<"','"
         << rep.rep_date <<"',"
         << rep.rep_flag <<",'"
         << rep.ad_name <<"')";
         query.execute();
    }mycatch(); 
   
   hotelMIS::HRepToTalCtrl totalCtrl(_pCon);
   if ( 0 == opType )
      totalCtrl.addNum(rep.food_id,rep.rep_num);
   else
	  totalCtrl.delNum(rep.food_id,rep.rep_num);
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepertoryCtrl::update(HRepertory& rep)
// Purpose:    Implementation of HRepertoryCtrl::update()
// Comment:    入库调整(暂无用)
// Parameters:
// - rep
// Return:     void
////////////////////////////////////////////////////////////////////////

void HRepertoryCtrl::update(HRepertory& rep)
{
   // TODO : implement
    try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_repertory SET "
         <<"rep_num="<<rep.rep_num <<","
         //<<"rep_price="<<rep.rep_price<<","
         <<"rep_flag ="<<rep.rep_flag<<","
         <<"ad_name='"<<rep.ad_name<<"'"
         <<" WHERE food_id = "<<rep.food_id;
         query.execute();
         }mycatch();
   hotelMIS::HRepToTalCtrl totalCtrl(_pCon);
   totalCtrl.delNum(rep.food_id,rep.rep_num);
}

HRepertoryVec HRepertoryCtrl::getAllRepertory(string sDate,string eDate)
{
	HRepertoryVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_repertory WHERE rep_date >='"
			 << sDate <<"' AND rep_date <='"
			 << eDate <<"' ORDER BY rep_date ";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		HRepertory rep;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			rep.food_id = row.lookup_by_name("food_id");
			rep.food_name = row.lookup_by_name("food_name");
			rep.rep_date = row.lookup_by_name("rep_date");
			rep.rep_flag = row.lookup_by_name("rep_flag");
			rep.rep_id = row.lookup_by_name("rep_id");
			rep.rep_num = row.lookup_by_name("rep_num");
			rep.rep_price = row.lookup_by_name("rep_price");
			rep.unit = row.lookup_by_name("unit");
			
			vec.push_back(rep);
			
		}
	}mycatch();
	return vec;
}

void HRepertoryCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_repertory";
		query.execute();
	}mycatch();
}