/***********************************************************************
 * Module:  HJobSetCtrl.h
 * Author:  babala
 * Modified: 2005��4��23�� 17:27:41
 * Purpose: Declaration of the class HJobSetCtrl
 ***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HJobSetCtrl_h)
#define __hotelMIS_HJobSetCtrl_h
#include "config.h"
#include "HJobSet.h"
#include <vector>
using namespace std;
namespace hotelMIS{
	typedef vector<HJobSet> HJobSetVec;
	class HJobSetCtrl
	{
	public:
		HJobSetCtrl(mysqlpp::Connection * pCon);
		~HJobSetCtrl();
		void insert(string jobName);
		void Delete(int jobId);
		vector<HJobSet> getAllJob(void);
		HJobSet get(int id);
		void Update(HJobSet &jobSet);
	protected:
	private:
		mysqlpp::Connection* _pCon;


	};
}
#endif