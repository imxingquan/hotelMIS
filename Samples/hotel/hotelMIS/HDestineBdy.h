/***********************************************************************
 * Module:  HDestineBdy.h
 * Author:  babala
 * Modified: 2005年5月12日 17:44:33
 * Purpose: Declaration of the class HDestineBdy
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
#if !defined(__hotelMIS_HDestineBdy_h)
#define __hotelMIS_HDestineBdy_h
#include <HDestineCtrl.h>
#include <KDBCon.h>

namespace hotelMIS{
	class HDestineBdy
	{
	public:
		HDestineBdy();
		~HDestineBdy();
		/* 就餐操作 */
		void destine(string guest_name, string guest_phone,string come_date, string come_time, int person_num, float subscription, string remark);
		void modify(int id,string guest_name,string guest_phone, string come_date, string come_time, int person_num, float subscription, string remark);

		/* 由订餐状态,转换到就餐状态 */
		void chgRepast(void);
		/* 取消定餐 */
		void cancelDestine(void);
		/*返回控制器句柄*/
		HDestineCtrl * getCtrl()const;
	protected:
	private:
		HDestineCtrl* _ctrl;
		mysqlpp::Connection *_pCon;
		hotelMIS::KDBCon m_con;
		int table_id;
		int room_id;


	};
}
#endif