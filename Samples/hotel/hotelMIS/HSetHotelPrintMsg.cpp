#include "stdAfx.h"

#include "HSetHotelPrintMsg.h"
using namespace hotelMIS;

HSetHotelPrintMsg::HSetHotelPrintMsg(mysqlpp::Connection* pCon)
{
	_pCon  = pCon;
}

HSetHotelPrintMsg::~HSetHotelPrintMsg()
{
}

void HSetHotelPrintMsg::Update(string hotelname,string hoteltel,string hoteltel2,string hotelhttp)
{
	 try{
         mysqlpp::Query query = _pCon->query();
		 query << "UPDATE t_hotelmsg SET hotelname ='"
			 <<hotelname<<"',"
			 <<"hoteltel='"<<hoteltel<<"',"
			 <<"hoteltel2='"<<hoteltel2<<"',"
			 <<"hotelhttp='"<<hotelhttp<<"'";
		 query.execute();
	}mycatch();
}

HotelMsg HSetHotelPrintMsg::getHotelMsg()
{
	HotelMsg msg;
	try{
		mysqlpp::Query query = _pCon->query();
		query<< "SELECT * FROM t_hotelmsg";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it = res.begin() ;
		mysqlpp::Row row;
		if ( !res.empty())
		{
			row = *it;
			msg.hotelname = row.lookup_by_name("hotelname");
			msg.hoteltel = row.lookup_by_name("hoteltel");
			msg.hoteltel2 = row.lookup_by_name("hoteltel2");
			msg.hotelhttp = row.lookup_by_name("hotelhttp");
		}
	}mycatch();
	return msg;
}