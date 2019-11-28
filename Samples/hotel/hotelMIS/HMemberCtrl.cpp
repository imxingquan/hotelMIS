//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HMemberCtrl.cpp
//
// Description:    
//			   实现对 HMember 的数据库基础操作
//
// Version: 1.4
//
// Hostory:		
//			06-03-2006	邢泉	Created	
//			
//---------------------------------------------------------
#include "stdAfx.h"
#include "HMemberCtrl.h"

using namespace hotelMIS;

HMemberCtrl::HMemberCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HMemberCtrl::~HMemberCtrl()
{

}

//
// 数据库基础操作
//
void HMemberCtrl::insert(HMember &hMember)
{
	try{
	mysqlpp::Query query = _pCon->query();
	query << "INSERT INTO t_member(bh,mname,sex,mbirth,telphone,mdjid,mdjname,zhekou,czmoney,rhdate,remark) VALUES( '"
		  << hMember.bh << "','"
		  << hMember.mname << "','"
		  << hMember.sex << "','"
		  << hMember.mbirth <<"','"
		  << hMember.telphone<<"',"
		  << hMember.mdjid <<",'"
		  << hMember.mdjname<<"',"
		  << hMember.zhekou <<","
		  << hMember.czmoney<<",'"
		  << hMember.rhdate <<"','"
		  << hMember.remark <<"')";

	query.execute();
	
	}mycatch();
}


void HMemberCtrl::update(HMember &hMember)
{
	try{
	mysqlpp::Query query = _pCon->query();
	query << "UPDATE t_member SET mname='"
		  << hMember.mname <<"',"
		  << "mbirth='" << hMember.mbirth<<"',"
		  << "sex='"<<hMember.sex<<"',"
		  << "telphone='"<<hMember.telphone<<"',"
		  << "mdjid="<<hMember.mdjid<<","
		  << "mdjname='"<<hMember.mdjname<<"',"
		  << "zhekou="<<hMember.zhekou<<","
		  //<< "czmoney="<<hMember.czmoney<<","
		 // << "rhdate='"<<hMember.rhdate<<"',"
		  << "remark='"<<hMember.remark<<"'"
		  << " WHERE bh='"<<hMember.bh <<"'";
	query.execute();
	
	}mycatch();
}

void HMemberCtrl::Delete(string bh)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_member WHERE bh='"<<bh<<"'";
		query.execute();
	}mycatch();
}

void HMemberCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_member ";
		query.execute();
	}mycatch();
}

HMember HMemberCtrl::getMember(string bh)
{
	HMember hMember;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_member WHERE bh='"<<bh<<"'";
		 mysqlpp::Result res = query.store();
         mysqlpp::Result::iterator it;
         mysqlpp::Row row;
		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 hMember.bh = bh;
			 hMember.czmoney = row.lookup_by_name("czmoney");
			 hMember.mbirth = row.lookup_by_name("mbirth");
			 hMember.mdjid = row.lookup_by_name("mdjid");
			 hMember.mdjname = row.lookup_by_name("mdjname");
			 hMember.sex = row.lookup_by_name("sex");
			 hMember.mname = row.lookup_by_name("mname");
			 hMember.rhdate = row.lookup_by_name("rhdate");
			 hMember.telphone = row.lookup_by_name("telphone");
			 hMember.zhekou = row.lookup_by_name("zhekou");
			 hMember.remark = row.lookup_by_name("remark");
		 }
	}mycatch();
	return hMember;
}

HMemberVec HMemberCtrl::getAllMember()
{
	HMemberVec hMemberVec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_member ";
		 mysqlpp::Result res = query.store();
         mysqlpp::Result::iterator it;
         mysqlpp::Row row;
		 HMember hMember;
		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 hMember.bh = row.lookup_by_name("bh");
			 hMember.czmoney = row.lookup_by_name("czmoney");
			 hMember.mbirth = row.lookup_by_name("mbirth");
			 hMember.mdjid = row.lookup_by_name("mdjid");
			 hMember.mdjname = row.lookup_by_name("mdjname");
			 hMember.sex = row.lookup_by_name("sex");
			 hMember.mname = row.lookup_by_name("mname");
			 hMember.rhdate = row.lookup_by_name("rhdate");
			 hMember.telphone = row.lookup_by_name("telphone");
			 hMember.zhekou = row.lookup_by_name("zhekou");
			 hMember.remark = row.lookup_by_name("remark");
			 hMemberVec.push_back(hMember);
		 }
	}mycatch();
	return hMemberVec;
}

HMember HMemberCtrl::getByName(string name)
{
	HMember hMember;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_member WHERE mname='"<< name <<"'";
		 mysqlpp::Result res = query.store();
         mysqlpp::Result::iterator it;
         mysqlpp::Row row;
		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 hMember.bh = row.lookup_by_name("bh");
			 hMember.czmoney = row.lookup_by_name("czmoney");
			 hMember.mbirth = row.lookup_by_name("mbirth");
			 hMember.mdjid = row.lookup_by_name("mdjid");
			 hMember.mdjname = row.lookup_by_name("mdjname");
			 hMember.mname = row.lookup_by_name("mname");
			 hMember.sex = row.lookup_by_name("sex");
			 hMember.rhdate = row.lookup_by_name("rhdate");
			 hMember.telphone = row.lookup_by_name("telphone");
			 hMember.zhekou = row.lookup_by_name("zhekou");
			 hMember.remark = row.lookup_by_name("remark");
		 }
	}mycatch();
	return hMember;
}


bool HMemberCtrl::isExist(string bh)
{
	//已经存在
	
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_member WHERE bh='"<< bh <<"'";
		 mysqlpp::Result res = query.store();
		 if ( res.empty() )
			 return false;
	}mycatch();
	return true;
}	

void HMemberCtrl::cz(string bh,float czmoney)
{
	//会员充值
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_member SET czmoney = czmoney+"
			  << czmoney
			  << " WHERE bh ='"
			  << bh << "'";
		query.execute();
	}mycatch();
}
void HMemberCtrl::xf(string bh,float czmoney)
{
	//会员消费
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_member SET czmoney = czmoney-"
			  << czmoney
			  << " WHERE bh ='"
			  << bh << "'";
		query.execute();
	}mycatch();
}

void HMemberCtrl::zz(string sbh,string dbh, float zzmoney)
{
	//会员转账
	
	try{
		mysqlpp::Query query = _pCon->query();
		//源账户减少
		query << "UPDATE t_member SET czmoney = czmoney-"
			<< zzmoney
			<< " WHERE bh='"
			<< sbh <<"'";
		query.execute();
		//目的账户增加
		query << "UPDATE t_member SET czmoney = czmoney+"
			<< zzmoney
			<< " WHERE bh='"
			<< dbh <<"'";
		query.execute();
	}mycatch();
}

//=========================================================================================
// HMdjCtrl

HMdjCtrl::HMdjCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HMdjCtrl::~HMdjCtrl()
{
}


void HMdjCtrl::insert(string djname,float zhekou)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_mdj (djname,zhekou) VALUES('"
			<<djname<<"',"
			<<zhekou<<")";
		query.execute();
	}mycatch();
}

void HMdjCtrl::Delete(int id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mdj WHERE id="<< id;
		query.execute();
	}mycatch();
}

//-------------------------------------------------------------------------------------------------
void HMdjCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mdj";
		query.execute();
	}mycatch();
}
//--------------------------------------------------------------------------------------------------
void HMdjCtrl::Update(int id,string djname,float zhekou)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_mdj SET "
			<< "djname='"<< djname <<"',"
			<< "zhekou="<<zhekou
			<< " WHERE id="<< id;
		query.execute();
	}mycatch();
}

HMdj HMdjCtrl::getMdj(int id)
{
	HMdj hMdj;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_mdj WHERE id="<< id;
		mysqlpp::Result::iterator it;
        mysqlpp::Row row;
		mysqlpp::Result res = query.store();
			 
		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 hMdj.id = id;
			 hMdj.djname = row.lookup_by_name("djname");
			 hMdj.zhekou = row.lookup_by_name("zhekou");
		 }
		
	}mycatch();
	return hMdj;
}

HMdjVec HMdjCtrl::getAllMdj()
{
	HMdjVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_mdj ";
		mysqlpp::Result::iterator it;
        mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		
		 HMdj hMdj;
		 for ( it = res.begin(); it != res.end(); it++)
		 {
			 row = *it;
			 hMdj.id = row.lookup_by_name("id");
			 hMdj.djname = row.lookup_by_name("djname");
			 hMdj.zhekou = row.lookup_by_name("zhekou");
			 
			 vec.push_back(hMdj);
		 }
	}mycatch();
	return vec;
}


//===================================================================================================
// HMczCtrl
HMczCtrl::HMczCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

HMczCtrl::~HMczCtrl()
{
}

//-------------------------------------------------------------------------------------------------------
void HMczCtrl::insert(HMcz &hmcz)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_mcz(bh,czmoney,czdate,opname,remark) VALUES('"
			<< hmcz.bh << "',"
			<< hmcz.czmoney << ",'"
			<< hmcz.czdate <<"','"
			<< hmcz.opname <<"','"
			<< hmcz.remark <<"')";
		query.execute();
	}mycatch();
}

//---------------------------------------------------------------------------------------------------------
void HMczCtrl::Delete(int id)
{
	try{
			mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mcz WHERE id = "<< id;
		query.execute();
	}mycatch();
}

//------------------------------------------------------------------------------------------------------------
HMczVec HMczCtrl::getAllMcz()
{
	HMczVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_mcz ";
		mysqlpp::Result::iterator it;
        mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		HMcz hmcz;

		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			hmcz.bh = row.lookup_by_name("bh");
			hmcz.czdate = row.lookup_by_name("czdate");
			hmcz.czmoney = row.lookup_by_name("czmoney");
			hmcz.id = row.lookup_by_name("id");
			hmcz.opname = row.lookup_by_name("opname");
			hmcz.remark = row.lookup_by_name("remark");

			vec.push_back(hmcz);
		}
	}mycatch();

	return vec;
}

//----------------------------------------------------------------------------------------------------------------
HMczVec HMczCtrl::getMCz(string d1,string d2,string bh)
{
	HMczVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		if ( bh.empty() ){
			query << "SELECT * FROM t_mcz WHERE date_format(czdate,'%Y-%m-%d')>='"<<d1<<"' AND date_format(czdate,'%Y-%m-%d') <='"<< d2<<"'";
		}else{
			query << "SELECT * FROM t_mcz WHERE date_format(czdate,'%Y-%m-%d')>='"<<d1<<"' AND date_format(czdate,'%Y-%m-%d') <='"<< d2<<"' AND bh='"<< bh<<"'";
		}
		mysqlpp::Result::iterator it;
		mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		HMcz hmcz;
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			hmcz.bh = row.lookup_by_name("bh");
			hmcz.czdate = row.lookup_by_name("czdate");
			hmcz.czmoney = row.lookup_by_name("czmoney");
			hmcz.id = row.lookup_by_name("id");
			hmcz.opname = row.lookup_by_name("opname");
			hmcz.remark = row.lookup_by_name("remark");

			vec.push_back(hmcz);
		}
	}mycatch();
	return vec;
}
//-----------------------------------------------------------------------------------------------------------------
void HMczCtrl::Delete(string bh)
{
	try{
			mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mcz WHERE bh = '"<< bh <<"'";
		query.execute();
	}mycatch();
}

//-------------------------------------------------------------------------------------------------------------------
void HMczCtrl::DeleteAll()
{
	try{
			mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mcz ";
		query.execute();
	}mycatch();

}

//================================================================================================================
//	class HMzzCtrl

HMzzCtrl::HMzzCtrl(mysqlpp::Connection *pCon)
{
	_pCon = pCon;
}

//-------------------------------------------------------------------------------------------------------------------
HMzzCtrl::~HMzzCtrl()
{
}

//-------------------------------------------------------------------------------------------------------------------
void HMzzCtrl::insert(HMzz &hmzz)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "INSERT INTO t_mzz (sbh,dbh,zzmoney,zzdate,remark) VALUES('"
			<< hmzz.sbh <<"','"
			<< hmzz.dbh <<"',"
			<< hmzz.zzmoney <<",'"
			<< hmzz.zzdate<<"','"
			<< hmzz.remark <<"')";
		query.execute();
	}mycatch();
}

//-------------------------------------------------------------------------------------------------------------------
void HMzzCtrl::Delete(int id)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mzz WHERE id = "<< id;
		query.execute();
	}mycatch();
}
	
//--------------------------------------------------------------------------------------------------------------------
HMzzVec HMzzCtrl::getAllMzz()
{
	HMzzVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_mzz";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HMzz mzz;
		for ( it = res.begin(); it != res.end(); it++)
		{	row = *it;
			mzz.id = row.lookup_by_name("id");
			mzz.sbh = row.lookup_by_name("sbh");
			mzz.dbh = row.lookup_by_name("dbh");
			mzz.zzmoney = row.lookup_by_name("zzmoney");
			mzz.remark = row.lookup_by_name("remark");
			mzz.zzdate= row.lookup_by_name("zzdate");
			vec.push_back(mzz);
		}
	}mycatch();
	return vec;
}

//---------------------------------------------------------------------------------------------------------------------
void HMzzCtrl::DeleteAll()
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mzz";
		query.execute();
	}mycatch();
}

//----------------------------------------------------------------------------------------------------------------------
//根据 sbh 返回所有冲值记录
HMzzVec HMzzCtrl::getMzz(string sbh)
{
	HMzzVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_mzz WHERE sbh='"<< sbh <<"'";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HMzz mzz;
		for ( it = res.begin(); it != res.end(); it++)
		{	row = *it;
			mzz.id = row.lookup_by_name("id");
			mzz.sbh = row.lookup_by_name("sbh");
			mzz.dbh = row.lookup_by_name("dbh");
			mzz.zzmoney = row.lookup_by_name("zzmoney");
			mzz.remark = row.lookup_by_name("remark");
			mzz.zzdate =row.lookup_by_name("zzdate");
			vec.push_back(mzz);
		}
	}mycatch();
	return vec;
}

//-----------------------------------------------------------------------------------------------------------------------
//清除本账号的转账记录
void HMzzCtrl::DeleteBySbh(string sbh)
{
	try{
		mysqlpp::Query query = _pCon->query();
		query << "DELETE FROM t_mzz WHERE sbh='"<<sbh<<"'";
		query.execute();
	}mycatch();
}

//----------------------------------------------------------------------------------------------------
HMzzVec HMzzCtrl::getMzz(string d1,string d2,string bh)
{
	HMzzVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		if ( bh.empty() ){
			query << "SELECT * FROM t_mzz WHERE date_format(zzdate,'%Y-%m-%d')>='"<< d1 <<"' AND date_format(zzdate,'%Y-%m-%d') <='"<<d2<<"'";
		}else{
			query << "SELECT * FROM t_mzz WHERE date_format(zzdate,'%Y-%m-%d')>='"<< d1 <<"' AND date_format(zzdate,'%Y-%m-%d') <='"<<d2<<"' AND sbh='"<<bh<<"'";
		}
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HMzz mzz;
		for ( it = res.begin(); it != res.end(); it++)
		{	row = *it;
			mzz.id = row.lookup_by_name("id");
			mzz.sbh = row.lookup_by_name("sbh");
			mzz.dbh = row.lookup_by_name("dbh");
			mzz.zzmoney = row.lookup_by_name("zzmoney");
			mzz.remark = row.lookup_by_name("remark");
			mzz.zzdate =row.lookup_by_name("zzdate");
			vec.push_back(mzz);
		}
	}mycatch();
	return vec;
}