//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		KDBCon.h
//
// Description:    
//				����mysql���ݿ�
//		
//
// Version: 1.0
//
// Hostory:		
//			03-31-2005	��Ȫ	Created	
//			
//---------------------------------------------------------
#if !defined(__HotelMis_KDBCon_h)
#define __HotelMis_KDBCon_h

#include <mysql++.h>

namespace hotelMIS{
	
	// *** global ***
	struct DBSTR{
		std::string db;			//���ݿ�����
		std::string host;		//������
		std::string user;		//���ݵ�¼�û�
		std::string password;	//��¼����
		std::string port;		//�˿ں�
	};
	
	CString ReplaceChar(CString &str);

	class KDBCon
	{
	public:
		// Construct /Destruct
		KDBCon();
		~KDBCon();	

		/**
		*��ʼ�������ַ���
		*������֮ǰ����������һ��
		*
		*/
		void init();
		void init(std::string host, std::string port="3306",
			std::string user="root",std::string password="",std::string db="mysql");
		
		//����mysql������
		mysqlpp::Connection* get_con(void);

		//ȷ������
		bool isConnect();

		//�ر�����
		void close();

	private:
		//mysql ��Ĭ������
		static mysqlpp::Connection * _pCon;	

		//�����ַ����ṹ
		static DBSTR _DBSTR;

	};
}
#endif