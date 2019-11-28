/***********************************************************************
* Module:  HFoodKindCtrl.h
* Author:  babala
* Modified: 2005��4��25�� 1:53:51
* Purpose: Declaration of the class HFoodKindCtrl
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/25/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HFoodKindCtrl_h)
#define __hotelMIS_HFoodKindCtrl_h

#include "config.h"
#include <HFoodKind.h>
#include <vector>
#include <string>
using namespace std;
namespace hotelMIS{
	typedef vector<HFoodKind> HFoodKindVec;
	class HFoodKindCtrl
	{
	public:
		HFoodKindCtrl(mysqlpp::Connection * pCon);
		~HFoodKindCtrl();
		void insert(string name, int flag=0, int ts=0,int kind_zk=0,int zdyprice=0);
		void update(HFoodKind& foodKind);
		void Delete(int kindId);
		HFoodKind getKind(int kindId);
		vector<HFoodKind> getAllKind(void);
		vector<HFoodKind> getTsKind(void);
		vector<HFoodKind> getAllKindExceptTs(void);

		void DeleteAll();
		
		// ��鱾��� id �ǲ���ϵͳ����
		bool isInnerKind(int kindId);	
		
		// �˲����±��Ѿ��в�,����true
		bool haveChild(int kindId);		
		
		// �жϴ˲����Ƿ�����
		// ����Ʒ���ڲ�������ʾ
		bool isHideKind(int kindId);	

		bool isZdyPrice(int kindId);

	protected:
	private:
		mysqlpp::Connection * _pCon;


	};
}
#endif