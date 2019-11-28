#include "stdAfx.h"

#include "HAdminBdy.h"
#include "HSetHotelPrintMsg.h"

namespace hotelMIS{
	
	string HAdminBdy::_log_name;
	string HAdminBdy::_ad_name;

	HAdminBdy::HAdminBdy(mysqlpp::Connection* pConn)
	{
		_pConn = pConn;
	}
	
	bool HAdminBdy::login(const string &name, const string &password)
	{
		try{
			mysqlpp::Query query =_pConn->query();
			query << "SELECT ad_log_name,ad_name FROM t_admin WHERE ad_log_name = '"<<name.c_str() << "'"
				<<"AND ad_passwd = '" << password.c_str() << "'";

			mysqlpp::Result result = query.store();
			if ( !result.empty() ){
				mysqlpp::Row row = *result.begin();
				_log_name = name;
				_ad_name = row.lookup_by_name("ad_name");
				return true;
			}
		}mycatch();
		return false;
	}

	HAdmin HAdminBdy::getAdminInfo(const string& name)
	{
		HAdmin admin;
		try{
			mysqlpp::Query query =_pConn->query();
			query << "SELECT * FROM t_admin WHERE ad_log_name = '"<<name.c_str() << "'";
			mysqlpp::Result result = query.store();
			
			mysqlpp::Row row;
			mysqlpp::Result::iterator it;
			for ( it = result.begin(); it != result.end(); it++){
				row = *it;
				int id = row.lookup_by_name("id");
				string log_name = row.lookup_by_name("ad_log_name");
				string ad_name = row.lookup_by_name("ad_name");
				string optype = row.lookup_by_name("optype");
				string desc = row.lookup_by_name("ad_desc");
				admin.setId(id);
				admin.setLoginId(log_name);
				admin.setName(ad_name);
				admin.setOpType(optype);
				admin.setDesc(desc);
			}
			
		}mycatch();
		return admin;
	}
	
	HAdmin HAdminBdy::getLoginUserInfo()
	{
		HAdmin admin;
		try{
			mysqlpp::Query query =_pConn->query();
			query << "SELECT * FROM t_admin WHERE ad_log_name = '"<<_log_name.c_str() << "'";
			mysqlpp::Result result = query.store();
			
			mysqlpp::Row row;
			mysqlpp::Result::iterator it;
			for ( it = result.begin(); it != result.end(); it++){
				row = *it;
				int id = row.lookup_by_name("ad_id");
				string log_name = row.lookup_by_name("ad_log_name");
				string ad_name = row.lookup_by_name("ad_name");
				string password = row.lookup_by_name("ad_passwd");
				string optype = row.lookup_by_name("optype");
				string desc = row.lookup_by_name("ad_desc");
				admin.setId(id);
				admin.setLoginId(log_name);
				admin.setName(ad_name);
				admin.setPassword(password);
				admin.setOpType(optype);
				admin.setDesc(desc);
			}
			
		}mycatch();
		return admin;
	}

	vector<HAdmin> HAdminBdy::getAllAdminInfo()
	{
		vector<HAdmin> vec;
		try{
			mysqlpp::Query query =_pConn->query();
			query << "SELECT * FROM t_admin ";
			mysqlpp::Result result = query.store();
			
			mysqlpp::Row row;
			mysqlpp::Result::iterator it;
			for ( it = result.begin(); it != result.end(); it++){
				HAdmin admin;
				row = *it;
				int id = row.lookup_by_name("ad_id");
				string log_name = row.lookup_by_name("ad_log_name");
				string password = row.lookup_by_name("ad_passwd");
				string ad_name = row.lookup_by_name("ad_name");
				string optype = row.lookup_by_name("optype");
				string desc = row.lookup_by_name("ad_desc");
				admin.setId(id);
				admin.setLoginId(log_name);
				admin.setPassword(password);
				admin.setName(ad_name);
				admin.setOpType(optype);
				admin.setDesc(desc);
				vec.push_back(admin);
			}
			
		}mycatch();
		return vec;
	}
	
	void HAdminBdy::insert(HAdmin& admin)
	{
		try{
			mysqlpp::Query query = _pConn->query();
			query << "INSERT INTO t_admin (ad_log_name,ad_passwd,optype,ad_desc,ad_name) VALUES('"
				<< admin.getLoginId() << "','"
				<< admin.getPassword()<< "','"
				<< admin.getOpType() << "','"
				<< admin.getDesc() << "','"
				<< admin.getName() << "')";
			query.execute();
		}mycatch();
	}
	void HAdminBdy::Delete(int id)
	{
		try{
			mysqlpp::Query query = _pConn->query();
			query << "DELETE FROM t_admin WHERE ad_id ="<<id;
			query.execute();
		}mycatch();
	}
	void HAdminBdy::update(HAdmin& admin)
	{
		try{
			mysqlpp::Query query = _pConn->query();
			query << "UPDATE t_admin SET ad_log_name='"<< admin.getLoginId()<<"',"
				<<"ad_passwd ='"<< admin.getPassword() <<"',"
				<<"optype ='"<< admin.getOpType() <<"',"
				<<"ad_desc='"<<admin.getDesc() <<"',"
				<<"ad_name='"<<admin.getName()<<"' "
				<<"WHERE ad_id = " << admin.getId() ;
			query.execute();
		}mycatch();
	}

	string HAdminBdy::getHotelname()
	{
		hotelMIS::HSetHotelPrintMsg s(_pConn);
		return s.getHotelMsg().hotelname;
		
	}
}