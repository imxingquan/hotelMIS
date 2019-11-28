/***********************************************************************
* Module:  HTableInfo.h
* Author:  babala
* Modified: 2005��4��22�� 0:52:20
* Purpose: Declaration of the class HTableInfo
***********************************************************************/
/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/22/05	v1.2 
	��Ȫ	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HTableInfo_h)
#define __hotelMIS_HTableInfo_h
//#include "HTableStatusCtrl.h"
#include <string>
using namespace std;
namespace hotelMIS{
	class HTableInfo
	{
	public:
		HTableInfo();
		~HTableInfo();
		int getTable_id(void);
		void setTable_id(int newTable_id);
		int getRoom_id(void);
		void setRoom_id(int newRoom_id);
		string getRoom_name(void);
		void setRoom_name(string newRoom_name);
		string getState_name(void);
		void setState_name(string newState_name);
		int getPerson_num(void);
		void setPerson_num(int newPerson_num);
		int getRe_state(void);
		void setRe_state(int newRe_state);
		friend class HTableStatusCtrl;
	
		int table_id;
		int room_id;
		string room_name;
		string state_name;
		int person_num;
		int re_state;

	};
}
#endif