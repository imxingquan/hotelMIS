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
#ifndef HADMIN_H_HEADER_INCLUDED_BDA4F70C
#define HADMIN_H_HEADER_INCLUDED_BDA4F70C
#include <string>
using namespace std;
namespace hotelMIS{
	class HAdmin
	{
	public:
		//   Constructor
		HAdmin();
		void setId(int id);

		void setLoginId(string loginId);

		void setPassword(string password);

		void setDesc(string desc);

		void setName(string name);
		
		void setOpType(string opType);

		int getId();

		string getLoginId();

		string getPassword();

		string getDesc();

		string getName();

		string getOpType();

	private:
		int _id;

		string _login_id;

		string _password;

		string _desc;

		string _name;

		string _opType;

	};

}

#endif /* HADMIN_H_HEADER_INCLUDED_BDA4F70C */
