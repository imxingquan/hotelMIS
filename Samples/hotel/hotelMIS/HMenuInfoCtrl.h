/***********************************************************************
* Module:  HMenuInfoCtrl.h
* Author:  babala
* Modified: 2005年4月25日 2:29:41
* Purpose: Declaration of the class HMenuInfoCtrl
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
	邢泉	04/06/06	添加分厨
--*/
#if !defined(__hotelMIS_HMenuInfoCtrl_h)
#define __hotelMIS_HMenuInfoCtrl_h
#include "config.h"
#include <HMenuInfo.h>
#include <HFoodKind.h>
#include <vector>
#include <string>
using namespace std;
namespace hotelMIS{
	typedef vector<HMenuInfo> HMenuInfoVec;
	typedef vector<HTcMenuInfo> HTcMenuInfoVec;

	class HMenuInfoCtrl
	{
	public:
		HMenuInfoCtrl(mysqlpp::Connection * pCon);
		~HMenuInfoCtrl();
		void insert(HMenuInfo& menuInfo,bool sp = false);
		void update(HMenuInfo& menuInfo);
		void Delete(int foodId,bool sp = false);
		HMenuInfo getMenuInfo(int foodId);
		vector<HMenuInfo> getAllMenuInfo(void);
		vector<HMenuInfo> getAllMenuInfoExceptSpKind(void);
		vector<HMenuInfo> getMenuInfoByKind(int kindId);
		vector<HMenuInfo> getAllMenuInfoRep();
		void AddSpecialMenu(int kindTsId,int foodId);
		bool isExist(int kindId,int foodId);
		
		vector<HMenuInfo> getMenuByCook(int cookId); //根据厨房ID返回菜谱

		void AddToChuFang(int cookId, int foodId); //将菜添加到特定厨房
		void AddToChuFangByKind(int cookId,int kindId); //将整个类别添加到厨房
		
		void RemoveFromChuFang(int foodId); //将菜从特定的厨房中删除
		void DeleteAll();

		//================================================================
		//套餐管理
		//返回所有套餐类别
		HMenuInfoVec getTaoCanList(); 

		//返回 套餐的所有细节
		HMenuInfoVec getChildMenu(int parent_food_id); 

		//向套餐中添加
		void addToTaoCan(int parent_food_id,int food_id,int food_num);
		bool isExistTaoCan(int parent_food_id,int food_id);

		//返回套餐中某项的数量
		int getNum(int parent_food_id,int food_id);

		// 根据拼音简码返回菜谱列表
		HMenuInfoVec getMenuByPy(string py);

		// 删除套餐中的项
		void delTaoCan(int parent_food_id,int food_id);
		
		// 删除套餐中所有项
		void delTaoCan(int parent_food_id);

		//=================================================================		

		int getFoodFlag(int food_id);
		
		// 判断当前菜是否属于后厨类别
		bool isHouChu(int flag);

		//================================================================
		// 返回菜单实例
		static HMenuInfoVec menuInfoFactory();

		//=================================================================
		bool isTaoCan(int food_id);

		//返回套餐
		HTcMenuInfoVec getTcMenuInfo(int parent_food_id);

		//根据名称返回菜单详细
		HMenuInfo getMenuInfoByName(string name);

	private:
		void _fill(HMenuInfo &menuInfo,mysqlpp::Result &res);
		void _fill_vec(HMenuInfoVec &vec,mysqlpp::Result &res);

		static HMenuInfoVec _menuInfoVec;
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif