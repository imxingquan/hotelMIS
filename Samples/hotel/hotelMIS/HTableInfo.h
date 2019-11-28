/***********************************************************************
* Module:  HTableInfo.h
* Author:  babala
* Modified: 2005年4月22日 0:52:20
* Purpose: Declaration of the class HTableInfo
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/22/05	v1.2 
	邢泉	08/28/05	v1.3 

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