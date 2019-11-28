#include "stdafx.h"
#include ".\kprofile.h"


KProfile::KProfile(std::string file,std::string path)
{
	if ( path.empty() ){
		char dir[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH,dir);
		strcat(dir,"\\");
		currpath = dir;
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

std::string KProfile::GetProfile(std::string appName,std::string key,
								 std::string defVal)
{
	char returnBuff[MAX_PATH];
	::GetPrivateProfileString(appName.c_str(),key.c_str(),defVal.c_str(),returnBuff,MAX_PATH,filePath.c_str());
	return std::string(returnBuff);
}

bool KProfile::WirteProfile(std::string appName,std::string key,std::string value)
{
	return ::WritePrivateProfileString(appName.c_str(),key.c_str(),value.c_str(),filePath.c_str());
}