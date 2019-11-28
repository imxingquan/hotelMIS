//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		KProfile.cpp
//
// Description:    
//				KProifle 类实现文件		
//
// Version: 1.0
//
// Hostory:		
//			04-28-2005	邢泉	Created	
//			
//---------------------------------------------------------

#include "stdafx.h"
#include ".\kprofile.h"

namespace hotelMIS{

	KProfile::KProfile(std::string file,std::string path)
	{
		if ( path.empty() ){
			char dir[MAX_PATH];
			::GetCurrentDirectory(MAX_PATH,dir);
			strcat(dir,"\\");
			filePath = dir + file;
		}
		else{
			/*if (path.at(path.length()-1) == "\\" || path.at(path.length()-1) == "/")
			filePath = path + file;
			else*/
			filePath = path + "\\" + file;
		}

	}

	KProfile::~KProfile(void)
	{
	}
	
	//
	// 读配置文件
	//
	std::string KProfile::GetProfile(std::string appName,std::string key,
		std::string defVal)
	{
		char returnBuff[MAX_PATH];
		::GetPrivateProfileString(appName.c_str(),key.c_str(),defVal.c_str(),returnBuff,MAX_PATH,filePath.c_str());
		return std::string(returnBuff);
	}
	
	//
	// 写配置文件
	//
	bool KProfile::WirteProfile(std::string appName,std::string key,std::string value)
	{
		return ::WritePrivateProfileString(appName.c_str(),key.c_str(),value.c_str(),filePath.c_str());
	}
}