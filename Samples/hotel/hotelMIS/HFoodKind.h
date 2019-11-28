/***********************************************************************
* Module:  HFoodKind.h
* Author:  babala
* Modified: 2005年4月25日 0:56:22
* Purpose: Declaration of the class HFoodKind
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/25/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HFoodKind_h)
#define __hotelMIS_HFoodKind_h
#include <string>
using namespace std;
namespace hotelMIS{
	class HFoodKind
	{
	public:
		enum SYS_MENU{
			TC = -11	,	//套餐: -11
			HOUCHU_FLAG = 1,		//库存
			ZDY=-99 //自定义类
		};    
		HFoodKind();
		~HFoodKind();
		int getKind_id(void);
		void setKind_id(int newKind_id);
		string getKind_name(void);
		void setKind_name(string newKind_name);
		int getKind_flag(void);
		void setKind_flag(int newKind_flag);
		int getKind_ts(void);
		void setKind_ts(int newKind_ts);
		void setKind_zk(int newKind_zk);
		int getKind_zk(void);
		void setZdy_price(int newZdy_price);
		int getZdy_price(void);
	public:
		int kind_id;
		string kind_name;
		int kind_flag;
		int kind_ts;
		int kind_zk;
		int zdy_price;


	};
}
#endif