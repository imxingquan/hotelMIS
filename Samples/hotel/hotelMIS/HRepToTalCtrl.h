/***********************************************************************
* Module:  HRepToTalCtrl.h
* Author:  babala
* Modified: 2005��5��4�� 3:45:29
* Purpose: Declaration of the class HRepToTalCtrl
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/04/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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