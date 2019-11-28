/***********************************************************************
* Module:  HReportBdy.h
* Author:  babala
* Modified: 2005年5月22日 21:59:45
* Purpose: Declaration of the class HReportBdy
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/22/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HReportBdy_h)
#define __hotelMIS_HReportBdy_h

#include <HAccountCtrl.h>
#include <HAccDetailsCtrl.h>
#include "KDBCon.h"
namespace hotelMIS{
	
	class HReportBdy
	{
	public:
		HReportBdy();
		~HReportBdy();
		HAccountVec totalByDay(string sDate,string eDate,int jsfs);
		HAccountVec totalByMonth(string year, string month);
		HAccountVec totalByYear(string year);
		HTotalByCookVec totalByCookDay(string day);
		HTotalByCookVec totalByCookMonth(string year,string month);
		HTotalByCookVec totalByCookYear(string month);
		/*HAccountVec totalByDayNoPay(string day);
		HAccountVec totalByMonthNoPay(string month);
		HAccountVec totalByYearNoPay(string year);*/
		void DeleteByAccountId(string accountId);
		void DeleteAll();

		// 按指定的时间间隔查询
		HAccountVec totalByDateTime(string start_dtime,string end_dtime,int jsfs);
		HTotalAccountVec totalByPayStatus(string start_dtime,string end_dtime);
		
		// 按月 结算统计
		HTotalAccountVec totalByPayStatus(string year,string month,int bf);
		
		// 按年 结算统计
		HTotalAccountVec totalByPayStatus(string year);
	protected:
	private:
		HAccountCtrl* pAccountCtrl;
		HAccDetailsCtrl* pAccDetailsCtrl;
		KDBCon m_con;


	};
}
#endif