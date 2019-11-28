/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "config.h"
namespace hotelMIS{
	class HotelMsg
	{
	public:
		HotelMsg()
			:hotelname("")
			,hoteltel("")
			,hotelhttp("")
			,hoteltel2("")
		{

		}
		string hotelname;
		string hoteltel;
		string hoteltel2;
		string hotelhttp;
	};

	class HSetHotelPrintMsg{
	public:

		HSetHotelPrintMsg(mysqlpp::Connection* pCon);
		~HSetHotelPrintMsg();
	public:
		void Update(string hotelname,string hoteltel,string hoteltel2,string hotelhttp);
		HotelMsg getHotelMsg();
	private:
		mysqlpp::Connection * _pCon;
	};
}