/***********************************************************************
 * Module:  HOutStore.h
 * Author:  babala
 * Modified: 2005年5月5日 14:45:18
 * Purpose: Declaration of the class HOutStore
 ***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/05/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HOutStore_h)
#define __hotelMIS_HOutStore_h
#include <string>
using namespace std;
namespace hotelMIS{
class HOutStore
{
public:
   HOutStore();
   ~HOutStore();

   long out_id;
   int food_id;
   string food_name;
   float out_price;
   string out_date;
   int out_flag;
   string ad_name;
   int out_num;
   string out_unit;
protected:
private:
  


};
}
#endif