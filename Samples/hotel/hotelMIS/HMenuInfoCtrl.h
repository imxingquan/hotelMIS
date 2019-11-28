/***********************************************************************
* Module:  HMenuInfoCtrl.h
* Author:  babala
* Modified: 2005��4��25�� 2:29:41
* Purpose: Declaration of the class HMenuInfoCtrl
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/25/05	v1.2 
	��Ȫ	08/28/05	v1.3 
	��Ȫ	04/06/06	��ӷֳ�
--*/
#if !defined(__hotelMIS_HMenuInfoCtrl_h)
#define __hotelMIS_HMenuInfoCtrl_h
#include "config.h"
#include <HMenuInfo.h>
#include <HFoodKind.h>
#include <vector>
#include <string>
using namespace std;
namespace hotelMIS{
	typedef vector<HMenuInfo> HMenuInfoVec;
	typedef vector<HTcMenuInfo> HTcMenuInfoVec;

	class HMenuInfoCtrl
	{
	public:
		HMenuInfoCtrl(mysqlpp::Connection * pCon);
		~HMenuInfoCtrl();
		void insert(HMenuInfo& menuInfo,bool sp = false);
		void update(HMenuInfo& menuInfo);
		void Delete(int foodId,bool sp = false);
		HMenuInfo getMenuInfo(int foodId);
		vector<HMenuInfo> getAllMenuInfo(void);
		vector<HMenuInfo> getAllMenuInfoExceptSpKind(void);
		vector<HMenuInfo> getMenuInfoByKind(int kindId);
		vector<HMenuInfo> getAllMenuInfoRep();
		void AddSpecialMenu(int kindTsId,int foodId);
		bool isExist(int kindId,int foodId);
		
		vector<HMenuInfo> getMenuByCook(int cookId); //���ݳ���ID���ز���

		void AddToChuFang(int cookId, int foodId); //������ӵ��ض�����
		void AddToChuFangByKind(int cookId,int kindId); //�����������ӵ�����
		
		void RemoveFromChuFang(int foodId); //���˴��ض��ĳ�����ɾ��
		void DeleteAll();

		//================================================================
		//�ײ͹���
		//���������ײ����
		HMenuInfoVec getTaoCanList(); 

		//���� �ײ͵�����ϸ��
		HMenuInfoVec getChildMenu(int parent_food_id); 

		//���ײ������
		void addToTaoCan(int parent_food_id,int food_id,int food_num);
		bool isExistTaoCan(int parent_food_id,int food_id);

		//�����ײ���ĳ�������
		int getNum(int parent_food_id,int food_id);

		// ����ƴ�����뷵�ز����б�
		HMenuInfoVec getMenuByPy(string py);

		// ɾ���ײ��е���
		void delTaoCan(int parent_food_id,int food_id);
		
		// ɾ���ײ���������
		void delTaoCan(int parent_food_id);

		//=================================================================		

		int getFoodFlag(int food_id);
		
		// �жϵ�ǰ���Ƿ����ں�����
		bool isHouChu(int flag);

		//================================================================
		// ���ز˵�ʵ��
		static HMenuInfoVec menuInfoFactory();

		//=================================================================
		bool isTaoCan(int food_id);

		//�����ײ�
		HTcMenuInfoVec getTcMenuInfo(int parent_food_id);

		//�������Ʒ��ز˵���ϸ
		HMenuInfo getMenuInfoByName(string name);

	private:
		void _fill(HMenuInfo &menuInfo,mysqlpp::Result &res);
		void _fill_vec(HMenuInfoVec &vec,mysqlpp::Result &res);

		static HMenuInfoVec _menuInfoVec;
	private:
		mysqlpp::Connection * _pCon;
	};
}
#endif