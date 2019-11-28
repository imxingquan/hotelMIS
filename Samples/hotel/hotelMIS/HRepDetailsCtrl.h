/***********************************************************************
* Module:  HRepDetailsCtrl.h
* Author:  babala
* Modified: 2005��5��6�� 21:38:14
* Purpose: Declaration of the class HRepDetailsCtrl
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/06/05	v1.2 
	��Ȫ	08/28/05	v1.3 
	��Ȫ	04/07/06	�ֳ���ȡ��
	��Ȫ    2006-06-04	������Ͳ�
--*/
#if !defined(__hotelMIS_HRepDetailsCtrl_h)
#define __hotelMIS_HRepDetailsCtrl_h
#include "config.h"
#include <HRepDetails.h>
namespace hotelMIS{
	typedef vector<HRepDetails> HRepDetailsVec;
	typedef pair<float,float> HTotalPair;
	class HRepDetailsCtrl
	{
	public:
		HRepDetailsCtrl(mysqlpp::Connection * pCon);
		~HRepDetailsCtrl();
		void insert(HRepDetails& repDetails);
		void Delete(string accountId, int foodId);
		void Delete(string accountId);
		void Delete(int id ); //����idɾ��
		void Delete(int id,int foodNum); //����id��������
		void update(string accountId, int foodId, int foodNum,bool bAdd = true);
		void update(string accountId, float zk_num);

		int getFoodNum(string accountId, int foodId);
		vector<HRepDetails> getAllDetails(string accountId);
		HRepDetails getRepDetails(string accountId,int foodId);
		HTotalPair getAllPrice(string accountId);
		bool isExistFoodInAccId(string accountId,int foodId);
		bool isExistAccountId(string accountId);
		void transferToAccDetails(string accountId);

		//�ֳ���ȡ��
		vector<HRepDetails> getFengchu(string accountId,int foodCook); //foodCook = 0 ���, 1 ����, 2 �Ȳ�
		//����id����ȡ�ز���
		vector<HRepDetails> getDetailsByIdVec(vector<int> &vecId);

		//get id
		int GetID();
		//�˲�
		void foodCancel(int id,int num,string msg);
		
		//����idȡ�˵���ϸ����
		HRepDetails getDetailsById(int id);

		//����˲˿��õ�����
		int getCancelNum(string accountId,int foodId);

		void DeleteAll();

		//����
		void foodAward(int id);
		void update(HRepDetails &hRepDetails);
		//��ò˵�״̬
		int getFoodStatus(int id); //
	protected:
		

	protected:
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif