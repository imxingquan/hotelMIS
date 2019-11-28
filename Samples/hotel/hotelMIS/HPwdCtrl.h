//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HPwdCtrl.h
//
// Description:    
//			   对 HMember 对应 t_member 表的基础操作
//
// Version: 1.4
//
// Hostory:		
//			06-04-2006	邢泉	Created	
//			
//---------------------------------------------------------

#pragma once

#include "config.h"
#include "HPwd.h"

#include <vector>
using namespace std;

namespace hotelMIS{
	
	class HPwdCtrl{

	public:
		HPwdCtrl(mysqlpp::Connection *pCon);
		~HPwdCtrl();

	public:
		void setAwardPwd(string pwd);
		string getAwardPwd();

	private:
		mysqlpp::Connection * _pCon;	 //数据库连接

	};//end class HPwdCtrl

}; //end namepace hotelMIS