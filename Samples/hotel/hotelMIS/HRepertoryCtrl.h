/***********************************************************************
* Module:  HRepertoryCtrl.h
* Author:  babala
* Modified: 2005��5��1�� 23:31:04
* Purpose: Declaration of the class HRepertoryCtrl
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/01/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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
		/* ��� */
		void insert(HRepertory& rep,int opType = 0);
		/* ������ */
		void update(HRepertory& rep);
		/* ��������¼*/
		HRepertoryVec getAllRepertory(string sDate,string eDate);

		void DeleteAll();

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif