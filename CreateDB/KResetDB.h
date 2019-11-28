/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		重置数据库
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉	08/28/05	v1.3 版本

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
