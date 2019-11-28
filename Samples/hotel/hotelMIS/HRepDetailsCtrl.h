/***********************************************************************
* Module:  HRepDetailsCtrl.h
* Author:  babala
* Modified: 2005年5月6日 21:38:14
* Purpose: Declaration of the class HRepDetailsCtrl
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/06/05	v1.2 
	邢泉	08/28/05	v1.3 
	邢泉	04/07/06	分厨房取菜
	邢泉    2006-06-04	添加赠送菜
--*/
#if !defined(__hotelMIS_HRepDetailsCtrl_h)
#define __hotelMIS_HRepDetailsCtrl_h
#include "config.h"
#include <HRepDetails.h>
namespace hotelMIS{
	typedef vector<HRepDetails> HRepDetailsVec;
	typedef pair<float,float> HTotalPair;
	class HRepDetailsCtrl
	{
	public:
		HRepDetailsCtrl(mysqlpp::Connection * pCon);
		~HRepDetailsCtrl();
		void insert(HRepDetails& repDetails);
		void Delete(string accountId, int foodId);
		void Delete(string accountId);
		void Delete(int id ); //根据id删除
		void Delete(int id,int foodNum); //根据id减少数量
		void update(string accountId, int foodId, int foodNum,bool bAdd = true);
		void update(string accountId, float zk_num);

		int getFoodNum(string accountId, int foodId);
		vector<HRepDetails> getAllDetails(string accountId);
		HRepDetails getRepDetails(string accountId,int foodId);
		HTotalPair getAllPrice(string accountId);
		bool isExistFoodInAccId(string accountId,int foodId);
		bool isExistAccountId(string accountId);
		void transferToAccDetails(string accountId);

		//分厨房取菜
		vector<HRepDetails> getFengchu(string accountId,int foodCook); //foodCook = 0 面点, 1 凉菜, 2 热菜
		//根据id集合取回菜谱
		vector<HRepDetails> getDetailsByIdVec(vector<int> &vecId);

		//get id
		int GetID();
		//退菜
		void foodCancel(int id,int num,string msg);
		
		//根据id取菜的详细资料
		HRepDetails getDetailsById(int id);

		//获得退菜可用的数量
		int getCancelNum(string accountId,int foodId);

		void DeleteAll();

		//赠送
		void foodAward(int id);
		void update(HRepDetails &hRepDetails);
		//获得菜的状态
		int getFoodStatus(int id); //
	protected:
		

	protected:
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif