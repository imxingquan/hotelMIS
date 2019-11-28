/***********************************************************************
* Module:  HRepToTalCtrl.h
* Author:  babala
* Modified: 2005年5月4日 3:45:29
* Purpose: Declaration of the class HRepToTalCtrl
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
#if !defined(__hotelMIS_HRepToTalCtrl_h)
#define __hotelMIS_HRepToTalCtrl_h
#include "config.h"
#include <HRepTotal.h>

namespace hotelMIS{
	typedef vector<HRepTotal> HRepTotalVec;
	class HRepToTalCtrl
	{
	public:
		HRepToTalCtrl(mysqlpp::Connection * pCon);
		~HRepToTalCtrl();
		void insert(int foodId, int totalNum=0);
		void Delete(int foodId);
		void addNum(int foodId, int repNum);
		void delNum(int foodId, int repNum);
		int  getNum(int foodId);
		bool isExist(int foodId);
		HRepTotalVec getAllRepTotal();

		void DeleteAll();
	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif