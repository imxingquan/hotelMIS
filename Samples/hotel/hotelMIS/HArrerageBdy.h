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
		//����
		int Add(string gzName,string gzPhone,string gzDept,string gzMemo,int cw);  //��Ӳ���
		int Delete(int arid); //ɾ������
        int Modify(int arid,string gzName,string gzPhone,string gzDept,string gzMemo,int cw);  //�޸Ĳ���
		hotelMIS::HArrerageZHVec getAllZH();
		hotelMIS::HArrerageZH getArrerageZH(int arid);

		//����
		void gz(int arid,string accoundId);
		//
		void tranToAcc(int tableId,int roomId,string accountId,float gz);
		
		//����arid �����������Ϣ
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