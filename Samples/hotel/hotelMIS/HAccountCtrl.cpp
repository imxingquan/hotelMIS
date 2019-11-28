//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HAccountCtrl.cpp
//
// Description:    
//				HAccountCtrl ���ʵ��
//		
//
// Version: 1.0
//
// Hostory:		
//			05-6-2005	��Ȫ	Created	
//			
//---------------------------------------------------------

#include "stdAfx.h"
#include "HAccountCtrl.h"
#include "HRepastCtrl.h"
#include "HRepDetailsCtrl.h"
#include "HMemberCtrl.h"

using namespace hotelMIS;

HAccountCtrl::HAccountCtrl(mysqlpp::Connection * pCon)
{
    _pCon  = pCon;
}



HAccountCtrl::~HAccountCtrl()
{
  
}

//
// *** ���������ݲ��� ***
//
// ����
void HAccountCtrl::insert(HAccount& account)
{
   // TODO : 
   try{
         mysqlpp::Query query  = _pCon->query();
         query << "INSERT INTO t_account (account_id,room_id,table_id,cust_date,cust_time,subscription,acc_status,ad_name)VALUES('"
                     <<  account.account_id << "',"
                     << account.room_id <<","
                     << account.table_id <<",'"
                     << account.cust_date<<"','"
                     << account.cust_time<<"',"
					 << account.subscription<<","
                     << account.acc_status<<",'"
                     << account.ad_name <<"')";
         query.execute();
   }mycatch();
}


//
// �޸�
//
void HAccountCtrl::update(HAccount& account)
{
   
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_account SET room_id ="
                     << account.room_id      <<",table_id ="
                     << account.table_id     <<",cust_date = '" 
                     << account.cust_date    <<"',cust_time='"
                     << account.cust_time    <<"',subscription="
					 << account.subscription << ",pay_date='"
					 << account.pay_date     << "',pay_time='"
					 << account.pay_time     <<"',yscost="
                     << account.yscost       <<",erase_zero="
                     << account.erase_zero   <<",zhekou="
                     << account.zhekou       <<",reckoning="
                     << account.reckoning    <<",sscost="
                     << account.sscost       <<",acc_status="
                     << account.acc_status   <<",ad_name='"
                     << account.ad_name      <<"',daijin="
					 << account.daijin		 <<",sj="
					 << account.sj			 << ",zy="
					 << account.zy			 <<",pay_status="
					 << account.paystatus   <<",bz='"
					 << account.bz			<<"',arid="
					 << account.arid		<<",zfprice="
					 << account.zfprice		<<",sswr="
					 << account.sswr		<<" WHERE account_id = '"
                     << account.account_id   << "'";
        query.execute();              
   }mycatch();
}

//
// ɾ������
//
void HAccountCtrl::Delete(string accountId)
{
   try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_account WHERE account_id ='"
                     << accountId <<"'";
         query.execute();
   }mycatch();
}

//
// ɾ������
//
void HAccountCtrl::DeleteAll()
{
try{
         mysqlpp::Query query = _pCon->query();
         query << "DELETE FROM t_account ";
         query.execute();
   }mycatch();
}

// *** ҵ���߼� ****
//
//	���ص������ѵ��˵�����
//
int HAccountCtrl::getNowCnt(void)
{
   int cnt = 0;
   try{
         mysqlpp::Query query = _pCon->query();
         query << "SELECT count(*)as acnt FROM t_account WHERE cust_date = NOW()";
         mysqlpp::Result res = query.store();
         if ( !res.empty()){
            mysqlpp::Row row;
            mysqlpp::Result::iterator it = res.begin();
            row = *it;
            cnt = row.lookup_by_name("acnt");
         }
         
   }mycatch();
   return cnt;
}

//
// ȡ���˵�
//
void HAccountCtrl::cancel(string accountId)
{
   
	try{
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_account SET acc_status = -1 WHERE account_id = '"
			<< accountId <<"'";
		query.execute();

		//��������ϸ���ϵ��뵽 t_accountDetails��
		HRepDetailsCtrl repDetailsCtrl(_pCon);
		HRepastCtrl repastCtrl(_pCon);
		repDetailsCtrl.transferToAccDetails(accountId);
		//ɾ��
		repastCtrl.Delete(accountId);
		repDetailsCtrl.Delete(accountId);

	}mycatch();
}

//
// �޸Ķ���
//
void HAccountCtrl::updateSubscription(string accountId, float subscription)
{
   try{
         mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_account SET subscription="
                     << subscription <<" WHERE account_id = '"
                     << accountId << "'";
        query.execute();              
   }mycatch();
}

//
// �����˵����޸��������ں�ʱ��
//
void HAccountCtrl::updateRepDateAndTime(string accountId,string date,string time)
{
	try{
		mysqlpp::Query query = _pCon->query();
         query << "UPDATE t_account SET cust_date='"
                     << date <<"', cust_time='"
					 << time <<"' WHERE account_id = '"
                     << accountId << "'";
        query.execute();   
	}mycatch();
}


//-------------------------------------------------------------------------------------------------
void HAccountCtrl::_fill_(HAccount &acc,mysqlpp::Result &res)
{
	if ( !res.empty())
		{
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			acc.account_id = row.lookup_by_name("account_id");
			acc.acc_status = row.lookup_by_name("acc_status");
			acc.ad_name = row.lookup_by_name("ad_name");
			acc.cust_date = row.lookup_by_name("cust_date");
			acc.cust_time = row.lookup_by_name("cust_time");
			acc.erase_zero = row.lookup_by_name("erase_zero");
			acc.pay_date = row.lookup_by_name("pay_date");
			acc.pay_time = row.lookup_by_name("pay_time");
			acc.reckoning = row.lookup_by_name("reckoning");
			acc.room_id = row.lookup_by_name("room_id");
			acc.sscost = row.lookup_by_name("sscost");
			acc.subscription = row.lookup_by_name("subscription");
			acc.table_id = row.lookup_by_name("table_id");
			acc.yscost = row.lookup_by_name("yscost");
			acc.zhekou = row.lookup_by_name("zhekou");
			acc.daijin = row.lookup_by_name("daijin");
			acc.sj = row.lookup_by_name("sj");
			acc.zy = row.lookup_by_name("zy");
			acc.paystatus = row.lookup_by_name("pay_status");
			acc.bz = row.lookup_by_name("bz");
			acc.arid = row.lookup_by_name("arid");
			acc.zfprice = row.lookup_by_name("zfprice");
			acc.sswr = row.lookup_by_name("sswr");
		}
}

//----------------------------------------------------------------------------------------------------
void HAccountCtrl::_fill_vec(HAccountVec &vec,mysqlpp::Result &res)
{
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HAccount acc;
		for ( it = res.begin(); it!= res.end(); it++)
		{
			row = *it;
			acc.account_id = row.lookup_by_name("account_id");
			acc.acc_status = row.lookup_by_name("acc_status");
			acc.ad_name = row.lookup_by_name("ad_name");
			acc.cust_date = row.lookup_by_name("cust_date");
			acc.cust_time = row.lookup_by_name("cust_time");
			acc.erase_zero = row.lookup_by_name("erase_zero");
			acc.pay_date = row.lookup_by_name("pay_date");
			acc.pay_time = row.lookup_by_name("pay_time");
			acc.reckoning = row.lookup_by_name("reckoning");
			acc.room_id = row.lookup_by_name("room_id");
			acc.sscost = row.lookup_by_name("sscost");
			acc.subscription = row.lookup_by_name("subscription");
			acc.table_id = row.lookup_by_name("table_id");
			acc.yscost = row.lookup_by_name("yscost");
			acc.zhekou = row.lookup_by_name("zhekou");
			acc.daijin = row.lookup_by_name("daijin");
			acc.sj = row.lookup_by_name("sj");
			acc.zy = row.lookup_by_name("zy");
			acc.paystatus = row.lookup_by_name("pay_status");
			acc.bz = row.lookup_by_name("bz");
			acc.arid = row.lookup_by_name("arid");
			acc.zfprice = row.lookup_by_name("zfprice");
			acc.sswr = row.lookup_by_name("sswr");
			vec.push_back(acc);
		}
}
//
// �����˵���ȡ���˵�����ϸ����
//
HAccount HAccountCtrl::getAccount(string accountId)
{
	HAccount acc;
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"SELECT * FROM t_account WHERE account_id = '"
				<< accountId <<"'";
		mysqlpp::Result res = query.store();
		_fill_(acc,res);
	}mycatch();
	return acc;
}

//
// �����������˵���ϸ
//
vector<HAccount> HAccountCtrl::getAllAccount()
{
	vector<HAccount> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"SELECT * FROM t_account ";
		mysqlpp::Result res = query.store();
		
		_fill_vec(vec,res);

	}mycatch();
	return vec;
}

//
// �����˵���ȡ�ض���
//
float HAccountCtrl::getSubscription(string accountId)
{
	float subscription = 0.0f;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT subscription FROM t_account WHERE account_id = '"
			<<accountId << "'";
		mysqlpp::Result res = query.store();
		if ( !res.empty())
		{
			mysqlpp::Result::iterator it = res.begin();
			mysqlpp::Row row = *it;
			subscription = row.lookup_by_name("subscription");
		}
	}mycatch();
	return subscription;
}

//
// ���ص�����˵���ϸ
// �ѹ���
vector<HAccount> HAccountCtrl::getByDay(string sDate,string eDate,int jsfs)
{	
	vector<HAccount> vec;
	try{
		mysqlpp::Query query = _pCon->query();

		//jsfs = 0 ���У�=1 �ų����˽��� 2 ���˽��˲���
		if ( jsfs== 1)
		{
			query << "SELECT * FROM t_account WHERE pay_date >='"
				<< sDate << "' AND pay_date <='"
				<< eDate << "' AND acc_status = 1 ";
		}
		else if ( jsfs==2)
		{
			query << "SELECT * FROM t_account WHERE pay_date >='"
				<< sDate << "' AND pay_date <='"
				<< eDate << "' AND acc_status=3";
		}
		else{
			query << "SELECT * FROM t_account WHERE ( pay_date >='"
				<< sDate << "' AND pay_date <='"
				<< eDate << "' AND acc_status = 1) OR ( pay_date >='" 
				<< sDate << "' AND pay_date <='"
				<< eDate << "' AND acc_status=3)";
		}
		
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//
// �����µ��˵���ϸ
//
vector<HAccount> HAccountCtrl::getByMonth(string year,string month)
{
	vector<HAccount> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"SELECT * FROM t_account WHERE year(pay_date) ='"
			<< year << "' AND month(pay_date) ='"<<month<<"' AND acc_status =1";
		mysqlpp::Result res = query.store();
	
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//
// ��������˵���ϸ
//
vector<HAccount> HAccountCtrl::getByYear(string year)
{
	vector<HAccount> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query <<"SELECT * FROM t_account WHERE year(pay_date) ='"<<year<<"' AND acc_status =1";
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//
// ���� sData �� eDate �������� ״̬Ϊ accStatus ���˵���ϸ
//

vector<HAccount> HAccountCtrl::search(string sDate,string eDate,int accStatus,int arid,int cw,int jsfs)
{
	vector<HAccount> vec;
	try{
		mysqlpp::Query query = _pCon->query();
		if ( arid !=0 ) //������λ�ı���
		{
			
			if ( jsfs==5 ){
				query << "SELECT * FROM t_account WHERE cust_date >='"
					<< sDate << "' AND cust_date <='"
					<< eDate << "' AND acc_status = "
					<< accStatus<<" AND arid = "
					<< arid << " AND daijin !=0 ";

				
			}
			else if ( jsfs !=0){
				if ( jsfs== 1){ //�ֽ�
					query << "SELECT * FROM t_account WHERE cust_date >='"
						<< sDate << "' AND cust_date <='"
						<< eDate << "' AND acc_status = "
						<< accStatus<<" AND arid = "
						<< arid << " AND pay_status= "
						<< jsfs << " AND sj != 0";
				}
				else{ //��Ա�������ÿ���֧Ʊ
					query << "SELECT * FROM t_account WHERE cust_date >='"
						<< sDate << "' AND cust_date <='"
						<< eDate << "' AND acc_status = "
						<< accStatus<<" AND arid = "
						<< arid << " AND pay_status= "
						<< jsfs ;
				}
				
			}
			else{
				query << "SELECT * FROM t_account WHERE cust_date >='"
					<< sDate << "' AND cust_date <='"
					<< eDate << "' AND acc_status = "
					<< accStatus<<" AND arid = "
					<< arid;
			}
			
		}
		else if (cw!=0) //�ų�������
		{
			
			if ( jsfs==5){
				query << "SELECT * FROM t_account INNER JOIN t_arrerage_zh ON t_account.arid=t_arrerage_zh.ar_id WHERE cust_date >='"
					<< sDate << "' AND cust_date <='"
					<< eDate << "' AND acc_status = "
					<< accStatus << " AND daijin !=0 AND cw !=1";
			}
			else if ( jsfs !=0 ){
				if( jsfs == 1){ //�ֽ�
					query << "SELECT * FROM t_account INNER JOIN t_arrerage_zh ON t_account.arid=t_arrerage_zh.ar_id WHERE cust_date >='"
						<< sDate << "' AND cust_date <='"
						<< eDate << "' AND acc_status = "
						<< accStatus << " AND pay_status="
						<< jsfs <<" AND sj !=0 AND cw !=1";
				}
				else{	//��Ա�������ÿ���֧Ʊ
					query << "SELECT * FROM t_account INNER JOIN t_arrerage_zh ON t_account.arid=t_arrerage_zh.ar_id WHERE cust_date >='"
						<< sDate << "' AND cust_date <='"
						<< eDate << "' AND acc_status = "
						<< accStatus << " AND pay_status="
						<< jsfs <<" AND cw !=1";
				}
				
			}
			else{
				query << "SELECT * FROM t_account INNER JOIN t_arrerage_zh ON t_account.arid=t_arrerage_zh.ar_id WHERE cust_date >='"
					<< sDate << "' AND cust_date <='"
					<< eDate << "' AND acc_status = "
					<< accStatus << " AND cw !=1";
			}
		}
		else{
			if ( jsfs== 5){
				query << "SELECT * FROM t_account WHERE cust_date >='"
					<< sDate << "' AND cust_date <='"
					<< eDate << "' AND acc_status = "
					<< accStatus << " AND daijin !=0";
			}
			else if ( jsfs !=0 ){
				if ( jsfs == 1 ){ //�ֽ�
					query << "SELECT * FROM t_account WHERE cust_date >='"
						<< sDate << "' AND cust_date <='"
						<< eDate << "' AND acc_status = "
						<< accStatus << " AND pay_status="
						<< jsfs << " AND sj !=0";
				}
				else{	//��Ա�������ÿ�
					query << "SELECT * FROM t_account WHERE cust_date >='"
						<< sDate << "' AND cust_date <='"
						<< eDate << "' AND acc_status = "
						<< accStatus << " AND pay_status="
						<< jsfs;
				}
				
			
			}
			else{
				query << "SELECT * FROM t_account WHERE cust_date >='"
					<< sDate << "' AND cust_date <='"
					<< eDate << "' AND acc_status = "
					<< accStatus;
			}
		}
		mysqlpp::Result res = query.store();
		_fill_vec(vec,res);
	}mycatch();
	return vec;
}

//
//	���ر��˵��ŵ����ѽ��
//
float HAccountCtrl::getPriceByAccountId(string accountId)
{
	
	float price = 0.0f;
	
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT * FROM t_account WHERE account_id = '" << accountId << "'";
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		mysqlpp::Result res = query.store();
		if ( !res.empty())
		{
		
			row = *res.begin();		
			price = row.lookup_by_name("sscost");
			
		}
	}mycatch();
	return price;
}


//
//	���˽���
//
bool HAccountCtrl::gzJZ(string accountId,float* restMoney,int reckoning,string date,string time)
{
	float sscost = getPriceByAccountId(accountId);
	if ( sscost <= *restMoney ){
		//���ˣ�����־		
		try{
			mysqlpp::Query query = _pCon->query();
			query << "UPDATE t_account SET pay_date = '" 
				<< date << "', pay_time= '"
				<< time << "',zy=0,acc_status = 3,pay_status=1,bz=concat(bz,'[�ҽ�]') WHERE account_id ='"
				
				<< accountId << "'";
			query.execute();
		}mycatch();
		(*restMoney) -= sscost;
		if (*restMoney < 0.001) *restMoney = 0;
		return true;
	}
	return false;
}

//��Ա������
void HAccountCtrl::memberJz(string accountId,float czmoney,string mbh)
{
	try{
		//����Ա���д�뱾�˵�
		mysqlpp::Query query = _pCon->query();
		query << "UPDATE t_account SET m_bh='"<<mbh
			 <<"' WHERE account_id ='"<<accountId<<"'";
		query.execute();

		//�ӻ�Ա���ϼ�ȥ��ֵ���
		hotelMIS::HMemberCtrl hMemberCtrl(_pCon);
		hMemberCtrl.xf(mbh,czmoney);

	}mycatch();
}

//------------------------------------------------------------------------------------------------------------------------
// ��ָ��ʱ���� ���㷽ʽͳ��
HTotalAccountVec HAccountCtrl::totalByPayStatus(string start_dtime,string end_dtime)
{
	HTotalAccountVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT pay_status,sum(sscost+subscription) as sum_sscost \
				 ,pay_date,acc_status FROM t_account group by pay_status HAVING pay_date >='"
			<< start_dtime 
			<<"' AND pay_date <='"<< end_dtime 
			<<"' AND acc_status = 1";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HTotalAccount ta;
		
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			ta.pay_status = row.lookup_by_name("pay_status");
			ta.sum_sscost = row.lookup_by_name("sum_sscost");
			vec.push_back(ta);
		}
	}mycatch();
	return vec;
}

//-------------------------------------------------------------------------------------------------------------------------
// ���� ����ͳ��
HTotalAccountVec HAccountCtrl::totalByPayStatus(string year,string month,int bf)
{
HTotalAccountVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT pay_status,sum(sscost+subscription) as sum_sscost \
				 ,pay_date,acc_status FROM t_account group by pay_status HAVING YEAR(pay_date)='"
			<< year
			<<"' AND MONTH(pay_date) ='"<< month 
			<<"' AND acc_status = 1";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HTotalAccount ta;
		
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			ta.pay_status = row.lookup_by_name("pay_status");
			ta.sum_sscost = row.lookup_by_name("sum_sscost");
			vec.push_back(ta);
		}
	}mycatch();
	return vec;
}

//-------------------------------------------------------------------------------------------------------------------------
// ���� ����ͳ��
HTotalAccountVec HAccountCtrl::totalByPayStatus(string year)
{
	HTotalAccountVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		query << "SELECT pay_status,sum(sscost+subscription) as sum_sscost \
				 ,pay_date,acc_status FROM t_account group by pay_status HAVING YEAR(pay_date) ='"
			<< year
			<<"' AND acc_status = 1";
		mysqlpp::Result res = query.store();
		mysqlpp::Result::iterator it ;
		mysqlpp::Row row;
		HTotalAccount ta;
		
		for ( it = res.begin(); it != res.end(); it++)
		{
			row = *it;
			ta.pay_status = row.lookup_by_name("pay_status");
			ta.sum_sscost = row.lookup_by_name("sum_sscost");
			vec.push_back(ta);
		}
	}mycatch();
	return vec;
}

//--------------------------------------------------------------------------------------------------------------------------
// ����������
HAccountVec HAccountCtrl::getAccount(string d1,string d2,string bh)
{
	HAccountVec vec;
	try{
		mysqlpp::Query query = _pCon->query();
		if ( !bh.empty() ){
			query << "SELECT * FROM t_account WHERE date_format(pay_date,'%Y-%m-%d') >='"<<d1
				<< "' AND date_format(pay_date,'%Y-%m-%d') <='"<< d2 <<"' AND m_bh = '"<< bh <<"'";
				mysqlpp::Result res = query.store();
			_fill_vec(vec,res);
		}
	}mycatch();
	return vec;
}