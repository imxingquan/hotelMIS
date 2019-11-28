//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HReportDetailsCtrl.cpp
// 
// Desc:  经营明细报表
//
// Author:  xq
// 
// Modified: 2005年6月14日 6:09
//-----------------------------------------------------------------------
#include "stdAfx.h"
#include "HReportDtailsCtrl.h"
#include "HReportDetails.h"

#include <vector>
using namespace std;

using namespace hotelMIS;

HReportDetailsCtrl::HReportDetailsCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HReportDetailsCtrl::~HReportDetailsCtrl()
{

}

std::vector<HReportDetails> HReportDetailsCtrl::reportDetails(string datetimeStart,string datetimeEnd,int kind_id)
{
	std::vector<HReportDetails> vec;
	try{
	
		HReportDetails repds;

		mysqlpp::Query query = _pCon->query();
		query << "select food_id,food_name,food_unit,sum(food_num) AS sum_num ,sum(food_num*food_price*zk_num) AS sum_price,kind_id FROM `t_accountdetails` inner join t_account on t_account.account_id = t_accountdetails.account_id WHERE \
				 t_account.cust_date >='"
			 <<datetimeStart <<"' and t_account.cust_date <='"
			<< datetimeEnd <<"' GROUP by food_id having kind_id="
			<< kind_id;
		mysqlpp::Result res = query.store();
		mysqlpp::Row row;
		mysqlpp::Result::iterator it;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			repds.food_id = row.lookup_by_name("food_id");
			repds.kind_id = row.lookup_by_name("kind_id");
			repds.food_unit = row.lookup_by_name("food_unit");
			repds.food_name = row.lookup_by_name("food_name");
			repds.sum_num = row.lookup_by_name("sum_num");
			repds.sum_price =row.lookup_by_name("sum_price");
			vec.push_back(repds);
		}

	}mycatch();
	return vec;
}