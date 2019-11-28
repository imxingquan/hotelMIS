/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/22/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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

		//���ý���ʣ��
		void setJZRest(int arid,float price);
		float getJZRest(int arid);
	
		void DeleteAll();
	private:
		mysqlpp::Connection * _pCon;
	};

	//����
	typedef vector<HArrerage> HArrerageVec;
	class HArrerageCtrl{
	public:
		HArrerageCtrl(mysqlpp::Connection* pCon);
		~HArrerageCtrl();
		void insert(HArrerage arrerage);
		void Delete(int arid);
		HArrerageVec getAll();
		HArrerageVec getByArId(int arid);
		
		void DeleteByAccountId(string accountId); //�����ˣ�Ȼ���˵��Ŵӹ����˻������
		void writeArrIdtoAccount(int arid,string accountId);
		void DeleteAll();
	private:
		mysqlpp::Connection *_pCon;
	};
}