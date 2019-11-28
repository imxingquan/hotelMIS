/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/22/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#ifndef HAdminBdy_H_HEADER_INCLUDED_BDA4FCE2
#define HAdminBdy_H_HEADER_INCLUDED_BDA4FCE2
#include "HAdmin.h"
#include "config.h"

#include <vector>
#include <string>

using namespace std;

namespace hotelMIS{
typedef vector<HAdmin> HAdminVec;
class HAdminBdy
{
  public:
    // Constructor
	HAdminBdy(mysqlpp::Connection* pConn);

    //用户登陆
	bool login(const string& name,const string& password);
	// 设置HAdmin信息
    HAdmin getAdminInfo(const string& name);
	
	//获得登陆用户信息
	void insert(HAdmin& admin);
	void Delete(int id);
	void update(HAdmin& admin);

	HAdmin getLoginUserInfo();
    vector<HAdmin> getAllAdminInfo();
	
	string getHotelname();

	static string _log_name;
	static string _ad_name;
  private:
    mysqlpp::Connection* _pConn;
	
};

}

#endif /* HAdminBdy_H_HEADER_INCLUDED_BDA4FCE2 */
