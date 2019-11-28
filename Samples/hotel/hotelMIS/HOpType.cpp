#include "stdAfx.h"

#include "HOpType.h"
#include "HAdmin.h"
#include <cassert>
namespace hotelMIS{

	HOpType::HOpType(string opType,mysqlpp::Connection* pConn)
	{
		_opType = opType;
		_pConn = pConn;
	}
	HOpType::HOpType(mysqlpp::Connection* pConn)
	{
		_pConn = pConn;
	}
	void HOpType::setQx(int op, const string& moduleNo)
	{
		try{
		mysqlpp::Query query = _pConn->query();
		query << "UPDATE t_opright SET haveright = "  << op << " WHERE module_no ='"<<moduleNo<<"' AND optype='"
			<< _opType << "'";
		query.execute();
		}mycatch();
	}
	
	int HOpType::getQx(const string& moduleNo)
	{
		int qx=0 ;
		try{
			
			mysqlpp::Query query = _pConn->query();
			query << "SELECT haveright FROM t_opright  WHERE module_no ='"<<moduleNo<<"' AND optype='"
				<< _opType << "'";
			TRACE("sql=%s\n",query.preview().c_str());
			mysqlpp::Result result = query.store();
			assert(result.size() > 0);
				mysqlpp::Row row;
				mysqlpp::Result::iterator it = result.begin();
				if (it != result.end()){
					row = *it;
					qx = row.lookup_by_name("haveright");
				}
			
		}mycatch();
		return qx;
	}
	
	bool HOpType::isExist(const string& optype)
	{
		try{
			mysqlpp::Query query = _pConn->query();
			query << "SELECT optype FROM t_opright WHERE optype='"<<optype<<"'";
			mysqlpp::Result res = query.store();
			if ( !res.empty() )
				return true;
		}mycatch();
		return false;
	}

	void HOpType::addPurview()
	{
		//��ʼ��ֻ�в���������������ܵ�Ȩ��
		try{
			mysqlpp::Query query = _pConn->query();
			query << "INSERT INTO t_opright (optype,module_no,haveright) VALUES"
				<<"('"<< _opType <<"','M0',1),"
				<<"('"<< _opType <<"','M1',0),"
				<<"('"<< _opType <<"','M2',0),"
				<<"('"<< _opType <<"','M3',0),"
				<<"('"<< _opType <<"','M4',0),"
				<<"('"<< _opType <<"','M5',0),"
				<<"('"<< _opType <<"','M6',0),"
				<<"('"<< _opType <<"','M7',1),"
				<<"('"<< _opType <<"','M8',0)";
			query.execute();
		}mycatch();
	}
	
	void HOpType::delPurview()
	{
		try{
			mysqlpp::Query query = _pConn->query();
			query << "DELETE FROM t_opright WHERE opType ='"<< _opType<<"'";
			query.execute();
		}mycatch();
	}
	
	vector<string> HOpType::getAllPurview()
	{
		vector<string> vec;
		try{
			mysqlpp::Query query = _pConn->query();
			query << "SELECT distinct optype FROM t_opright ";
			mysqlpp::Result res = query.store();
			mysqlpp::Result::iterator it;
			mysqlpp::Row row;
			string optype;
			for ( it = res.begin(); it!= res.end(); it++)
			{
				row = *it;
				optype = row.lookup_by_name("optype");
				vec.push_back(optype);
			}
		}mycatch();
		return vec;
	}

	void HOpType::setM0(int op)
	{
		//��������
		setQx(op,"M0");

	}
	int HOpType::getM0()
	{
		return getQx("M0");
	}

	void HOpType::setM1(int op)
	{
		//������
		setQx(op,"M1");

	}

	int HOpType::getM1()
	{
		return getQx("M1");
	}

	void HOpType::setM2(int op)
	{
		//�˵���ѯ
		return setQx(op,"M2");
	}

	int HOpType::getM2()
	{
		return getQx("M2");
	}

	void HOpType::setM3(int op)
	{
		//��Ա����
		setQx(op,"M3");

	}

	int HOpType::getM3()
	{
		return getQx("M3");
	}

	void HOpType::setM4(int op)
	{
		//���׹���
		setQx(op,"M4");

	}

	int HOpType::getM4()
	{
		return getQx("M4");
	}

	void HOpType::setM5(int op)
	{
		//��������
		setQx(op,"M5");
	}

	int HOpType::getM5()
	{
		return getQx("M5");
	}

	void HOpType::setM6(int op)
	{
		//ϵͳ����
		setQx(op,"M6");
	}

	int HOpType::getM6()
	{
		return getQx("M6");
	}

	void HOpType::setM7(int op)
	{
		//��������
		setQx(op,"M7");
	}

	int HOpType::getM7()
	{
		return getQx("M7");
	}
	
	//��Ա����
	void HOpType::setM8(int op )
	{
		setQx(op,"M8");
	}

	int HOpType::getM8()
	{
		return getQx("M8");
	}
}