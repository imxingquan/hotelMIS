/***********************************************************************
* Module:  HRepTotal.h
* Author:  babala
* Modified: 2005年5月4日 3:50:45
* Purpose: Declaration of the class HRepTotal
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