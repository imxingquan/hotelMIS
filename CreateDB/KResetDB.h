/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		�������ݿ�
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ	08/28/05	v1.3 �汾

--*/

#pragma once
#include <string>
#include "config.h"
using namespace std;
class KResetDB
{
public:
	KResetDB(mysqlpp::Connection * pCon);
	~KResetDB(void);
	bool ResetDB(string dbfile);
private:
	string sql;
	mysqlpp::Connection * _pCon;
};
