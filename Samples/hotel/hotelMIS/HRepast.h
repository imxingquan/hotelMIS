/***********************************************************************
* Module:  HRepast.h
* Author:  babala
* Modified: 2005年5月6日 15:39:10
* Purpose: Declaration of the class HRepast
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
#if !defined(__hotelMIS_HRepast_h)
#define __hotelMIS_HRepast_h
#include <string>
using namespace std;
namespace hotelMIS{
	class HRepast
	{
	public:
		enum{emptyState=0,repastState=1,destineState=2};
		HRepast();
		~HRepast();

		/* 账号 */
		string account_id;
		/* 桌号 */
		int table_id;
		/* 消费日期 */
		string cust_date;
		/* 消费时间 */
		string cust_time;
		/* 餐厅号 */
		int room_id;
		/* 消费状态
		* 0: 空桌
		* 1: 就餐
		* 2: 预定 */
		int re_state;

	protected:
	private:

	};
}
#endif