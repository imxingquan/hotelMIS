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
#include <string>
using namespace std;
namespace hotelMIS{
	class HArrerageZH{
	public:
		HArrerageZH()
			:arid(0),
			guest_name(""),
			guest_phone(""),
			guest_dept(""),
			ar_memo(""),
			cw(0)
		{}
		~HArrerageZH(){}
	
		int arid;
		string guest_name;
		string guest_phone;
		string guest_dept;
		string ar_memo;
		int cw;
	};

	class HArrerage{
	public:
		HArrerage(){}
		~HArrerage(){}
		int arid;
		string account_id;
		string ar_date;
	};

	
}