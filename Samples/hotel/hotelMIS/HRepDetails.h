/***********************************************************************
* Module:  HRepDetails.h
* Author:  babala
* Modified: 2005年5月6日 20:38:06
* Purpose: Declaration of the class HRepDetails
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/06/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HRepDetails_h)
#define __hotelMIS_HRepDetails_h
#include <string>
using namespace std;
namespace hotelMIS{
	class HRepDetails
	{
	public:
		enum FOOD_STATUS{ FOOD_AWARD = 1,FOOD_BACK = 2 };
		HRepDetails();
		~HRepDetails();
		int id;
		string account_id;
		int food_id;
		string food_name;
		int food_num;
		float food_price;
		string ck_name;
		string food_unit;
		int food_cook;
		string food_cancel_msg;
		int food_status;			//菜的状态   赠菜为 1  退菜为 2
		int kind_zk;	//是否打折
		int kind_id;
		float zk_num;
		int total_fl;
	protected:
	private:

	};
}
#endif