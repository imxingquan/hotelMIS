/***********************************************************************
* Module:  HMenuInfo.h
* Author:  babala
* Modified: 2005年4月25日 2:29:10
* Purpose: Declaration of the class HMenuInfo
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/25/05	v1.2 
	邢泉	08/28/05	v1.3 
	邢泉    2006-6-5	添加拼音检索功能

--*/
#if !defined(__hotelMIS_HMenuInfo_h)
#define __hotelMIS_HMenuInfo_h
#include <HFoodKind.h>
#include <string>
using namespace std;
namespace hotelMIS{
	class HMenuInfo
	{
	public:
		HMenuInfo();
		~HMenuInfo();
		
		enum MENU_STATUS{
			TC = -11	,		//套餐: -11
			REP_CALC = 1,		//库存并计算 : 1
			REP_NOCALC = 2,		//库存不计算 : 2
			REP_NO = 0			//不进库存	 : 0
		}; 

	public:
		int food_id;		//id
		int kind_id;		//种类id
		string food_name;	//名称
		int food_num;		//数量
		float food_price;	//单价
		string food_unit;	//单位
		
		int repertory_flag;	//是否参与库存/或计算

		string ck_name;		//厨师名
		int food_cook;		//厨房
		string food_py;		//拼音简码
		
		bool bTaocan;		//套餐
		
		int total_fl;		//统计分类
		HFoodKind foodKind; //所属类别信息
	protected:
	private:
		
	};

	class HTcMenuInfo
	{
	public:
		HTcMenuInfo()
			:parent_food_id(0),
			food_id(0),
			food_num(0)
		{
		}
		~HTcMenuInfo()
		{
		}

	public:
		int parent_food_id;
		int food_id;
		int food_num;
	};
}
#endif