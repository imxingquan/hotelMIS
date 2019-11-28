/***********************************************************************
* Module:  HPayBdy.h
* Author:  babala
* Modified: 2005年5月14日 11:35:48
* Purpose: Declaration of the class HPayBdy
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/14/05	v1.2 
	邢泉	08/28/05	v1.3 
	
	邢泉    06/04/06	修改结账方式
	原来为 void jz(int reckoning); 更改成 
	void jz(int reckoning,int paystatus);
--*/
#if !defined(__hotelMIS_HPayBdy_h)
#define __hotelMIS_HPayBdy_h
#include <string>
#include "HRepastCtrl.h"
#include "HAccountCtrl.h"
#include "HRepDetailsCtrl.h"
using namespace std;
namespace hotelMIS{
	class HPayBdy
	{
	public:
		HPayBdy(int tableId, int roomId, mysqlpp::Connection* pCon);
		~HPayBdy();
		float getYsPrice(void);
		float calc(float ml, float zk, float sj); //已过期
		
		//含代金卷结账
		float calc(float ml, float zk, float sj,float zfprice,bool bdaijin,float daijin=0.0f);
		float calc2(float ml, float zk, float sj,float zfprice, bool bdaijin,float daijin=0.0f);
		float myRound(float x);
		float getSsPrice(void);
		
		//void jz(int reckoning);
		// 2006-6-4 增加结账方式
		void jz(int reckoning,int paystatus,float zfprice,string bz,int sswr);

		void gz(int reckoning,string bz,int sswr);
		//退单
		void cancelMenu(int reckoning,string bz);

		//会员卡结账
		void memberJz(int paystatus,float zfprice ,string bh);

	protected:
	private:
		int table_id;
		int room_id;
		HRepastCtrl* repastCtrl;
		HRepDetailsCtrl* repDetailsCtrl;
		HAccountCtrl* accountCtrl;
		string accountId;
		float yscost,yscost2;
		float sscost;
		float subscription;
		float erase_zero;
		float zhekou;
		float daijin;
		float sj;
		float zy;
		
	};
}
#endif