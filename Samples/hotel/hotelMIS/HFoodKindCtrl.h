/***********************************************************************
* Module:  HFoodKindCtrl.h
* Author:  babala
* Modified: 2005年4月25日 1:53:51
* Purpose: Declaration of the class HFoodKindCtrl
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
#if !defined(__hotelMIS_HFoodKindCtrl_h)
#define __hotelMIS_HFoodKindCtrl_h

#include "config.h"
#include <HFoodKind.h>
#include <vector>
#include <string>
using namespace std;
namespace hotelMIS{
	typedef vector<HFoodKind> HFoodKindVec;
	class HFoodKindCtrl
	{
	public:
		HFoodKindCtrl(mysqlpp::Connection * pCon);
		~HFoodKindCtrl();
		void insert(string name, int flag=0, int ts=0,int kind_zk=0,int zdyprice=0);
		void update(HFoodKind& foodKind);
		void Delete(int kindId);
		HFoodKind getKind(int kindId);
		vector<HFoodKind> getAllKind(void);
		vector<HFoodKind> getTsKind(void);
		vector<HFoodKind> getAllKindExceptTs(void);

		void DeleteAll();
		
		// 检查本类别 id 是不是系统内置
		bool isInnerKind(int kindId);	
		
		// 此菜类下边已经有菜,返回true
		bool haveChild(int kindId);		
		
		// 判断此菜类是否隐藏
		// 消耗品不在菜谱中显示
		bool isHideKind(int kindId);	

		bool isZdyPrice(int kindId);

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif