/***********************************************************************
* Module:  HRepTotal.h
* Author:  babala
* Modified: 2005��5��4�� 3:50:45
* Purpose: Declaration of the class HRepTotal
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
#if !defined(__hotelMIS_HRepTotal_h)
#define __hotelMIS_HRepTotal_h
#include <string>
using namespace std;
namespace hotelMIS{
	class HRepTotal
	{
	public:
		HRepTotal();
		~HRepTotal();

		int food_id;
		int rep_num;
		string food_name;
	protected:
	private:

	};
}
#endif