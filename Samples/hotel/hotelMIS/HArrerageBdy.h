/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    05/22/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once

#include "config.h"
#include "KDBCon.h"
//#include <HArrerageZH.h>
#include <HArrerageCtrl.h>
#include <HArrerageBdy.h>
#include <HAccountCtrl.h>
#include <map>
#include <string>
#include <cassert>
using namespace std;

namespace hotelMIS{
	class HArrerageBdy{
	public:
		HArrerageBdy();
		~HArrerageBdy();
	public:
		//操作
		int Add(string gzName,string gzPhone,string gzDept,string gzMemo,int cw);  //添加操作
		int Delete(int arid); //删除操作
        int Modify(int arid,string gzName,string gzPhone,string gzDept,string gzMemo,int cw);  //修改操作
		hotelMIS::HArrerageZHVec getAllZH();
		hotelMIS::HArrerageZH getArrerageZH(int arid);

		//挂账
		void gz(int arid,string accoundId);
		//
		void tranToAcc(int tableId,int roomId,string accountId,float gz);
		
		//根据arid 返回其挂账信息
		hotelMIS::HArrerageVec getArrerageByArId(int arid);
		
		float getPriceByAccountId(string accountId);
		void writeArrIdtoAccount(int arid,string accountId);

		hotelMIS::HArrerageCtrl * getArrerageCtrl(){
			assert(pArrCtrl != NULL);
			return pArrCtrl;
		}
		
		hotelMIS::HArrerageZHCtrl * getArrerageZHCtrl(){
			assert(pArrZHCtrl != NULL);
			return pArrZHCtrl;
		}
		
		hotelMIS::HAccountCtrl * getAccountCtrl(){
			assert(pAccountCtrl != NULL);
			return pAccountCtrl;
		}
	private:
		hotelMIS::HArrerageCtrl *pArrCtrl;
		hotelMIS::HArrerageZHCtrl *pArrZHCtrl;
		hotelMIS::HAccountCtrl *pAccountCtrl;
		hotelMIS::KDBCon m_con;
	};
}