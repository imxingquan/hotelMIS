#include "StdAfx.h"
#include ".\kresetdb.h"
#include "MsgDetails.h"
#include "CreateDB.h"

#include <fstream>
using namespace std;

KResetDB::KResetDB(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

KResetDB::~KResetDB(void)
{
}

bool KResetDB::ResetDB(string dbfile)
{
	string SQL;
	vector<string> sqlVec;
	vector<string>::iterator it;
	
	ifstream infile(dbfile.c_str(),ios::in);
	if (! infile){
		MessageBox(NULL,_T("数据文件打开错误"),_T("数据错误"),MB_OK);
		return false;
	}
	while (getline(infile,SQL,';')){
		if ( !SQL.empty() )
		sqlVec.push_back(SQL);
	}

	try{

		mysqlpp::Query query = _pCon->query();
		for ( it = sqlVec.begin(); it != sqlVec.end(); it++)
		{
			theApp.globaStr = (*it);
			query << (*it) ;
			query.execute();
			::SendMessage(AfxGetMainWnd()->m_hWnd,WM_DETAILS,0,0);
		}
	}mycatch();
	if ( it != sqlVec.end()) return false;

	return true;
}