/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/22/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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

    //�û���½
	bool login(const string& name,const string& password);
	// ����HAdmin��Ϣ
    HAdmin getAdminInfo(const string& name);
	
	//��õ�½�û���Ϣ
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
