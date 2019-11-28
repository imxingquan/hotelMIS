//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		KDBCon.cpp
//
// Description:    
//				����mysql���ݿ�
//		
//
// Version: 1.0
//
// Hostory:		
//			03-31-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"

#include "KDBCon.h"
#include "KProfile.h"

namespace hotelMIS{

	DBSTR KDBCon::_DBSTR ;	//��̬������ʼ��

	mysqlpp::Connection * KDBCon::_pCon= NULL;	//���ݿ����Ӿ��

	CString ReplaceChar(CString &str)
	{
		//�滻�ַ��е� "'" �Լ�
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
	// �������ļ���ʼ������
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
	// ����ָ����ֵ��ʼ������
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
	// ������ݿ������
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
	// �жϵ�ǰ�Ƿ��Ѿ��������ݿ�
	//
	bool KDBCon::isConnect()
	{
		if ( _pCon )
			return _pCon->connected();
		else
			return false;
	}

	//
	// �ر�����
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