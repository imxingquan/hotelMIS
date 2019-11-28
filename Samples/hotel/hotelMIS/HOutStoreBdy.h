/***********************************************************************
* Module:  HOutStoreBdy.h
* Author:  babala
* Modified: 2005年5月11日 2:53:44
* Purpose: Declaration of the class HOutStoreBdy
* Comment: 出库界面类
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/11/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HOutStoreBdy_h)
#define __hotelMIS_HOutStoreBdy_h
#include "config.H"
#include <string>
using namespace std;
namespace hotelMIS{

	class HOutStoreBdy
	{
	public:
		HOutStoreBdy(mysqlpp::Connection *pCon);
		~HOutStoreBdy();
		int outStore(string accountId, int foodId, int foodNum);
		int revertRep(string accountId, int foodId, int foodNum);

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif