/***********************************************************************
 * Module:  HJobSetCtrl.cpp
 * Author:  babala
 * Modified: 2005��4��23�� 17:27:41
 * Purpose: Implementation of the class HJobSetCtrl
 ***********************************************************************/

#include "HJobSetCtrl.h"

////////////////////////////////////////////////////////////////////////
// Name:       HJobSetCtrl::HJobSetCtrl(mysqlpp::Connection * pCon)
// Purpose:    Implementation of HJobSetCtrl::HJobSetCtrl()
// Parameters:
// - pCon
// Return:     
////////////////////////////////////////////////////////////////////////

HJobSetCtrl::HJobSetCtrl(mysqlpp::Connection * pCon)
{
   // TODO : implement
   _pCon = pCon;
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSetCtrl::~HJobSetCtrl()
// Purpose:    Implementation of HJobSetCtrl::~HJobSetCtrl()
// Return:     
////////////////////////////////////////////////////////////////////////

HJobSetCtrl::~HJobSetCtrl()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSetCtrl::insert(string jobName)
// Purpose:    Implementation of HJobSetCtrl::insert()
// Parameters:
// - jobName
// Return:     void
////////////////////////////////////////////////////////////////////////

void HJobSetCtrl::insert(string jobName)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "INSERT INTO t_job_set ( job_name) VALUES('"<<jobName<<"')";
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSetCtrl::Delete(int jobId)
// Purpose:    Implementation of HJobSetCtrl::Delete()
// Parameters:
// - jobId
// Return:     void
////////////////////////////////////////////////////////////////////////

void HJobSetCtrl::Delete(int jobId)
{
   // TODO : implement
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_job_set WHERE job_id = " << jobId;
         query.execute();
   }mycatch();
}

////////////////////////////////////////////////////////////////////////
// Name:       HJobSetCtrl::getAllJob()
// Purpose:    Implementation of HJobSetCtrl::getAllJob()
// Return:     vector<HJobset>
////////////////////////////////////////////////////////////////////////

vector<HJobset> HJobSetCtrl::getAllJob(void)
{
   // TODO : implement
   vector<HJobSet> vec;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT  *  FROM t_job_set";
         mysqlpp::Row row;
         mysqlpp::Result res = query.store();
         mysqlpp::Result::iterator it;
         HJobSet jobSet;
         int jobId;
         string jobName;
         for ( it = res.begin(); it != res.end(); it++)
         {
               row = *it;
               jobId = row.lookup_by_name("job_id");
               jobName = row.lookup_by_name("job_name");
               jobSet.setJob_id(jobId);
               jobSet.setJob_name(jobName);
               vec.push_back(jobSet);
         }
   }mycatch();
   return vec;
}