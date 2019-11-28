//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		KDBCon.cpp
//
// Description:    
//				连接mysql数据库
//		
//
// Version: 1.0
//
// Hostory:		
//			03-31-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"

#include "KDBCon.h"
#include "KProfile.h"

namespace hotelMIS{

	DBSTR KDBCon::_DBSTR ;	//静态变量初始化

	mysqlpp::Connection * KDBCon::_pCon= NULL;	//数据库连接句柄

	CString ReplaceChar(CString &str)
	{
		//替换字符中的 "'" 以及
		CString strReturn("");
		TRY
		{
			if(str.GetLength()>0)
			{
				strReturn=str;
				strReturn.TrimLeft();
				strReturn.TrimRight();

				strReturn.Replace(_T("'"),_T("''"));
				strReturn.Replace(_T("\\"),_T(""));
			}
		}
		CATCH(CException,e){
			e->ReportError();
		}
		END_CATCH
			return strReturn;
	}

	KDBCon::KDBCon()
	{
	}

	KDBCon::~KDBCon()
	{
		//this->close();
	}

	//
	// 从配置文件初始化连接
	//
	void KDBCon::init()
	{
		KProfile profile("set.ini");
		KDBCon::_DBSTR.db = profile.GetProfile("HOST_SET","db");
		KDBCon::_DBSTR.host = profile.GetProfile("HOST_SET","host");
		KDBCon::_DBSTR.user = profile.GetProfile("HOST_SET","user");
		KDBCon::_DBSTR.password = profile.GetProfile("HOST_SET","pwd");
		KDBCon::_DBSTR.port  = profile.GetProfile("HOST_SET","port");
		//TRACE("port = %s \n",KDBCon::_DBSTR.port.c_str());
	}

	//
	// 根据指定的值初始化连接
	//
	void KDBCon::init(std::string host, std::string port,std::string user,std::string password,std::string db)
	{
		KDBCon::_DBSTR.db = db;
		KDBCon::_DBSTR.host = host;
		KDBCon::_DBSTR.user = user;
		KDBCon::_DBSTR.password = password;
		KDBCon::_DBSTR.port  = port;

	}

	//
	// 获得数据库的连接
	//
	mysqlpp::Connection* KDBCon::get_con(void)
	{
		if ( !_pCon ){
			try{
				_pCon = new mysqlpp::Connection(mysqlpp::use_exceptions);
				if ( KDBCon::_DBSTR.port.empty() )
					_pCon->connect(_DBSTR.db.c_str(),_DBSTR.host.c_str(),_DBSTR.user.c_str(),_DBSTR.password.c_str());
				else{
					//					TRACE("port = %d \n",atoi(KDBCon::_DBSTR.port.c_str()));
					_pCon->real_connect(_DBSTR.db.c_str(),_DBSTR.host.c_str(),_DBSTR.user.c_str(),_DBSTR.password.c_str(),atoi(_DBSTR.port.c_str()),0,60,NULL,0);
				}
			}catch(mysqlpp::BadQuery er){
				TRACE(er.what());
				_pCon->close();
				delete _pCon;
				_pCon = NULL;
			}catch(mysqlpp::BadConversion er){
				TRACE(er.what());
				_pCon->close(); 
				delete _pCon;
				_pCon = NULL;
			}catch(exception er){
				_pCon->close();
				delete _pCon;
				_pCon = NULL;
			}
		}// end if ( !_pCon) 
		return _pCon;
	}

	//
	// 判断当前是否已经连接数据库
	//
	bool KDBCon::isConnect()
	{
		if ( _pCon )
			return _pCon->connected();
		else
			return false;
	}

	//
	// 关闭连接
	//
	void KDBCon::close()
	{
		try{
			if ( _pCon && _pCon->connected() ){
				_pCon->close();
				delete _pCon;
			}else if ( _pCon ){
				delete _pCon;
				_pCon = NULL;
			}
		}catch(mysqlpp::BadQuery er){
			TRACE(er.what());
			if ( _pCon && _pCon->connected() ){ _pCon->close(); delete _pCon;}
		}catch(mysqlpp::BadConversion er){
			TRACE(er.what());
			if ( _pCon && _pCon->connected() ){ _pCon->close(); delete _pCon;}
		}
	}
}