/***********************************************************************
* Module:  HDestineCtrl.h
* Author:  babala
* Modified: 2005年5月12日 18:11:35
* Purpose: Declaration of the class HDestineCtrl
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/12/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HDestineCtrl_h)
#define __hotelMIS_HDestineCtrl_h
#include "config.h"
#include <HDestine.h>
namespace hotelMIS
{
	typedef vector<HDestine> HDestineVec;
	class HDestineCtrl
	{
	public:
		
		HDestineCtrl(mysqlpp::Connection* pCon);
		~HDestineCtrl();
		void insert(HDestine& destine);
		void Delete(int id);
		void update(HDestine& destine);
		HDestine getDestine(int id);
		vector<HDestine> getAllDestine();
		void setWarning(int id);

		void DeleteAll();
	protected:
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif