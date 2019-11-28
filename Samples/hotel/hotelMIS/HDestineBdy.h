/***********************************************************************
 * Module:  HDestineBdy.h
 * Author:  babala
 * Modified: 2005��5��12�� 17:44:33
 * Purpose: Declaration of the class HDestineBdy
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
		/* �ͲͲ��� */
		void destine(string guest_name, string guest_phone,string come_date, string come_time, int person_num, float subscription, string remark);
		void modify(int id,string guest_name,string guest_phone, string come_date, string come_time, int person_num, float subscription, string remark);

		/* �ɶ���״̬,ת�����Ͳ�״̬ */
		void chgRepast(void);
		/* ȡ������ */
		void cancelDestine(void);
		/*���ؿ��������*/
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