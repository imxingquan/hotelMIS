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
#include <HarrerageZH.h>
#include "config.h"

namespace hotelMIS{
	typedef vector<HArrerageZH> HArrerageZHVec;
	class HArrerageZHCtrl{
	public:
		HArrerageZHCtrl(mysqlpp::Connection* pCon);
		~HArrerageZHCtrl();
		void insertZH(HArrerageZH arrerageZH);
		void updateZH(HArrerageZH arrerageZH);
		void DeleteZH(int arid);
		HArrerageZHVec getAll();
		HArrerageZH getArrerageZH(int arid);
		bool isExitGZName(string gzName);

		//设置结余剩余
		void setJZRest(int arid,float price);
		float getJZRest(int arid);
	
		void DeleteAll();
	private:
		mysqlpp::Connection * _pCon;
	};

	//挂账
	typedef vector<HArrerage> HArrerageVec;
	class HArrerageCtrl{
	public:
		HArrerageCtrl(mysqlpp::Connection* pCon);
		~HArrerageCtrl();
		void insert(HArrerage arrerage);
		void Delete(int arid);
		HArrerageVec getAll();
		HArrerageVec getByArId(int arid);
		
		void DeleteByAccountId(string accountId); //结完账，然后将账单号从挂账账户中清除
		void writeArrIdtoAccount(int arid,string accountId);
		void DeleteAll();
	private:
		mysqlpp::Connection *_pCon;
	};
}