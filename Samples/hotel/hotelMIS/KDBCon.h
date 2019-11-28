//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		KDBCon.h
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
#if !defined(__HotelMis_KDBCon_h)
#define __HotelMis_KDBCon_h

#include <mysql++.h>

namespace hotelMIS{
	
	// *** global ***
	struct DBSTR{
		std::string db;			//数据库名称
		std::string host;		//主机名
		std::string user;		//数据登录用户
		std::string password;	//登录密码
		std::string port;		//端口号
	};
	
	CString ReplaceChar(CString &str);

	class KDBCon
	{
	public:
		// Construct /Destruct
		KDBCon();
		~KDBCon();	

		/**
		*初始化连接字符串
		*在连接之前，至少配置一次
		*
		*/
		void init();
		void init(std::string host, std::string port="3306",
			std::string user="root",std::string password="",std::string db="mysql");
		
		//返回mysql的连接
		mysqlpp::Connection* get_con(void);

		//确认连接
		bool isConnect();

		//关闭连接
		void close();

	private:
		//mysql 的默认连接
		static mysqlpp::Connection * _pCon;	

		//连接字符串结构
		static DBSTR _DBSTR;

	};
}
#endif