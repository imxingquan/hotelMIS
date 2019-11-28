/***********************************************************************
* Module:  HPayBdy.h
* Author:  babala
* Modified: 2005��5��14�� 11:35:48
* Purpose: Declaration of the class HPayBdy
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    05/14/05	v1.2 
	��Ȫ	08/28/05	v1.3 
	
	��Ȫ    06/04/06	�޸Ľ��˷�ʽ
	ԭ��Ϊ void jz(int reckoning); ���ĳ� 
	void jz(int reckoning,int paystatus);
--*/
#if !defined(__hotelMIS_HPayBdy_h)
#define __hotelMIS_HPayBdy_h
#include <string>
#include "HRepastCtrl.h"
#include "HAccountCtrl.h"
#include "HRepDetailsCtrl.h"
using namespace std;
namespace hotelMIS{
	class HPayBdy
	{
	public:
		HPayBdy(int tableId, int roomId, mysqlpp::Connection* pCon);
		~HPayBdy();
		float getYsPrice(void);
		float calc(float ml, float zk, float sj); //�ѹ���
		
		//����������
		float calc(float ml, float zk, float sj,float zfprice,bool bdaijin,float daijin=0.0f);
		float calc2(float ml, float zk, float sj,float zfprice, bool bdaijin,float daijin=0.0f);
		float myRound(float x);
		float getSsPrice(void);
		
		//void jz(int reckoning);
		// 2006-6-4 ���ӽ��˷�ʽ
		void jz(int reckoning,int paystatus,float zfprice,string bz,int sswr);

		void gz(int reckoning,string bz,int sswr);
		//�˵�
		void cancelMenu(int reckoning,string bz);

		//��Ա������
		void memberJz(int paystatus,float zfprice ,string bh);

	protected:
	private:
		int table_id;
		int room_id;
		HRepastCtrl* repastCtrl;
		HRepDetailsCtrl* repDetailsCtrl;
		HAccountCtrl* accountCtrl;
		string accountId;
		float yscost,yscost2;
		float sscost;
		float subscription;
		float erase_zero;
		float zhekou;
		float daijin;
		float sj;
		float zy;
		
	};
}
#endif