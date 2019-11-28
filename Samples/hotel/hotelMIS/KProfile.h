//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		KProfile.h
//
// Description:    
//				操作 ini 配置文件的类
//		
//
// Version: 1.0
//
// Hostory:		
//			04-28-2005	邢泉	Created	
//			
//---------------------------------------------------------
#pragma once
#include <string>
namespace hotelMIS{
	
	/*--------------------------------------------------------------------------------------
	* class KProfile
	*
	*	member function:
	*		KProfile(std::string file,std::string path="");
	*			parameters:
	*				- file	文件名称
	*				- path	文件路径 
	*		
	*		// 获取 对应块中相应键的值
	*		GetProfile(std::string appName,std::string key,	std::string defVal="")
	*			parameters:
	*				- appname	块名(ini 文件[appName]中的内容
	*				- key		键
	*				- defVal	值 默认为空
	*			return : bool	
	*		
	*		// 将键值写入配置文件
	*		WirteProfile(std::string appName,std::string key,std::string value)
	*			parameters:
	*				- appName	块名
	*				- key		键
	*				- value		值
	*
	*		Example:
	*			KProfile profile("set.ini"); //如果未设置 path 参数则为当前应用程序的目录
	*			//获取数据库连接的字符串
	*			string connectionString = profile.GetProfile("DATA","ConnectinString");
	*		
	*----------------------------------------------------------------------------------------*/

	class KProfile
	{
	public:
		KProfile(std::string file,std::string path="");
		~KProfile(void);
	public:

		std::string KProfile::GetProfile(std::string appName,std::string key,
			std::string defVal="");

		bool WirteProfile(std::string appName,std::string key,std::string value);
	
	private:
		std::string filePath;

	}; // end class KProfile

} // end namespace hotelMIS