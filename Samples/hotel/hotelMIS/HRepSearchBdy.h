/***********************************************************************
* Module:  HRepSearchBdy.h
* Author:  babala
* Modified: 2005��5��28�� 14:31:53
* Purpose: Declaration of the class HRepSearchBdy
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/28/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HRepSearchBdy_h)
#define __hotelMIS_HRepSearchBdy_h

#include <KDBCon.h>
#include <HOutStoreCtrl.h>
#include <HRepertoryCtrl.h>
#include <HRepTotalCtrl.h>

namespace hotelMIS{
	class HRepSearchBdy
	{
	public:
		HRepSearchBdy();
		~HRepSearchBdy();
		HRepTotalVec RestRepSearch(void);
		HRepertoryVec InRepSearch(string startDate, string endDate);
		HOutStoreVec OutRepSearch(string startDate, string endDate);

	protected:
	private:
		hotelMIS::HOutStoreCtrl* pOutStoreCtrl;
		hotelMIS::HRepertoryCtrl* pRepertoryCtrl;
		hotelMIS::HRepToTalCtrl* pRepTotalCtrl;
		hotelMIS::KDBCon m_con;
	};
}
#endif