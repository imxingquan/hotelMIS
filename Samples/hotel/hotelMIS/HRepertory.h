/***********************************************************************
* Module:  HRepertory.h
* Author:  babala
* Modified: 2005��5��4�� 3:50:55
* Purpose: Declaration of the class HRepertory
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/04/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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
		/* 1: ��� 2: ������ */
		int rep_flag;
		string ad_name;

	protected:
	private:

	};
}
#endif