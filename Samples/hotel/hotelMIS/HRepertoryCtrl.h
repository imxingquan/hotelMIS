/***********************************************************************
* Module:  HRepertoryCtrl.h
* Author:  babala
* Modified: 2005年5月1日 23:31:04
* Purpose: Declaration of the class HRepertoryCtrl
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/01/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HRepertoryCtrl_h)
#define __hotelMIS_HRepertoryCtrl_h
#include "config.h"
#include <HRepertory.h>
namespace hotelMIS{
	typedef vector<HRepertory> HRepertoryVec;
	class HRepertoryCtrl
	{
	public:
		HRepertoryCtrl(mysqlpp::Connection * pCon);
		~HRepertoryCtrl();
		/* 入库 */
		void insert(HRepertory& rep,int opType = 0);
		/* 入库调整 */
		void update(HRepertory& rep);
		/* 返回入库记录*/
		HRepertoryVec getAllRepertory(string sDate,string eDate);

		void DeleteAll();

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif