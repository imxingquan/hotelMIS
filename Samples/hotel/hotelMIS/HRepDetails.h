/***********************************************************************
* Module:  HRepDetails.h
* Author:  babala
* Modified: 2005��5��6�� 20:38:06
* Purpose: Declaration of the class HRepDetails
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
		int food_status;			//�˵�״̬   ����Ϊ 1  �˲�Ϊ 2
		int kind_zk;	//�Ƿ����
		int kind_id;
		float zk_num;
		int total_fl;
	protected:
	private:

	};
}
#endif