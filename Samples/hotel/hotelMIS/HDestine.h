/***********************************************************************
 * Module:  HDestine.h
 * Author:  babala
 * Modified: 2005��5��12�� 18:22:45
 * Purpose: Declaration of the class HDestine
 ***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/12/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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