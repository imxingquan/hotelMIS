#include "stdafx.h"
#include "HAdmin.h"
namespace hotelMIS{

	HAdmin::HAdmin()
		:_id(-1),
		_login_id(""),
		_password(""),
		_desc(""),
		_name(""),
		_opType("")
	{
	}

	void HAdmin::setId(int id)
	{
		_id = id;
	}
	void HAdmin::setLoginId(string loginId)
	{
		_login_id = loginId;
	}

	void HAdmin::setPassword(string password)
	{
		_password = password;
	}


	void HAdmin::setDesc(string desc)
	{
		_desc = desc;
	}

	void HAdmin::setName(string name)
	{
		_name = name;
	}

	void HAdmin::setOpType(string opType)
	{
		_opType = opType;
	}

	int HAdmin::getId()
	{
		return _id;
	}

	string HAdmin::getLoginId()
	{
		return _login_id;
	}

	string HAdmin::getPassword()
	{
		return _password;
	}

	
	string HAdmin::getName()
	{
		return _name;
	}
	
	string HAdmin::getOpType()
	{
		return _opType;
	}

	string HAdmin::getDesc()
	{
		return _desc;
	}
	

}