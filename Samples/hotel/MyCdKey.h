/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		验证注册码,取cpu 和硬盘序列号
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include <string>
#include <cassert>
using namespace std;
class MyCdKey 
{
public:
	MyCdKey(void);
	~MyCdKey(void);
	
	DWORD GetCpuPeInfo()
	{
		SYSTEM_INFO info;

		DWORD SeriaNumber=NULL;

		DWORD Register=NULL; 

		GetSystemInfo(&info); //调用函数填SYSTEM_INFO结构 
		GetVolumeInformation("C:\\",NULL,NULL,&SeriaNumber,NULL,NULL,NULL,NULL); //获取C盘序列号 

		Register=SeriaNumber+info.wProcessorRevision+info.dwOemId; 

		Register=Register^info.wProcessorLevel; 
		
		return Register;
	}
	
	int m_key[4];
	CString m_cdkey;

	CString getKey(){
		DWORD cdkey = GetCpuPeInfo();
		for ( int i = 0; i < 4; i++)
			m_key[i] = (cdkey ^ ((i+1)*402059985)) % 10000;
		m_cdkey.Format("%.4d-%.4d-%.4d-%.4d",m_key[0],m_key[1],m_key[2],m_key[3]);
		return m_cdkey;
	}

	BOOL RegisterCdKey();

	/*BOOL IsValidateDate()
	{
		CWinApp* pWinApp = AfxGetApp();
		CString date = pWinApp->GetProfileString("Setting","invalidate",0);
		if ( 

	}*/

};
