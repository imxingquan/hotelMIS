/***********************************************************************
* Module:  HRepertory.h
* Author:  babala
* Modified: 2005年5月4日 3:50:55
* Purpose: Declaration of the class HRepertory
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/04/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HRepertory_h)
#define __hotelMIS_HRepertory_h
#include <string>
using namespace std;
namespace hotelMIS{
	class HRepertory
	{
	public:
		HRepertory();
		~HRepertory();

		int rep_id;
		int food_id;
		string food_name;
		int rep_num;
		float rep_price;
		string unit;
		string rep_date;
		/* 1: 入库 2: 入库调整 */
		int rep_flag;
		string ad_name;

	protected:
	private:

	};
}
#endif