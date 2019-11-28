#include "stdAfx.h"
#include "./myexp.h"
namespace mysqlpp{

	void WriteErrFile(const char* strErr)
	{
		//纪录错误信息到文本文件
		CString strPath;
		char dir[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH,dir);
		strPath.Format("%s\\",dir);
		//日志文件名格式为logYYYYMMDD(年月日).txt

		CFile cFile;
		CString strErrFileName;
		tm* nowTime;
		__time64_t tm64;
		_time64(&tm64);
		nowTime = _localtime64(&tm64);
		strErrFileName.Format("%d-%d-%d",nowTime->tm_year,nowTime->tm_mon,nowTime->tm_mday);
		strErrFileName = "log"+strErrFileName+".txt";
		strErrFileName = strPath+strErrFileName;
		BOOL bOpenState;

		//判断文件是否存在
		if((bOpenState=cFile.Open(strErrFileName,CFile::modeWrite,NULL)))
		{
			//判断文件存在

		}
		else
		{
			//判断文件不存在，则创建此文件
			if(bOpenState=cFile.Open(strErrFileName,CFile::modeCreate|CFile::modeWrite,NULL))
			{

			}
		}
		if(bOpenState)
		{
			//文件创建或打开成功
			//记录文件加上日期
			cFile.SeekToEnd();
			CString strDate;
			tm* nowTime;
			__time64_t tm64;
			_time64(&tm64);
			nowTime = _localtime64(&tm64);
			strDate.Format("%d-%d-%d %d:%d:%d",nowTime->tm_year,nowTime->tm_mon,nowTime->tm_mday,
				nowTime->tm_hour,nowTime->tm_min,nowTime->tm_sec);
			strDate=strDate + CString("	") + strErr + CString("\r\n");
			cFile.Write(strDate,strDate.GetLength());
			cFile.Close();
		}	
	}
}