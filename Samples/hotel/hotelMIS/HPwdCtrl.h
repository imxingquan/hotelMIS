//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HPwdCtrl.h
//
// Description:    
//			   �� HMember ��Ӧ t_member ��Ļ�������
//
// Version: 1.4
//
// Hostory:		
//			06-04-2006	��Ȫ	Created	
//			
//---------------------------------------------------------

#pragma once

#include "config.h"
#include "HPwd.h"

#include <vector>
using namespace std;

namespace hotelMIS{
	
	class HPwdCtrl{

	public:
		HPwdCtrl(mysqlpp::Connection *pCon);
		~HPwdCtrl();

	public:
		void setAwardPwd(string pwd);
		string getAwardPwd();

	private:
		mysqlpp::Connection * _pCon;	 //���ݿ�����

	};//end class HPwdCtrl

}; //end namepace hotelMIS