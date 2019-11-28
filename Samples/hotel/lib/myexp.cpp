#include "stdAfx.h"
#include "./myexp.h"
namespace mysqlpp{

	void WriteErrFile(const char* strErr)
	{
		//��¼������Ϣ���ı��ļ�
		CString strPath;
		char dir[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH,dir);
		strPath.Format("%s\\",dir);
		//��־�ļ�����ʽΪlogYYYYMMDD(������).txt

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

		//�ж��ļ��Ƿ����
		if((bOpenState=cFile.Open(strErrFileName,CFile::modeWrite,NULL)))
		{
			//�ж��ļ�����

		}
		else
		{
			//�ж��ļ������ڣ��򴴽����ļ�
			if(bOpenState=cFile.Open(strErrFileName,CFile::modeCreate|CFile::modeWrite,NULL))
			{

			}
		}
		if(bOpenState)
		{
			//�ļ�������򿪳ɹ�
			//��¼�ļ���������
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