/***********************************************************************
* Module:  HRepast.h
* Author:  babala
* Modified: 2005��5��6�� 15:39:10
* Purpose: Declaration of the class HRepast
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/06/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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

		/* �˺� */
		string account_id;
		/* ���� */
		int table_id;
		/* �������� */
		string cust_date;
		/* ����ʱ�� */
		string cust_time;
		/* ������ */
		int room_id;
		/* ����״̬
		* 0: ����
		* 1: �Ͳ�
		* 2: Ԥ�� */
		int re_state;

	protected:
	private:

	};
}
#endif