/***********************************************************************
 * Module:  HOutStore.h
 * Author:  babala
 * Modified: 2005��5��5�� 14:45:18
 * Purpose: Declaration of the class HOutStore
 ***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/05/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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