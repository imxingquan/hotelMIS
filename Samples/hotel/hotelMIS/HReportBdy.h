/***********************************************************************
* Module:  HReportBdy.h
* Author:  babala
* Modified: 2005��5��22�� 21:59:45
* Purpose: Declaration of the class HReportBdy
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/22/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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

		// ��ָ����ʱ������ѯ
		HAccountVec totalByDateTime(string start_dtime,string end_dtime,int jsfs);
		HTotalAccountVec totalByPayStatus(string start_dtime,string end_dtime);
		
		// ���� ����ͳ��
		HTotalAccountVec totalByPayStatus(string year,string month,int bf);
		
		// ���� ����ͳ��
		HTotalAccountVec totalByPayStatus(string year);
	protected:
	private:
		HAccountCtrl* pAccountCtrl;
		HAccDetailsCtrl* pAccDetailsCtrl;
		KDBCon m_con;


	};
}
#endif