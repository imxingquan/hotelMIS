/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#pragma once
#include <string>

class KProfile
{
public:
	KProfile(std::string file,std::string path="");
	~KProfile(void);
public:
	
	std::string KProfile::GetProfile(std::string appName,std::string key,
								 std::string defVal="");
	bool WirteProfile(std::string appName,std::string key,std::string value);

	std::string getPath()
	{
		return currpath;
	}
private:
	std::string filePath;
	std::string currpath;
	
};
