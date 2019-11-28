//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HPwdCtrl.cpp
//
// Description:    
//			   实现对 HMember 的数据库基础操作
//
// Version: 1.4
//
// Hostory:		
//			06-04-2006	邢泉	Created	
//			
//---------------------------------------------------------
#include "stdAfx.h"
#include "HPwdCtrl.h"

using namespace hotelMIS;

HPwdCtrl::HPwdCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HPwdCtrl::~HPwdCtrl()
{
}

//
// 设置赠菜密码
//
void HPwdCtrl::setAwardPwd(string pwd)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_pwd SET awardPwd ='"<<pwd<<"'";
		query.execute();
	}mycatch();
}

string HPwdCtrl::getAwardPwd()
{
	string pwd = "";
	try{
	mysqlpp::Query query = _pCon->query();
	query <<"SELECT awardPwd FROM t_pwd ";
	mysqlpp::Result res = query.store();
	if ( ! res.empty()){
		mysqlpp::Row row = *res.begin();
		//mysqlpp::Result::iterator it = res.begin();
		//row = *it;
		pwd = row.lookup_by_name("awardPwd");
	}
	}mycatch();
	return pwd;
}