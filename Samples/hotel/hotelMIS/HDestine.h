/***********************************************************************
 * Module:  HDestine.h
 * Author:  babala
 * Modified: 2005年5月12日 18:22:45
 * Purpose: Declaration of the class HDestine
 ***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/12/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HDestine_h)
#define __hotelMIS_HDestine_h
#include <string>
using namespace std;
namespace hotelMIS{
	class HDestine
	{
	public:
		HDestine();
		~HDestine();

		int id;
		string guest_name;
		string guest_phone;
		string come_date;
		string come_time;
		int person_num;
		float subscription;
		string remark;
		int bdisp;
	protected:
	private:

	};
}
#endif