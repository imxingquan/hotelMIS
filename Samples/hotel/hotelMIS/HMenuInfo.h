/***********************************************************************
* Module:  HMenuInfo.h
* Author:  babala
* Modified: 2005��4��25�� 2:29:10
* Purpose: Declaration of the class HMenuInfo
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
	��Ȫ    2006-6-5	���ƴ����������

--*/
#if !defined(__hotelMIS_HMenuInfo_h)
#define __hotelMIS_HMenuInfo_h
#include <HFoodKind.h>
#include <string>
using namespace std;
namespace hotelMIS{
	class HMenuInfo
	{
	public:
		HMenuInfo();
		~HMenuInfo();
		
		enum MENU_STATUS{
			TC = -11	,		//�ײ�: -11
			REP_CALC = 1,		//��沢���� : 1
			REP_NOCALC = 2,		//��治���� : 2
			REP_NO = 0			//�������	 : 0
		}; 

	public:
		int food_id;		//id
		int kind_id;		//����id
		string food_name;	//����
		int food_num;		//����
		float food_price;	//����
		string food_unit;	//��λ
		
		int repertory_flag;	//�Ƿ������/�����

		string ck_name;		//��ʦ��
		int food_cook;		//����
		string food_py;		//ƴ������
		
		bool bTaocan;		//�ײ�
		
		int total_fl;		//ͳ�Ʒ���
		HFoodKind foodKind; //���������Ϣ
	protected:
	private:
		
	};

	class HTcMenuInfo
	{
	public:
		HTcMenuInfo()
			:parent_food_id(0),
			food_id(0),
			food_num(0)
		{
		}
		~HTcMenuInfo()
		{
		}

	public:
		int parent_food_id;
		int food_id;
		int food_num;
	};
}
#endif