/***********************************************************************
* Module:  HOutStoreBdy.h
* Author:  babala
* Modified: 2005��5��11�� 2:53:44
* Purpose: Declaration of the class HOutStoreBdy
* Comment: ���������
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/11/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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