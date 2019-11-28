/***********************************************************************
 * Module:  HRepertoryCtrl.cpp
 * Author:  babala
 * Modified: 2005年5月1日 23:31:04
 * Purpose: Implementation of the class HRepertoryCtrl
 ***********************************************************************/

#include "HRepertoryCtrl.h"

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

void HRepertoryCtrl::insert(HRepertory& rep)
{
   // TODO : 入库
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_repertory ( food_id,food_name,rep_num,rep_price,unit,rep_date,rep_flag,ad_name ) VALUES("
         << rep.food_id << ","
         << rep.food_name<<","
         << rep.rep_num << ","
         << rep.rep_price << ",'"
         << rep.unit <<"','"
         << rep.rep_date <<"',"
         << rep.rep_flag <<",'"
         << rep_ad_name <<"')";
         query.execute();
         }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HRepertoryCtrl::update(HRepertory& rep)
// Purpose:    Implementation of HRepertoryCtrl::update()
// Comment:    入库调整
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
         <<"ad_name='"<<ad_name<<"'"
         <<" WHERE food_id = "<<food_id;
         query.execute();
         }mycatch();
}